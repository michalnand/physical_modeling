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
                                    unsigned int testing_count
                                );

        virtual ~DatasetTrajectoryRuntime();

        unsigned int get_training_size();
        sDatasetItem get_random_training();

        sDatasetItem get_testing(unsigned int idx);


        unsigned int get_testing_size();

    private:
        void create_testing(TensorInterface &tensor, unsigned int count);
        void create_testing_all(TensorInterface &tensor);

    private:
        unsigned int testing_count;
        TensorInterface *training_tensor;
        TensorInterface *testing_tensor;

};

#endif
