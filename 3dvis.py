# Deep Learning for Autonomous Driving
# Material for Problem 2 of Project 1
# For further questions contact Ozan Unal, ozan.unal@vision.ee.ethz.ch

import vispy
from vispy.scene import visuals, SceneCanvas
import numpy as np
import os
from load_data import load_data
import math

class Visualizer():
    def __init__(self):
        self.canvas = SceneCanvas(keys='interactive', show=True)
        self.grid = self.canvas.central_widget.add_grid()
        self.view = vispy.scene.widgets.ViewBox(border_color='white',
                        parent=self.canvas.scene)
        self.grid.add_widget(self.view, 0, 0)

        # Point Cloud Visualizer
        self.sem_vis = visuals.Markers()
        self.view.camera = vispy.scene.cameras.TurntableCamera(up='z', azimuth=90)
        self.view.add(self.sem_vis)
        visuals.XYZAxis(parent=self.view.scene)
        
        # Object Detection Visualizer
        self.obj_vis = visuals.Line()
        self.view.add(self.obj_vis)
        self.connect = np.asarray([[0,1],[0,3],[0,4],
                                   [2,1],[2,3],[2,6],
                                   [5,1],[5,4],[5,6],
                                   [7,3],[7,4],[7,6]])

    def update(self, points):
        '''
        :param points: point cloud data
                        shape (N, 3)          
        Task 2: Change this function such that each point
        is colored depending on its semantic label
        '''
        #Itterate over each point and add the color corresponding to it's semantic label
        colors = []
        for num, point in enumerate(points):
            label = data["sem_label"][num]
            color = [i/255.0 for i in reversed(data["color_map"][label[0]])] #Flip BGR=>RGB
            colors.append(color)
        self.sem_vis.set_data(points,face_color=colors, size=3)
    
    def update_boxes(self, corners):
        '''
        :param corners: corners of the bounding boxes
                        shape (N, 8, 3) for N boxes
        (8, 3) array of vertices for the 3D box in
        following order:
            1 -------- 0
           /|         /|
          2 -------- 3 .
          | |        | |
          . 5 -------- 4
          |/         |/
          6 -------- 7
        If you plan to use a different order, you can
        change self.connect accordinly.
        '''
        for i in range(corners.shape[0]):
            connect = np.concatenate((connect, self.connect+8*i), axis=0) \
                    if i>0 else self.connect
        self.obj_vis.set_data(corners.reshape(-1,3),
                            connect=connect,
                            width=2,
                            color=[0,1,0,1])

if __name__ == '__main__':
    data = load_data('data/data.p') # Change to data.p for your final submission 
    visualizer = Visualizer()
    visualizer.update(data['velodyne'][:,:3])
    '''
    Task 2: Compute all bounding box corners from given
    annotations. You can visualize the bounding boxes using
    visualizer.update_boxes(corners)
    '''
    R3 = np.linalg.inv(data["T_cam0_velo"])#Camera to Velodyne space
    boxes = []
    #Create the bopunding boxes
    for obj in data["objects"]:
        location = np.array([obj[11],obj[12],obj[13],1])

        #Rotation matrix and transfromation matrix to turn the bounding box
        theta = obj[14] + math.pi/2
        c, s = np.cos(theta), np.sin(theta)
        R = np.array([[c,0,s,0],\
                    [0,1,0,0],\
                    [-s,0,c,0],\
                    [0,0,0,1]])
        T = np.array([[1,0,0,-location[0]],\
                    [0,1,0,0],\
                    [0,0,1,-location[2]],\
                    [0,0,0,1]])
                
        Tr = R3@np.linalg.inv(T)@R@T#Center bounding box, turn the box, bring back to original postion, transform to screen space of cam2
        
        #Create each point of the bounding box and transform it to velodyne space
        p1 = Tr@[location[0]+obj[9]/2,location[1],location[2]-obj[10]/2,1]
        p2 = Tr@[location[0]-obj[9]/2,location[1],location[2]-obj[10]/2,1]
        p3 = Tr@[location[0]+obj[9]/2,location[1],location[2]+obj[10]/2,1]
        p4 = Tr@[location[0]-obj[9]/2,location[1],location[2]+obj[10]/2,1]
        p10 = Tr@[location[0]+obj[9]/2,location[1]-obj[8],location[2]-obj[10]/2,1]
        p20 = Tr@[location[0]-obj[9]/2,location[1]-obj[8],location[2]-obj[10]/2,1]
        p30 = Tr@[location[0]+obj[9]/2,location[1]-obj[8],location[2]+obj[10]/2,1]
        p40 = Tr@[location[0]-obj[9]/2,location[1]-obj[8],location[2]+obj[10]/2,1]
        boxes.append(np.array([p2[0:3],p1[0:3],p3[0:3],p4[0:3],p20[0:3],p10[0:3],p30[0:3],p40[0:3]]))
    
    #Display the boxes
    visualizer.update_boxes(np.array(boxes))
    vispy.app.run()




