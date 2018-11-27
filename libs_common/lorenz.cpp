#include "lorenz.h"
#include <log.h>


Lorenz::Lorenz(unsigned int length, unsigned int count)
{
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
}

Lorenz::~Lorenz()
{

}

void Lorenz::save(std::string file_name)
{
  Log log(file_name);
  for (unsigned int j = 0; j < state.size(); j++)
  {
    log << j << " ";

    log << state[j].x() << " ";
    log << state[j].y() << " ";
    log << state[j].z() << " ";

    log << output[j].x() << " ";
    log << output[j].y() << " ";
    log << output[j].z() << " ";

    log << "\n";
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
