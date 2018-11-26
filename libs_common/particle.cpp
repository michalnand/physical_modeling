#include "particle.h"
#include <iostream>

Particle::Particle(V3 x, V3 v, float mass, float dt)
{
  this->x   = x;
  this->v   = v;

  this->a.zero();

  this->mass  = mass;
  this->dt    = dt;
}

Particle::Particle(Particle& other)
{
  copy(other);
}

Particle::Particle(const Particle& other)
{
  copy(other);
}

Particle::~Particle()
{

}

Particle& Particle::operator= (Particle& other)
{
  copy(other);
  return *this;
}

Particle& Particle::operator= (const Particle& other)
{
  copy(other);
  return *this;
}


void Particle::copy(Particle& other)
{
  dt    = other.dt;
  mass  = other.mass;
  x     = other.x;
  v     = other.v;
  a     = other.a;
}

void Particle::copy(const Particle& other)
{
  dt    = other.dt;
  mass  = other.mass;
  x     = other.x;
  v     = other.v;
  a     = other.a;
}

void Particle::compute(float fx, float fy, float fz)
{
  V3 f;

  f.set(fx, fy, fz);

  compute(f);
}

void Particle::compute(V3 f)
{
  a = f/mass;
  v = v + a*dt;
  x = x + v*dt;
}

void Particle::saturate_position(float min, float max)
{
  x.saturate(min, max);
}

V3 Particle::get_position()
{
  return x;
}

V3 Particle::get_velocity()
{
  return v;
}


V3 Particle::distance(Particle &other)
{
  auto tmp = other.get_position();
  auto res = x - tmp;
  return res;
}

void Particle::random(float min, float max)
{
  a.random(0, 0);
  v.random(0, 0);
  x.random(min, max);

  this->mass = 1.0;
  this->dt   = 0.0001;
}

void Particle::print()
{
  std::cout << "x = ";
  x.print();
  std::cout << "\n";

  std::cout << "v = ";
  v.print();
  std::cout << "\n";

  std::cout << "a = ";
  a.print();
  std::cout << "\n";
}
