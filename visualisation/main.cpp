#include <iostream>

#include <dats_to_motion_tensor.h>
#include <DatasetTrajectory.h>
#include <motion_tensor_visualisation.h>

int main()
{
/*
  DatsToMotionTensor testing_dats_to_motion_tensor;

  testing_dats_to_motion_tensor.load("testing_dats.json", "motion_tensor.json");
  //testing_dats_to_motion_tensor.tensor().save_json("testing.json");
*/

  MotionTensor target;
  target.load_json("trajectory_result/target.json");

  MotionTensor experiment_0;
  experiment_0.load_json("trajectory_result/experiment_0.json");

  MotionTensor experiment_1;
  experiment_1.load_json("trajectory_result/experiment_1.json");

  MotionTensor experiment_2;
  experiment_2.load_json("trajectory_result/experiment_2.json");

  MotionTensor experiment_3;
  experiment_3.load_json("trajectory_result/experiment_3.json");

  MotionTensorVisualisation visualisation;

  while (1)
  {
    visualisation.start();
    visualisation.render(target,        1.0, 0.0, 0.0);
    visualisation.render(experiment_0,  0.0, 1.0, 0.0);
    visualisation.render(experiment_1,  0.0, 0.0, 1.0);
    visualisation.render(experiment_2,  1.0, 1.0, 0.0);
    visualisation.render(experiment_3,  1.0, 0.0, 1.0);
    visualisation.finish();
  }


  std::cout << "program done\n";

  return 0;
}
