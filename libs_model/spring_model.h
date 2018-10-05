#ifndef _SPRING_MODEL_H_
#define _SPRING_MODEL_H_

#include <vector>
#include <glvisualisation.h>
#include <particle.h>



class SpringModel
{
  protected:
    unsigned int size;
    t_num ks, kf;
    t_num mass;

    std::vector<sParticle> particles;

    sParticle *cu_particles;

  protected:
    GLVisualisation visualisation;

  public:
    SpringModel(unsigned int size, t_num ks, t_num kf, t_num mass);
    ~SpringModel();

    void compute(t_num Fx, t_num Fy, t_num Fz);
    void render();


  protected:
    void init();
    int to_idx(int x, int y, int z);

};

#endif
