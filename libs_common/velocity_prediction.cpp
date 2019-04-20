#include "velocity_prediction.h"

#include <iostream>
#include <math.h>

VelocityPrediction::VelocityPrediction(MotionTensor &target_trajectory)
{
    this->target_trajectory = &target_trajectory;
    extremes = this->target_trajectory->get_extremes();
}

VelocityPrediction::~VelocityPrediction()
{

}


unsigned int VelocityPrediction::process( std::string network_file_name,
                                            TensorInterface &tensor_interface,
                                            unsigned int prediction_offset)
{
  sGeometry input_geometry, output_geometry;

  input_geometry.w = tensor_interface.input_width();
  input_geometry.h = tensor_interface.input_height();
  input_geometry.d = tensor_interface.input_depth();

  output_geometry.w = tensor_interface.output_width();
  output_geometry.h = tensor_interface.output_height();
  output_geometry.d = tensor_interface.output_depth();

  CNN nn(network_file_name, input_geometry, output_geometry);


  result.init(target_trajectory->width(), target_trajectory->height(), target_trajectory->depth());
  result.clear();


  unsigned int time_max = target_trajectory->height() - prediction_offset;

  for (unsigned int time_idx = 0; time_idx < time_max; time_idx++)
  {
      for (unsigned int particle_idx = 0; particle_idx < result.depth(); particle_idx++)
      {
        predict(nn, tensor_interface, time_idx, particle_idx, prediction_offset);
      }

      if ((time_idx%100) == 0)
      {
        float done = time_idx*100.0/time_max;
        std::cout << "done = " << done << "%\n";
      }

  }


  return result.height();
}

MotionTensor& VelocityPrediction::get_result()
{
    return result;
}





float VelocityPrediction::map_to(float source_min, float source_max, float dest_min, float dest_max, float x)
{
  float k = (dest_max - dest_min)/(source_max - source_min);
  float q = dest_max - k*source_max;

  return k*x + q;
}


int VelocityPrediction::predict( CNN &nn,   TensorInterface &tensor_interface,
                                            unsigned int time_idx,
                                            unsigned int particle_idx,
                                            unsigned int prediction_offset
                                )
{
  int ti_res = tensor_interface.create(time_idx, particle_idx, result);

  if (ti_res != 0)
  {
      return -1;
  }

  auto dataset_item = tensor_interface.get();

  unsigned int output_size = dataset_item.output.size();


  std::vector<float> nn_output(output_size);

  nn.forward(nn_output, dataset_item.input);


  for (unsigned int x = 0; x < output_size; x++)
  {
    float v_norm   = nn_output[x];

    result.set(x, time_idx + prediction_offset, particle_idx, v_norm);
  }

  return 0;
}
