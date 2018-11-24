%module pyphy

%include <std_string.i>
%include <std_vector.i>

%template(CharVector) std::vector<char>;
%template(UnsignedCharVector) std::vector<unsigned char>;
%template(IntVector) std::vector<int>;
%template(UnsignedIntVector) std::vector<unsigned int>;
%template(FloatVector) std::vector<float>;
%template(DoubleVector) std::vector<double>;

%template(IntMatrix) std::vector<std::vector<int>>;
%template(UnsignedIntMatrix) std::vector<std::vector<unsigned int>>;

%template(FloatMatrix) std::vector<std::vector<float>>;
%template(DoubleMatrix) std::vector<std::vector<double>>;


%{
#include <dats_to_trajectory.h>
#include <nn_trajectory_spatial_input.h>

#include <predict_trajectory.h>
#include <trajectory_compare.h>
#include <trajectory.h>


#include <dat_load.h>
#include <dats_load.h>
#include <dataset_interface.h>
#include <DatasetParticlesMotion.h>

#include <log.h>
#include <json_config.h>
#include <regression_experiment.h>
%}


/* Let's just grab the original header file here */
%include <dats_to_trajectory.h>
%include <nn_trajectory_spatial_input.h>

%include <predict_trajectory.h>
%include <trajectory_compare.h>
%include <trajectory.h>


%include <dat_load.h>
%include <dats_load.h>
%include <dataset_interface.h>
%include <DatasetParticlesMotion.h>

%include <log.h>
%include <json_config.h>
%include <regression_experiment.h>

%include "pyphy.h"
