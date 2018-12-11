#ifndef _MOTION_TENSOR_H_
#define _MOTION_TENSOR_H_

#include <vector>

struct sMotionTensorExtreme
{
  float min, max;
};

class MotionTensor
{
  public:
    MotionTensor();
    MotionTensor(unsigned int width_, unsigned int height_, unsigned int depth_);
    MotionTensor(MotionTensor& other);
    MotionTensor(const MotionTensor& other);

    virtual ~MotionTensor();

    MotionTensor& operator= (MotionTensor& other);
    MotionTensor& operator= (const MotionTensor& other);

  protected:
    void copy(MotionTensor& other);
    void copy(const MotionTensor& other);

  public:
    void init(unsigned int width_, unsigned int height_, unsigned int depth_);

  public:
    float get(unsigned int x, unsigned int y, unsigned int z);
    void set(unsigned int x, unsigned int y, unsigned int z, float value);

  public:
    unsigned int width()
    {
      return m_width;
    }

    unsigned int height()
    {
      return m_height;
    }

    unsigned int depth()
    {
      return m_depth;
    }

    void set_extremes(std::vector<sMotionTensorExtreme>& extremes)
    {
      this->extremes = extremes;
    }

    std::vector<sMotionTensorExtreme> get_extremes()
    {
      return extremes;
    } 

  public:
    void print(bool verbose = false);
    void clear();
    void normalise();
    void add_noise(float noise_level);
    void velocity_from_position();

  private:
    unsigned int m_width, m_height, m_depth;
    std::vector<std::vector<std::vector<float>>> v;

    std::vector<sMotionTensorExtreme> extremes;


  private:
    void find_extremes();
    sMotionTensorExtreme find_column_extreme(unsigned int column);
    void normalise_column(sMotionTensorExtreme extreme, unsigned int column);

};

#endif
