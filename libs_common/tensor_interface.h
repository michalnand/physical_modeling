#ifndef _TENSOR_INTERFACE_H_
#define _TENSOR_INTERFACE_H_

#include <string>
#include <vector>

#include <dataset_interface.h>
#include <motion_tensor.h>

class TensorInterface
{
  protected:
    unsigned int m_input_width,  m_input_height,  m_input_depth;
    unsigned int m_output_width, m_output_height, m_output_depth;

    unsigned int m_input_size, m_output_size;

    sDatasetItem result;

    MotionTensor *m_motion_tensor;

  public:
    TensorInterface();
    TensorInterface(  MotionTensor &motion_tensor);
    TensorInterface(  MotionTensor &motion_tensor,
                      unsigned int input_width_, unsigned int input_height_, unsigned int input_depth_,
                      unsigned int output_width_, unsigned int output_height_, unsigned int output_depth_);
    TensorInterface(TensorInterface& other);
    TensorInterface(const TensorInterface& other);

    virtual ~TensorInterface();

    TensorInterface& operator= (TensorInterface& other);
    TensorInterface& operator= (const TensorInterface& other);

  protected:
    void copy(TensorInterface& other);
    void copy(const TensorInterface& other);

  public:
    sDatasetItem get();


    unsigned int input_width();
    unsigned int input_height();
    unsigned int input_depth();

    unsigned int output_width();
    unsigned int output_height();
    unsigned int output_depth();

    unsigned int input_size();
    unsigned int output_size();

    std::string asString();
    void print();

    unsigned int get_max_y_offset();
    unsigned int get_max_z_offset();
  public:
    virtual int create(unsigned int y_offset, unsigned int z_offset);

  protected:
    void set_input_dimensions(unsigned int width_, unsigned int height_, unsigned int depth_);
    void set_output_dimensions(unsigned int width_, unsigned int height_, unsigned int depth_);

    void set_input(unsigned int x, unsigned int y, unsigned z, float value);
    void set_output(unsigned int x, unsigned int y, unsigned z, float value);

    void clear();
};

#endif
