#include "nn_trajectory_spatial_input.h"
#include <iostream>
#include <json_config.h>
#include <math.h>

NNTrajectorySpatialInput::NNTrajectorySpatialInput()
{
  load_percentage     = 0.0;
  padding             = 0;
  time_window_size    = 0;
  time_window_stride  = 0;
  prediction_step     = 0;

  discretisation_x = 0;
  discretisation_y = 0;
  discretisation_z = 0;

  width     = 0;
  height    = 0;
  channels  = 0;
}

NNTrajectorySpatialInput::NNTrajectorySpatialInput(std::string config_file_name)
{
  JsonConfig json(config_file_name);

  load_percentage = json.result["inputs parameters"]["load percentage"].asFloat();

  for (unsigned int i = 0; i < json.result["inputs parameters"]["columns to read"].size(); i++)
    input_columns_to_read.push_back(json.result["inputs parameters"]["columns to read"][i].asInt());

  for (unsigned int i = 0; i < json.result["inputs parameters"]["particles to read"].size(); i++)
    input_particles_to_read.push_back(json.result["inputs parameters"]["particles to read"][i].asInt());

  padding             = json.result["inputs parameters"]["padding"].asInt();
  time_window_size    = json.result["inputs parameters"]["time window size"].asInt();
  time_window_stride  = json.result["inputs parameters"]["time window stride"].asInt();

  for (unsigned int i = 0; i < json.result["output parameters"]["columns to read"].size(); i++)
    output_columns_to_read.push_back(json.result["output parameters"]["columns to read"][i].asInt());

  prediction_step = json.result["output parameters"]["prediction step"].asInt();

  discretisation_x = json.result["inputs parameters"]["discretisation x"].asInt();
  discretisation_y = json.result["inputs parameters"]["discretisation y"].asInt();
  discretisation_z = json.result["inputs parameters"]["discretisation z"].asInt();

  width   = discretisation_x  + 2*padding;
  height  = discretisation_y  + 2*padding;
  //channels= discretisation_z*time_window_size*2;
  channels= discretisation_z*time_window_size;
}

NNTrajectorySpatialInput::NNTrajectorySpatialInput(NNTrajectorySpatialInput& other)
{
  copy(other);
}

NNTrajectorySpatialInput::NNTrajectorySpatialInput(const NNTrajectorySpatialInput& other)
{
  copy(other);
}

NNTrajectorySpatialInput::~NNTrajectorySpatialInput()
{

}

NNTrajectorySpatialInput& NNTrajectorySpatialInput::operator= (NNTrajectorySpatialInput& other)
{
  copy(other);
  return *this;
}

NNTrajectorySpatialInput& NNTrajectorySpatialInput::operator= (const NNTrajectorySpatialInput& other)
{
  copy(other);
  return *this;
}

void NNTrajectorySpatialInput::copy(NNTrajectorySpatialInput& other)
{
  load_percentage         = other.load_percentage;
  input_columns_to_read   = other.input_columns_to_read;
  input_particles_to_read = other.input_particles_to_read;

  padding             = other.padding;
  time_window_size    = other.time_window_size;
  time_window_stride  = other.time_window_stride;

  output_columns_to_read  = other.output_columns_to_read;
  prediction_step         = other.prediction_step;

  discretisation_x    = other.discretisation_x;
  discretisation_y    = other.discretisation_y;
  discretisation_z    = other.discretisation_z;

  width     = other.width;
  height    = other.height;
  channels  = other.channels;
}

void NNTrajectorySpatialInput::copy(const NNTrajectorySpatialInput& other)
{
  load_percentage           = other.load_percentage;
  input_columns_to_read     = other.input_columns_to_read;
  input_particles_to_read   = other.input_particles_to_read;

  padding             = other.padding;
  time_window_size    = other.time_window_size;
  time_window_stride  = other.time_window_stride;

  output_columns_to_read  = other.output_columns_to_read;
  prediction_step         = other.prediction_step;

  discretisation_x    = other.discretisation_x;
  discretisation_y    = other.discretisation_y;
  discretisation_z    = other.discretisation_z;

  width     = other.width;
  height    = other.height;
  channels  = other.channels;
}

sDatasetItem NNTrajectorySpatialInput::create(DatsLoad &raw_data, unsigned int line)
{
  sDatasetItem result;

    for (unsigned int particle = 0; particle < input_particles_to_read.size(); particle++)
      if ((rand()%100) < load_percentage)
       if (line < (raw_data.get_lines_count() - (time_window_size+1)*time_window_stride) )
        if (line < raw_data.get_lines_count() - (prediction_step + 1))
        {
          unsigned int top_particle_idx = input_particles_to_read[particle];

          result.input  = make_input(top_particle_idx, line, raw_data);
          result.output = make_output(top_particle_idx, line, raw_data);
        }

  return result;
}



