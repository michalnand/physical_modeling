#ifndef _DATA_PARTICLES_MOTION_H_
#define _DATA_PARTICLES_MOTION_H_

#include <string>
#include <vector>

#include <trajectory.h>

#include <dataset_interface.h>
#include <nn_trajectory_spatial_input.h>

class DatasetParticlesMotion: public DatasetInterface
{
  public:
    DatasetParticlesMotion( Trajectory &trajectory_training_input,
                            Trajectory &trajectory_training_output,
                            Trajectory &trajectory_testing_input,
                            Trajectory &trajectory_testing_output,
                            std::string config_file_name);

    virtual ~DatasetParticlesMotion();
  private:
    void create(  NNTrajectorySpatialInput nn_trajectory_input,
                  Trajectory &trajectory_input,
                  Trajectory &trajectory_output,
                  bool put_to_testing);
    void print_testing_item(unsigned int idx);
};

#endif
