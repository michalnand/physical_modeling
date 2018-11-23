#include "trajectory.h"
#include <log.h>
#include <iostream>

Trajectory::Trajectory()
{

}

Trajectory::Trajectory(Trajectory& other)
{
  copy(other);
}

Trajectory::Trajectory(const Trajectory& other)
{
  copy(other);
}

Trajectory::~Trajectory()
{

}

Trajectory& Trajectory::operator= (Trajectory& other)
{
  copy(other);

  return *this;
}

Trajectory& Trajectory::operator= (const Trajectory& other)
{
  copy(other);

  return *this;
}

void Trajectory::copy(Trajectory& other)
{
  trajectory = other.trajectory;
}

void Trajectory::copy(const Trajectory& other)
{
  trajectory = other.trajectory;
}

void Trajectory::add(std::vector<float> &value)
{
  trajectory.push_back(value);
}

void Trajectory::clear()
{
  for (unsigned int i = 0; i < trajectory.size(); i++)
    trajectory[i].clear();
  trajectory.clear();
}


unsigned int Trajectory::dim()
{
  return trajectory[0].size();
}

unsigned int Trajectory::size()
{
  return trajectory.size();
}

std::vector<std::vector<float>>& Trajectory::get()
{
  return trajectory;
}

std::vector<float>& Trajectory::get_line(unsigned int idx)
{
  return trajectory[idx];
}

void Trajectory::print()
{
  for (unsigned int j = 0; j < size(); j++)
    print(j);
}


void Trajectory::save(std::string file_name)
{
  Log log(file_name);
  for (unsigned int j = 0; j < size(); j++)
  {
    auto tmp = asString(j);
    log << j << " ";
    log << tmp;
    log << "\n";
  }
}



void Trajectory::random(unsigned int length, unsigned int dim, float dt)
{
  clear();

  std::vector<float> dif(dim);
  std::vector<float> position(dim);
  for (unsigned int i = 0; i < position.size(); i++)
    position[i] = 0.0;

  for (unsigned int j = 0; j < length; j++)
  {
    for (unsigned int i = 0; i < dif.size(); i++)
    {
      float v = (rand()%100000)/100000.0;
      if (rand()%2)
        v = -v;
      dif[i] = v;
    }

    trajectory.push_back(position);

    for (unsigned int i = 0; i < dif.size(); i++)
      position[i]+= dif[i]*dt;
  }
}

std::string Trajectory::asString(unsigned int idx)
{
  std::string result;
  for (unsigned int i = 0; i < trajectory[idx].size(); i++)
    result+= std::to_string(trajectory[idx][i]) + " ";

  return result;
}

void Trajectory::print(unsigned int idx)
{
  std::cout << asString(idx) << "\n";
}
