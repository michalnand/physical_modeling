#include "dats_to_trajectory.h"
#include <json_config.h>

DatsToTrajectory::DatsToTrajectory()
{

}

DatsToTrajectory::DatsToTrajectory(DatsLoad &raw_data, std::string config_file_name)
{
  JsonConfig json(config_file_name);

  std::vector<unsigned int> input_columns_to_read, output_columns_to_read, particles_to_read;

  for (unsigned int i = 0; i < json.result["input parameters"]["particles to read"].size(); i++)
    particles_to_read.push_back(json.result["input parameters"]["particles to read"][i].asInt());

  for (unsigned int i = 0; i < json.result["input parameters"]["columns to read"].size(); i++)
    input_columns_to_read.push_back(json.result["input parameters"]["columns to read"][i].asInt());

  for (unsigned int i = 0; i < json.result["output parameters"]["columns to read"].size(); i++)
    output_columns_to_read.push_back(json.result["output parameters"]["columns to read"][i].asInt());

  {
    trajectory_input.init(input_columns_to_read.size(), raw_data.get_lines_count(), particles_to_read.size());

    for (unsigned int k = 0; k < particles_to_read.size(); k++)
    for (unsigned int j = 1; j < raw_data.get_lines_count(); j++)
    for (unsigned int i = 0; i < input_columns_to_read.size(); i++)
    {
      float value = raw_data.get(particles_to_read[k], input_columns_to_read[i], j);
      trajectory_input.set(i, j, k, value);
    }
  }

  {
    trajectory_output.init(output_columns_to_read.size(), raw_data.get_lines_count(), particles_to_read.size());

    for (unsigned int k = 0; k < particles_to_read.size(); k++)
    for (unsigned int j = 1; j < raw_data.get_lines_count(); j++)
    for (unsigned int i = 0; i < output_columns_to_read.size(); i++)
    {
      float value = raw_data.get(particles_to_read[k], output_columns_to_read[i], j);
      trajectory_output.set(i, j, k, value);

      /*
      float x0 = raw_data.get(particles_to_read[k], output_columns_to_read[i], j - 1);
      float x1 = raw_data.get(particles_to_read[k], output_columns_to_read[i], j);
      float v = x1 - x0;
      trajectory_output.set(i, j, k, v);
      */
    }
  }
}

DatsToTrajectory::DatsToTrajectory(DatsToTrajectory& other)
{
  copy(other);
}

DatsToTrajectory::DatsToTrajectory(const DatsToTrajectory& other)
{
  copy(other);
}

DatsToTrajectory::~DatsToTrajectory()
{

}

DatsToTrajectory& DatsToTrajectory::operator= (DatsToTrajectory& other)
{
  copy(other);

  return *this;
}

DatsToTrajectory& DatsToTrajectory::operator= (const DatsToTrajectory& other)
{
  copy(other);

  return *this;
}

void DatsToTrajectory::copy(DatsToTrajectory& other)
{
  trajectory_input  = other.trajectory_input;
  trajectory_output = other.trajectory_output;
}

void DatsToTrajectory::copy(const DatsToTrajectory& other)
{
  trajectory_input  = other.trajectory_input;
  trajectory_output = other.trajectory_output;
}
