#include <iostream>

#include <dats_to_motion_tensor.h>
#include <tensor_no_spatial.h>

#include <DatasetTrajectory.h>

#include <regression_experiment.h>

int main()
{
  DatsToMotionTensor training_dats_to_motion_tensor("training_dats.json", "motion_tensor.json");
  DatsToMotionTensor testing_dats_to_motion_tensor("testing_dats.json", "motion_tensor.json", training_dats_to_motion_tensor.tensor());

  TensorNoSpatial training_tensor("no_spatial_tensor.json", training_dats_to_motion_tensor.tensor());
  TensorNoSpatial testing_tensor("no_spatial_tensor.json", testing_dats_to_motion_tensor.tensor());

  DatasetTrajectory dataset(training_tensor, training_tensor);


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
