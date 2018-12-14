#include <iostream>

#include <dats_to_motion_tensor.h>
#include <tensor_no_spatial.h>

#include <trajectory_prediction.h>
#include <motion_tensor_visualisation.h>

#include <cnn.h>

#include <math.h>

int main()
{
  DatsToMotionTensor dats_to_motion_tensor("testing_dats.json", "motion_tensor.json");

  TensorNoSpatial tensor_interface("no_spatial_tensor.json", dats_to_motion_tensor.tensor());


  TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
  unsigned int line_offset = 800;


  prediction.process( "experiment_3/trained/cnn_config.json", tensor_interface, line_offset);


  MotionTensorVisualisation visualisation;
  while (1)
  {
    visualisation.start();
    visualisation.render(dats_to_motion_tensor.tensor(), 1.0, 0.0, 0.0);
    visualisation.render(prediction.get_result(), 0.0, 0.0, 1.0, line_offset);
    visualisation.finish();
  }

  std::cout << "program done\n";

  return 0;
}
