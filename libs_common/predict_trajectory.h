#ifndef _PREDICT_TRAJECTORY_H_
#define _PREDICT_TRAJECTORY_H_

#include <nn_trajectory_spatial_input.h>
#include <trajectory_compare.h>
#include <cnn.h>

#include <trajectory.h>

class PredictTrajectory
{
  private:
    DatsLoad *initial_conditions;
    std::string dataset_config_file_name;
    std::string experiment_dir;

    Trajectory trajectory;

  public:
    PredictTrajectory(
                      DatsLoad &initial_conditions,
                      std::string dataset_config_file_name,
                      std::string experiment_dir
                    );
    virtual ~PredictTrajectory();

    Trajectory& get_trajectory()
    {
      return trajectory;
    }

    void process();
};


#endif
