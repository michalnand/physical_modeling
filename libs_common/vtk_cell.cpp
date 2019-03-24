#include "vtk_cell.h"
#include <experimental/filesystem>
#include <algorithm>
#include <iostream>

VTKCell::VTKCell()
{
    min_extreme.x = 0;
    min_extreme.y = 0;
    min_extreme.z = 0;

    max_extreme = min_extreme;

    min_extreme_global = 0.0;
    max_extreme_global = 0.0;
}

VTKCell::VTKCell(VTKCell& other)
{
    copy(other);
}

VTKCell::VTKCell(const VTKCell& other)
{
    copy(other);
}

VTKCell::VTKCell(std::string cell_path, std::string file_name_prefix)
{
    auto file_names = get_sorted_file_names(cell_path, file_name_prefix);

    for (unsigned int i = 0; i < file_names.size(); i++)
    {
        vtk.push_back(VTK(file_names[i]));
    }

    find_extreme();
}

VTKCell::~VTKCell()
{

}

VTKCell& VTKCell::operator= (VTKCell& other)
{
    copy(other);
    return *this;
}

VTKCell& VTKCell::operator= (const VTKCell& other)
{
    copy(other);
    return *this;
}

void VTKCell::copy(VTKCell& other)
{
    vtk = other.vtk;

    min_extreme      = other.min_extreme;
    max_extreme      = other.max_extreme;

    min_extreme_global      = other.min_extreme_global;
    max_extreme_global      = other.max_extreme_global;
}

void VTKCell::copy(const VTKCell& other)
{
    vtk = other.vtk;

    min_extreme      = other.min_extreme;
    max_extreme      = other.max_extreme;

    min_extreme_global      = other.min_extreme_global;
    max_extreme_global      = other.max_extreme_global;
}

unsigned int VTKCell::get_time_steps()
{
    return vtk.size();
}

unsigned int VTKCell::get_points_count(unsigned int time_idx)
{
    return vtk[time_idx].get_points_count();
}

sVTKPoint VTKCell::get(unsigned int time_idx, unsigned int point_idx)
{
    return vtk[time_idx].get(point_idx);
}

VTK& VTKCell::get_vtk(unsigned int time_idx)
{
    return vtk[time_idx];
}

void VTKCell::normalise()
{
    for (unsigned int j = 0; j < vtk.size(); j++)
        vtk[j].normalise(min_extreme, max_extreme);
}

void VTKCell::normalise(sVTKPoint min_extreme, sVTKPoint max_extreme)
{
    for (unsigned int j = 0; j < vtk.size(); j++)
        vtk[j].normalise(min_extreme, max_extreme);
}


void VTKCell::normalise_global()
{
    for (unsigned int j = 0; j < vtk.size(); j++)
        vtk[j].normalise_global(min_extreme_global, max_extreme_global);
}

void VTKCell::normalise_global(float min_extreme_global, float max_extreme_global)
{
    for (unsigned int j = 0; j < vtk.size(); j++)
        vtk[j].normalise_global(min_extreme_global, max_extreme_global);
}

sVTKPoint VTKCell::get_min_extreme()
{
    return min_extreme;
}

sVTKPoint VTKCell::get_max_extreme()
{
    return max_extreme;
}

float VTKCell::get_min_extreme_global()
{
    return min_extreme_global;
}

float VTKCell::get_max_extreme_global()
{
    return max_extreme_global;
}

void VTKCell::render(GLVisualisation &visualisation, unsigned int time_idx)
{
    visualisation.push();

    for (unsigned int i = 0; i < vtk[time_idx].get_points_count(); i++)
    {
        auto point = vtk[time_idx].get()[i];

        point.x = point.x*2.0 - 1.0;
        point.y = point.y*2.0 - 1.0;
        point.z = point.z*2.0 - 1.0;

        visualisation.push();
        visualisation.translate(point.x, point.y, point.z);
        visualisation.paint_point();
        visualisation.pop();
    }

    visualisation.pop();
}

std::vector<std::string> VTKCell::get_sorted_file_names(std::string cell_path, std::string file_name_prefix)
{
    std::vector<unsigned int> indicies;

    std::string extension = ".vtk";

    for (auto & p : std::experimental::filesystem::directory_iterator(cell_path))
    {
        std::string file_name;
        file_name = p.path();
        if (std::experimental::filesystem::path(file_name).extension() == extension)
        if (file_name.find(file_name_prefix) != std::string::npos)
        {
            //std::cout << "file name" << file_name << "\n";

            ptrdiff_t idx_begin = file_name.find(file_name_prefix) + file_name_prefix.length();
            ptrdiff_t idx_end = file_name.find(extension);

            std::string tmp = file_name.substr(idx_begin, idx_end - idx_begin);

            unsigned int tmp_i = std::stoi(tmp,nullptr,0);

            indicies.push_back(tmp_i);
        }
    }


    std::sort(indicies.begin(), indicies.end());

    std::vector<std::string> result;

    for (unsigned int i = 0; i < indicies.size(); i++)
    {
        std::string tmp = cell_path + file_name_prefix + std::to_string(indicies[i]) + extension;
        result.push_back(tmp);
    }


    return result;
}


void VTKCell::find_extreme()
{
    min_extreme = vtk[0].get_min_extreme();
    max_extreme = vtk[0].get_max_extreme();

    for (unsigned int j = 0; j < vtk.size(); j++)
    {
        auto min_extreme_j = vtk[j].get_min_extreme();
        auto max_extreme_j = vtk[j].get_max_extreme();

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
