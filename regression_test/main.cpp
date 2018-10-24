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
                                  "dataset_particles_motion_config.json");


  std::cout << "loading done\n";
/*
  unsigned int testing_size = dataset.get_testing_size();

  for (unsigned int i = 0; i < 100; i++)
  {
     sDatasetItem item = dataset.get_random_training();

     for (unsigned int j = 0; j < item.input.size(); j++)
      printf("%6.3f ", item.input[j]);

    printf("\n\n");


    for (unsigned int j = 0; j < item.output.size(); j++)
     printf("%6.3f ", item.output[j]);

   printf("\n\n\n\n\n");
  }
*/

  RegressionExperiment experiment(dataset, "rbc_0/");
  experiment.run();

  std::cout << "program done\n";
  return 0;
}
