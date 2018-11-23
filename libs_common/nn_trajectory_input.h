#ifndef _NN_TRAJECTORY_INPUT_H_
#define _NN_TRAJECTORY_INPUT_H_

#include <string>
#include <vector>

#include <dats_load.h>
#include <dataset_interface.h>

class NNTrajectoryInput
{
  public:
    NNTrajectoryInput();

    NNTrajectoryInput(std::string config_file_name);

    NNTrajectoryInput(NNTrajectoryInput& other);
    NNTrajectoryInput(const NNTrajectoryInput& other);

    virtual ~NNTrajectoryInput();

    NNTrajectoryInput& operator= (NNTrajectoryInput& other);
    NNTrajectoryInput& operator= (const NNTrajectoryInput& other);

  protected:
    void copy(NNTrajectoryInput& other);
    void copy(const NNTrajectoryInput& other);

  public:
    virtual sDatasetItem create(DatsLoad &raw_data, unsigned int line);

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
    float load_percentage;

    std::vector<unsigned int> input_columns_to_read, input_particles_to_read;
    unsigned int padding, time_window_size, time_window_stride;

    std::vector<unsigned int> output_columns_to_read;
    unsigned int prediction_step;

  private:
    unsigned int width, height, channels;

  private:
    std::vector<float> make_input(unsigned int top_particle_idx, unsigned int line, DatsLoad &raw_data);
    std::vector<float> make_output( unsigned int top_particle_idx, unsigned int line, DatsLoad &raw_data);
    unsigned int input_idx(unsigned int particle, unsigned int row, unsigned int column);

};

#endif
