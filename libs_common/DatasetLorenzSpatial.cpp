#include <DatasetLorenzSpatial.h>
#include "lorenz.h"
#include <iostream>
#include <math.h>

DatasetLorenzSpatial::DatasetLorenzSpatial(unsigned int training_count, unsigned int testing_count, unsigned int discretization)
{
  width     = discretization;
  height    = discretization;
  channels  = discretization;

  training.resize(1);

  create(training_count, discretization, false);
  create(testing_count, discretization, true);

  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
}

DatasetLorenzSpatial::~DatasetLorenzSpatial()
{

}


void DatasetLorenzSpatial::create(unsigned int count, unsigned int discretization, bool put_to_testing)
{
  unsigned int a = sqrt(count);
  unsigned int b = sqrt(count);
  Lorenz lorenz(a, b);

  sDatasetItem item;
  unsigned int size = discretization*discretization*discretization;
  item.input.resize(size);
  item.output.resize(3);

  for (unsigned int i = 0; i < lorenz.size(); i++)
  {
    auto input = lorenz.get_state(i);
    auto output = lorenz.get_output(i);

    for (unsigned int i = 0; i < item.input.size(); i++)
      item.input[i] = 0.0;

    unsigned int x = input.x()*discretization;
    unsigned int y = input.y()*discretization;
    unsigned int z = input.z()*discretization;

    if (x >= discretization)
      x = discretization-1;

    if (y >= discretization)
      y = discretization-1;

    if (z >= discretization)
      z = discretization-1;

    unsigned int idx = (z*discretization + y)*discretization + x;

    item.input[idx] = 1.0;

    item.output[0] = output.x();
    item.output[1] = output.y();
    item.output[2] = output.z();

    if (put_to_testing)
      add_testing(item);
    else
      add_training_for_regression(item);
  }
}
