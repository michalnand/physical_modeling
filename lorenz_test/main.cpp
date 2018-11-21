#include <iostream>
#include <lorenz96.h>
#include <log.h>
#include <trajectory_compare.h>

int main()
{
  unsigned int iterations_count = 5000;
  unsigned int variables_count = 10;

  std::vector<std::vector<float>> target_trajectory;
  {
    Log log("result/target_trajectory.log");

    Lorenz96 lorenz96(variables_count);
    lorenz96.set_random_initial_conditions(0.01);

    for (unsigned int iteration = 0; iteration < iterations_count; iteration++)
    {
      lorenz96.next(0.1);

      target_trajectory.push_back(lorenz96.get_x());

      log << iteration << " ";

      for (unsigned int i = 0; i < variables_count; i++)
        log << lorenz96.get_x()[i] << " ";
      log << "\n";
    }
  }


  std::vector<std::vector<float>> resulted_trajectory;
  {
    Log log("result/resulted_trajectory.log");

    Lorenz96 lorenz96(variables_count);
    lorenz96.set_random_initial_conditions(0.01);

    for (unsigned int iteration = 0; iteration < iterations_count; iteration++)
    {
      lorenz96.next(0.1);

      resulted_trajectory.push_back(lorenz96.get_x());

      log << iteration << " ";

      for (unsigned int i = 0; i < variables_count; i++)
        log << lorenz96.get_x()[i] << " ";
      log << "\n";
    }
  }

  TrajectoryCompare compare;
  compare.process("result/compared", target_trajectory, resulted_trajectory);

  std::cout << "program done\n";
  return 0;
}
