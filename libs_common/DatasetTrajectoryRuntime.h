#ifndef _DATASET_TRAJECTORY_RUNTIME_H_
#define _DATASET_TRAJECTORY_RUNTIME_H_

#include <tensor_interface.h>
#include <dataset_interface.h>

class DatasetTrajectoryRuntime: public DatasetInterface
{
    public:
        DatasetTrajectoryRuntime(
                                    TensorInterface &training_tensor_interface,
                                    TensorInterface &testing_tensor_interface,
                                    unsigned int testing_count = 0
                                );

        virtual ~DatasetTrajectoryRuntime();

        unsigned int get_training_size();
        sDatasetItem get_random_training();

    private:
        void create_testing(TensorInterface &tensor, unsigned int count);
        void create_testing_all(TensorInterface &tensor);

    private:
        TensorInterface *training_tensor;
};

#endif
