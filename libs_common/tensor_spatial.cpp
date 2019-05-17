#include "tensor_spatial.h"
#include <json_config.h>
#include <iostream>
#include <math.h>

TensorSpatial::TensorSpatial(std::string config_file_name, MotionTensor &motion_tensor)
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

    use_gaussian_kernel   = json.result["use gaussian kernel"].asBool();

    discretization_x      = json.result["discretization x"].asInt();
    discretization_y      = json.result["discretization y"].asInt();
    discretization_z      = json.result["discretization z"].asInt();

    float _input_data_corruption             = json.result["input data corruption"].asFloat();
    float _input_data_corruption_noise_level = json.result["input data corruption noise level"].asFloat();

    input_data_corruption             = 0.0;
    input_data_corruption_noise_level = 0.0;

    if ((_input_data_corruption >= 0.0)&&(_input_data_corruption <= 1.0))
        input_data_corruption = _input_data_corruption;

    if ((_input_data_corruption_noise_level >= 0.0)&&(_input_data_corruption_noise_level <= 1.0))
        input_data_corruption_noise_level = _input_data_corruption_noise_level;



    float _output_data_corruption             = json.result["output data corruption"].asFloat();
    float _output_data_corruption_noise_level = json.result["output data corruption noise level"].asFloat();

    output_data_corruption             = 0.0;
    output_data_corruption_noise_level = 0.0;

    if ((_output_data_corruption >= 0.0)&&(_output_data_corruption <= 1.0))
        output_data_corruption = _output_data_corruption;

    if ((_output_data_corruption_noise_level >= 0.0)&&(_output_data_corruption_noise_level <= 1.0))
        output_data_corruption_noise_level = _output_data_corruption_noise_level;


    unsigned int width_, height_, depth_;

    width_  = discretization_x;
    height_ = discretization_y;
    depth_  = discretization_z*time_window_size;

    if (use_depth)
        depth_*= 2;

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



    create(6000, 20);
    //print();
}


TensorSpatial::TensorSpatial(TensorSpatial& other)
                :TensorInterface(other)
{
    copy_spatial(other);
}

TensorSpatial::TensorSpatial(const TensorSpatial& other)
                :TensorInterface(other)
{
    copy_spatial(other);
}

TensorSpatial::~TensorSpatial()
{

}

TensorSpatial& TensorSpatial::operator= (TensorSpatial& other)
{
    copy(other);
    copy_spatial(other);

    return *this;
}

TensorSpatial& TensorSpatial::operator= (const TensorSpatial& other)
{
    copy(other);
    copy_spatial(other);

    return *this;
}


void TensorSpatial::copy_spatial(TensorSpatial& other)
{
    input_columns   = other.input_columns;
    output_columns  = other.output_columns;

    time_window_size      = other.time_window_size;
    time_step_size        = other.time_step_size;
    prediction_step_size  = other.prediction_step_size;
    use_depth             = other.use_depth;

    use_gaussian_kernel   = other.use_gaussian_kernel;

    discretization_x      = other.discretization_x;
    discretization_y      = other.discretization_y;
    discretization_z      = other.discretization_z;

    input_data_corruption               = other.input_data_corruption;
    input_data_corruption_noise_level   = other.input_data_corruption_noise_level;
    output_data_corruption              = other.output_data_corruption;
    output_data_corruption_noise_level  = other.output_data_corruption_noise_level;
}

void TensorSpatial::copy_spatial(const TensorSpatial& other)
{
    input_columns   = other.input_columns;
    output_columns  = other.output_columns;

    time_window_size      = other.time_window_size;
    time_step_size        = other.time_step_size;
    prediction_step_size  = other.prediction_step_size;
    use_depth             = other.use_depth;

    use_gaussian_kernel   = other.use_gaussian_kernel;

    discretization_x      = other.discretization_x;
    discretization_y      = other.discretization_y;
    discretization_z      = other.discretization_z;

    input_data_corruption               = other.input_data_corruption;
    input_data_corruption_noise_level   = other.input_data_corruption_noise_level;
    output_data_corruption              = other.output_data_corruption;
    output_data_corruption_noise_level  = other.output_data_corruption_noise_level;
}


int TensorSpatial::create(unsigned int y_offset, unsigned int z_offset)
{
    return create(y_offset, z_offset, *m_motion_tensor);
}



