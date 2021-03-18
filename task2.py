from load_data import load_data
import numpy as np
import math
from PIL import Image

from numpy.core.fromnumeric import shape
import cv2


#Load data
data_path = "data/data.p"
demo_path = "data/demo.p"
data = load_data(data_path)

#Load relevant data
boundary_box_color = (0,255,0)
img = data["image_2"]
R1 = data["T_cam2_velo"]
R2 = data["P_rect_20"]
counter = 0

#Project the Velodyne points on the image 
for num, data_point in enumerate(data["velodyne"]):
    #In Homogenous coordinates transform to camera space
    data_point[3] = 1
    cam_space = R1@data_point 
    if cam_space[2] <= 0:
        continue #Filter points behind the screen
    
    #Compute screen coordinates
    screen_coord = R2@cam_space
    u = math.floor(screen_coord[0]/screen_coord[2])
    v = math.floor(screen_coord[1]/screen_coord[2])
    
    #Display point on screen
    if v >= 0 and v < img.shape[0] and u >=  0 and u < img.shape[1]:
        label = data["sem_label"][num]
        color = [i for i in reversed(data["color_map"][label[0]])]
        img[v,u] = np.array(color)

#Cam0 to Cam2 screen space transformation Matrix
R3 = R2@R1@np.linalg.inv(data["T_cam0_velo"])

#Draw bounding boxes
for obj in data["objects"]:
    location = np.array([obj[11],obj[12],obj[13],1]) #Coordinates of box
    theta = obj[14] + math.pi/2
    c, s = np.cos(theta), np.sin(theta)
    #Rotation matrix and transfromation matrix to turn the bounding box
    R = np.array([[c,0,s,0],\
                  [0,1,0,0],\
                  [-s,0,c,0],\
                  [0,0,0,1]])
    T = np.array([[1,0,0,-location[0]],\
                  [0,1,0,0],\
                  [0,0,1,-location[2]],\
                  [0,0,0,1]])
    Tr = R3@np.linalg.inv(T)@R@T #Center bounding box, turn the box, bring back to original postion,transform to screen space of cam2
    #Create each point of the bounding box and transform it onto screen space
    p1 = Tr@[location[0]+obj[9]/2,location[1],location[2]-obj[10]/2,1]
    p2 = Tr@[location[0]-obj[9]/2,location[1],location[2]-obj[10]/2,1]
    p3 = Tr@[location[0]+obj[9]/2,location[1],location[2]+obj[10]/2,1]
    p4 = Tr@[location[0]-obj[9]/2,location[1],location[2]+obj[10]/2,1]
    p10 = Tr@[location[0]+obj[9]/2,location[1]-obj[8],location[2]-obj[10]/2,1]
    p20 = Tr@[location[0]-obj[9]/2,location[1]-obj[8],location[2]-obj[10]/2,1]
    p30 = Tr@[location[0]+obj[9]/2,location[1]-obj[8],location[2]+obj[10]/2,1]
    p40 = Tr@[location[0]-obj[9]/2,location[1]-obj[8],location[2]+obj[10]/2,1]
    #2D Homogenous coordinates to 2D coordinates
    point1 = (math.floor(p1[0]/p1[2]),math.floor(p1[1]/p1[2]))
    point2 = (math.floor(p2[0]/p2[2]),math.floor(p2[1]/p2[2]))
    point3 = (math.floor(p3[0]/p3[2]),math.floor(p3[1]/p3[2]))
    point4 = (math.floor(p4[0]/p4[2]),math.floor(p4[1]/p4[2]))
    point10 = (math.floor(p10[0]/p10[2]),math.floor(p10[1]/p10[2]))
    point20 = (math.floor(p20[0]/p20[2]),math.floor(p20[1]/p20[2]))
    point30 = (math.floor(p30[0]/p30[2]),math.floor(p30[1]/p30[2]))
    point40 = (math.floor(p40[0]/p40[2]),math.floor(p40[1]/p40[2]))

    #Draw the bounding box
    img = cv2.line(img,point1,point2,boundary_box_color,2)
    img = cv2.line(img,point3,point1,boundary_box_color,2)
    img = cv2.line(img,point3,point4,boundary_box_color,2)
    img = cv2.line(img,point4,point2,boundary_box_color,2)
    img = cv2.line(img,point10,point20,boundary_box_color,2)
    img = cv2.line(img,point30,point10,boundary_box_color,2)
    img = cv2.line(img,point30,point40,boundary_box_color,2)
    img = cv2.line(img,point40,point20,boundary_box_color,2)
    img = cv2.line(img,point1,point10,boundary_box_color,2)
    img = cv2.line(img,point2,point20,boundary_box_color,2)
    img = cv2.line(img,point3,point30,boundary_box_color,2)
    img = cv2.line(img,point4,point40,boundary_box_color,2)
#Store image
im = Image.fromarray(np.uint8(img), "RGB")
im.save("task2_result.png")