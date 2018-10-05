#include "cuda_particle_allocator.cuh"
#include <iostream>

CudaParticleAllocator cuda_particle_allocator;


CudaParticleAllocator::CudaParticleAllocator()
{

}

CudaParticleAllocator::~CudaParticleAllocator()
{

}

sParticle* CudaParticleAllocator::malloc(unsigned int count)
{
  mutex.lock();

  sParticle *result = nullptr;

  cudaMalloc(&result, count*sizeof(sParticle));

  mutex.unlock();

  clear(result, count);

  return result;
}

void CudaParticleAllocator::free(void *ptr)
{
  mutex.lock();

  if (ptr != nullptr)
  {
    cudaFree(ptr);
    ptr = nullptr;
  }

  mutex.unlock();
}

void CudaParticleAllocator::host_to_device(sParticle *dev_ptr, sParticle *host_ptr, unsigned int size)
{
  cudaMemcpy(dev_ptr, host_ptr, size*sizeof(sParticle), cudaMemcpyHostToDevice);
}

void CudaParticleAllocator::device_to_host(sParticle *host_ptr, sParticle *dev_ptr, unsigned int size)
{
  cudaMemcpy(host_ptr, dev_ptr, size*sizeof(sParticle), cudaMemcpyDeviceToHost);
}

void CudaParticleAllocator::device_to_device(sParticle *dest_ptr, sParticle *src_ptr, unsigned int size)
{
  cudaMemcpy(dest_ptr, src_ptr, size*sizeof(sParticle), cudaMemcpyDeviceToDevice);
}

void CudaParticleAllocator::clear(sParticle *result, unsigned int size)
{
  cudaMemset(result, 0, size*sizeof(sParticle));
}
