#include "trajectory_compare.h"
#include <math.h>

TrajectoryCompare::TrajectoryCompare()
{

}

TrajectoryCompare::~TrajectoryCompare()
{

} 

void TrajectoryCompare::process(  std::string file_name_prefix,
                                  std::vector<std::vector<float>> &target,
                                  std::vector<std::vector<float>> &resulted)
{
  h_target.clear();
  h_resulted.clear();
  h_distance.clear();
  h_error.clear();

  l_distance.set_output_file_name(file_name_prefix + "_accumulated_distance.log");

  for (unsigned int j = 0; j < target.size(); j++)
  {
    for (unsigned int i = 0; i < target[j].size(); i++)
      h_target.add(target[j][i]);

    for (unsigned int i = 0; i < resulted[j].size(); i++)
      h_resulted.add(resulted[j][i]);

    float distance = dist(target[j], resulted[j]);
      h_distance.add(distance);

    for (unsigned int i = 0; i < target[j].size(); i++)
    {
      float error = target[j][i] - resulted[j][i];
        h_error.add(error);
    }

    l_distance << j << " " << distance << "\n";
  }

  h_target.compute(101);
  h_resulted.compute(101);
  h_distance.compute(101);
  h_error.compute(101);

  h_target.save(file_name_prefix+"_h_target.log");
  h_resulted.save(file_name_prefix+"_h_resulted.log");
  h_distance.save(file_name_prefix+"_h_distance.log");
  h_error.save(file_name_prefix+"_h_error.log");

  Log l_summary(file_name_prefix + "_summary.log");

  l_summary << "items count = \t" << target.size() << "\n";
  l_summary << "variables count = \t" << target[0].size() << "\n";
  l_summary << "\n";
  l_summary << "target average value = \t" << h_target.get_average() << "\n";
  l_summary << "target min value = \t" << h_target.get_min() << "\n";
  l_summary << "target max value = \t" << h_target.get_max() << "\n";
  l_summary << "\n";
  l_summary << "resulted average value = \t" << h_resulted.get_average() << "\n";
  l_summary << "resulted min value = \t" << h_resulted.get_min() << "\n";
  l_summary << "resulted max value = \t" << h_resulted.get_max() << "\n";
  l_summary << "\n";
  l_summary << "error average value = \t" << h_error.get_average() << "\n";
  l_summary << "error min value = \t" << h_error.get_min() << "\n";
  l_summary << "error max value = \t" << h_error.get_max() << "\n";
  l_summary << "\n";
}


float TrajectoryCompare::dist(std::vector<float> &va, std::vector<float> &vb)
{
  float result = 0.0;
  for (unsigned int i = 0; i < va.size(); i++)
    result+= (va[i] - vb[i])*(va[i] - vb[i]);

  return sqrt(result);
}
