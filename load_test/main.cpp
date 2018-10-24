#include <iostream>

#include <dat_load.h>
#include <dats_load.h>
#include <glvisualisation.h>

#include <DatasetParticlesMotion.h>

int main()
{
  DatsLoad raw_dataset_training("training.json");
  DatsLoad raw_dataset_testing("testing.json");

  raw_dataset_training.normalise_column();
  raw_dataset_testing.normalise_column();



  DatasetParticlesMotion dataset( raw_dataset_training,
                                  raw_dataset_testing,
                                  "dataset_particles_motion_config.json");


  std::cout << "loading done\n";

  
/*
  GLVisualisation visualisation;

  unsigned int step_training = 0;
  unsigned int step_testing = 0;
  while (1)
  {
    visualisation.start();

    visualisation.translate(0.0, 0.0, -3.0);

    // visualisation.rotate(-60.0, 0.0, 0.0);

    for (unsigned int cell = 0; cell < raw_dataset_training.get_dat_count(); cell++)
    {
      float x = 2.0*raw_dataset_training.get(cell, 1, step_training) - 1.0;
      float y = 2.0*raw_dataset_training.get(cell, 2, step_training) - 1.0;
      float z = 0.1*raw_dataset_training.get(cell, 3, step_training);

      visualisation.push();
      visualisation.set_color(1.0, 0.0, 0.0);
      visualisation.translate(x, y, z);
      visualisation.paint_sphere(0.05);
      visualisation.pop();
    }

    step_training = (step_training + 1)%raw_dataset_training.get_lines_count();


    for (unsigned int cell = 0; cell < raw_dataset_testing.get_dat_count(); cell++)
    {
      float x = 2.0*raw_dataset_testing.get(cell, 1, step_testing) - 1.0;
      float y = 2.0*raw_dataset_testing.get(cell, 2, step_testing) - 1.0;
      float z = 0.1*raw_dataset_testing.get(cell, 3, step_testing);

      visualisation.push();
      visualisation.set_color(0.0, 1.0, 0.0);
      visualisation.translate(x, y, z);
      visualisation.paint_sphere(0.05);
      visualisation.pop();
    }

    visualisation.finish();

    step_testing = (step_testing + 1)%raw_dataset_testing.get_lines_count();
  }
*/
  std::cout << "program done\n";
  return 0;
}
