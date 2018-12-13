import sys
sys.path.insert(0, '../../libs_python')
import pyphy


#1, load data from dats files and create motion tensor with normalised columns

#load training data
training_dats_to_motion_tensor = pyphy.DatsToMotionTensor("training_dats.json", "motion_tensor.json")

#load testing data, for normalisation use range from testing
testing_dats_to_motion_tensor = pyphy.DatsToMotionTensor("testing_dats.json", "motion_tensor.json", training_dats_to_motion_tensor.tensor())

#2, create network input making class - TensorNoSpatial
training_tensor = pyphy.TensorNoSpatial("no_spatial_tensor.json", training_dats_to_motion_tensor.tensor())
testing_tensor  = pyphy.TensorNoSpatial("no_spatial_tensor.json", testing_dats_to_motion_tensor.tensor())

#3, create dataset
dataset = pyphy.DatasetTrajectory(training_tensor, training_tensor)



#4, run experiments, train network

experiment_0 = pyphy.RegressionExperiment(dataset, "experiment_0/")
experiment_0.run()

experiment_1 = pyphy.RegressionExperiment(dataset, "experiment_1/")
experiment_1.run()

experiment_2 = pyphy.RegressionExperiment(dataset, "experiment_2/")
experiment_2.run()

experiment_3 = pyphy.RegressionExperiment(dataset, "experiment_3/")
experiment_3.run()

print("program done")
