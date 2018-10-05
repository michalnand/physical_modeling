#include "spring_model_kernel.cuh"


__global__
void cuda_particles_kernel(sParticle *particles, t_num dt, unsigned int size)
{
    unsigned int idx = threadIdx.x + blockIdx.x*blockDim.x;
    if (idx < size)
    {
      t_num Fx = 0.0;
      t_num Fy = 0.0;
      t_num Fz = 0.0;

      t_num ks = 2.0;
      t_num kf = 0.1;

      t_num fsx = 0.0;
      t_num fsy = 0.0;
      t_num fsz = 0.0;

      sParticle particle = particles[idx];

      for (unsigned int j = 0; j < INTERACTION_POINT_MAX; j++)
      {
        int idx_b = particle.interaction_idx[j];
        if (idx_b >= 0)
        {
          t_num dx_new = particle.x - particles[idx_b].x;
          t_num dy_new = particle.y - particles[idx_b].y;
          t_num dz_new = particle.z - particles[idx_b].z;

          fsx+= dx_new - particle.interaction_idx_dx[j];
          fsy+= dy_new - particle.interaction_idx_dy[j];
          fsz+= dz_new - particle.interaction_idx_dz[j];
        }
      }

      fsx = -fsx*ks;
      fsy = -fsy*ks;
      fsz = -fsz*ks;

      t_num ffx = -kf*particle.vx;
      t_num ffy = -kf*particle.vy;
      t_num ffz = -kf*particle.vz;

      particle.fx = Fx + fsx + ffx;
      particle.fy = Fy + fsy + ffy;
      particle.fz = Fz + fsz + ffz;

      particle.ax = particle.fx/particle.mass;
      particle.ay = particle.fy/particle.mass;
      particle.az = particle.fz/particle.mass;

      particle.vx+= particle.ax*dt;
      particle.vy+= particle.ay*dt;
      particle.vz+= particle.az*dt;

      particle.x+= particle.vx*dt;
      particle.y+= particle.vy*dt;
      particle.z+= particle.vz*dt;

      particles[idx] = particle;
    }
}

__host__
void cpu_particles_kernel(sParticle *particles, t_num dt, unsigned int size)
{
    for (unsigned int idx = 0; idx < size; idx++)
    {
      t_num Fx = 0.0;
      t_num Fy = 0.0;
      t_num Fz = 0.0;

      t_num ks = 1.0;
      t_num kf = 0.1;

      t_num fsx = 0.0;
      t_num fsy = 0.0;
      t_num fsz = 0.0;

      for (unsigned int j = 0; j < INTERACTION_POINT_MAX; j++)
      {
        int idx_b = particles[idx].interaction_idx[j];
        if (idx_b >= 0)
        {
          t_num dx_new = particles[idx].x - particles[idx_b].x;
          t_num dy_new = particles[idx].y - particles[idx_b].y;
          t_num dz_new = particles[idx].z - particles[idx_b].z;

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

void particles_kernel(sParticle *particles, t_num dt, unsigned int size)
{
  #ifdef _PARTICLES_USE_CUDA_
    dim3 block(32);
    dim3 grid((size + block.x - 1)/block.x);

    cuda_particles_kernel<<<grid, block>>>(particles, dt, size);
    cudaDeviceSynchronize();
  #else
    cpu_particles_kernel(particles, dt, size);
  #endif
}
