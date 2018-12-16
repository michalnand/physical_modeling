import json


#print basic tensor informations
def print_tensor_info(tensor):

    #extract tensor dimensions to int
    width   = tensor["width"]   #axis results
    height  = tensor["height"]  #lines
    depth   = tensor["depth"]   #cells

    #extract position tensor extremes in all 3 axis to floats
    min_x = tensor["extremes"][0]["min"]
    max_x = tensor["extremes"][0]["max"]
    min_y = tensor["extremes"][1]["min"]
    max_y = tensor["extremes"][1]["max"]
    min_z = tensor["extremes"][2]["min"]
    max_z = tensor["extremes"][2]["max"]

    #print some info

    print("width = ", width)        #6 axis : 3 for positions, 3 for velocity
    print("height = ", height)      #count of time steps
    print("depth = ", depth)        #count of cells in file
    print("\n")


    print("min x = ", min_x)
    print("max x = ", max_x)
    print("\n")
    print("min y = ", min_y)
    print("max y = ", max_y)
    print("\n")
    print("min z = ", min_z)
    print("max z = ", max_z)
    print("\n")


#print trajectory of selected cell
def print_cell_trajectory(tensor, cell_idx):

    #extract tensor extremes in all 3 axis to floats
    min_x = tensor["extremes"][0]["min"]
    max_x = tensor["extremes"][0]["max"]
    min_y = tensor["extremes"][1]["min"]
    max_y = tensor["extremes"][1]["max"]
    min_z = tensor["extremes"][2]["min"]
    max_z = tensor["extremes"][2]["max"]

    #lines count in tensor
    height = tensor["height"]

    for time in range(0, height):
        #print only each 100 step
        if (time%100) == 0:

            x_raw = tensor["values"][cell_idx][time][0] #x axis on index 0
            y_raw = tensor["values"][cell_idx][time][1] #y axis on index 1
            z_raw = tensor["values"][cell_idx][time][2] #z axis on index 2

            x = max_x*x_raw + min_x #denormalise from <0, 1> interval into <min_x, max_x>
            y = max_y*y_raw + min_y #denormalise from <0, 1> interval into <min_y, max_y>
            z = max_z*z_raw + min_z #denormalise from <0, 1> interval into <min_z, max_z>

            #result is now in [um]

            print(time, " : ", x, y, z)


#program starts here :

#load target values -> ground truth (real trajectory)
with open("trajectory_result/target.json") as f:
    target_tensor = json.load(f)

#print some info
print_tensor_info(target_tensor)

#print trajectory of cell 7
print_cell_trajectory(target_tensor, 7)
