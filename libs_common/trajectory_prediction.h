#ifndef _TRAJECTORY_PREDICTION_H_
#define _TRAJECTORY_PREDICTION_H_

#include <motion_tensor.h>
#include <tensor_interface.h>

class TrajectoryPrediction
{
  private:
    MotionTensor *initial_conditions;
    MotionTensor result;

  public:
    TrajectoryPrediction(MotionTensor &initial_conditions);
    virtual ~TrajectoryPrediction();

    void process( std::string network_file_name,
                  TensorInterface &tensor_interface,
                  unsigned int line_offset);

    MotionTensor& get_result();
};


#endif
