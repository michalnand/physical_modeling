#include "spring_model_kernel.cuh"

#include <stdio.h>

sParticle* cuda_spring_model_allocate(unsigned int count)
{
  sParticle *result = nullptr;
  auto res = cudaMalloc(&result, count*sizeof(sParticle));

  return result;
}


void cuda_spring_model_init(sParticle *cu_particles, std::vector<sParticle> &particles)
{
  cu_particles = cuda_spring_model_allocate(particles.size());

  auto res = cudaMemcpy(cu_particles, &particles[0], particles.size()*sizeof(sParticle), cudaMemcpyHostToDevice);
}

void cuda_spring_model_to_host(std::vector<sParticle> &particles, sParticle *cu_particles)
{
  cudaMemcpy(&particles[0], cu_particles, particles.size()*sizeof(sParticle), cudaMemcpyDeviceToHost);
} 

void cuda_spring_model_compute(sParticle *cu_particles)
{

}
