#ifndef _VTK_CELLS_H_
#define _VTK_CELLS_H_

#include <vtk_cell.h>
#include <string>
#include <vector>

class VTKCells
{
    public:
        VTKCells();
        VTKCells(VTKCells& other);
        VTKCells(const VTKCells& other);

        VTKCells(std::string json_config_file_name);

        virtual ~VTKCells();

        VTKCells& operator= (VTKCells& other);
        VTKCells& operator= (const VTKCells& other);

    public:
        void load(std::string json_config_file_name);

        void normalise();
        void normalise_global();

        void find_extreme();

    public:
        void render(GLVisualisation &visualisation, unsigned int time_idx, float r = 1.0, float g = 0.0, float b = 0.0);

    public:
        unsigned int get_cells_count();
        unsigned int get_time_steps();
        unsigned int get_points_count();

        sVTKPoint get(unsigned int cell_idx, unsigned int time_idx, unsigned int point_idx);

    public:
        void print();

    protected:
        void copy(VTKCells& other);
        void copy(const VTKCells& other);

    private:
        std::vector<VTKCell> vtk_cells;

        sVTKPoint min_extreme, max_extreme;
        float min_extreme_global, max_extreme_global;

    private:
        int check_consitence();
};

#endif
