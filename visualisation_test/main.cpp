#include <iostream>

#include <dats_to_motion_tensor.h>
#include <tensor_no_spatial.h>

#include <DatasetTrajectory.h>

#include <glvisualisation.h>

int main()
{
  DatsToMotionTensor training_dats_to_motion_tensor;
  DatsToMotionTensor testing_dats_to_motion_tensor;

  training_dats_to_motion_tensor.load("training_dats.json", "motion_tensor.json");
  testing_dats_to_motion_tensor.load("testing_dats.json", "motion_tensor.json", training_dats_to_motion_tensor.tensor());

  TensorNoSpatial training_tensor("no_spatial_tensor.json", training_dats_to_motion_tensor.tensor());
  TensorNoSpatial testing_tensor("no_spatial_tensor.json", testing_dats_to_motion_tensor.tensor());

  GLVisualisation visualisation;

  unsigned int line_training = 0;
  unsigned int line_testing = 0;

  while (1)
  {
    visualisation.start();

    visualisation.translate(0.0, 0.0, -3.0);

    for (unsigned int particle = 0; particle < training_dats_to_motion_tensor.tensor().depth(); particle++)
    {
      float x = training_dats_to_motion_tensor.tensor().get(0, line_training, particle);
      float y = training_dats_to_motion_tensor.tensor().get(1, line_training, particle);
      float z = 0.5; //training_dats_to_motion_tensor.tensor().get(2, line_training, particle);

      visualisation.push();

        visualisation.translate(x*2.0 - 1.0, y*2.0 - 1.0, z*2.0 - 1.0);
        visualisation.set_color(1.0, 0.0, 0.0);
        visualisation.paint_sphere(0.01);

      visualisation.pop();
    }


    for (unsigned int particle = 0; particle < testing_dats_to_motion_tensor.tensor().depth(); particle++)
    {
      float x = testing_dats_to_motion_tensor.tensor().get(0, line_testing, particle);
      float y = testing_dats_to_motion_tensor.tensor().get(1, line_testing, particle);
      float z = 0.5; //testing_dats_to_motion_tensor.tensor().get(2, line_testing, particle);

      visualisation.push();

        visualisation.translate(x*2.0 - 1.0, y*2.0 - 1.0, z*2.0 - 1.0);
        visualisation.set_color(0.0, 0.0, 1.0);
        visualisation.paint_sphere(0.01);

      visualisation.pop();
    }

    line_training = (line_training+1)%training_dats_to_motion_tensor.tensor().height();
    line_testing = (line_testing+1)%testing_dats_to_motion_tensor.tensor().height();


    visualisation.finish();
  }

  std::cout << "program done\n";

  return 0;
}