std::vector<float> NNTrajectorySpatialInput::make_input(  unsigned int top_particle_idx,
                                                          unsigned int line,
                                                          DatsLoad &raw_data)
{
    unsigned int result_size = width*height*channels;

    std::vector<float> result(result_size);

    for (unsigned int i = 0; i < result.size(); i++)
      result[i] = 0.0;

    for (unsigned int time_idx = 0; time_idx < time_window_size; time_idx++)
    {
      float x = raw_data.get(top_particle_idx, input_columns_to_read[0], time_idx*time_window_stride + line);
      float y = raw_data.get(top_particle_idx, input_columns_to_read[1], time_idx*time_window_stride + line);
      float z = raw_data.get(top_particle_idx, input_columns_to_read[2], time_idx*time_window_stride + line);

      unsigned int x_ = saturate(x*discretisation_x, 0, discretisation_x-1);
      unsigned int y_ = saturate(y*discretisation_y, 0, discretisation_y-1);
      unsigned int z_ = saturate(z*discretisation_z, 0, discretisation_z-1);

      unsigned int kernel_size = 5;
      auto kernel = make_kernel(x*discretisation_x, y*discretisation_y, kernel_size);

      for (unsigned int ky = 0; ky < kernel_size; ky++)
      for (unsigned int kx = 0; kx < kernel_size; kx++)
      {
        unsigned int idx = to_idx(x_ + kx, y_ + ky, z_, time_idx, 0);
        result[idx]+= kernel[ky][kx];
      }
    }

/*
    for (unsigned int particle = 0; particle < input_particles_to_read.size(); particle++)
    for (unsigned int time_idx = 0; time_idx < time_window_size; time_idx++)
    {
      float x = raw_data.get(particle, input_columns_to_read[0], time_idx*time_window_stride + line);
      float y = raw_data.get(particle, input_columns_to_read[1], time_idx*time_window_stride + line);
      float z = raw_data.get(particle, input_columns_to_read[2], time_idx*time_window_stride + line);

      unsigned int x_ = saturate(x*discretisation_x, 0, discretisation_x-1);
      unsigned int y_ = saturate(y*discretisation_y, 0, discretisation_y-1);
      unsigned int z_ = saturate(z*discretisation_z, 0, discretisation_z-1);

      result[to_idx(x_, y_, z_, time_idx, 1)] = 1.0;
    }
*/
  return result;
}


std::vector<float> NNTrajectorySpatialInput::make_output(  unsigned int top_particle_idx,
                                                    unsigned int line,
                                                    DatsLoad &raw_data)
{
  unsigned int otput_size = output_columns_to_read.size();
  std::vector<float> result(otput_size);

  for (unsigned int column = 0; column < otput_size; column++)
  {
    float value = raw_data.get(
                                top_particle_idx,
                                output_columns_to_read[column],
                                prediction_step + line
                              );

    result[column] = value;
  }

  return result;
}



int NNTrajectorySpatialInput::saturate(int x, int min, int max)
{
  if (x >= max)
    x = max;

  if (x <= min)
    x = min;

  return x;
}

unsigned int NNTrajectorySpatialInput::to_idx(unsigned int x, unsigned int y, unsigned int z, unsigned int t, unsigned int w)
{
  unsigned int result;

  if (x >= discretisation_x)
    x = discretisation_x-1;

  if (y >= discretisation_y)
    y = discretisation_y-1;

  if (z >= discretisation_z)
    z = discretisation_z-1;

  result = (((w*time_window_size + t)*discretisation_z + z)*discretisation_y + y + padding)*discretisation_x + x + padding;
  return result;
}


std::vector<std::vector<float>> NNTrajectorySpatialInput::make_kernel(float x, float y, unsigned int kernel_size)
{
  std::vector<std::vector<float>> result(kernel_size, std::vector<float>(kernel_size));

  for (unsigned int j = 0; j < kernel_size; j++)
    for (unsigned int i = 0; i < kernel_size; i++)
      result[j][i] = 0.0;

  for (unsigned int j = 0; j < kernel_size; j++)
  {
    for (unsigned int i = 0; i < kernel_size; i++)
    {
      float x_discretized = x + (i - kernel_size/2.0);
      float y_discretized = y + (j - kernel_size/2.0);


      float d = 0.0;
      d+= pow(x - x_discretized, 2);
      d+= pow(y - y_discretized, 2);

      result[j][i] = exp(-d);
    }
  }
    float sum = 0.0;
    for (unsigned int j = 0; j < kernel_size; j++)
      for (unsigned int i = 0; i < kernel_size; i++)
        sum+= result[j][i];

    if (sum > 0.0)
    {
      for (unsigned int j = 0; j < kernel_size; j++)
        for (unsigned int i = 0; i < kernel_size; i++)
          result[j][i]/= sum;
    }


  return result;
}
