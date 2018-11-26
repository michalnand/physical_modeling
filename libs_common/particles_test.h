#ifndef _PARTICLES_TEST_H_
#define _PARTICLES_TEST_H_

#include <vector>
#include <string>
#include <glvisualisation.h>
#include <log.h>

#include "particle.h"


class ParticlesTest
{
  private:
    std::vector<Particle> particles;
    GLVisualisation visualisation;

  public:
    ParticlesTest(unsigned int partices_count);
    virtual ~ParticlesTest();

    void process();
    void render();

  private:
    V3 interraction(unsigned int idx);
};

#endif
