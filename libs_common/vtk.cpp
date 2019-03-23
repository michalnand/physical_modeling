#include "vtk.h"

#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>

VTK::VTK()
{
    center.x = 0.0;
    center.y = 0.0;
    center.z = 0.0;

    max_extreme.x = 0.0;
    max_extreme.y = 0.0;
    max_extreme.z = 0.0;

    min_extreme = max_extreme;

    max_extreme_global = 0.0;
    min_extreme_global = min_extreme_global;

    normalised = false;
}

VTK::VTK(VTK& other)
{
    copy(other);
}

VTK::VTK(const VTK& other)
{
    copy(other);
}



VTK::VTK(std::string file_name)
{
    std::ifstream infile(file_name);

    std::string line;

    std::vector<std::string> lines;

    while (std::getline(infile, line))
    {
        lines.push_back(line);
    }

    int points_starting_line = find_points_starting_line(lines);

    if (points_starting_line < 0)
    {
        std::cout << "VTK - missing POINTS\n";
        return;
    }

    int points_count = get_points_count(lines[points_starting_line]);

    if (points_starting_line <= 0)
    {
        std::cout << "VTK - wrong points count\n";
        return;
    }

    for (unsigned int i = 0; i < (unsigned int)points_count; i++)
    {
        points.push_back( get_point(lines[points_starting_line + 1 + i]) );
    }

    find_extremes();
}

VTK::~VTK()
{

}

VTK& VTK::operator= (VTK& other)
{
    copy(other);
    return *this;
}

VTK& VTK::operator= (const VTK& other)
{
    copy(other);
    return *this;
}


sVTKPoint VTK::get_center()
{
    return center;
}

sVTKPoint VTK::get_max_extreme()
{
    return max_extreme;
}

sVTKPoint VTK::get_min_extreme()
{
    return min_extreme;
}

void VTK::normalise()
{
    normalise(min_extreme, max_extreme);
}

void VTK::normalise(sVTKPoint min_extreme, sVTKPoint max_extreme)
{
    float kx = 1.0/(max_extreme.x - min_extreme.x);
    float ky = 1.0/(max_extreme.y - min_extreme.y);
    float kz = 1.0/(max_extreme.z - min_extreme.z);

    float cx = 1.0 - kx*max_extreme.x;
    float cy = 1.0 - ky*max_extreme.y;
    float cz = 1.0 - kz*max_extreme.z;

    for (unsigned int i = 0; i < points.size(); i++)
    {
        points[i].x = kx*points[i].x + cx;
        points[i].y = ky*points[i].y + cy;
        points[i].z = kz*points[i].z + cz;
    }

    normalised = true;
}

void VTK::normalise_global()
{
    normalise_global(min_extreme_global, max_extreme_global);
}

void VTK::normalise_global(float min_extreme_global, float max_extreme_global)
{
    float k = 1.0/(max_extreme_global - min_extreme_global);

    float c = 1.0 - k*max_extreme_global;


    for (unsigned int i = 0; i < points.size(); i++)
    {
        points[i].x = k*points[i].x + c;
        points[i].y = k*points[i].y + c;
        points[i].z = k*points[i].z + c;
    }

    normalised = true;
}


void VTK::denormalise()
{
    denormalise(min_extreme, max_extreme);
}

void VTK::denormalise(sVTKPoint min_extreme, sVTKPoint max_extreme)
{
    float kx = (max_extreme.x - min_extreme.x)/1.0;
    float ky = (max_extreme.y - min_extreme.y)/1.0;
    float kz = (max_extreme.z - min_extreme.z)/1.0;

    float cx = max_extreme.x - kx*1.0;
    float cy = max_extreme.y - ky*1.0;
    float cz = max_extreme.z - kz*1.0;

    for (unsigned int i = 0; i < points.size(); i++)
    {
        points[i].x = kx*points[i].x + cx;
        points[i].y = ky*points[i].y + cy;
        points[i].z = kz*points[i].z + cz;
    }

    normalised = false;
}

bool VTK::is_normalised()
{
    return normalised;
}


void VTK::print()
{
    for (unsigned int i = 0; i < points.size(); i++)
    {
        std::cout << i << " : ";
        std::cout << points[i].x << " ";
        std::cout << points[i].y << " ";
        std::cout << points[i].z << " ";
        std::cout << "\n";
    }
}

unsigned int VTK::get_points_count()
{
    return points.size();
}

std::vector<sVTKPoint>& VTK::get()
{
    return points;
}

void VTK::copy(VTK& other)
{
    points      = other.points;

    center      = other.center;
    max_extreme = other.max_extreme;
    min_extreme = other.min_extreme;

    max_extreme_global = other.max_extreme_global;
    min_extreme_global = other.min_extreme_global;

    normalised  = other.normalised;
}

void VTK::copy(const VTK& other)
{
    points      = other.points;

    center      = other.center;
    max_extreme = other.max_extreme;
    min_extreme = other.min_extreme;

    max_extreme_global = other.max_extreme_global;
    min_extreme_global = other.min_extreme_global;

    normalised  = other.normalised;
}




int VTK::find_points_starting_line(std::vector<std::string> &lines)
{
    int result = -1;

    for (unsigned int i = 0; i < lines.size(); i++)
    {
        auto found = lines[i].find("POINTS");
        if (found != std::string::npos)
        {
            result = i;
            break;
        }
    }

    return result;
}

int VTK::get_points_count(std::string &line)
{
    std::istringstream buf(line);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> tokens(beg, end);

    int result = std::stoi(tokens[1],nullptr,0);

    return result;
}


sVTKPoint VTK::get_point(std::string &line)
{
    sVTKPoint result;

    std::istringstream buf(line);
    std::istream_iterator<std::string> beg(buf), end;

    std::vector<std::string> tokens(beg, end);

    result.x = std::stof(tokens[0]);
    result.y = std::stof(tokens[1]);
    result.z = std::stof(tokens[2]);

    return result;
}

void VTK::find_extremes()
{
    center.x = 0.0;
    center.y = 0.0;
    center.z = 0.0;

    max_extreme.x = points[0].x;
    max_extreme.y = points[0].y;
    max_extreme.z = points[0].z;

    min_extreme = max_extreme;

    for (unsigned int i = 0; i < points.size(); i++)
    {
        center.x+= points[i].x/points.size();
        center.y+= points[i].y/points.size();
        center.z+= points[i].z/points.size();

        if (points[i].x > max_extreme.x)
            max_extreme.x = points[i].x;

        if (points[i].x < min_extreme.x)
            min_extreme.x = points[i].x;

        if (points[i].y > max_extreme.y)
            max_extreme.y = points[i].y;

        if (points[i].y < min_extreme.y)
            min_extreme.y = points[i].y;

        if (points[i].z > max_extreme.z)
            max_extreme.z = points[i].z;

        if (points[i].z < min_extreme.z)
            min_extreme.z = points[i].z;
    }

    max_extreme_global = max_extreme.x;
    if (max_extreme.y > max_extreme_global)
        max_extreme_global = max_extreme.y;

    if (max_extreme.z > max_extreme_global)
        max_extreme_global = max_extreme.z;

    min_extreme_global = min_extreme.x;
    if (min_extreme.y < min_extreme_global)
        min_extreme_global = min_extreme.y;
    if (min_extreme.z < min_extreme_global)
        min_extreme_global = min_extreme.z;
}
