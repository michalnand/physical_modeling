#include "nn_trajectory_input.h"
#include <iostream>
#include <json_config.h>

NNTrajectoryInput::NNTrajectoryInput()
{
  load_percentage     = 0.0;
  padding             = 0;
  time_window_size    = 0;
  time_window_stride  = 0;
  prediction_step     = 0;

  width     = 0;
  height    = 0;
  channels  = 0;
}

NNTrajectoryInput::NNTrajectoryInput(std::string config_file_name)
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

  width   = input_columns_to_read.size()    + 2*padding;
  height  = time_window_size                + 2*padding;
  channels= input_particles_to_read.size()  + 1;
}

NNTrajectoryInput::NNTrajectoryInput(NNTrajectoryInput& other)
{
  copy(other);
}

NNTrajectoryInput::NNTrajectoryInput(const NNTrajectoryInput& other)
{
  copy(other);
}

NNTrajectoryInput::~NNTrajectoryInput()
{

}

NNTrajectoryInput& NNTrajectoryInput::operator= (NNTrajectoryInput& other)
{
  copy(other);
  return *this;
}

NNTrajectoryInput& NNTrajectoryInput::operator= (const NNTrajectoryInput& other)
{
  copy(other);
  return *this;
}

void NNTrajectoryInput::copy(NNTrajectoryInput& other)
{
  load_percentage         = other.load_percentage;
  input_columns_to_read   = other.input_columns_to_read;
  input_particles_to_read = other.input_particles_to_read;

  padding             = other.padding;
  time_window_size    = other.time_window_size;
  time_window_stride  = other.time_window_stride;

  output_columns_to_read  = other.output_columns_to_read;
  prediction_step         = other.prediction_step;

  width     = other.width;
  height    = other.height;
  channels  = other.channels;
}

void NNTrajectoryInput::copy(const NNTrajectoryInput& other)
{
  load_percentage           = other.load_percentage;
  input_columns_to_read     = other.input_columns_to_read;
  input_particles_to_read   = other.input_particles_to_read;

  padding             = other.padding;
  time_window_size    = other.time_window_size;
  time_window_stride  = other.time_window_stride;

  output_columns_to_read  = other.output_columns_to_read;
  prediction_step         = other.prediction_step;

  width     = other.width;
  height    = other.height;
  channels  = other.channels;
}

sDatasetItem NNTrajectoryInput::create(DatsLoad &raw_data, unsigned int line)
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

std::vector<float> NNTrajectoryInput::make_input(unsigned int top_particle_idx,
                                                      unsigned int line,
                                                      DatsLoad &raw_data)
{
  unsigned int colums_count     = input_columns_to_read.size();
  unsigned int rows_count       = time_window_size;
  unsigned int particles_count  = input_particles_to_read.size();
  unsigned int result_size      = width*height*(particles_count + 1);

  std::vector<float> result(result_size);

  for (unsigned int row = 0; row < rows_count; row++)
  for (unsigned int column = 0; column < colums_count; column++)
  {
    float value = raw_data.get(
                                top_particle_idx,
                                input_columns_to_read[column],
                                row*time_window_stride + line
                              );

    unsigned int idx = input_idx(0, row, column);
    result[idx] = value;
  }

  for (unsigned int particle = 0; particle < particles_count; particle++)
  for (unsigned int row = 0; row < rows_count; row++)
  for (unsigned int column = 0; column < colums_count; column++)
  {
    float value = raw_data.get(
                                input_particles_to_read[particle],
                                input_columns_to_read[column],
                                row*time_window_stride + line
                              );

    unsigned int idx = input_idx(particle+1, row, column);
    result[idx] = value;
  }

  return result;
}


std::vector<float> NNTrajectoryInput::make_output(  unsigned int top_particle_idx,
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


unsigned int NNTrajectoryInput::input_idx(unsigned int particle, unsigned int row, unsigned int column)
{
  unsigned int result;

  result = (particle*height + row+padding)*width + column + padding;

  return result;
}