int TensorSpatial::create(unsigned int y_offset, unsigned int z_offset, MotionTensor &motion_tensor)
{
    clear();

    if ((input_height()*time_step_size + y_offset) >= motion_tensor.height())
        return -1;

    if ((prediction_step_size + y_offset) >= motion_tensor.height())
        return -2;


    unsigned int kernel_size = 5;

    for (unsigned int time_idx = 0; time_idx < time_window_size; time_idx++)
    {
        float x = motion_tensor.get(input_columns[0], time_idx*time_step_size + y_offset, z_offset);
        float y = motion_tensor.get(input_columns[1], time_idx*time_step_size + y_offset, z_offset);
        float z = motion_tensor.get(input_columns[2], time_idx*time_step_size + y_offset, z_offset);

        if (rnd(0.0, 1.0) < input_data_corruption)
        {
            x = (1.0 - input_data_corruption_noise_level)*x + input_data_corruption_noise_level*rnd(-1.0, 1.0);
            y = (1.0 - input_data_corruption_noise_level)*y + input_data_corruption_noise_level*rnd(-1.0, 1.0);
            z = (1.0 - input_data_corruption_noise_level)*z + input_data_corruption_noise_level*rnd(-1.0, 1.0);
        }

        x = clamp(x, 0.0, 1.0);
        y = clamp(y, 0.0, 1.0);
        z = clamp(z, 0.0, 1.0);


        float x_raw = x*discretization_x;
        float y_raw = y*discretization_y;
        float z_raw = z*discretization_z;

        unsigned int x_rounded = round(x_raw);
        unsigned int y_rounded = round(y_raw);
        unsigned int z_rounded = round(z_raw);

        if (x_rounded >= discretization_x)
            x_rounded = discretization_x - 1;

        if (y_rounded >= discretization_y)
            y_rounded = discretization_y - 1;

        if (z_rounded >= discretization_z)
            z_rounded = discretization_z - 1;

        if (use_gaussian_kernel)
        {
            auto kernel = make_kernel(x_raw, y_raw, x_rounded, y_rounded, kernel_size);

            for (unsigned int j = 0; j < kernel_size; j++)
                for (unsigned int i = 0; i < kernel_size; i++)
                {
                    int x_ = (int)x_rounded + (int)i - (int)kernel_size/2;
                    int y_ = (int)y_rounded + (int)j - (int)kernel_size/2;

                    if ((x_ > 0)&&(y_>0))
                    if ((x_ < (int)discretization_x)&&(y_ < (int)discretization_y))
                        set_input(x_, y_, z_rounded + time_idx*discretization_z, kernel[j][i]);
                }
        }
        else
        {
            set_input(x_rounded, y_rounded, z_rounded + time_idx*discretization_z, 1.0);
        }
    }

    bool output_corruption = false;
    if (rnd(0.0, 1.0) < output_data_corruption)
        output_corruption = true;

    for (unsigned int x = 0; x < output_columns.size(); x++)
    {
        float value = motion_tensor.get(output_columns[x], prediction_step_size + y_offset, z_offset);
        if (output_corruption)
        {
            value = (1.0 - output_data_corruption_noise_level)*value + output_data_corruption_noise_level*rnd(-1.0, 1.0);
        }

        set_output(0, 0, x, value);
    } 

    return 0;
}


std::vector<std::vector<float>> TensorSpatial::make_kernel(float x, float y, float x_rounded, float y_rounded, unsigned int size)
{
    std::vector<std::vector<float>> result;
    result.resize(size);
    for (unsigned int j = 0; j < size; j++)
    {
        result[j].resize(size);
        for (unsigned int i = 0; i < size; i++)
            result[j][i] = 1.0;
    }


    float xc = x + (int)(((int)size-1)/2);
    float yc = y + (int)(((int)size-1)/2);


    for (unsigned int j = 0; j < size; j++)
        for (unsigned int i = 0; i < size; i++)
        {
            float x_ = 1.0*i + x_rounded;
            float y_ = 1.0*j + y_rounded;

            float d = 0.0;
            d+= pow(x_ - xc, 2.0);
            d+= pow(y_ - yc, 2.0);

            result[j][i] = exp(-d);
        }


    return result;
}
