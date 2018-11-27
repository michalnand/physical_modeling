#include "lorenz.h"
#include <log.h>


Lorenz::Lorenz(unsigned int length, unsigned int count)
{
  this->length = length;
  this->count  = count;
  
  float dt = 0.01;

  for (unsigned int j = 0; j < count; j++)
  {
    float x0 = 10.0*(rand()%100000)/100000.0;
    float y0 = 10.0*(rand()%100000)/100000.0;
    float z0 = 10.0*(rand()%100000)/100000.0;

    V3 input(x0, y0, z0);
    for (unsigned int i = 0; i < length; i++)
    {
      auto dif = compute(input);

      state.push_back(input);
      output.push_back(dif);

      input = input + (dif*dt);
    }
  }

  normalise(state);
  normalise(output);
}

Lorenz::~Lorenz()
{

}

void Lorenz::save(std::string file_name_prefix)
{
  unsigned int ptr = 0;

  for (unsigned int j = 0; j < count; j++)
  {
    std::string file_name = file_name_prefix + std::to_string(j) + ".dat";
    Log log(file_name);

    for (unsigned int i = 0; i < length; i++)
    {
      log << i << " ";

      log << state[ptr].x() << " ";
      log << state[ptr].y() << " ";
      log << state[ptr].z() << " ";

      log << output[ptr].x() << " ";
      log << output[ptr].y() << " ";
      log << output[ptr].z() << " ";

      log << "\n";
      ptr++;
    }
  }
}

V3 Lorenz::compute(V3 &input)
{
  float sigma = 10.0;
  float ro    = 28.0;
  float beta  = 8.0/3.0;

  float dx = sigma*(input.y() - input.x());
  float dy = input.x()*(ro - input.z()) - input.y();
  float dz = input.x()*input.y() - beta*input.z();

  V3 res(dx, dy, dz);

  return res;
}

void Lorenz::normalise(std::vector<V3> &v)
{
  float min_x = v[0].x();
  float min_y = v[0].y();
  float min_z = v[0].z();

  float max_x = v[0].x();
  float max_y = v[0].y();
  float max_z = v[0].z();

  for (unsigned int i = 0; i < v.size(); i++)
  {
    if (v[i].x() > max_x)
      max_x = v[i].x();
    if (v[i].x() < min_x)
      min_x = v[i].x();

    if (v[i].y() > max_y)
      max_y = v[i].y();
    if (v[i].y() < min_y)
      min_y = v[i].y();

    if (v[i].z() > max_z)
      max_z = v[i].z();
    if (v[i].z() < min_z)
      min_z = v[i].z();
  }

  float kx = 0.0;
  float ky = 0.0;
  float kz = 0.0;
  float qx = 0.0;
  float qy = 0.0;
  float qz = 0.0;

  if (max_x > min_x)
  {
    kx = 1.0/(max_x - min_x);
    qx = 1.0 - kx*max_x;
  }

  if (max_y > min_y)
  {
    ky = 1.0/(max_y - min_y);
    qy = 1.0 - ky*max_y;
  }


  if (max_z > min_z)
  {
    kz = 1.0/(max_z - min_z);
    qz = 1.0 - kz*max_z;
  }

  for (unsigned int i = 0; i < v.size(); i++)
  {
    v[i].set_x(kx*v[i].x() + qx);
    v[i].set_y(ky*v[i].y() + qy);
    v[i].set_z(kz*v[i].z() + qz);
  }
}
