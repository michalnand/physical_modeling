#ifndef _TENSOR_NO_SPATIAL_H_
#define _TENSOR_NO_SPATIAL_H_

class TensorNoSpatial
{
  public:
    TensorNoSpatial(std::string config_file_name);
    virtual ~TensorNoSpatial();

    sDatasetItem create(MotionTensor &motion_tensor, unsigned int y_offset);
};


#endif
