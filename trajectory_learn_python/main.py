import sys
sys.path.insert(0, '../libs_python')
import pyphy

#load dataset
dats_training   = pyphy.DatsLoad("training.json")
dats_testing    = pyphy.DatsLoad("testing.json")

#find extremes -> use training set extremes for both (training and testing) normalisation
dats_training.find_extreme()

extremes = dats_training.get_extremes()
dats_training.set_extremes(extremes)
dats_testing.set_extremes(extremes)

#normalise values -> use extremes
dats_training.normalise_column(0.0, 1.0, False)
dats_testing.normalise_column(0.0, 1.0, False)

#convert raw values to trajectories
training_trajectory = pyphy.DatsToTrajectory(dats_training, "dataset_particles_motion_spatial_config.json")
testing_trajectory = pyphy.DatsToTrajectory(dats_testing, "dataset_particles_motion_spatial_config.json")
print("loading done")

#save trajectories for further usage

training_trajectory.get_trajectory_input().save("trajectory_training_target/input")
training_trajectory.get_trajectory_output().save("trajectory_training_target/output")
testing_trajectory.get_trajectory_input().save("trajectory_testing_target/input")
testing_trajectory.get_trajectory_output().save("trajectory_testing_target/output")

print("saving done")


#create dataset for neural network
dataset = pyphy.DatasetParticlesMotion( training_trajectory.get_trajectory_input(),
                                        training_trajectory.get_trajectory_output(),
                                        testing_trajectory.get_trajectory_input(),
                                        testing_trajectory.get_trajectory_output(),
                                        "dataset_particles_motion_spatial_config.json")

print("dataset creating done")

#run experiments with different networks

experiment_0 = pyphy.RegressionExperiment(dataset, "experiment_0/")
experiment_0.run()

experiment_1 = pyphy.RegressionExperiment(dataset, "experiment_1/")
experiment_1.run()

experiment_2 = pyphy.RegressionExperiment(dataset, "experiment_2/")
experiment_2.run()

experiment_3 = pyphy.RegressionExperiment(dataset, "experiment_3/")
experiment_3.run()

print("program done")
