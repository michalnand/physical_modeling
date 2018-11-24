#ifndef _DATS_TO_TRAJECTORY_H_
#define _DATS_TO_TRAJECTORY_H_

#include <trajectory.h>
#include <dats_load.h>

class DatsToTrajectory
{
  private:
    Trajectory trajectory_input;
    Trajectory trajectory_output;

  public:
    DatsToTrajectory();
    DatsToTrajectory(DatsLoad &raw_data, std::string config_file_name);

    DatsToTrajectory(DatsToTrajectory& other);
    DatsToTrajectory(const DatsToTrajectory& other);

    virtual ~DatsToTrajectory();

    DatsToTrajectory& operator= (DatsToTrajectory& other);
    DatsToTrajectory& operator= (const DatsToTrajectory& other);

  protected:
    void copy(DatsToTrajectory& other);
    void copy(const DatsToTrajectory& other);

  public:
    Trajectory& get_trajectory_input()
    {
      return trajectory_input;
    }

    Trajectory& get_trajectory_output()
    {
      return trajectory_output;
    }
};

#endif
