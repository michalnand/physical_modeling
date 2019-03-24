#include <iostream>
#include <timer.h>

#include <glvisualisation.h>
#include <vtk_cells.h>

int main()
{
    Timer timer;
    GLVisualisation visualisation;

    VTKCells vtk_cells_training("config_training.json");
    vtk_cells_training.normalise_global();
    vtk_cells_training.print();

    VTKCells vtk_cells_testing("config_testing.json");
    vtk_cells_testing.normalise_global();
    vtk_cells_testing.print();


    unsigned int time_idx = 0;

    while (1)
    {
        visualisation.start();
        visualisation.translate(0, 0, -2.0);

        vtk_cells_training.render(visualisation, time_idx%vtk_cells_training.get_time_steps(), 1.0, 0.0, 0.0);
        vtk_cells_testing.render(visualisation, time_idx%vtk_cells_testing.get_time_steps(), 0.0, 0.0, 1.0);

        visualisation.finish();

        timer.sleep_ms(10);
        time_idx++;
    }


    std::cout << "program done\n";

    return 0;
}
