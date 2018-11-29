#include <DatasetParticlesMotionRuntime.h>

#include <json_config.h>
#include <iostream>

DatasetParticlesMotionRuntime::DatasetParticlesMotionRuntime( Trajectory &trajectory_training_input,
                                                Trajectory &trajectory_training_output,
                                                Trajectory &trajectory_testing_input,
                                                Trajectory &trajectory_testing_output,
                                                std::string config_file_name)
                       :DatasetInterface()
{
  nn_trajectory_input = NNTrajectorySpatialInput(config_file_name);

  JsonConfig json(config_file_name);

  training_load_percentage = json.result["training load percentage"].asFloat();
  testing_load_percentage  = json.result["training load percentage"].asFloat();

  width     = nn_trajectory_input.get_width();
  height    = nn_trajectory_input.get_height();
  channels  = nn_trajectory_input.get_channels();

  this->trajectory_training_input = &trajectory_training_input;
  this->trajectory_training_output= &trajectory_training_output;

  training.resize(1);

  create(nn_trajectory_input, trajectory_testing_input, trajectory_testing_output, true);

  training_size = training_load_percentage*0.01*(this->trajectory_training_input->get_height()*this->trajectory_training_input->get_depth());
 
  std::cout << "training size = " << training_size << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
/*
  print_testing_item(rand());
  print_training_item();
*/
}

DatasetParticlesMotionRuntime::~DatasetParticlesMotionRuntime()
{

}



void DatasetParticlesMotionRuntime::create(  NNTrajectorySpatialInput &nn_trajectory_input,
                                      Trajectory &trajectory_input,
                                      Trajectory &trajectory_output,
                                      bool put_to_testing)
{
  float p = 0.0;
  if (put_to_testing)
    p = testing_load_percentage/100.0;
  else
    p = training_load_percentage/100.0;

  for (unsigned int line = 0; line < trajectory_input.get_height(); line++)
  for (unsigned int particle = 0; particle < trajectory_input.get_depth(); particle++)
  if (((rand()%10000)/10000.0) < p)
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


unsigned int DatasetParticlesMotionRuntime::get_training_size()
{
  return training_size;
}


unsigned int DatasetParticlesMotionRuntime::get_output_size()
{
  return 3;
}


sDatasetItem DatasetParticlesMotionRuntime::get_random_training()
{
  sDatasetItem result;

  do
  {
    unsigned int line = rand()%trajectory_training_input->get_height();
    unsigned int particle = rand()%trajectory_training_input->get_depth();
    result = nn_trajectory_input.create(  *trajectory_training_input,
                                           *trajectory_training_output,
                                           line, particle);
  }
  while ((result.input.size() == 0) || (result.output.size() == 0));

  return result;
}


void DatasetParticlesMotionRuntime::print_testing_item(unsigned int idx)
{
  idx = idx%testing.size();

  unsigned int id = 0;
  for (unsigned int ch = 0; ch < channels; ch++)
  {
    for (unsigned int y = 0; y < height; y++)
    {
      for (unsigned int x = 0; x < width; x++)
      {
        printf("%2.3f ", testing[idx].input[id]);
        id++;
      }
      printf("\n");
    }
    printf("\n");
  }

  printf("\n");
}


void DatasetParticlesMotionRuntime::print_training_item()
{
  auto item = get_random_training();

  unsigned int id = 0;
  for (unsigned int ch = 0; ch < channels; ch++)
  {
    for (unsigned int y = 0; y < height; y++)
    {
      for (unsigned int x = 0; x < width; x++)
      {
        printf("%2.3f ", item.input[id]);
        id++;
      }
      printf("\n");
    }
    printf("\n");
  }

  printf("\n");
}
