#include "trajectory_prediction.h"
#include <cnn.h>

#include <iostream>

TrajectoryPrediction::TrajectoryPrediction(MotionTensor &initial_conditions)
{
  this->initial_conditions = &initial_conditions;
}

TrajectoryPrediction::~TrajectoryPrediction()
{

}


float map_to(float source_min, float source_max, float dest_min, float dest_max, float x)
{
  float k = (dest_max - dest_min)/(source_max - source_min);
  float q = dest_max - k*source_max;

  return k*x + q;
}

void TrajectoryPrediction::process( std::string network_file_name,
                                    TensorInterface &tensor_interface,
                                    unsigned int line_offset)
{
  sGeometry input_geometry, output_geometry;

  input_geometry.w = tensor_interface.input_width();
  input_geometry.h = tensor_interface.input_height();
  input_geometry.d = tensor_interface.input_depth();

  output_geometry.w = tensor_interface.output_width();
  output_geometry.h = tensor_interface.output_height();
  output_geometry.d = tensor_interface.output_depth();

  CNN nn(network_file_name, input_geometry, output_geometry);

  unsigned int prediction_step = line_offset;


  result.init(initial_conditions->width(), initial_conditions->height(), initial_conditions->depth());
  result.clear();

  for (unsigned int y = 0; y < line_offset; y++)
  for (unsigned int z = 0; z < result.depth(); z++)
  for (unsigned int x = 0; x < result.width(); x++)
  {
    float v = initial_conditions->get(x, y, z);
    result.set(x, y, z, v);
  }

  std::vector<float> nn_output(tensor_interface.output_size());


  unsigned int width = initial_conditions->width()/2;


  auto extremes = initial_conditions->get_extremes();

  for (unsigned int y = 0; y < result.height()/10; y++)
  {
    for (unsigned int z = 0; z < result.depth(); z++)
    {
      int ti_res = tensor_interface.create(y, z, result);
      if (ti_res == 0)
      {
        auto dataset_item = tensor_interface.get();
      //  nn.forward(nn_output, dataset_item.input);

        for (unsigned int x = 0; x < width; x++)
        {
          float v_norm   = initial_conditions->get(x + width, y, z);
          //TODO not working
          //float v_norm   = nn_output[x];

          float pos_norm = result.get(x, y, z);

          float v_orig, pos_orig;

          v_orig = map_to(0.0, 1.0,
                          extremes[width + x].min, extremes[width + x].max,
                          v_norm);

          pos_orig = map_to(0.0, 1.0,
                            extremes[x].min, extremes[x].max,
                            pos_norm);



          float predicted_orig = pos_orig + v_orig;

          float predicted = map_to(extremes[x].min, extremes[x].max, 0.0, 1.0, predicted_orig);

          result.set(x, y + prediction_step, z, predicted);
          result.set(x + 3, y + prediction_step, z, v_norm);

        }
      }
    }

    if ((y%100) == 0)
    {
      float done = y*100.0/result.height();
      std::cout << "done = " << done << "%\n";
    }
  }

}

MotionTensor& TrajectoryPrediction::get_result()
{
  return result;
}
