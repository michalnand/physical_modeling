#ifndef _DATASET_MOTION_TEST_H_
#define _DATASET_MOTION_TEST_H_

#include <string>
#include <vector>
#include <dataset_interface.h>


class DatasetMotionTest: public DatasetInterface
{
  public:
    DatasetMotionTest(unsigned int training_count, unsigned int testing_count);
    virtual ~DatasetMotionTest();

  private:
    void create(unsigned int count, bool put_to_testing);
    sDatasetItem create_item();

};

#endif
