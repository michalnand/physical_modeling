import sys
sys.path.insert(0, '../libs_python')
import pyphy


def non_spatial(training_count, testing_count):
    dataset = pyphy.DatasetLorenz(training_count, testing_count)

    print("non spatial dataset creating done")

    experiment = pyphy.RegressionExperiment(dataset, "experiment_0/")
    experiment.run()

    print("training done")


def spatial_a(training_count, testing_count):
    dataset = pyphy.DatasetLorenzSpatial(training_count, testing_count, 16)

    print("spatial dataset 16 creating done")

    experiment = pyphy.RegressionExperiment(dataset, "experiment_1/")
    experiment.run()

    print("training done")


def spatial_b(training_count, testing_count):
    dataset = pyphy.DatasetLorenzSpatial(training_count, testing_count, 32)

    print("spatial dataset 32 creating done")

    experiment = pyphy.RegressionExperiment(dataset, "experiment_2/")
    experiment.run()

    print("training done")


def spatial_c():
    training = pyphy.Lorenz(100, 100)
    testing  = pyphy.Lorenz(100, 100)

    training.save("experiment_3/data/training/lorenz")
    training.save("experiment_3/data/testing/lorenz")

    print("initialising done")

    #load dataset
    dats_training   = pyphy.DatsLoad("experiment_3/training.json")
    dats_testing    = pyphy.DatsLoad("experiment_3/testing.json")

    #find extremes -> use training set extremes for both (training and testing) normalisation
    dats_training.find_extreme()

    extremes = dats_training.get_extremes()
    dats_training.set_extremes(extremes)
    dats_testing.set_extremes(extremes)

    #normalise values -> use extremes
    dats_training.normalise_column(0.0, 1.0, False)
    dats_testing.normalise_column(0.0, 1.0, False)

    #convert raw values to trajectories
    training_trajectory = pyphy.DatsToTrajectory(dats_training, "experiment_3/dataset_particles_motion_spatial_config.json")
    testing_trajectory = pyphy.DatsToTrajectory(dats_testing, "experiment_3/dataset_particles_motion_spatial_config.json")
    print("loading done")


    #create dataset for neural network
    dataset = pyphy.DatasetParticlesMotion( training_trajectory.get_trajectory_input(),
                                            training_trajectory.get_trajectory_output(),
                                            testing_trajectory.get_trajectory_input(),
                                            testing_trajectory.get_trajectory_output(),
                                            "experiment_3/dataset_particles_motion_spatial_config.json")

    print("dataset creating done")

    experiment = pyphy.RegressionExperiment(dataset, "experiment_3/")
    experiment.run()

    print("training done")



training_count = 10000
testing_count  = 10000

#non_spatial(training_count, testing_count)
#spatial_a(training_count, testing_count)
#spatial_b(training_count, testing_count)
spatial_c()


print("program done")
