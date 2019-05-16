#ifndef _TENSOR_SPATIAL_H_
#define _TENSOR_SPATIAL_H_


#include <tensor_interface.h>

class TensorSpatial: public TensorInterface
{
  public:
    TensorSpatial(std::string config_file_name, MotionTensor &motion_tensor);
    TensorSpatial(TensorSpatial& other);
    TensorSpatial(const TensorSpatial& other);

    virtual ~TensorSpatial();

    TensorSpatial& operator= (TensorSpatial& other);
    TensorSpatial& operator= (const TensorSpatial& other);

  protected:
    void copy_spatial(TensorSpatial& other);
    void copy_spatial(const TensorSpatial& other);

  public:
    int create(unsigned int y_offset, unsigned int z_offset);
    int create(unsigned int y_offset, unsigned int z_offset, MotionTensor &motion_tensor);

    private:
        std::vector<std::vector<float>> make_kernel(float x, float y, float x_rounded, float y_rounded, unsigned int size);

  private:
    std::vector<unsigned int> input_columns;
    std::vector<unsigned int> output_columns;
    unsigned int time_window_size;
    unsigned int time_step_size;
    unsigned int prediction_step_size;
    bool use_depth;
    bool use_gaussian_kernel;

    unsigned int discretization_x, discretization_y, discretization_z;

    float input_data_corruption, input_data_corruption_noise_level;
    float output_data_corruption, output_data_corruption_noise_level;

};


#endif
