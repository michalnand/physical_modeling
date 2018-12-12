#include <iostream>


#include <DatasetVelocitySimple.h>
#include <regression_experiment.h>


int main()
{
  unsigned int training_count = 1000000;
  unsigned int testing_count  = 20000;

  DatasetVelocitySimple  dataset("training_dats.json", "testing_dats.json", "motion_tensor.json", training_count, testing_count);

  RegressionExperiment experiment(dataset, "experiment_0/");
  experiment.run();

  std::cout << "program done\n";

  return 0;
}
