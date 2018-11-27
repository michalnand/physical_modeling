#ifndef _LORENZ_H_
#define _LORENZ_H_

#include <string>
#include <vector>
#include <v3.h>

class Lorenz
{
  private:
    unsigned int length, count;
    
    std::vector<V3> state;
    std::vector<V3> output;

  public:
    Lorenz(unsigned int length, unsigned int count);
    virtual ~Lorenz();

    void save(std::string file_name_prefix);

    unsigned int size()
    {
      return state.size();
    }

    V3& get_state(unsigned int idx)
    {
      return state[idx];
    }

    V3& get_output(unsigned int idx)
    {
      return output[idx];
    }

  private:
    V3 compute(V3 &input);
    void normalise(std::vector<V3> &v);
};

#endif
