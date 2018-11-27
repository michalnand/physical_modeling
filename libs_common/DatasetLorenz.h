#ifndef _DATA_LORENZ_H_
#define _DATA_LORENZ_H_

#include <string>
#include <vector>
#include <dataset_interface.h>


class DatasetLorenz: public DatasetInterface
{
  public:
    DatasetLorenz(unsigned int training_count, unsigned int testing_count);
    virtual ~DatasetLorenz();

  private:
    void create(unsigned int count, bool put_to_testing);

};

#endif
