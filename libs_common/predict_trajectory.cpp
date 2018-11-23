#include "predict_trajectory.h"


PredictTrajectory::PredictTrajectory(
                  DatsLoad &initial_conditions,
                  std::string dataset_config_file_name,
                  std::string experiment_dir
                )
{
  this->initial_conditions        = &initial_conditions;
  this->dataset_config_file_name  = dataset_config_file_name;
  this->experiment_dir            = experiment_dir;
}

PredictTrajectory::~PredictTrajectory()
{

}

void PredictTrajectory::process()
{
  trajectory.clear();
}
