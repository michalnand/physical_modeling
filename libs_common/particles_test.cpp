#include "particles_test.h"
#include <math.h>

ParticlesTest::ParticlesTest(unsigned int partices_count)
{
  particles.resize(partices_count);

  for (unsigned int i = 0; i < particles.size(); i++)
    particles[i].random();


  for (unsigned int i = 0; i < particles.size(); i++)
    particles[i].print();

}

ParticlesTest::~ParticlesTest()
{

}

void ParticlesTest::process()
{
  for (unsigned int i = 0; i < particles.size(); i++)
  {
    V3 interraction_force = interraction(i);

    particles[i].compute(interraction_force);
    particles[i].saturate_position(-4.0, 4.0);
  }
}

void ParticlesTest::render()
{
  visualisation.start();

  visualisation.translate(0.0, 0.0, -3.0);



  for (unsigned int i = 0; i < particles.size(); i++)
  {
    auto pos = particles[i].get_position();

    float k = 0.8;
    float x = pos.x()*k;
    float y = pos.y()*k;
    float z = pos.z()*k;

    visualisation.push();

    visualisation.set_color(1.0, 1.0, 1.0);
    visualisation.translate(x, y, z);
    visualisation.paint_sphere(0.01);

    visualisation.pop();
  }

  visualisation.finish();
}

V3 ParticlesTest::interraction(unsigned int idx)
{
  V3 result;
  for (unsigned int i = 0; i < particles.size(); i++)
    if (i != idx)
    {
      V3 r_ = (particles[idx].get_position() - particles[i].get_position());
      float r = pow(r_.size(), 3.0);
      if (r < 0.001)
        r = 0.001;

      V3 force = r_*(particles[idx].get_mass()*particles[i].get_mass()/r);
      result = result - force;
    }

  return result;
}
