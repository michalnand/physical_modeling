#include <DatasetParticlesMotion.h>

#include <json_config.h>
#include <iostream>

DatasetParticlesMotion::DatasetParticlesMotion( DatsLoad &raw_data_training,
                                                DatsLoad &raw_data_testing,
                                                std::string config_file_name)
                       :DatasetInterface()
{
  NNTrajectoryInput nn_trajectory_input(config_file_name);



  width     = nn_trajectory_input.get_width();
  height    = nn_trajectory_input.get_height();
  channels  = nn_trajectory_input.get_channels();


  training.resize(1);

  create(nn_trajectory_input, raw_data_training, false);
  create(nn_trajectory_input, raw_data_testing, true);


  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
}


void DatasetParticlesMotion::create(NNTrajectoryInput nn_trajectory_input, DatsLoad &raw_data, bool put_to_testing)
{
  for (unsigned int line = 0; line < raw_data.get_lines_count(); line++)
  {
    sDatasetItem item = nn_trajectory_input.create(raw_data, line);

    if (item.input.size() == 0)
      break;
      
    if (item.output.size() == 0)
      break;

    if (put_to_testing)
      add_testing(item);
    else
      add_training_for_regression(item);
  }
}
