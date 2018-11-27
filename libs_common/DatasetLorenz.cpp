#include <DatasetLorenz.h>
#include "lorenz.h"
#include <iostream>
#include <math.h>

DatasetLorenz::DatasetLorenz(unsigned int training_count, unsigned int testing_count)
{
  width     = 1;
  height    = 1;
  channels  = 3;

  training.resize(1);

  create(training_count, false);
  create(testing_count, true);

  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
}

DatasetLorenz::~DatasetLorenz()
{

}


void DatasetLorenz::create(unsigned int count, bool put_to_testing)
{
  unsigned int a = sqrt(count);
  unsigned int b = sqrt(count);
  Lorenz lorenz(a, b);

  for (unsigned int i = 0; i < lorenz.size(); i++)
  {
    auto input = lorenz.get_state(i);
    auto output = lorenz.get_output(i);

    sDatasetItem item;
    item.input.resize(3);
    item.output.resize(3);

    item.input[0] = input.x();
    item.input[1] = input.y();
    item.input[2] = input.z();

    item.output[0] = output.x();
    item.output[1] = output.y();
    item.output[2] = output.z();

    if (put_to_testing)
      add_testing(item);
    else
      add_training_for_regression(item);
  }
}
