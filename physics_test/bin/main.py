import sys
sys.path.insert(0, '../libs_python')
import pyphy

training_count = 1000000
testing_count  = 20000

dataset = pyphy.DatasetVelocitySimple("training_dats.json", "testing_dats.json", "motion_tensor.json", training_count, testing_count)

experiment_0 = pyphy.RegressionExperiment(dataset, "experiment_0/")
experiment_0.run()

experiment_1 = pyphy.RegressionExperiment(dataset, "experiment_1/")
experiment_1.run()

experiment_2 = pyphy.RegressionExperiment(dataset, "experiment_2/")
experiment_2.run()

experiment_3 = pyphy.RegressionExperiment(dataset, "experiment_3/")
experiment_3.run()

print("program done")
