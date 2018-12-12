#ifndef _TENSOR_NO_SPATIAL_H_
#define _TENSOR_NO_SPATIAL_H_


#include <tensor_interface.h>

class TensorNoSpatial: public TensorInterface
{
  public:
    TensorNoSpatial(std::string config_file_name, MotionTensor &motion_tensor);
    TensorNoSpatial(TensorNoSpatial& other);
    TensorNoSpatial(const TensorNoSpatial& other);

    virtual ~TensorNoSpatial();

    TensorNoSpatial& operator= (TensorNoSpatial& other);
    TensorNoSpatial& operator= (const TensorNoSpatial& other);

  protected:
    void copy_no_spatial(TensorNoSpatial& other);
    void copy_no_spatial(const TensorNoSpatial& other);

  public:
    int create(unsigned int y_offset, unsigned int z_offset);
    int create(unsigned int y_offset, unsigned int z_offset, MotionTensor &motion_tensor);

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
