#ifndef _TRAJECTORY_PREDICTION_H_
#define _TRAJECTORY_PREDICTION_H_

#include <motion_tensor.h>
#include <tensor_interface.h>

#include <dat_load.h>
#include <cnn.h>

class TrajectoryPrediction
{
  private:
    MotionTensor *initial_conditions;
    std::vector<sMotionTensorExtreme> extremes;

    MotionTensor result;

  public:
    TrajectoryPrediction(MotionTensor &initial_conditions);
    virtual ~TrajectoryPrediction();

    unsigned int process( std::string network_file_name,
                          TensorInterface &tensor_interface,
                          unsigned int prediction_offset);

    MotionTensor& get_result();

  private:
    std::vector<float> predict( CNN &nn, TensorInterface &tensor_interface,
                                unsigned int time_idx,
                                unsigned int particle_idx,
                                unsigned int prediction_offset);

    float map_to(float source_min, float source_max, float dest_min, float dest_max, float x);

};


#endif
