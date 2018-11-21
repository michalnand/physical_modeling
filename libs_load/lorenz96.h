#ifndef _LORENZ96_H_
#define _LORENZ96_H_


#include <vector>

class Lorenz96
{
  private:
    std::vector<float> x, dif;

  public:
    Lorenz96(unsigned int variables_count);
    virtual ~Lorenz96();

    void set_initial_conditions(std::vector<float> &x_initial);
    void set_random_initial_conditions(float range = 0.001);

    void next(float dt = 0.001);

    std::vector<float>&  get_x();
    std::vector<float>&  get_dif();

  private:
    std::vector<float> const_vector(unsigned int size, float value);
    std::vector<float> random_vector(unsigned int size, float range);

    std::vector<float> compute_dif(std::vector<float> &x);
    void apply_dif(std::vector<float> &x, std::vector<float> &dif, float dt = 0.001);
};


#endif
