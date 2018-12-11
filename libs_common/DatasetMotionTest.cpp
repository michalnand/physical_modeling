#include "DatasetMotionTest.h"

#include <iostream>

DatasetMotionTest::DatasetMotionTest(unsigned int training_count, unsigned int testing_count)
{
  width     = 1;
  height    = 1;
  channels  = 32;

  training.resize(1);

  create(training_count, false);
  create(testing_count, true);

  std::cout << "training size = " << training[0].size() << "\n";
  std::cout << "testing size  = " << testing.size() << "\n";

  print();
}

DatasetMotionTest::~DatasetMotionTest()
{

}



void DatasetMotionTest::create(unsigned int count, bool put_to_testing)
{
  for (unsigned int i = 0; i < count; i++)
  {
    auto item = create_item();

    if (put_to_testing)
      add_testing(item);
    else
      add_training_for_regression(item);
  }
}


sDatasetItem DatasetMotionTest::create_item()
{
  unsigned int time_steps = channels;

  sDatasetItem result;

  result.input.resize(width*height*channels);
  result.output.resize(1);

  float x = 0.0;
  float v = (rand()%100000)/100000.0;

  float af = -(rand()%100000)/100000.0;
  unsigned int xf = (rand()%(time_steps/4)) + (time_steps*25)/100;

  float dt = 0.01;

  for (unsigned int t = 0; t < time_steps; t++)
  {
    result.input[t] = x;

    x+= v*dt;

    float a = 0.0;
    if (t >= xf)
      a = af;
    else
      a = 0.0;

    v+= a*dt;
  }

  result.output[0] = af;

  return result;
}
