#ifndef _DATA_LORENZ_SPATIAL_H_
#define _DATA_LORENZ_SPATIAL_H_

#include <string>
#include <vector>
#include <dataset_interface.h>


class DatasetLorenzSpatial: public DatasetInterface
{
  public:
    DatasetLorenzSpatial(unsigned int training_count, unsigned int testing_count, unsigned int discretization = 16);
    virtual ~DatasetLorenzSpatial();

  private:
    void create(unsigned int count, unsigned int discretization, bool put_to_testing);

};

#endif
