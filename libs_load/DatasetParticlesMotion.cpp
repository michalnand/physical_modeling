#include <DatasetParticlesMotion.h>

#include <json_config.h>
#include <iostream>

DatasetParticlesMotion::DatasetParticlesMotion( Trajectory &trajectory_training_input,
                                                Trajectory &trajectory_training_output,
                                                Trajectory &trajectory_testing_input,
                                                Trajectory &trajectory_testing_output,
                                                std::string config_file_name)
                       :DatasetInterface()
{
  NNTrajectorySpatialInput nn_trajectory_input(config_file_name);

  width     = nn_trajectory_input.get_width();
  height    = nn_trajectory_input.get_height();
  channels  = nn_trajectory_input.get_channels();


  training.resize(1);

  create(nn_trajectory_input, trajectory_training_input, trajectory_training_output, false);
  create(nn_trajectory_input, trajectory_testing_input, trajectory_testing_output, true);

  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();

/*
  for (unsigned int i = 0; i < 10; i++)
    print_testing_item(rand());
*/
}

DatasetParticlesMotion::~DatasetParticlesMotion()
{

}


void DatasetParticlesMotion::create(  NNTrajectorySpatialInput nn_trajectory_input,
                                      Trajectory &trajectory_input,
                                      Trajectory &trajectory_output,
                                      bool put_to_testing)
{
  for (unsigned int line = 0; line < trajectory_input.get_height(); line++)
  for (unsigned int particle = 0; particle < trajectory_input.get_depth(); particle++)
  {
    sDatasetItem item = nn_trajectory_input.create(trajectory_input, trajectory_output, line, particle);

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
