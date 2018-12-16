#ifndef _MOTION_TENSOR_VISUALISATION_H_
#define _MOTION_TENSOR_VISUALISATION_H_

#include <motion_tensor.h>
#include <glvisualisation.h>

class MotionTensorVisualisation
{
    private:
        unsigned int time_idx;
        bool m_new_loop;
        GLVisualisation visualisation;

    public:
        MotionTensorVisualisation();
        virtual ~MotionTensorVisualisation();

        void start();
        void render(  MotionTensor &motion_tensor,
                      float r, float g, float b,
                      unsigned int view_mode = 0,
                      unsigned int min = 0, unsigned int max = 0
                    );
        void finish();

        bool new_loop();

    private:
        void render_raw( MotionTensor &motion_tensor,
                         float r, float g, float b,
                         unsigned int min, unsigned int max);

        float scale_x(float v);
        float scale_y(float v);
        float scale_z(float v);


};

#endif
