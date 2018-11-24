#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include <vector>
#include <string>

class Trajectory
{
  private:
    std::vector<std::vector<std::vector<float>>> trajectory;

  public:
    Trajectory();
    Trajectory(unsigned int w, unsigned int h, unsigned int d);
    Trajectory(Trajectory& other);
    Trajectory(const Trajectory& other);

    virtual ~Trajectory();
    Trajectory& operator= (Trajectory& other);
    Trajectory& operator= (const Trajectory& other);

  protected:
    void copy(Trajectory& other);
    void copy(const Trajectory& other);

  public:
    void init(unsigned int w, unsigned int h, unsigned int d, float value = 0.0);
    void clear();

    unsigned int get_width()
    {
      return trajectory[0][0].size();
    }

    unsigned int get_height()
    {
      return trajectory[0].size();
    }

    unsigned int get_depth()
    {
      return trajectory.size();
    }

    void set(unsigned int x, unsigned int y, unsigned int z, float value);
    float get(unsigned int x, unsigned int y, unsigned int z);

  public:
    void print();
    void save(std::string file_name_prefix);

    void random(unsigned int width, unsigned int height, unsigned int depth, float dt = 0.001);

};

#endif
