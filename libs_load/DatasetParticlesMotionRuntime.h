#ifndef _DATA_PARTICLES_MOTION_RUNTIME_H_
#define _DATA_PARTICLES_MOTION_RUNTIME_H_

#include <string>
#include <vector>

#include <trajectory.h>

#include <dataset_interface.h>
#include <nn_trajectory_spatial_input.h>

class DatasetParticlesMotionRuntime: public DatasetInterface
{
  private:
    NNTrajectorySpatialInput nn_trajectory_input;

    Trajectory *trajectory_training_input;
    Trajectory *trajectory_training_output;

    float training_load_percentage;
    float testing_load_percentage;

  public:
    DatasetParticlesMotionRuntime(  Trajectory &trajectory_training_input,
                                    Trajectory &trajectory_training_output,
                                    Trajectory &trajectory_testing_input,
                                    Trajectory &trajectory_testing_output,
                                    std::string config_file_name);

    virtual ~DatasetParticlesMotionRuntime();


  public:
    unsigned int get_training_size();
    unsigned int get_output_size();

    sDatasetItem get_random_training();

    void print_testing_item(unsigned int idx);
    void print_training_item();

  private:
    void create(  NNTrajectorySpatialInput &nn_trajectory_input,
                  Trajectory &trajectory_input,
                  Trajectory &trajectory_output,
                  bool put_to_testing);
};

#endif
