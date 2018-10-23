#include <iostream>

#include <spring_model.h>
#include <glvisualisation.h>
#include <timer.h>

int main()
{
  SpringModel model(8, 100.0, 0.3, 2.0);

  model.render();
  //getchar();

  unsigned int iterations = 32;
  float time_f = 0.0;
  float k = 0.95;
  while (1)
  {
    timer.start();

    for (unsigned int i = 0; i < iterations; i++)
      model.compute(0.0, 0.0, 0.0);
    timer.stop();

    time_f = k*time_f + ((1.0 - k)*timer.get_duration())/iterations;

    std::cout << "computing time " << time_f << "[ms]\n";

    model.render();
  }

  std::cout << "program done\n";
  return 0;
}
