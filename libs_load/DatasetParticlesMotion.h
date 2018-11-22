#ifndef _DATA_PARTICLES_MOTION_H_
#define _DATA_PARTICLES_MOTION_H_

#include <string>
#include <vector>

#include <dats_load.h>

#include <dataset_interface.h>
#include <nn_trajectory_input.h>

class DatasetParticlesMotion: public DatasetInterface
{
  public:
    DatasetParticlesMotion( DatsLoad &raw_data_training, DatsLoad &raw_data_testing,
                            std::string config_file_name);

  private:
    void create(NNTrajectoryInput nn_trajectory_input, DatsLoad &raw_data, bool put_to_testing);
};

#endif
