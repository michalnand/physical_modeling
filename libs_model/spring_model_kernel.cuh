#ifndef _SPRING_MODEL_KERNEL_CUH_
#define _SPRING_MODEL_KERNEL_CUH_

#include <particle.h>
#include <vector>

void cuda_spring_model_init(sParticle *cu_particles, std::vector<sParticle> &particles);
void cuda_spring_model_to_host(std::vector<sParticle> &particles, sParticle *cu_particles);
void cuda_compute(sParticle *cu_particles);

#endif
