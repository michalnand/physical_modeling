#ifndef _NN_TRAJECTORY_SPATIAL_INPUT_H_
#define _NN_TRAJECTORY_SPATIAL_INPUT_H_

#include <string>
#include <vector>

#include <dataset_interface.h>
#include <dats_load.h>
#include <trajectory.h>

class NNTrajectorySpatialInput
{
  public:
    NNTrajectorySpatialInput();

    NNTrajectorySpatialInput(std::string config_file_name);

    NNTrajectorySpatialInput(NNTrajectorySpatialInput& other);
    NNTrajectorySpatialInput(const NNTrajectorySpatialInput& other);

    virtual ~NNTrajectorySpatialInput();

    NNTrajectorySpatialInput& operator= (NNTrajectorySpatialInput& other);
    NNTrajectorySpatialInput& operator= (const NNTrajectorySpatialInput& other);

  protected:
    void copy(NNTrajectorySpatialInput& other);
    void copy(const NNTrajectorySpatialInput& other);

  public:
    virtual sDatasetItem create(DatsLoad &raw_data, unsigned int line, unsigned int particle);
    virtual sDatasetItem create(  Trajectory &trajectory_input,
                                  Trajectory &trajectory_output, 
                                  unsigned int line, unsigned int particle);

    unsigned int get_width()
    {
      return width;
    };

    unsigned int get_height()
    {
      return height;
    }

    unsigned int get_channels()
    {
      return channels;
    }

  private:
    bool use_other_particles;
    float load_percentage;

    std::vector<unsigned int> input_columns_to_read, input_particles_to_read;
    unsigned int padding, time_window_size, time_window_stride;

    std::vector<unsigned int> output_columns_to_read;
    unsigned int prediction_step;

    unsigned int discretisation_x;
    unsigned int discretisation_y;
    unsigned int discretisation_z;

  private:
    unsigned int width, height, channels;

  private:
    std::vector<float> make_input(unsigned int top_particle_idx, unsigned int line, DatsLoad &raw_data);
    std::vector<float> make_output( unsigned int top_particle_idx, unsigned int line, DatsLoad &raw_data);

    std::vector<float> make_input(unsigned int top_particle_idx, unsigned int line, Trajectory &trajectory);
    std::vector<float> make_output( unsigned int top_particle_idx, unsigned int line, Trajectory &raw_data);

    int saturate(int x, int min, int max);
    unsigned int to_idx(unsigned int x, unsigned int y, unsigned int z, unsigned int t, unsigned int w);
    std::vector<std::vector<float>> make_kernel(float x, float y, unsigned int kernel_size);

};

#endif
