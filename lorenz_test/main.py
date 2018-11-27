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

training_count = 10000
testing_count  = 10000

non_spatial(training_count, testing_count)
spatial_a(training_count, testing_count)
spatial_b(training_count, testing_count)



print("program done")
