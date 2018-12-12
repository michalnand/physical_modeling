#include "dats_to_motion_tensor.h"

#include <dats_load.h>
#include <json_config.h>
#include <iostream>

DatsToMotionTensor::DatsToMotionTensor()
{

}


DatsToMotionTensor::DatsToMotionTensor(
                                        std::string dats_json_file_name,
                                        std::string motion_tensor_file_name
                                      )
{
  load(dats_json_file_name, motion_tensor_file_name);
}



DatsToMotionTensor::DatsToMotionTensor(
                                        std::string dats_json_file_name,
                                        std::string motion_tensor_file_name,
                                        MotionTensor &other
                                      )
{
  load(dats_json_file_name, motion_tensor_file_name, other);
}

DatsToMotionTensor::DatsToMotionTensor(DatsToMotionTensor& other)
{
  copy(other);
}

DatsToMotionTensor::DatsToMotionTensor(const DatsToMotionTensor& other)
{
  copy(other);
}

DatsToMotionTensor& DatsToMotionTensor::operator= (DatsToMotionTensor& other)
{
  copy(other);
  return *this;
}

DatsToMotionTensor& DatsToMotionTensor::operator= (const DatsToMotionTensor& other)
{
  copy(other);
  return *this;
}

DatsToMotionTensor::~DatsToMotionTensor()
{

}


void DatsToMotionTensor::load(  std::string dats_json_file_name,
                                std::string motion_tensor_file_name)
{
    DatsLoad dats(dats_json_file_name);
    JsonConfig json(motion_tensor_file_name);

    bool normalise = json.result["normalise"].asBool();
    bool velocity_from_position = json.result["velocity from position"].asBool();

    std::vector<unsigned int> dats_to_load, columns_to_load;

    for (unsigned int i = 0; i < json.result["columns to load"].size(); i++)
      columns_to_load.push_back(json.result["columns to load"][i].asInt());

    for (unsigned int i = 0; i < json.result["dats to load"].size(); i++)
      dats_to_load.push_back(json.result["dats to load"][i].asInt());

    unsigned int columns_count = columns_to_load.size();
    if (velocity_from_position)
      columns_count = columns_count*2;

    motion_tensor.init(columns_count, dats.get_lines_count(), dats_to_load.size());

    for (unsigned int z = 0; z < dats_to_load.size(); z++)
    for (unsigned int y = 0; y < dats.get_lines_count(); y++)
    for (unsigned int x = 0; x < columns_to_load.size(); x++)
    {
      float value = dats.get(dats_to_load[z], columns_to_load[x], y);
      motion_tensor.set(x, y, z, value);
    }

    if (velocity_from_position)
      motion_tensor.velocity_from_position();

    motion_tensor.find_extremes();

    if (normalise)
      motion_tensor.normalise();
}

void DatsToMotionTensor::load(  std::string dats_json_file_name,
                                std::string motion_tensor_file_name,
                                MotionTensor &other)
{
    DatsLoad dats(dats_json_file_name);
    JsonConfig json(motion_tensor_file_name);

    bool normalise = json.result["normalise"].asBool();
    bool velocity_from_position = json.result["velocity from position"].asBool();

    std::vector<unsigned int> dats_to_load, columns_to_load;

    for (unsigned int i = 0; i < json.result["columns to load"].size(); i++)
      columns_to_load.push_back(json.result["columns to load"][i].asInt());

    for (unsigned int i = 0; i < json.result["dats to load"].size(); i++)
      dats_to_load.push_back(json.result["dats to load"][i].asInt());

    unsigned int columns_count = columns_to_load.size();
    if (velocity_from_position)
      columns_count = columns_count*2;

    motion_tensor.init(columns_count, dats.get_lines_count(), dats_to_load.size());

    for (unsigned int z = 0; z < dats_to_load.size(); z++)
    for (unsigned int y = 0; y < dats.get_lines_count(); y++)
    for (unsigned int x = 0; x < columns_to_load.size(); x++)
    {
      float value = dats.get(dats_to_load[z], columns_to_load[x], y);
      motion_tensor.set(x, y, z, value);
    }

    if (velocity_from_position)
      motion_tensor.velocity_from_position();

    if (normalise)
    {
      auto extremes = other.get_extremes();
      motion_tensor.set_extremes(extremes);
      motion_tensor.normalise();
    }
}


void DatsToMotionTensor::copy(DatsToMotionTensor& other)
{
  motion_tensor = other.motion_tensor;
}

void DatsToMotionTensor::copy(const DatsToMotionTensor& other)
{
  motion_tensor = other.motion_tensor;
}
