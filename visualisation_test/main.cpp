#include <iostream>

#include <dats_to_motion_tensor.h>
#include <DatasetTrajectory.h>
#include <motion_tensor_visualisation.h>

int main()
{
  DatsToMotionTensor training_dats_to_motion_tensor;
  DatsToMotionTensor testing_dats_to_motion_tensor;

  training_dats_to_motion_tensor.load("training_dats.json", "motion_tensor.json");
  testing_dats_to_motion_tensor.load("testing_dats.json", "motion_tensor.json", training_dats_to_motion_tensor.tensor());


  MotionTensorVisualisation visualisation;
  //while (1)
  {
    visualisation.start();
    visualisation.render(training_dats_to_motion_tensor.tensor(), 1.0, 0.0, 0.0);
    visualisation.render(testing_dats_to_motion_tensor.tensor(), 0.0, 0.0, 1.0);
    visualisation.finish();
  }

  while (1)
  {
    
  }

  std::cout << "program done\n";

  return 0;
}
