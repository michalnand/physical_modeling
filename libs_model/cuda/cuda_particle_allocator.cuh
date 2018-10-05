#ifndef _CUDA_PARTICLE_ALLOCATOR_CUH_
#define _CUDA_PARTICLE_ALLOCATOR_CUH_

#include <mutex>
#include "../particle.h"

class CudaParticleAllocator
{
  private:
    std::mutex mutex;

  public:
      CudaParticleAllocator();
      virtual ~CudaParticleAllocator();

      sParticle* malloc(unsigned int count);
      void free(void *ptr);
 

  public:

      void host_to_device(sParticle *dev_ptr, sParticle *host_ptr, unsigned int size);
      void device_to_host(sParticle *host_ptr, sParticle *dev_ptr, unsigned int size);
      void device_to_device(sParticle *dest_ptr, sParticle *src_ptr, unsigned int size);

      void clear(sParticle *result, unsigned int size);
};


extern CudaParticleAllocator cuda_particle_allocator;


#endif
