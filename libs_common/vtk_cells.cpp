#include "vtk_cells.h"
#include <json_config.h>
#include <iostream>

VTKCells::VTKCells()
{

}

VTKCells::VTKCells(VTKCells& other)
{
    copy(other);
}

VTKCells::VTKCells(const VTKCells& other)
{
    copy(other);
}

VTKCells::VTKCells(std::string json_config_file_name)
{
    load(json_config_file_name);
}

VTKCells::~VTKCells()
{

}

VTKCells& VTKCells::operator= (VTKCells& other)
{
    copy(other);
    return *this;
}

VTKCells& VTKCells::operator= (const VTKCells& other)
{
    copy(other);
    return *this;
}

void VTKCells::copy(VTKCells& other)
{
    vtk_cells = other.vtk_cells;

    min_extreme = other.min_extreme;
    max_extreme = other.max_extreme;
}

void VTKCells::copy(const VTKCells& other)
{
    vtk_cells = other.vtk_cells;

    min_extreme = other.min_extreme;
    max_extreme = other.max_extreme;
}



void VTKCells::load(std::string json_config_file_name)
{
    JsonConfig json(json_config_file_name);

    vtk_cells.clear();

    std::string path = json.result["path"].asString();
    for (unsigned int j = 0; j < json.result["file_name_prefix"].size(); j++)
    {
        std::string file_name_prefix = json.result["file_name_prefix"][j].asString();
        //std::cout << "loading cell" << path+file_name_prefix << "\n";
        vtk_cells.push_back(VTKCell(path, file_name_prefix));
    }

    if (check_consitence() != 0)
        return;

    find_extreme();
}


void VTKCells::normalise()
{
    for (unsigned int j = 0; j < vtk_cells.size(); j++)
    {
        vtk_cells[j].normalise(min_extreme, max_extreme);
    }
}

void VTKCells::normalise_global()
{
    for (unsigned int j = 0; j < vtk_cells.size(); j++)
    {
        vtk_cells[j].normalise_global(min_extreme_global, max_extreme_global);
    }
}



void VTKCells::find_extreme()
{
    min_extreme = vtk_cells[0].get_min_extreme();
    max_extreme = vtk_cells[0].get_max_extreme();

    for (unsigned int j = 0; j < vtk_cells.size(); j++)
    {
        auto min_extreme_j = vtk_cells[j].get_min_extreme();
        auto max_extreme_j = vtk_cells[j].get_max_extreme();

        if (min_extreme_j.x < min_extreme.x)
            min_extreme.x = min_extreme_j.x;
        if (max_extreme_j.x > max_extreme.x)
            max_extreme.x = max_extreme_j.x;

        if (min_extreme_j.y < min_extreme.y)
            min_extreme.y = min_extreme_j.y;
        if (max_extreme_j.y > max_extreme.y)
            max_extreme.y = max_extreme_j.y;

        if (min_extreme_j.z < min_extreme.z)
            min_extreme.z = min_extreme_j.z;
        if (max_extreme_j.z > max_extreme.z)
            max_extreme.z = max_extreme_j.z;
    }

    min_extreme_global = min_extreme.x;

    if (min_extreme.y < min_extreme_global)
        min_extreme.y = min_extreme_global;

    if (min_extreme.z < min_extreme_global)
        min_extreme.z = min_extreme_global;


    max_extreme_global = max_extreme.x;

    if (max_extreme.y > max_extreme_global)
        max_extreme.y = max_extreme_global;

    if (max_extreme.z > max_extreme_global)
        max_extreme.z = max_extreme_global;
}


void VTKCells::render(GLVisualisation &visualisation, unsigned int time_idx, float r, float g, float b)
{
    visualisation.push();


    visualisation.push();
    visualisation.set_color(0.8, 0.8, 0.8);
    visualisation.translate(0.0, 0.0, -3.0);
    visualisation.paint_square(10.0);
    visualisation.pop();

    visualisation.set_color(r, g, b);

    for (unsigned int j = 0; j < vtk_cells.size(); j++)
        vtk_cells[j].render(visualisation, time_idx);

    visualisation.pop();
}


unsigned int VTKCells::get_cells_count()
{
    return vtk_cells.size();
}

unsigned int VTKCells::get_time_steps()
{
    return vtk_cells[0].get_time_steps();
}

unsigned int VTKCells::get_points_count()
{
    return vtk_cells[0].get_points_count();
}

sVTKPoint VTKCells::get(unsigned int cell_idx, unsigned int time_idx, unsigned int point_idx)
{
    return vtk_cells[cell_idx].get(time_idx, point_idx);
}

void VTKCells::print()
{
    std::cout << "\n";

    std::cout << "data consistence result " << check_consitence() << "\n";
    std::cout << "cells count  " << get_cells_count() << "\n";
    std::cout << "time steps   " << get_time_steps() << "\n";
    std::cout << "points count " << get_points_count() << "\n";

    std::cout << "extreme_min = " << "[";
    std::cout << min_extreme.x << " " << min_extreme.y << " " << min_extreme.z << "]\n";

    std::cout << "extreme_max = " << "[";
    std::cout << max_extreme.x << " " << max_extreme.y << " " << max_extreme.z << "]\n";

    std::cout << "min = " << min_extreme_global << ", " << "max = " << max_extreme_global << "\n";

    std::cout << "\n\n\n";
}

int VTKCells::check_consitence()
{
    for (unsigned int j = 0; j < vtk_cells.size(); j++)
    {
        if (get_time_steps() != vtk_cells[j].get_time_steps())
            return -1;

        if (get_points_count() != vtk_cells[j].get_points_count())
            return -2;
    }

    return 0;
}
