#ifndef _MOTION_TENSOR_VISUALISATION_H_
#define _MOTION_TENSOR_VISUALISATION_H_

#include <motion_tensor.h>
#include <glvisualisation.h>

class MotionTensorVisualisation
{
  private:
    unsigned int time_idx;
    GLVisualisation visualisation;

  public:
    MotionTensorVisualisation();
    virtual ~MotionTensorVisualisation();

    void start();
    void render(  MotionTensor &motion_tensor,
                  float r, float g, float b,
                  unsigned int min = 0, unsigned int max = 0
                );
    void finish();
};

#endif
