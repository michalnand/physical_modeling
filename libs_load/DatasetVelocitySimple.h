#ifndef _DATASET_VELOCITY_SIMPLE_H_
#define _DATASET_VELOCITY_SIMPLE_H_

#include <dataset_interface.h>
#include <dats_to_motion_tensor.h>

class DatasetVelocitySimple: public DatasetInterface
{
  public:
    DatasetVelocitySimple(
                            std::string training_dats_json_file_name,
                            std::string testing_dats_json_file_name,
                            std::string motion_tensor_file_name,
                            unsigned int training_count,
                            unsigned int testing_count
                         );

    virtual ~DatasetVelocitySimple();


  private:
    void create(MotionTensor &tensor, bool put_to_testing, unsigned int count);


  private:
    DatsToMotionTensor training_motion_tensor, testing_motion_tensor;

};

#endif
