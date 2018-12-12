#ifndef _TENSOR_NO_SPATIAL_H_
#define _TENSOR_NO_SPATIAL_H_


#include <tensor_interface.h>

class TensorNoSpatial: public TensorInterface
{
  public:
    TensorNoSpatial(std::string config_file_name, MotionTensor &motion_tensor);
    virtual ~TensorNoSpatial();

    int create(unsigned int y_offset, unsigned int z_offset);

  private:
    std::vector<unsigned int> input_columns;
    std::vector<unsigned int> output_columns;
    unsigned int time_window_size;
    unsigned int time_step_size;
    unsigned int prediction_step_size;
    bool use_depth;
    unsigned int padding;
};


#endif
