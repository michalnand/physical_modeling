#include "lorenz96.h"
#include <math.h>
#include <iostream>

Lorenz96::Lorenz96(unsigned int variables_count)
{
  x   = const_vector(variables_count, 1.0);
  dif = const_vector(variables_count, 0.0);
}

Lorenz96::~Lorenz96()
{

}

void Lorenz96::set_initial_conditions(std::vector<float> &x_initial)
{
  for (unsigned int i = 0; i < x.size(); i++)
    x[i] = x_initial[i];
}

void Lorenz96::set_random_initial_conditions(float range)
{
  auto noise = random_vector(x.size(), range);
  for (unsigned int i = 0; i < x.size(); i++)
    x[i]+= noise[i];
}

void Lorenz96::next(float dt)
{
  float f = 0.1;
  dif = compute_dif(x);
  apply_dif(x, dif, dt);

  for (unsigned int i = 0; i < x.size(); i++)
    x[i]+= f;
}

std::vector<float>& Lorenz96::get_x()
{
  return x;
}

std::vector<float>& Lorenz96::get_dif()
{
  return dif;
}

std::vector<float> Lorenz96::random_vector(unsigned int size, float range)
{
  std::vector<float> result(size);

  for (unsigned int i = 0; i < size; i++)
  {
    float v = (rand()%100000)/100000.0;
    if ((rand()%2) == 0)
      v = -v;
    result[i] = range*v;
  }

  return result;
}

std::vector<float> Lorenz96::const_vector(unsigned int size, float value)
{
  std::vector<float> result(size);

  for (unsigned int i = 0; i < size; i++)
    result[i] = value;

  return result;
}



std::vector<float> Lorenz96::compute_dif(std::vector<float> &x)
{
  unsigned int N = x.size();
  std::vector<float> result(N);

  result[0]   = (x[1] - x[N-2]) * x[N-1] - x[0];
  result[1]   = (x[2] - x[N-1]) * x[0]- x[1];
  result[N-1] = (x[0] - x[N-3]) * x[N-2] - x[N-1];

  for (unsigned int i = 2; i < (N-1); i++)
    result[i] = (x[i+1] - x[i-2]) * x[i-1] - x[i];


  return result;
}


void Lorenz96::apply_dif(std::vector<float> &x, std::vector<float> &dif, float dt)
{
  for (unsigned int i = 0; i < x.size(); i++)
    x[i]+= dif[i]*dt;
}
