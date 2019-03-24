#ifndef _VTK_CELL_H_
#define _VTK_CELL_H_

#include <vtk.h>
#include <glvisualisation.h>

class VTKCell
{
    public:
        VTKCell();
        VTKCell(VTKCell& other);
        VTKCell(const VTKCell& other);
        VTKCell(std::string cell_path, std::string file_name_prefix);

        virtual ~VTKCell();

        VTKCell& operator= (VTKCell& other);
        VTKCell& operator= (const VTKCell& other);

    protected:
        void copy(VTKCell& other);
        void copy(const VTKCell& other);

    public:
        unsigned int get_time_steps();
        unsigned int get_points_count(unsigned int time_idx = 0);
        sVTKPoint get(unsigned int time_idx, unsigned int point_idx);
        VTK& get_vtk(unsigned int time_idx);


    public:
        void normalise();
        void normalise(sVTKPoint min_extreme, sVTKPoint max_extreme);

        void normalise_global();
        void normalise_global(float min_extreme_global, float max_extreme_global);


        sVTKPoint get_min_extreme();
        sVTKPoint get_max_extreme();

        float get_min_extreme_global();
        float get_max_extreme_global();

        void render(GLVisualisation &visualisation, unsigned int time_idx);


    private:
        std::vector<std::string> get_sorted_file_names(std::string cell_path, std::string file_name_prefix);
        void find_extreme();

    private:
        std::vector<VTK> vtk;
        sVTKPoint min_extreme, max_extreme;
        float min_extreme_global, max_extreme_global;
};

#endif
