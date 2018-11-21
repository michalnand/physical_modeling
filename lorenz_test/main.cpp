#include <iostream>
#include <lorenz96.h>
#include <log.h>
#include <trajectory_compare.h>
#include <DatasetLorenz96.h>
#include <regression_experiment.h>


void predict(std::string experiment_dir, unsigned int variables_count)
{
  sGeometry input_geometry, output_geometry;
  input_geometry.w = 1;
  input_geometry.h = 1;
  input_geometry.d = variables_count;

  output_geometry.w = 1;
  output_geometry.h = 1;
  output_geometry.d = variables_count;

  CNN nn(experiment_dir+"trained/cnn_config.json", input_geometry, output_geometry);

  Log trajectory_target_log(experiment_dir+"trajectory/trajectory_target.log");
  Log trajectory_predicted_log(experiment_dir+"trajectory/trajectory_predicted.log");

  Lorenz96 lorenz96(variables_count);
  lorenz96.set_random_initial_conditions(0.1);

  float dt = 0.1;

  lorenz96.next(dt);


  std::vector<std::vector<float>> trajectory_target, trajectory_predicted;

  auto predicted = lorenz96.get_x();
  std::vector<float> target(variables_count);
  std::vector<float> dif(variables_count);

  for (unsigned int j = 0; j < 1000; j++)
  {
    auto initial = lorenz96.get_x();

    nn.forward(dif, initial);
    for (unsigned int i = 0; i < variables_count; i++)
      predicted[i] = predicted[i] + dif[i]*dt;

    lorenz96.next(dt);
    auto target = lorenz96.get_x();

    trajectory_target.push_back(target);
    trajectory_predicted.push_back(predicted);

    trajectory_target_log << target << "\n";
    trajectory_predicted_log << predicted << "\n";
  }

  TrajectoryCompare compare;
  compare.process(experiment_dir + "trajectory/", trajectory_target, trajectory_predicted);

}

int main()
{
  unsigned int variables_count = 10;

/*
  DatasetLorenz96 dataset(variables_count, 100, 100);
  dataset.print();

  {
    RegressionExperiment experiment(dataset, "experiment_0/");
    experiment.run();
  }

*/
  predict("experiment_0/", variables_count);

  std::cout << "program done\n";
  return 0;
}
