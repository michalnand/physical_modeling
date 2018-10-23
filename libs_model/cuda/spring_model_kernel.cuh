#ifndef _SPRING_MODEL_KERNEL_CUH_
#define _SPRING_MODEL_KERNEL_CUH_

#include <particle.h>
#include <vector>


void cuda_compute(sParticle *cu_particles);


void particles_kernel(sParticle *particles, t_num dt, unsigned int size);

#endif
