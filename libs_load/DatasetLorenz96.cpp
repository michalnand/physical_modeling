#include "DatasetLorenz96.h"
#include <math.h>

DatasetLorenz96::DatasetLorenz96(unsigned int variables_count, unsigned int training_size, unsigned int testing_size)
{
  Lorenz96 lorenz96(variables_count);

  width   = 1;
  height  = 1;
  channels= variables_count;


  training.resize(1);


  unsigned int batch_count, batch_size;

  batch_count = sqrt(training_size);
  batch_size  = sqrt(training_size);
  create(lorenz96, batch_count, batch_size, false);

  batch_count = sqrt(testing_size);
  batch_size  = sqrt(testing_size);
  create(lorenz96, batch_count, batch_size, true);
}

DatasetLorenz96::~DatasetLorenz96()
{

}

void DatasetLorenz96::create(Lorenz96 &lorenz96, unsigned int batch_count, unsigned int batch_size, bool put_to_testing)
{
  for (unsigned int j = 0; j < batch_count; j++)
  {
    lorenz96.set_random_initial_conditions(0.1);

    for (unsigned int i = 0; i < batch_size; i++)
    {
      lorenz96.next();

      sDatasetItem item;
      item.input  = lorenz96.get_x();
      item.output = lorenz96.get_dif();

      if (put_to_testing)
        add_testing(item);
      else
        add_training_for_regression(item);
    }
  }
}
