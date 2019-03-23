#include <iostream>

#include <vtk.h>
#include <glvisualisation.h>

void vtk_render(GLVisualisation &visualisation, VTK &vtk)
{
    for (unsigned int i = 0; i < vtk.get_points_count(); i++)
    {
        auto point = vtk.get()[i];

        point.x = point.x*2.0 - 1.0;
        point.y = point.y*2.0 - 1.0;
        point.z = point.z*2.0 - 1.0;

        visualisation.push();
        visualisation.set_color(1.0, 1.0, 1.0);
        visualisation.translate(point.x, point.y, point.z);
        visualisation.paint_point();
        visualisation.pop();
    }
}

int main()
{
    VTK vtk_a("vtk/rbc4_2250000.vtk");
    VTK vtk_b("vtk/rbc5_3300000.vtk");
    VTK vtk_c("vtk/rbc6_2700000.vtk");
    VTK vtk_d("vtk/rbc32_690000.vtk");

    vtk_a.normalise_global();
    vtk_b.normalise_global();
    vtk_c.normalise_global();
    vtk_d.normalise_global();

    GLVisualisation visualisation;

    while (1)
    {
        visualisation.start();
        visualisation.translate(0, 0, -3);
        //visualisation.rotate(40, 0.0, 0.0);


        vtk_render(visualisation, vtk_a);
        vtk_render(visualisation, vtk_b);
        vtk_render(visualisation, vtk_c);
        vtk_render(visualisation, vtk_d);

        visualisation.finish();
    }



    std::cout << "program done\n";

    return 0;
}
