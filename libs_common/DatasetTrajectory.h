#ifndef _DATASET_TRAJECTORY_H_
#define _DATASET_TRAJECTORY_H_

#include <tensor_interface.h>
#include <dataset_interface.h>

class DatasetTrajectory: public DatasetInterface
{
  public:
    DatasetTrajectory(
                        TensorInterface &training_tensor_interface,
                        TensorInterface &testing_tensor_interface,
                        unsigned int training_count,
                        unsigned int testing_count
                      );

    virtual ~DatasetTrajectory();


  private:
    void create(TensorInterface &tensor, bool put_to_testing, unsigned int count);

};

#endif
