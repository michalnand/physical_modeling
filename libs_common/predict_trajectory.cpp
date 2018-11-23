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

  NNTrajectorySpatialInput nn_trajectory_input(dataset_config_file_name);
  sGeometry input_geometry;
  sGeometry output_geometry;

  input_geometry.w = nn_trajectory_input.get_width();
  input_geometry.h = nn_trajectory_input.get_height();
  input_geometry.d = nn_trajectory_input.get_channels();

  output_geometry.w = 1;
  output_geometry.h = 1;
  output_geometry.d = 3;

  CNN nn(experiment_dir + "trained/cnn_config.json", input_geometry, output_geometry);

  for (unsigned int line = 0; line < initial_conditions->get_lines_count(); line++)
  {
    sDatasetItem item = nn_trajectory_input.create(*initial_conditions, line, 0);

  }
}
