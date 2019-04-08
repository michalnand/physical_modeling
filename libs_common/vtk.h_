#ifndef _VTK_H_
#define _VTK_H_

#include <string>
#include <vector>

struct sVTKPoint
{
    float x, y, z;
};

class VTK
{
    public:
        VTK();
        VTK(VTK& other);
        VTK(const VTK& other);

        VTK(std::string file_name);

        virtual ~VTK();

        VTK& operator= (VTK& other);
        VTK& operator= (const VTK& other);

    public:
        sVTKPoint get_center();
        sVTKPoint get_max_extreme();
        sVTKPoint get_min_extreme();

        std::vector<sVTKPoint>& get();
        sVTKPoint get(unsigned int idx);
        unsigned int get_points_count();

    public:
        void normalise();
        void normalise(sVTKPoint min_extreme, sVTKPoint max_extreme);
        void normalise_global();
        void normalise_global(float min_extreme_global, float max_extreme_global);


        void denormalise();
        void denormalise(sVTKPoint min_extreme, sVTKPoint max_extreme);
        void denormalise_global();
        void denormalise_global(float min_extreme_global, float max_extreme_global);

        bool is_normalised();

        void print();

    protected:
        void copy(VTK& other);
        void copy(const VTK& other);

    private:
        int find_points_starting_line(std::vector<std::string> &lines);
        int get_points_count(std::string &line);

        sVTKPoint get_point(std::string &line);

        void find_extremes();
        void find_center();

    protected:
        std::vector<sVTKPoint> points;

        sVTKPoint center, max_extreme, min_extreme;

        float max_extreme_global;
        float min_extreme_global;

        bool normalised;

};

#endif
