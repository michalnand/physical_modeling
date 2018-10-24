#ifndef _DATA_PARTICLES_MOTION_H_
#define _DATA_PARTICLES_MOTION_H_

#include <string>
#include <vector>

#include <dats_load.h>

#include <dataset_interface.h>

class DatasetParticlesMotion: public DatasetInterface
{
  public:
    DatasetParticlesMotion( DatsLoad &raw_data_training, DatsLoad &raw_data_testing,
                            std::string config_file_name);

  private:
    void create(DatsLoad &raw_data, bool put_to_testing);

    std::vector<float> make_input(unsigned int top_particle_idx, unsigned int line, DatsLoad &raw_data);
    std::vector<float> make_output( unsigned int top_particle_idx, unsigned int line, DatsLoad &raw_data);

    unsigned int input_idx(unsigned int particle, unsigned int row, unsigned int column);


  private:
    float load_percentage;

    std::vector<unsigned int> input_columns_to_read, input_particles_to_read;
    unsigned int padding, time_window_size, time_window_stride;

    std::vector<unsigned int> output_columns_to_read;
    unsigned int prediction_step;
};

#endif
