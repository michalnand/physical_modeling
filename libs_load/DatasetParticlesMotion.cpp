#include <DatasetParticlesMotion.h>

#include <json_config.h>
#include <iostream>

DatasetParticlesMotion::DatasetParticlesMotion( DatsLoad &raw_data_training,
                                                DatsLoad &raw_data_testing,
                                                std::string config_file_name)
                       :DatasetInterface()
{
  JsonConfig json(config_file_name);

  load_percentage = json.result["inputs parameters"]["load percentage"].asFloat();

  for (unsigned int i = 0; i < json.result["inputs parameters"]["columns to read"].size(); i++)
    input_columns_to_read.push_back(json.result["inputs parameters"]["columns to read"][i].asInt());


  for (unsigned int i = 0; i < json.result["inputs parameters"]["particles to read"].size(); i++)
    input_particles_to_read.push_back(json.result["inputs parameters"]["particles to read"][i].asInt());


  padding             = json.result["inputs parameters"]["padding"].asInt();
  time_window_size   = json.result["inputs parameters"]["time window size"].asInt();
  time_window_stride = json.result["inputs parameters"]["time window stride"].asInt();


  for (unsigned int i = 0; i < json.result["output parameters"]["columns to read"].size(); i++)
    output_columns_to_read.push_back(json.result["output parameters"]["columns to read"][i].asInt());


  prediction_step = json.result["output parameters"]["prediction step"].asInt();

  width   = input_columns_to_read.size() + 2*padding;
  height  = time_window_size             + 2*padding;
  channels= input_particles_to_read.size() + 1;


  training.resize(1);

//  training_size = training[0].size();

  create(raw_data_training, false);
  create(raw_data_testing, true);


  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
}


void DatasetParticlesMotion::create(DatsLoad &raw_data, bool put_to_testing)
{
  for (unsigned int line = 0; line < raw_data.get_lines_count(); line++)
    for (unsigned int particle = 0; particle < input_particles_to_read.size(); particle++)
      if ((rand()%100) < load_percentage)
       if (line < (raw_data.get_lines_count() - (time_window_size+1)*time_window_stride) )
        if (line < raw_data.get_lines_count() - (prediction_step + 1))
        {
          unsigned int top_particle_idx = input_particles_to_read[particle];

          sDatasetItem item;
          item.input  = make_input(top_particle_idx, line, raw_data);
          item.output = make_output(top_particle_idx, line, raw_data);

          if (put_to_testing)
            add_testing(item);
          else
            add_training_for_regression(item);
            //training[0].push_back(item);
        }
}


std::vector<float> DatasetParticlesMotion::make_input(unsigned int top_particle_idx,
                                                      unsigned int line,
                                                      DatsLoad &raw_data)
{
  unsigned int colums_count     = input_columns_to_read.size();
  unsigned int rows_count       = time_window_size;
  unsigned int particles_count  = input_particles_to_read.size();
  unsigned int result_size      = width*height*(particles_count + 1);

  std::vector<float> result(result_size);


  for (unsigned int row = 0; row < rows_count; row++)
  for (unsigned int column = 0; column < colums_count; column++)
  {
    float value = raw_data.get(
                                top_particle_idx,
                                input_columns_to_read[column],
                                row*time_window_stride + line
                              );

    unsigned int idx = input_idx(0, row, column);
    result[idx] = value;
  }

  for (unsigned int particle = 0; particle < particles_count; particle++)
  for (unsigned int row = 0; row < rows_count; row++)
  for (unsigned int column = 0; column < colums_count; column++)
  {
    float value = raw_data.get(
                                input_particles_to_read[particle],
                                input_columns_to_read[column],
                                row*time_window_stride + line
                              );

    unsigned int idx = input_idx(particle+1, row, column);
    result[idx] = value;
  }


  return result;
}


std::vector<float> DatasetParticlesMotion::make_output( unsigned int top_particle_idx,
                                                        unsigned int line,
                                                        DatsLoad &raw_data)
{
  unsigned int otput_size = output_columns_to_read.size();
  std::vector<float> result(otput_size);

  for (unsigned int column = 0; column < otput_size; column++)
  {
    float value = raw_data.get(
                                top_particle_idx,
                                output_columns_to_read[column],
                                prediction_step + line
                              );

    result[column] = value;
  }


  return result;
}


unsigned int DatasetParticlesMotion::input_idx(unsigned int particle, unsigned int row, unsigned int column)
{
  unsigned int result;

  result = (particle*height + row+padding)*width + column + padding;

  return result;
}
