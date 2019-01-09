import sys
sys.path.insert(0, '../../libs_python')
import pyphy



target = pyphy.MotionTensor()
target.load_json("trajectory_result/target.json")

'''
experiment_4 = pyphy.MotionTensor()
experiment_4.load_json("trajectory_result/experiment_4.json")

experiment_5 = pyphy.MotionTensor()
experiment_5.load_json("trajectory_result/experiment_5.json")

experiment_6 = pyphy.MotionTensor()
experiment_6.load_json("trajectory_result/experiment_6.json")
'''
experiment_7 = pyphy.MotionTensor()
experiment_7.load_json("trajectory_result/experiment_7.json")


visualisation = pyphy.MotionTensorVisualisation()

view = 0
while (True):
    visualisation.start()

    #render target tensor as red
    visualisation.render(target, 1.0, 0.0, 0.0, view)

    '''
    visualisation.render(experiment_4, 1.0, 1.0, 0.0, view)
    visualisation.render(experiment_5, 0.0, 1.0, 1.0, view)

    #render experiment_6 tensor as green
    visualisation.render(experiment_6, 0.0, 1.0, 0.0, view)
    '''
    
    #render experiment_7 tensor as blue
    visualisation.render(experiment_7, 0.0, 0.0, 1.0, view)


    visualisation.finish()

    #if visualisation.new_loop():
    #    view = view + 1
