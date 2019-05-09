#include "motion_tensor_visualisation.h"
#include <math.h>

MotionTensorVisualisation::MotionTensorVisualisation(unsigned int points_max_count)
{
  time_idx = 0;

  m_new_loop = false;

  unsigned int width  = 800;
  unsigned int height = 800;
  this->points_max_count = points_max_count;
  visualisation.init("visualisation", width, height);
}

MotionTensorVisualisation::~MotionTensorVisualisation()
{

}

void MotionTensorVisualisation::start()
{
  visualisation.start();

  visualisation.push();

  visualisation.translate(0.0, 0.0, -6.0);
  visualisation.set_color(1.0, 1.0, 1.0);
  visualisation.paint_square(20.0);

  visualisation.pop();
}



void MotionTensorVisualisation::render( MotionTensor &motion_tensor,
                                        float r, float g, float b,
                                        unsigned int view_mode,
                                        unsigned int min, unsigned int max
                                        )
{
    visualisation.push();
    visualisation.translate(0.0, 0.0, -3.0);

    switch (view_mode%3)
    {
        case 0: render_raw(motion_tensor, r, g, b, min, max); break;
        case 1: {
                    visualisation.push();
                        visualisation.rotate(-70.0, 0.0, 0.0);
                        visualisation.rotate(0.0, 0.0, 90.0);
                        render_raw(motion_tensor, r, g, b, min, max);
                    visualisation.pop();
                }
                break;

        case 2: {
                    visualisation.push();
                    visualisation.rotate(-85.0, 0.0, 0.0);
                    render_raw(motion_tensor, r, g, b, min, max);
                    visualisation.pop();
                }
                break;
    }

    visualisation.pop();
}

void MotionTensorVisualisation::render_raw( MotionTensor &motion_tensor,
                                            float r, float g, float b,
                                            unsigned int min, unsigned int max)
{
	
      unsigned int step = 1; 

	if (points_max_count > 0)
		step =	motion_tensor.height()/points_max_count;
	
	if (step < 1)
	        step = 1;

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

        float r_ = r;
        float g_ = g;
        float b_ = b;


        if (y < min)
        {
          r_ = 0.0;
          g_ = 0.0;
          b_ = 0.0;
        }

        float dx = x1 - x0;
        float dy = y1 - y0;
        float dz = z1 - z0;

        float dif_limit = 0.5;

        if ((fabs(dx) < dif_limit) && (fabs(dy) < dif_limit) && (fabs(dz) < dif_limit))
        {
            visualisation.push();


              visualisation.set_color(r_, g_, b_);
              visualisation.paint_line( scale_x(x0),
                                        scale_y(y0),
                                        scale_z(z0),

                                        scale_x(x1),
                                        scale_y(y1),
                                        scale_z(z1));


            visualisation.pop();
        }
      }

      unsigned int idx = time_idx%max_range;

      for (unsigned int particle = 0; particle < motion_tensor.depth(); particle++)
      {
        float x = motion_tensor.get(0, idx, particle);
        float y = motion_tensor.get(1, idx, particle);
        float z = 0.5;

        visualisation.push();

          visualisation.translate(scale_x(x), scale_y(y), scale_z(z));
          visualisation.set_color(r, g, b);
          visualisation.paint_sphere(0.01);

        visualisation.pop();
      }

        if ((time_idx+10)%20000 == 0)
            m_new_loop = true;
        else
            m_new_loop = false;

}

void MotionTensorVisualisation::finish()
{
  visualisation.finish();
  time_idx+= 10;
}

bool MotionTensorVisualisation::new_loop()
{
    return m_new_loop;
}


float MotionTensorVisualisation::scale_x(float v)
{
    return v*2.0 - 1.0;
}

float MotionTensorVisualisation::scale_y(float v)
{
    return v*2.0 - 1.0;
}

float MotionTensorVisualisation::scale_z(float v)
{
    return v*2.0 - 1.0;
}
