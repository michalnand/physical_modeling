#include <iostream>

#include <dats_to_motion_tensor.h>
#include <tensor_no_spatial.h>

#include <trajectory_prediction.h>
#include <motion_tensor_visualisation.h>

#include <cnn.h>

#include <math.h>

int main()
{
  DatsToMotionTensor dats_to_motion_tensor("training_dats.json", "motion_tensor.json");

  TensorNoSpatial tensor_interface("no_spatial_tensor.json", dats_to_motion_tensor.tensor());

  TrajectoryPrediction prediction(dats_to_motion_tensor.tensor());
  unsigned int line_offset = 1;

/*

  prediction.process( "experiment_0/trained/cnn_config.json", tensor_interface, line_offset);

  MotionTensorVisualisation visualisation;
  while (1)
  {
    visualisation.start();
    visualisation.render(dats_to_motion_tensor.tensor(), 1.0, 0.0, 0.0);
    visualisation.render(prediction.get_result(), 0.0, 0.0, 1.0, line_offset);
    visualisation.finish();
  }
*/

  sGeometry input_geometry, output_geometry;

  input_geometry.w = tensor_interface.input_width();
  input_geometry.h = tensor_interface.input_height();
  input_geometry.d = tensor_interface.input_depth();

  output_geometry.w = tensor_interface.output_width();
  output_geometry.h = tensor_interface.output_height();
  output_geometry.d = tensor_interface.output_depth();

  CNN nn("experiment_0/trained/cnn_config.json", input_geometry, output_geometry);

  std::vector<float> nn_output(output_geometry.d);

  for (unsigned int i = 0; i < 100; i++)
  {
    unsigned int y = rand()%dats_to_motion_tensor.tensor().height();
    unsigned int z = rand()%dats_to_motion_tensor.tensor().depth();
    int ti_res = tensor_interface.create(y, z, dats_to_motion_tensor.tensor());
    if (ti_res != 0)
      continue;

    auto dataset_item = tensor_interface.get();
    nn.forward(nn_output, dataset_item.input);

    for (unsigned int j = 0; j < dataset_item.output.size(); j++)
      std::cout << dataset_item.output[j] << " ";

    std::cout << " : ";

    for (unsigned int j = 0; j < nn_output.size(); j++)
      std::cout << nn_output[j] << " ";

    float error = 0.0;
    float base = 0.0;
    for (unsigned int j = 0; j < (dataset_item.output.size()-1); j++)
    {
      error+= pow(dataset_item.output[j] - nn_output[j], 2.0);
      base+= pow(dataset_item.output[j], 2.0);
    }

    float relative_error = 100.0*sqrt(error)/sqrt(base + 0.00000000000001);

    std::cout << " e = " << relative_error << "% ";

    std::cout << "\n";
  }

  return 0;

  prediction.process( "experiment_0/trained/cnn_config.json", tensor_interface, line_offset);

  unsigned int z = 0;

  //for (unsigned int y = prediction.get_result().height(); y++)
  for (unsigned int y = 0; y < 1000; y++)
  {
    std::cout << y << ": ";

    /*
    for (unsigned int x = 0; x < 3; x++)
    {
      std::cout << dats_to_motion_tensor.tensor().get(x, y, x) << " ";
    }

    std::cout << " : ";

    for (unsigned int x = 0; x < 3; x++)
    {
      std::cout << prediction.get_result().get(x, y, z) << " ";
    }
    */

    std::cout << " : ";

    for (unsigned int x = 0; x < 3; x++)
    {
      std::cout << dats_to_motion_tensor.tensor().get(x + 3, y, z) << " ";
    }

    std::cout << " : ";

    for (unsigned int x = 0; x < 3; x++)
    {
      std::cout << prediction.get_result().get(x + 3, y, z) << " ";
    }

    std::cout << "\n";
  }



  std::cout << "program done\n";

  return 0;
}
