#include "DatasetTrajectory.h"

#include <iostream>

DatasetTrajectory::DatasetTrajectory(
                                      TensorInterface &training_tensor_interface,
                                      TensorInterface &testing_tensor_interface,
                                      unsigned int training_count,
                                      unsigned int testing_count
                                    )
{
    width     = training_tensor_interface.input_width();
    height    = training_tensor_interface.input_height();
    channels  = training_tensor_interface.input_depth();

    std::cout << "creating dataset\n";

    if (training_count == 0)
        create_all(training_tensor_interface, false);
    else
        create(training_tensor_interface, false, training_count);

    if (testing_count == 0)
        create_all(testing_tensor_interface, true);
    else
        create(testing_tensor_interface, true, testing_count);

    print();
}

DatasetTrajectory::~DatasetTrajectory()
{

}


void DatasetTrajectory::create(TensorInterface &tensor, bool put_to_testing, unsigned int count)
{
    while (count > 0)
    {
        unsigned int y_offset =rand()%tensor.get_max_y_offset();
        unsigned int z_offset = rand()%tensor.get_max_z_offset();

        if (tensor.create(y_offset, z_offset) == 0)
        {
            auto item = tensor.get();

            if (put_to_testing)
                add_testing(item);
            else
                add_training_for_regression(item);

            count--;
        }
    }
}


void DatasetTrajectory::create_all(TensorInterface &tensor, bool put_to_testing)
{
    for (unsigned int y_offset = 0; y_offset < tensor.get_max_y_offset(); y_offset++)
        for (unsigned int z_offset = 0; z_offset < tensor.get_max_z_offset(); z_offset++)
            if (tensor.create(y_offset, z_offset) == 0)
            {
                auto item = tensor.get();

                if (put_to_testing)
                    add_testing(item);
                else
                    add_training_for_regression(item);
            }
}
