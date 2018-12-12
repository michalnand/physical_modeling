#include "tensor_interface.h"
#include <iostream>


TensorInterface::TensorInterface()
{
  m_motion_tensor = nullptr;
  set_input_dimensions(0, 0, 0);
  set_output_dimensions(0, 0, 0);
}

TensorInterface::TensorInterface(MotionTensor &motion_tensor)
{
  m_motion_tensor = &motion_tensor;
  set_input_dimensions(0, 0, 0);
  set_output_dimensions(0, 0, 0);
}

TensorInterface::TensorInterface(   MotionTensor &motion_tensor,
                                    unsigned int input_width_, unsigned int input_height_, unsigned int input_depth_,
                                    unsigned int output_width_, unsigned int output_height_, unsigned int output_depth_)
{
  m_motion_tensor = &motion_tensor;
  set_input_dimensions(input_width_, input_height_, input_depth_);
  set_output_dimensions(output_width_, output_height_, output_depth_);
}

TensorInterface::TensorInterface(TensorInterface& other)
{
  copy(other);
}

TensorInterface::TensorInterface(const TensorInterface& other)
{
  copy(other);
}

TensorInterface::~TensorInterface()
{

}

TensorInterface& TensorInterface::operator= (TensorInterface& other)
{
  copy(other);
  return *this;
}

TensorInterface& TensorInterface::operator= (const TensorInterface& other)
{
  copy(other);
  return *this;
}

void TensorInterface::copy(TensorInterface& other)
{
  m_input_width   = other.m_input_width;
  m_input_height  = other.m_input_height;
  m_input_depth   = other.m_input_depth;

  m_output_width   = other.m_output_width;
  m_output_height  = other.m_output_height;
  m_output_depth   = other.m_output_depth;

  m_input_size = other.m_input_size;
  m_output_size = other.m_output_size;

  result    = other.result;
}

void TensorInterface::copy(const TensorInterface& other)
{
  m_input_width   = other.m_input_width;
  m_input_height  = other.m_input_height;
  m_input_depth   = other.m_input_depth;

  m_output_width   = other.m_output_width;
  m_output_height  = other.m_output_height;
  m_output_depth   = other.m_output_depth;

  m_input_size = other.m_input_size;
  m_output_size = other.m_output_size;

  result    = other.result;
}



int TensorInterface::create(unsigned int y_offset, unsigned int z_offset)
{
  return create(y_offset, z_offset, *m_motion_tensor);
}


int TensorInterface::create(unsigned int y_offset, unsigned int z_offset, MotionTensor &motion_tensor)
{
  (void)y_offset;
  (void)z_offset;
  (void)motion_tensor;

  return 0;
}

sDatasetItem TensorInterface::get()
{
  return result;
}

unsigned int TensorInterface::input_width()
{
  return m_input_width;
}

unsigned int TensorInterface::input_height()
{
  return m_input_height;
}

unsigned int TensorInterface::input_depth()
{
  return m_input_depth;
}

unsigned int TensorInterface::output_width()
{
  return m_output_width;
}

unsigned int TensorInterface::output_height()
{
  return m_output_height;
}

unsigned int TensorInterface::output_depth()
{
  return m_output_depth;
}

unsigned int TensorInterface::input_size()
{
  return m_input_size;
}

unsigned int TensorInterface::output_size()
{
  return m_output_size;
}

std::string TensorInterface::asString()
{
  std::string str_res;

  str_res+= "[";
  str_res+= std::to_string(input_width()) + " ";
  str_res+= std::to_string(input_height()) + " ";
  str_res+= std::to_string(input_depth()) + " ";
  str_res+= "]";

  str_res+= "[";
  str_res+= std::to_string(output_width()) + " ";
  str_res+= std::to_string(output_height()) + " ";
  str_res+= std::to_string(output_depth()) + " ";
  str_res+= "]";
  str_res+= "\n";

  unsigned int ptr;

  ptr = 0;
  for (unsigned int z = 0; z < input_depth(); z++)
  {
    for (unsigned int y = 0; y < input_height(); y++)
    {
      for (unsigned int x = 0; x < input_width(); x++)
      {
        str_res+= std::to_string(result.input[ptr]) + " ";
        ptr++;
      }
      str_res+= "\n";
    }
    str_res+= "\n";
  }
  str_res+= "\n";


  ptr = 0;
  for (unsigned int z = 0; z < output_depth(); z++)
  {
    for (unsigned int y = 0; y < output_height(); y++)
    {
      for (unsigned int x = 0; x < output_width(); x++)
      {
        str_res+= std::to_string(result.output[ptr]) + " ";
        ptr++;
      }
      str_res+= "\n";
    }
    str_res+= "\n";
  }
  str_res+= "\n";

  return str_res;
}

void TensorInterface::print()
{
  std::cout << asString() << "\n";
}

unsigned int TensorInterface::get_max_y_offset()
{
  return m_motion_tensor->height();
}

unsigned int TensorInterface::get_max_z_offset()
{
  return m_motion_tensor->depth();
}


void TensorInterface::set_input_dimensions(unsigned int width_, unsigned int height_, unsigned int depth_)
{
    m_input_width   = width_;
    m_input_height  = height_;
    m_input_depth   = depth_;

    m_input_size = input_width()*input_height()*input_depth();

    result.input.resize(input_size());
    for (unsigned int i = 0; i < result.input.size(); i++)
      result.input[i] = 0.0;
}

void TensorInterface::set_output_dimensions(unsigned int width_, unsigned int height_, unsigned int depth_)
{
    m_output_width  = width_;
    m_output_height = height_;
    m_output_depth  = depth_;

    m_output_size = output_width()*output_height()*output_depth();

    result.output.resize(output_size());
    for (unsigned int i = 0; i < result.output.size(); i++)
      result.output[i] = 0.0;
}

void TensorInterface::set_input(unsigned int x, unsigned int y, unsigned z, float value)
{
  unsigned int idx;
  idx = (z*input_height() + y)*input_width() + x;
  result.input[idx] = value;
}

void TensorInterface::set_output(unsigned int x, unsigned int y, unsigned z, float value)
{
  unsigned int idx;
  idx = (z*output_height() + y)*output_width() + x;
  result.output[idx] = value;
}

void TensorInterface::clear()
{
  for (unsigned int i = 0; i < result.input.size(); i++)
    result.input[i] = 0.0;

  for (unsigned int i = 0; i < result.output.size(); i++)
    result.output[i] = 0.0;
}
