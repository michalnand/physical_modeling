#include "DatasetTrajectoryRuntime.h"

#include <iostream>

DatasetTrajectoryRuntime::DatasetTrajectoryRuntime(
                                                    TensorInterface &training_tensor_interface,
                                                    TensorInterface &testing_tensor_interface,
                                                    unsigned int testing_count
                                                )
{
    width     = training_tensor_interface.input_width();
    height    = training_tensor_interface.input_height();
    channels  = training_tensor_interface.input_depth();

    this->training_tensor = &training_tensor_interface;

    std::cout << "creating dataset\n";

    if (testing_count == 0)
        create_testing_all(testing_tensor_interface);
    else
        create_testing(testing_tensor_interface, testing_count);

    training_size = testing_tensor_interface.get_max_y_offset()*testing_tensor_interface.get_max_z_offset();

    auto item = get_random_training();

    this->output_size = item.output.size();

    /*
    training.resize(1);
    print();
    */

    print();
}

DatasetTrajectoryRuntime::~DatasetTrajectoryRuntime()
{

}

unsigned int DatasetTrajectoryRuntime::get_training_size()
{
  return training_size;
}

sDatasetItem DatasetTrajectoryRuntime::get_random_training()
{
    bool created = false;

    while (created != true)
    {
        unsigned int y_offset = rand()%training_tensor->get_max_y_offset();        //random time step
        unsigned int z_offset = rand()%training_tensor->get_max_z_offset();       //random cell

        if (training_tensor->create(y_offset, z_offset) == 0)
        {
            created = true;
        }
    }

    return training_tensor->get();
}


void DatasetTrajectoryRuntime::create_testing(TensorInterface &tensor, unsigned int count)
{
    while (count > 0)
    {
        unsigned int y_offset = rand()%tensor.get_max_y_offset();   //random time step
        unsigned int z_offset = rand()%tensor.get_max_z_offset();   //random cell

        if (tensor.create(y_offset, z_offset) == 0)
        {
            auto item = tensor.get();

            add_testing(item);

            count--;
        }
    }
}


void DatasetTrajectoryRuntime::create_testing_all(TensorInterface &tensor)
{
    for (unsigned int y_offset = 0; y_offset < tensor.get_max_y_offset(); y_offset++)
        for (unsigned int z_offset = 0; z_offset < tensor.get_max_z_offset(); z_offset++)
            if (tensor.create(y_offset, z_offset) == 0)
            {
                auto item = tensor.get();

                add_testing(item);
            }
}
