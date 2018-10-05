#include "spring_model.h"
#include <iostream>

#include <cuda/spring_model_kernel.cuh>
#include <cuda/cuda_particle_allocator.cuh>

SpringModel::SpringModel(unsigned int size, t_num ks, t_num kf, t_num mass)
{
  this->size = size;
  this->ks = ks;
  this->kf = kf;
  this->mass = mass;
  cu_particles = nullptr;


  this->width  = 20;
  this->height = 8;
  this->depth  = 20;

  init();
}

SpringModel::~SpringModel()
{

}


void SpringModel::init()
{
  particles.clear();


  for (int z = 0; z < (int)depth; z++)
  for (int y = 0; y < (int)height; y++)
  for (int x = 0; x < (int)width; x++)
  {
    t_num z_ = 1.4*(z*1.0/depth - 0.5)*2.0;
    t_num y_ = 0.3*(y*1.0/height - 0.5)*2.0;
    t_num x_ = 1.4*(x*1.0/width - 0.5)*2.0;

    sParticle particle;

    particle.fx = 0.0;
    particle.fy = 0.0;
    particle.fz = 0.0;

    particle.fsx = 0.0;
    particle.fsy = 0.0;
    particle.fsz = 0.0;

    particle.mass = mass;

    particle.ax = 0.0;
    particle.ay = 0.0;
    particle.az = 0.0;

    particle.vx = 0.0;
    particle.vy = 0.0;
    particle.vz = 0.0;




    int xc = width/2;
    int yc = height/2;
    int zc = depth/2;


    if ((x == xc)&&(y == (height-1) )&&(z == zc))
      particle.vy = 8;


    particle.x = x_;
    particle.y = y_;
    particle.z = z_;


    for (unsigned int i = 0; i < INTERACTION_POINT_MAX; i++)
      particle.interaction_idx[i] = -10000;

    particle.interaction_idx[0] = to_idx(x-1, y, z);
    particle.interaction_idx[1] = to_idx(x+1, y, z);
    particle.interaction_idx[2] = to_idx(x, y-1, z);
    particle.interaction_idx[3] = to_idx(x, y+1, z);
    particle.interaction_idx[4] = to_idx(x, y, z+1);
    particle.interaction_idx[5] = to_idx(x, y, z-1);

    particles.push_back(particle);
  }


  for (unsigned int idx = 0; idx < particles.size(); idx++)
  {
    for (unsigned int j = 0; j < INTERACTION_POINT_MAX; j++)
    {
      int idx_b = particles[idx].interaction_idx[j];
      if (idx_b >= 0)
      {
        particles[idx].interaction_idx_dx[j] = particles[idx].x - particles[idx_b].x;
        particles[idx].interaction_idx_dy[j] = particles[idx].y - particles[idx_b].y;
        particles[idx].interaction_idx_dz[j] = particles[idx].z - particles[idx_b].z;
      }
    }
  }


  #ifdef _PARTICLES_USE_CUDA_
    cu_particles = cuda_particle_allocator.malloc(particles.size());
    cuda_particle_allocator.host_to_device(cu_particles, &particles[0], particles.size());
    cuda_particle_allocator.device_to_host(&particles[0], cu_particles, particles.size());
  #else
    cu_particles = nullptr;
  #endif
}

int SpringModel::to_idx(int x, int y, int z)
{
  if (x < 0)
    return -1;

  if (y < 0)
    return -2;

  if (z < 0)
    return -3;

  if (x >= (int)width)
    return -4;

  if (y >= (int)height)
    return -5;

  if (z >= (int)depth)
    return -6;

  int result = (z*height + y)*width + x;

  return result;
}

void SpringModel::compute(t_num Fx, t_num Fy, t_num Fz)
{
  t_num dt = 0.01;

  #ifdef _PARTICLES_USE_CUDA_
    particles_kernel(cu_particles, dt, particles.size());
  #else
    particles_kernel(&particles[0], dt, particles.size());
  #endif
}


void SpringModel::render()
{
  #ifdef _PARTICLES_USE_CUDA_

    cuda_particle_allocator.device_to_host(&particles[0], cu_particles, particles.size());

  #endif

  t_num scale = 0.75;
  visualisation.start();

  visualisation.translate(0.0, 0.0, -3.0);
  visualisation.rotate(40.0, 10.0, 0.0);


  for (unsigned int i = 0; i < particles.size(); i++)
  {
    visualisation.push();
    visualisation.set_color(1.0, 1.0, 1.0);

    for (unsigned int j = 0; j < INTERACTION_POINT_MAX; j++)
    {
      int idx = particles[i].interaction_idx[j];
      if (idx < 0)
        continue;

      t_num x0 = particles[i].x;
      t_num y0 = particles[i].y;
      t_num z0 = particles[i].z;

      t_num x1 = particles[idx].x;
      t_num y1 = particles[idx].y;
      t_num z1 = particles[idx].z;

      visualisation.paint_line(scale*x0, scale*y0, scale*z0,
                               scale*x1, scale*y1, scale*z1);
    }

    visualisation.pop();
  }

  for (unsigned int i = 0; i < particles.size(); i++)
  {
    visualisation.push();

    visualisation.set_color(1.0, 0.0, 0.0);
    visualisation.translate(scale*particles[i].x, scale*particles[i].y, scale*particles[i].z);
    visualisation.paint_sphere(0.01);

    visualisation.pop();
  }

  visualisation.finish();
}
