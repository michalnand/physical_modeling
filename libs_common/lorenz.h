#ifndef _LORENZ_H_
#define _LORENZ_H_

#include <string>
#include <vector>
#include <v3.h>

class Lorenz
{
  private:
    std::vector<V3> state;
    std::vector<V3> output;

  public:
    Lorenz(unsigned int length, unsigned int count);
    virtual ~Lorenz();

    void save(std::string file_name);

  private:
    V3 compute(V3 &input);
};

#endif
