#ifndef _TRAJECTORY_COMPARE_H_
#define _TRAJECTORY_COMPARE_H_

#include <vector>
#include <string>

#include <log.h>
#include <histogram.h>

class TrajectoryCompare
{
  private:

    Histogram h_target;
    Histogram h_resulted;
    Histogram h_distance;
    Histogram h_error;

    Log l_distance;


  public:

    TrajectoryCompare();
    virtual ~TrajectoryCompare();

    void process( std::string file_name_prefix,
                  std::vector<std::vector<float>> &target,
                  std::vector<std::vector<float>> &resulted);

  private:

    float dist(std::vector<float> &va, std::vector<float> &vb);
};


#endif
