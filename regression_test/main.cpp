#include <iostream>
#include <dats_load.h>
#include <DatasetParticlesMotion.h>

#include <regression_experiment.h>

int main()
{
  DatsLoad raw_dataset_training("training.json");
  DatsLoad raw_dataset_testing("testing.json");

  raw_dataset_training.normalise_column();
  raw_dataset_testing.normalise_column();


  DatasetParticlesMotion dataset( raw_dataset_training,
                                  raw_dataset_testing,
                                  "dataset_particles_motion_spatial_config.json");


  std::cout << "loading done\n";


  RegressionExperiment experiment(dataset, "experiment_0/");
  experiment.run();
  std::cout << "program done\n";
  return 0;
}
