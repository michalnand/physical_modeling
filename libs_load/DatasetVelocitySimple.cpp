#include "DatasetVelocitySimple.h"

#include <iostream>

DatasetVelocitySimple::DatasetVelocitySimple(
                                              std::string training_dats_json_file_name,
                                              std::string testing_dats_json_file_name,
                                              std::string motion_tensor_file_name,
                                              unsigned int training_count,
                                              unsigned int testing_count
                                            )
{
  std::cout << "loading configs : \n";
  std::cout << training_dats_json_file_name << "\n";
  std::cout << testing_dats_json_file_name << "\n";
  std::cout << motion_tensor_file_name << "\n";

  training_motion_tensor.load(training_dats_json_file_name, motion_tensor_file_name);
  testing_motion_tensor.load(testing_dats_json_file_name, motion_tensor_file_name, training_motion_tensor.tensor());

  width     = 1;
  height    = 1;
  channels  = 3;

  std::cout << "creating dataset\n";

  create(training_motion_tensor.tensor(), false, training_count);
  create(testing_motion_tensor.tensor(), true, testing_count);

  training.resize(1);


  print();
}

DatasetVelocitySimple::~DatasetVelocitySimple()
{

}


void DatasetVelocitySimple::create(MotionTensor &tensor, bool put_to_testing, unsigned int count)
{
  sDatasetItem item;
  item.input.resize(3);
  item.output.resize(3);


  for (unsigned int i = 0; i < count; i++)
  {
    unsigned int z = rand()%tensor.depth();
    unsigned int y = rand()%tensor.height();
    item.input[0] = tensor.get(0, y, z);
    item.input[1] = tensor.get(1, y, z);
    item.input[2] = tensor.get(2, y, z);

    item.output[0] = tensor.get(3, y, z);
    item.output[1] = tensor.get(4, y, z);
    item.output[2] = tensor.get(5, y, z);

    if (put_to_testing)
      add_testing(item);
    else
      add_training_for_regression(item);
  }
}
