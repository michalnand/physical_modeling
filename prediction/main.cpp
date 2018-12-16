#include <iostream>

#include <dats_to_motion_tensor.h>
#include <tensor_no_spatial.h>
#include <tensor_spatial.h>

#include <trajectory_prediction.h>
#include <motion_tensor_visualisation.h>

#include <cnn.h>

#include <math.h>


int main()
{
  DatsToMotionTensor dats_to_motion_tensor("testing_dats.json", "motion_tensor.json");

  dats_to_motion_tensor.tensor().save_json("trajectory_result/target.json");

  unsigned int prediction_offset = 800;

  {
      std::cout << "processing experiment 0\n";

      TensorNoSpatial tensor_interface("no_spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_0/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_0.json");
  }

  {
      std::cout << "processing experiment 1\n";

      TensorNoSpatial tensor_interface("no_spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_1/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_1.json");
  }

  {
      std::cout << "processing experiment 2\n";

      TensorNoSpatial tensor_interface("no_spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_2/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_2.json");
  }

  {
      std::cout << "processing experiment 3\n";

      TensorNoSpatial tensor_interface("no_spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_3/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_3.json");
  }

  {
      std::cout << "processing experiment 4\n";

      TensorSpatial tensor_interface("spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_4/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_4.json");
  }

  {
      std::cout << "processing experiment 5\n";

      TensorSpatial tensor_interface("spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_5/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_5.json");
  }

  {
      std::cout << "processing experiment 6\n";

      TensorSpatial tensor_interface("spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_6/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_6.json");
  }

  {
      std::cout << "processing experiment 7\n";

      TensorSpatial tensor_interface("spatial_tensor.json", dats_to_motion_tensor.tensor());
      TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
      prediction.process( "experiment_7/trained/cnn_config.json", tensor_interface, prediction_offset);
      prediction.get_result().save_json("trajectory_result/experiment_7.json");
  }


  /*
  MotionTensorVisualisation visualisation;
  while (1)
  {
    visualisation.start();
    visualisation.render(dats_to_motion_tensor.tensor(), 1.0, 0.0, 0.0);
    visualisation.render(prediction.get_result(), 0.0, 0.0, 1.0, prediction_offset);
    visualisation.finish();
  }
  */

  std::cout << "program done\n";

  return 0;
}
