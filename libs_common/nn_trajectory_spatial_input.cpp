#include "nn_trajectory_spatial_input.h"
#include <iostream>
#include <json_config.h>
#include <math.h>

NNTrajectorySpatialInput::NNTrajectorySpatialInput()
{
  use_other_particles = false;
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

  use_other_particles = json.result["use other particles"].asBool();

  load_percentage = json.result["input parameters"]["load percentage"].asFloat();

  for (unsigned int i = 0; i < json.result["input parameters"]["columns to read"].size(); i++)
    input_columns_to_read.push_back(json.result["input parameters"]["columns to read"][i].asInt());

  for (unsigned int i = 0; i < json.result["input parameters"]["particles to read"].size(); i++)
    input_particles_to_read.push_back(json.result["input parameters"]["particles to read"][i].asInt());

  padding             = json.result["input parameters"]["padding"].asInt();
  time_window_size    = json.result["input parameters"]["time window size"].asInt();
  time_window_stride  = json.result["input parameters"]["time window stride"].asInt();

  for (unsigned int i = 0; i < json.result["output parameters"]["columns to read"].size(); i++)
    output_columns_to_read.push_back(json.result["output parameters"]["columns to read"][i].asInt());

  prediction_step = json.result["output parameters"]["prediction step"].asInt();

  discretisation_x = json.result["input parameters"]["discretisation x"].asInt();
  discretisation_y = json.result["input parameters"]["discretisation y"].asInt();
  discretisation_z = json.result["input parameters"]["discretisation z"].asInt();

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
  use_other_particles     = other.use_other_particles;
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
  use_other_particles       = other.use_other_particles;
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

sDatasetItem NNTrajectorySpatialInput::create(DatsLoad &raw_data, unsigned int line, unsigned int particle)
{
  sDatasetItem result;

  float p = 100.0*(rand()%10000)/10000.0;
      if (p < load_percentage)
       if (line < (raw_data.get_lines_count() - (time_window_size + 1)*time_window_stride))
        if (line < raw_data.get_lines_count() - (prediction_step + 1))
        {
          unsigned int top_particle_idx = input_particles_to_read[particle];

          result.input  = make_input(top_particle_idx, line, raw_data);
          result.output = make_output(top_particle_idx, line, raw_data);
        }

  return result;
}


sDatasetItem NNTrajectorySpatialInput::create(  Trajectory &trajectory_input,
                                                Trajectory &trajectory_output,
                                                unsigned int line, unsigned int particle)
{
  sDatasetItem result;

  float p = 100.0*(rand()%10000)/10000.0;
      if (p < load_percentage)
       if (line < (trajectory_input.get_height() - (time_window_size + 1)*time_window_stride))
        if (line < trajectory_input.get_height() - (prediction_step + 1))
        {
          unsigned int top_particle_idx = input_particles_to_read[particle];

          result.input  = make_input(top_particle_idx, line, trajectory_input);
          result.output = make_output(top_particle_idx, line, trajectory_output);
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

      float x_discretized = x*discretisation_x;
      float y_discretized = y*discretisation_y;
      float z_discretized = z*discretisation_z;

      unsigned int x_ = saturate(x_discretized, 0, discretisation_x-1);
      unsigned int y_ = saturate(y_discretized, 0, discretisation_y-1);
      unsigned int z_ = saturate(z_discretized, 0, discretisation_z-1);

      unsigned int kernel_size = 5;
      auto kernel = make_kernel(x_discretized, y_discretized, kernel_size);

      for (unsigned int ky = 0; ky < kernel_size; ky++)
      for (unsigned int kx = 0; kx < kernel_size; kx++)
      {
        unsigned int idx = to_idx(x_ + kx, y_ + ky, z_, time_idx, 0);
        result[idx]+= kernel[ky][kx];
      }
    }

    if (use_other_particles)
    {
      for (unsigned int particle = 0; particle < input_particles_to_read.size(); particle++)
      for (unsigned int time_idx = 0; time_idx < time_window_size; time_idx++)
      {
        float x = raw_data.get(top_particle_idx, input_columns_to_read[0], time_idx*time_window_stride + line);
        float y = raw_data.get(top_particle_idx, input_columns_to_read[1], time_idx*time_window_stride + line);
        float z = raw_data.get(top_particle_idx, input_columns_to_read[2], time_idx*time_window_stride + line);

        float x_discretized = x*discretisation_x;
        float y_discretized = y*discretisation_y;
        float z_discretized = z*discretisation_z;

        unsigned int x_ = saturate(x_discretized, 0, discretisation_x-1);
        unsigned int y_ = saturate(y_discretized, 0, discretisation_y-1);
        unsigned int z_ = saturate(z_discretized, 0, discretisation_z-1);

        unsigned int kernel_size = 5;
        auto kernel = make_kernel(x_discretized, y_discretized, kernel_size);

        for (unsigned int ky = 0; ky < kernel_size; ky++)
        for (unsigned int kx = 0; kx < kernel_size; kx++)
        {
          unsigned int idx = to_idx(x_ + kx, y_ + ky, z_, time_idx, 1);
          result[idx]+= kernel[ky][kx];
        }
      }
    }

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



std::vector<float> NNTrajectorySpatialInput::make_input(  unsigned int top_particle_idx,
                                                          unsigned int line,
                                                          Trajectory &trajectory)
{
    unsigned int result_size = width*height*channels;

    std::vector<float> result(result_size);

    for (unsigned int i = 0; i < result.size(); i++)
      result[i] = 0.0;

    for (unsigned int time_idx = 0; time_idx < time_window_size; time_idx++)
    {
      float x = trajectory.get(input_columns_to_read[0], time_idx*time_window_stride + line, top_particle_idx);
      float y = trajectory.get(input_columns_to_read[1], time_idx*time_window_stride + line, top_particle_idx);
      float z = trajectory.get(input_columns_to_read[2], time_idx*time_window_stride + line, top_particle_idx);

      float x_discretized = x*discretisation_x;
      float y_discretized = y*discretisation_y;
      float z_discretized = z*discretisation_z;

      unsigned int x_ = saturate(x_discretized, 0, discretisation_x-1);
      unsigned int y_ = saturate(y_discretized, 0, discretisation_y-1);
      unsigned int z_ = saturate(z_discretized, 0, discretisation_z-1);

      unsigned int kernel_size = 5;
      auto kernel = make_kernel(x_discretized, y_discretized, kernel_size);

      for (unsigned int ky = 0; ky < kernel_size; ky++)
      for (unsigned int kx = 0; kx < kernel_size; kx++)
      {
        unsigned int idx = to_idx(x_ + kx, y_ + ky, z_, time_idx, 0);
        result[idx]+= kernel[ky][kx];
      }
    }

    if (use_other_particles)
    {
      for (unsigned int particle = 0; particle < input_particles_to_read.size(); particle++)
      for (unsigned int time_idx = 0; time_idx < time_window_size; time_idx++)
      {
        float x = trajectory.get(input_columns_to_read[0], time_idx*time_window_stride + line, top_particle_idx);
        float y = trajectory.get(input_columns_to_read[1], time_idx*time_window_stride + line, top_particle_idx);
        float z = trajectory.get(input_columns_to_read[2], time_idx*time_window_stride + line, top_particle_idx);

        float x_discretized = x*discretisation_x;
        float y_discretized = y*discretisation_y;
        float z_discretized = z*discretisation_z;

        unsigned int x_ = saturate(x_discretized, 0, discretisation_x-1);
        unsigned int y_ = saturate(y_discretized, 0, discretisation_y-1);
        unsigned int z_ = saturate(z_discretized, 0, discretisation_z-1);

        unsigned int kernel_size = 5;
        auto kernel = make_kernel(x_discretized, y_discretized, kernel_size);

        for (unsigned int ky = 0; ky < kernel_size; ky++)
        for (unsigned int kx = 0; kx < kernel_size; kx++)
        {
          unsigned int idx = to_idx(x_ + kx, y_ + ky, z_, time_idx, 1);
          result[idx]+= kernel[ky][kx];
        }
      }
    }

  return result;
}


std::vector<float> NNTrajectorySpatialInput::make_output( unsigned int top_particle_idx,
                                                          unsigned int line,
                                                          Trajectory &trajectory)
{
  unsigned int otput_size = output_columns_to_read.size();
  std::vector<float> result(otput_size);

  for (unsigned int column = 0; column < otput_size; column++)
  {
    float value = trajectory.get( column,
                                  prediction_step + line,
                                  top_particle_idx);

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
