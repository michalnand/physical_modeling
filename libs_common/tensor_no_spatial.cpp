#include "tensor_no_spatial.h"
#include <json_config.h>
#include <iostream>

TensorNoSpatial::TensorNoSpatial(std::string config_file_name, MotionTensor &motion_tensor)
                :TensorInterface(motion_tensor)
{
  JsonConfig json(config_file_name);

  for (unsigned int i = 0; i < json.result["input columns"].size(); i++)
    input_columns.push_back(json.result["input columns"][i].asInt());

  for (unsigned int i = 0; i < json.result["output columns"].size(); i++)
    output_columns.push_back(json.result["output columns"][i].asInt());

  time_window_size      = json.result["time window size"].asInt();
  time_step_size        = json.result["time step size"].asInt();
  prediction_step_size  = json.result["prediction step size"].asInt();
  use_depth             = json.result["use depth"].asBool();

  padding               = json.result["padding"].asInt();

  unsigned int width_, height_, depth_;

  width_  = input_columns.size() + 2*padding;
  height_ = time_window_size     + 2*padding;
  depth_  = 1;


  if (use_depth)
    depth_+= m_motion_tensor->depth();


  set_input_dimensions(width_, height_, depth_);
  set_output_dimensions(1, 1, output_columns.size());

  /*
  unsigned int items = 0;
  for (unsigned int z = 0; z < m_motion_tensor->depth(); z++)
  for (unsigned int y = 0; y < m_motion_tensor->height(); y++)
  {
    int res = create(y, z);
    if (res == 0)
      items++;
  }

  std::cout << "total items " << items << "\n";

  */


  create(1, 1);
  print();
}


TensorNoSpatial::TensorNoSpatial(TensorNoSpatial& other)
                :TensorInterface(other)
{
  copy_no_spatial(other);
}

TensorNoSpatial::TensorNoSpatial(const TensorNoSpatial& other)
                :TensorInterface(other)
{
  copy_no_spatial(other);
}

TensorNoSpatial::~TensorNoSpatial()
{

}

TensorNoSpatial& TensorNoSpatial::operator= (TensorNoSpatial& other)
{
  copy(other);
  copy_no_spatial(other);
  return *this;
}

TensorNoSpatial& TensorNoSpatial::operator= (const TensorNoSpatial& other)
{
  copy(other);
  copy_no_spatial(other);
  return *this;
}


void TensorNoSpatial::copy_no_spatial(TensorNoSpatial& other)
{
  input_columns   = other.input_columns;
  output_columns  = other.output_columns;

  time_window_size      = other.time_window_size;
  time_step_size        = other.time_step_size;
  prediction_step_size  = other.prediction_step_size;
  use_depth             = other.use_depth;
  padding               = other.padding;
}

void TensorNoSpatial::copy_no_spatial(const TensorNoSpatial& other)
{
  input_columns   = other.input_columns;
  output_columns  = other.output_columns;

  time_window_size      = other.time_window_size;
  time_step_size        = other.time_step_size;
  prediction_step_size  = other.prediction_step_size;
  use_depth             = other.use_depth;
  padding               = other.padding;
}


int TensorNoSpatial::create(unsigned int y_offset, unsigned int z_offset)
{
  return create(y_offset, z_offset, *m_motion_tensor);
}

int TensorNoSpatial::create(unsigned int y_offset, unsigned int z_offset, MotionTensor &motion_tensor)
{
  clear();

  if ((input_height()*time_step_size + y_offset) >= motion_tensor.height())
    return -1;

  if ((prediction_step_size + y_offset) >= motion_tensor.height())
    return -2;

  for (unsigned int y = 0; y < (input_height() - 2*padding); y++)
  for (unsigned int x = 0; x < (input_width() - 2*padding); x++)
  {
    float value = motion_tensor.get(input_columns[x], y*time_step_size + y_offset, z_offset);
    set_input(x + padding, y + padding, 0, value);
  }

  if (use_depth)
  {
    for (unsigned int z = 0; z < (input_depth()-1); z++)
    for (unsigned int y = 0; y < (input_height() - 2*padding); y++)
    for (unsigned int x = 0; x < (input_width() - 2*padding); x++)
    {
      float value =  motion_tensor.get(input_columns[x], y*time_step_size + y_offset, z);
      set_input(x + padding, y + padding, z + 1, value);
    }
  }

  for (unsigned int x = 0; x < output_columns.size(); x++)
  {
    float value = motion_tensor.get(output_columns[x], prediction_step_size + y_offset, z_offset);
    set_output(0, 0, x, value);
  }

  return 0;
}
