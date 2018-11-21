#ifndef _DATASET_LORENZ_96_H_
#define _DATASET_LORENZ_96_H_


#include <vector>
#include <dataset_interface.h>
#include <lorenz96.h>

class DatasetLorenz96: public DatasetInterface
{
  private:
    float dt;

  public:
    DatasetLorenz96(unsigned int variables_count, unsigned int training_size, unsigned int testing_size);
    virtual ~DatasetLorenz96();

  private:
    void create(Lorenz96 &lorenz96, unsigned int batch_count, unsigned int batch_size, bool put_to_testing);

};

#endif
