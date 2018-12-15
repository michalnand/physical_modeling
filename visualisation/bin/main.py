import sys
sys.path.insert(0, '../../libs_python')
import pyphy



target = pyphy.MotionTensor()
target.load_json("trajectory_result/target.json")

experiment_6 = pyphy.MotionTensor()
experiment_6.load_json("trajectory_result/experiment_6.json")

experiment_7 = pyphy.MotionTensor()
experiment_7.load_json("trajectory_result/experiment_7.json")

visualisation = pyphy.MotionTensorVisualisation()

while (True):
    visualisation.start()

    #render target tensor as red
    visualisation.render(target, 1.0, 0.0, 0.0)

    #render experiment_6 tensor as green
    visualisation.render(experiment_6, 0.0, 1.0, 0.0)

    #render experiment_7 tensor as blue
    visualisation.render(experiment_7, 0.0, 0.0, 1.0)

    visualisation.finish()
