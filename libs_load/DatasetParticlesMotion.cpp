#include <DatasetParticlesMotion.h>

#include <json_config.h>
#include <iostream>

DatasetParticlesMotion::DatasetParticlesMotion( DatsLoad &raw_data_training,
                                                DatsLoad &raw_data_testing,
                                                std::string config_file_name)
                       :DatasetInterface()
{
  //NNTrajectoryInput nn_trajectory_input(config_file_name);

  NNTrajectorySpatialInput nn_trajectory_input(config_file_name);



  width     = nn_trajectory_input.get_width();
  height    = nn_trajectory_input.get_height();
  channels  = nn_trajectory_input.get_channels();


  training.resize(1);

  create(nn_trajectory_input, raw_data_training, false);
  create(nn_trajectory_input, raw_data_testing, true);


  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
/*
  for (unsigned int i = 0; i < 10; i++)
    print_testing_item(rand());
*/
}


void DatasetParticlesMotion::create(NNTrajectorySpatialInput nn_trajectory_input, DatsLoad &raw_data, bool put_to_testing)
{
  for (unsigned int line = 0; line < raw_data.get_lines_count(); line++)
  for (unsigned int particle = 0; particle < raw_data.get_dat_count(); particle++)
  {
    sDatasetItem item = nn_trajectory_input.create(raw_data, line, particle);

    if (item.input.size() != 0)
    if (item.output.size() != 0)
    {
      if (put_to_testing)
        add_testing(item);
      else
        add_training_for_regression(item);
    }  
  }
}

void DatasetParticlesMotion::print_testing_item(unsigned int idx)
{
  idx = idx%testing.size();

  unsigned int id = 0;
  for (unsigned int ch = 0; ch < channels; ch++)
  {
    for (unsigned int y = 0; y < height; y++)
    {
      for (unsigned int x = 0; x < width; x++)
      {
        /*
        if (testing[idx].input[id] > 0.0)
          printf("* ");
        else
          printf(". ");
        */
        printf("%2.3f ", testing[idx].input[id]);
        id++;
      }
      printf("\n");
    }
    printf("\n");
  }

  printf("\n");
}
