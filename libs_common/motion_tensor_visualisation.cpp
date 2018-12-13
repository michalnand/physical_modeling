#include "motion_tensor_visualisation.h"

MotionTensorVisualisation::MotionTensorVisualisation()
{
  time_idx = 0;

  unsigned int width  = 800;
  unsigned int height = 800;
  visualisation.init("visualisation", width, height);
}

MotionTensorVisualisation::~MotionTensorVisualisation()
{

}

void MotionTensorVisualisation::start()
{
  visualisation.start();
}

void MotionTensorVisualisation::render( MotionTensor &motion_tensor,
                                        float r, float g, float b,
                                        unsigned int min, unsigned int max)
{
  visualisation.push();
  visualisation.translate(0.0, 0.0, -3.0);

  unsigned int step = 100;

  float k = 2.0;
  float q = -1.0;

  unsigned int max_range = (motion_tensor.height()-step);

  if (max > max_range)
    max = max_range;

  if (max == 0)
    max = max_range;

  for (unsigned int y = 0; y < max_range; y+= step)
  for (unsigned int particle = 0; particle < motion_tensor.depth(); particle++)
  {
    float x0 = motion_tensor.get(0, y, particle);
    float y0 = motion_tensor.get(1, y, particle);
    float z0 = 0.5;

    float x1 = motion_tensor.get(0, y + step, particle);
    float y1 = motion_tensor.get(1, y + step, particle);
    float z1 = 0.5;

    float r_ = r*0.5;
    float g_ = g*0.5;
    float b_ = b*0.5;

    /*
    if ( (y >= min) && (y <= max) )
    {
      r_ = 1.0;
      g_ = 1.0;
      b_ = 1.0;
    }
    */
   
    visualisation.push();


      visualisation.set_color(r_, g_, b_);
      visualisation.paint_line(x0*k + q, y0*k + q, z0*k + q, x1*k + q, y1*k + q, z1*k + q);

    visualisation.pop();
  }

  unsigned int idx = time_idx%motion_tensor.height();

  for (unsigned int particle = 0; particle < motion_tensor.depth(); particle++)
  {
    float x = motion_tensor.get(0, idx, particle);
    float y = motion_tensor.get(1, idx, particle);
    float z = 0.5;

    visualisation.push();

      visualisation.translate(x*k + q, y*k + q, z*k + q);
      visualisation.set_color(r, g, b);
      visualisation.paint_sphere(0.01);

    visualisation.pop();
  }

  visualisation.pop();
}

void MotionTensorVisualisation::finish()
{
  visualisation.finish();
  time_idx+=5;
}
