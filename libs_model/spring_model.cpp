#include "spring_model.h"
#include <spring_model_kernel.cuh>

#include <iostream>


SpringModel::SpringModel(unsigned int size, t_num ks, t_num kf, t_num mass)
{
  this->size = size;
  this->ks = ks;
  this->kf = kf;
  this->mass = mass;
  init();
}

SpringModel::~SpringModel()
{

}


void SpringModel::init()
{
  particles.clear();

  for (int z = 0; z < (int)size; z++)
  for (int y = 0; y < (int)size; y++)
  for (int x = 0; x < (int)size; x++)
  {
    t_num z_ = (z*1.0/size - 0.5)*2.0;
    t_num y_ = (y*1.0/size - 0.5)*2.0;
    t_num x_ = (x*1.0/size - 0.5)*2.0;

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

    t_num v = 1.0;

    if (x == 0)
      particle.vx = -v;
    if (x == ((int)size-1))
      particle.vx = v;

/*
    if (y == 0)
      particle.vy = -v;
    if (y == ((int)size-1))
      particle.vy = v;

    if (z == 0)
      particle.vz = -v;
    if (z == ((int)size-1))
      particle.vz = v;
*/

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

  /*
  cuda_spring_model_init(cu_particles, particles);

  for (unsigned int idx = 0; idx < particles.size(); idx++)
  {
    particles[idx].x = 0.0;
    particles[idx].y = 0.0;
    particles[idx].z = 0.0;
  }

  cuda_spring_model_to_host(particles, cu_particles);
  */
}

int SpringModel::to_idx(int x, int y, int z)
{
  if (x < 0)
    return -1;

  if (y < 0)
    return -2;

  if (z < 0)
    return -3;

  if (x >= (int)size)
    return -4;

  if (y >= (int)size)
    return -5;

  if (z >= (int)size)
    return -6;

  int result = (z*size + y)*size + x;

  return result;
}

void SpringModel::compute(t_num Fx, t_num Fy, t_num Fz)
{
  t_num dt = 0.01;

  for (unsigned int idx = 0; idx < particles.size(); idx++)
  {
    float fsx = 0.0;
    float fsy = 0.0;
    float fsz = 0.0;

    for (unsigned int j = 0; j < INTERACTION_POINT_MAX; j++)
    {
      int idx_b = particles[idx].interaction_idx[j];
      if (idx_b >= 0)
      {
        float dx_new = particles[idx].x - particles[idx_b].x;
        float dy_new = particles[idx].y - particles[idx_b].y;
        float dz_new = particles[idx].z - particles[idx_b].z;

        fsx+= dx_new - particles[idx].interaction_idx_dx[j];
        fsy+= dy_new - particles[idx].interaction_idx_dy[j];
        fsz+= dz_new - particles[idx].interaction_idx_dz[j];
      }
    }

    fsx = -fsx*ks;
    fsy = -fsy*ks;
    fsz = -fsz*ks;

    t_num ffx = -kf*particles[idx].vx;
    t_num ffy = -kf*particles[idx].vy;
    t_num ffz = -kf*particles[idx].vz;

    particles[idx].fx = Fx + fsx + ffx;
    particles[idx].fy = Fy + fsy + ffy;
    particles[idx].fz = Fz + fsz + ffz;

    particles[idx].ax = particles[idx].fx/particles[idx].mass;
    particles[idx].ay = particles[idx].fy/particles[idx].mass;
    particles[idx].az = particles[idx].fz/particles[idx].mass;

    particles[idx].vx+= particles[idx].ax*dt;
    particles[idx].vy+= particles[idx].ay*dt;
    particles[idx].vz+= particles[idx].az*dt;

    particles[idx].x+= particles[idx].vx*dt;
    particles[idx].y+= particles[idx].vy*dt;
    particles[idx].z+= particles[idx].vz*dt;
  }
}


void SpringModel::render()
{
  t_num scale = 0.5;
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
    visualisation.paint_sphere(0.02);

    visualisation.pop();
  }

  visualisation.finish();
}
