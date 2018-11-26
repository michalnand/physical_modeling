#include <iostream>
#include <dats_load.h>
#include <DatasetParticlesMotion.h>

#include <regression_experiment.h>

#include <trajectory.h>
#include <dats_to_trajectory.h>

#include <particles_test.h>

int main()
{
  ParticlesTest particles_test(256);

  while (1)
  {
    particles_test.process();
    particles_test.render();
  }

  DatsLoad dats_training("training.json");
  DatsLoad dats_testing("testing.json");

  dats_training.find_extreme();

  auto extremes = dats_training.get_extremes();
  dats_training.set_extremes(extremes);
  dats_testing.set_extremes(extremes);

  dats_training.normalise_column(0.0, 1.0, false);
  dats_testing.normalise_column(0.0, 1.0, false);



  DatsToTrajectory training_trajectory(dats_training, "dataset_particles_motion_spatial_config.json");
  DatsToTrajectory testing_trajectory(dats_testing, "dataset_particles_motion_spatial_config.json");

  training_trajectory.get_trajectory_input().save("experiment_0/trajectory_training_target/input");
  training_trajectory.get_trajectory_output().save("experiment_0/trajectory_training_target/output");
  testing_trajectory.get_trajectory_input().save("experiment_0/trajectory_testing_target/input");
  testing_trajectory.get_trajectory_output().save("experiment_0/trajectory_testing_target/output");



  DatasetParticlesMotion dataset( training_trajectory.get_trajectory_input(),
                                  training_trajectory.get_trajectory_output(),
                                  testing_trajectory.get_trajectory_input(),
                                  testing_trajectory.get_trajectory_output(),

                                  "dataset_particles_motion_spatial_config.json");


  std::cout << "loading done\n";

 {
   RegressionExperiment experiment(dataset, "experiment_0/");
   experiment.run();
 }

 {
   RegressionExperiment experiment(dataset, "experiment_1/");
   experiment.run();
 }

 {
   RegressionExperiment experiment(dataset, "experiment_2/");
   experiment.run();
 }

 {
   RegressionExperiment experiment(dataset, "experiment_3/");
   experiment.run();
 }


  std::cout << "program done\n";
  return 0;
}
