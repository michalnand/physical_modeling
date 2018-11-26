#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "v3.h"

class Particle
{
  private:
    float dt, mass;
    V3 x, v, a;

  public:
    Particle( V3 x = {0, 0, 0},
              V3 v = {0, 0, 0},
              float mass = 1.0,
              float dt = 0.01);

    Particle(Particle& other);
    Particle(const Particle& other);

    virtual ~Particle();

    Particle& operator= (Particle& other);
    Particle& operator= (const Particle& other);

  protected:
    void copy(Particle& other);
    void copy(const Particle& other);

  public:
    void compute(float fx, float fy, float fz);
    void compute(V3 f);

    void saturate_position(float min = -1.0, float max = 1.0);

  public:
    V3 get_position();
    V3 get_velocity();

    float get_mass()
    {
      return mass;
    }
    
  public:
    V3 distance(Particle &other);

  public:
    void random(float min = -1.0, float max = 1.0);
    void print();

};

#endif
