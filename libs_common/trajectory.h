#ifndef _TRAJECTORY_H_
#define _TRAJECTORY_H_

#include <vector>
#include <string>

class Trajectory
{
  private:
    std::vector<std::vector<float>> trajectory;

  public:
    Trajectory();
    Trajectory(Trajectory& other);
    Trajectory(const Trajectory& other);

    virtual ~Trajectory();
    Trajectory& operator= (Trajectory& other);
    Trajectory& operator= (const Trajectory& other);

  protected:
    void copy(Trajectory& other);
    void copy(const Trajectory& other);

  public:
    void add(std::vector<float> &value);
    void clear();

    unsigned int dim();
    unsigned int size();

    std::vector<std::vector<float>>& get();
    std::vector<float>& get_line(unsigned int idx);


    void print();
    void save(std::string file_name);

  public:
    void random(unsigned int length, unsigned int dim = 3, float dt = 0.001);
    std::string asString(unsigned int idx);
    void print(unsigned int idx);

};

#endif
