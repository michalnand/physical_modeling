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
#include <dat_load.h>
#include <dats_load.h>

#include <motion_tensor.h>
#include <dats_to_motion_tensor.h>

#include <motion_tensor.h>
#include <tensor_interface.h>
#include <tensor_no_spatial.h>
#include <tensor_spatial.h>

#include <dataset_interface.h>
#include <DatasetVelocitySimple.h>
#include <DatasetTrajectory.h>
#include <DatasetTrajectoryRuntime.h>

#include <motion_tensor_visualisation.h>

#include <log.h>
#include <json_config.h>
#include <regression_experiment.h>

#include <trajectory_prediction.h>
%}


/* Let's just grab the original header file here */
%include <dat_load.h>
%include <dats_load.h>

%include <motion_tensor.h>
%include <dats_to_motion_tensor.h>

%include <motion_tensor.h>
%include <tensor_interface.h>
%include <tensor_no_spatial.h>
%include <tensor_spatial.h>

%include <dataset_interface.h>
%include <DatasetVelocitySimple.h>
%include <DatasetTrajectory.h>
%include <DatasetTrajectoryRuntime.h>

%include <motion_tensor_visualisation.h>

%include <log.h>
%include <json_config.h>
%include <regression_experiment.h>

%include <trajectory_prediction.h>

%include "pyphy.h"
