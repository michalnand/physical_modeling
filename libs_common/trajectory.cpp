#include "trajectory.h"
#include <log.h>
#include <iostream>

Trajectory::Trajectory()
{

}

Trajectory::Trajectory(unsigned int w, unsigned int h, unsigned int d)
{
  init(w, h, d);
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

void Trajectory::clear()
{
  for (unsigned int k = 0; k < trajectory.size(); k++)
  {
    for (unsigned int j = 0; j < trajectory[k].size(); j++)
      trajectory[k][j].clear();
    trajectory[k].clear();
  }

  trajectory.clear();
}

void Trajectory::init(unsigned int w, unsigned int h, unsigned int d, float value)
{
  clear();

  trajectory.resize(d);

  for (unsigned int k = 0; k < trajectory.size(); k++)
  {
    trajectory[k].resize(h);
    for (unsigned int j = 0; j < trajectory[k].size(); j++)
    {
      trajectory[k][j].resize(w);
      for (unsigned int i = 0; i < trajectory[k][j].size(); i++)
        trajectory[k][j][i] = value;
    }
  }
}

void Trajectory::set(unsigned int x, unsigned int y, unsigned int z, float value)
{
  trajectory[z][y][x] = value;
}

float Trajectory::get(unsigned int x, unsigned int y, unsigned int z)
{
  return trajectory[z][y][x];
}

void Trajectory::print()
{
  for (unsigned int z = 0; z < trajectory.size(); z++)
  {
    for (unsigned int y = 0; y < trajectory[z].size(); y++)
    {
      for (unsigned int x = 0; x < trajectory[z][y].size(); x++)
        std::cout << std::to_string(get(x, y, z)) << " ";
      std::cout << "\n";
    }

    std::cout << "\n";
  }

  std::cout << "\n";
}

void Trajectory::save(std::string file_name_prefix)
{
  for (unsigned int z = 0; z < trajectory.size(); z++)
  {
    std::string file_name = file_name_prefix + "_" + std::to_string(z) + ".log";
    Log log(file_name);

    for (unsigned int y = 0; y < trajectory[z].size(); y++)
    {
      for (unsigned int x = 0; x < trajectory[z][y].size(); x++)
        log << get(x, y, z) << " ";
      log << "\n";
    }
  }
}


void Trajectory::random(unsigned int width, unsigned int height, unsigned int depth, float dt)
{
  init(width, height, depth);

  for (unsigned int z = 0; z < trajectory.size(); z++)
  {
    for (unsigned int y = 1; y < trajectory[z].size(); y++)
      for (unsigned int x = 0; x < trajectory[z][y].size(); x++)
      {
        float v = (rand()%1000000)/1000000.0;
        if (rand()%2)
          v = -v;

        set(x, y, z, get(x, y-1, z) + dt*v);
      }
  }
}
