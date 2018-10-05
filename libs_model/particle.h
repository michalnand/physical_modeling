#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#define INTERACTION_POINT_MAX ((unsigned int)10)

#define _PARTICLES_USE_CUDA_ 1
 
typedef float t_num;

struct sParticle
{
  t_num fx, fy, fz;
  t_num fsx, fsy, fsz;

  t_num mass;
  t_num ax, ay, az;
  t_num vx, vy, vz;
  t_num x, y, z;

  int interaction_idx[INTERACTION_POINT_MAX];

  t_num interaction_idx_dx[INTERACTION_POINT_MAX];
  t_num interaction_idx_dy[INTERACTION_POINT_MAX];
  t_num interaction_idx_dz[INTERACTION_POINT_MAX];
};


#endif
