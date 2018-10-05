#include <iostream>

#include <spring_model.h>
#include <glvisualisation.h>
#include <timer.h>

int main()
{
  SpringModel model(16, 10.0, 0.3, 2.0);

  while (1)
  {
    timer.start();
    model.compute(0.0, 0.0, 0.0);
    timer.stop();

    std::cout << "computing time " << timer.get_duration() << "\n";

    model.render();
  }

  std::cout << "program done\n";
  return 0;
}
