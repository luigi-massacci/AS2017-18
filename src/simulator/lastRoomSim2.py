from tkinter import *
import math
import time


#GLOABAL VARIABLES
start_x = 100  #coordinates of the upper left point of the robot body in the beggining
start_y = 600

R_WIDTH = 100
R_HEIGHT = 50
r_vertices = [
    [start_x , start_y],
    [start_x , start_y+R_HEIGHT],
    [start_x +R_WIDTH, start_y+R_HEIGHT],
    [start_x +R_WIDTH, start_y],
]
W_WIDTH = 30
W_HEIGHT = 5
w1_vertices = [
    [start_x, start_y-W_HEIGHT],
    [start_x , start_y],
    [start_x + W_WIDTH, start_y],
    [start_x +W_WIDTH, start_y-W_HEIGHT],
]
w2_vertices = [
    [start_x, start_y+R_HEIGHT],
    [start_x , start_y+R_HEIGHT+W_HEIGHT],
    [start_x + W_WIDTH, start_y+R_HEIGHT+W_HEIGHT],
    [start_x +W_WIDTH, start_y+R_HEIGHT],
]
w3_vertices = [
    [start_x+R_WIDTH-W_WIDTH, start_y+R_HEIGHT],
    [start_x+R_WIDTH-W_WIDTH, start_y+R_HEIGHT+W_HEIGHT],
    [start_x+R_WIDTH, start_y+R_HEIGHT+W_HEIGHT],
    [start_x+R_WIDTH, start_y+R_HEIGHT],
]
w4_vertices = [
    [start_x+R_WIDTH-W_WIDTH, start_y-W_HEIGHT],
    [start_x+R_WIDTH-W_WIDTH, start_y],
    [start_x+R_WIDTH, start_y],
    [start_x+R_WIDTH, start_y-W_HEIGHT],
]


center = [r_vertices[0][0] + R_WIDTH/2, r_vertices[3][1] + R_HEIGHT/2]
current_angle = 0


#TK VARIABLES
CANVAS_WIDTH = 800
CANVAS_HEIGHT = 800

root = Tk()
canvas = Canvas(root, bg="white", height=CANVAS_HEIGHT, width=CANVAS_WIDTH)
canvas.pack()


def draw_square(points, color="blue"):
    return canvas.create_polygon(points, fill=color)

def move(points, distance):
    angle = math.radians(abs(current_angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    for i in range(0, 4):
        points[i][0] = points[i][0] + cos_val * distance
        points[i][1] = points[i][1] + sin_val * -distance

    return points

def movefor(distance):
    global robot
    global w1
    global w2
    global w3
    global w4
    global r_vertices
    global w1_vertices
    global w2_vertices
    global w3_vertices
    global w4_vertices
    for i in range(0, abs(distance)):
        step = 1
        if distance < 0:
            step = -step
        canvas.delete(robot)
        canvas.delete(w1)
        canvas.delete(w2)
        canvas.delete(w3)
        canvas.delete(w4)


        r_vertices = move(r_vertices, step)
        robot = draw_square(r_vertices)
        w1_vertices = move(w1_vertices, step)
        w1 = draw_square(w1_vertices, color="red")
        w2_vertices = move(w2_vertices, step)
        w2 = draw_square(w2_vertices, color="red")
        w3_vertices = move(w3_vertices, step)
        w3 = draw_square(w3_vertices, color="red")
        w4_vertices = move(w4_vertices, step)
        w4 = draw_square(w4_vertices, color="red")

        time.sleep(0.01)
        root.update()
        center[0] = (r_vertices[3][0] + r_vertices[1][0])/2
        center[1] = (r_vertices[3][1] + r_vertices[1][1])/2

def rotate(points, angle, center):
    angle = math.radians(angle)
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    cx, cy = center
    new_points = []
    for x_old, y_old in points:
        x_old -= cx
        y_old -= cy
        x_new = x_old * cos_val - y_old * sin_val
        y_new = x_old * sin_val + y_old * cos_val
        new_points.append([x_new + cx, y_new + cy])
    return new_points

def rotatefor(angle):
    global robot
    global w1
    global w2
    global w3
    global w4
    global r_vertices
    global w1_vertices
    global w2_vertices
    global w3_vertices
    global w4_vertices
    for i in range(0, abs(angle)):
        step = 1
        if angle < 0:
            step = -step
        canvas.delete(robot)
        canvas.delete(w1)
        canvas.delete(w2)
        canvas.delete(w3)
        canvas.delete(w4)

        r_vertices = rotate(r_vertices, step, center)
        robot = draw_square(r_vertices)
        w1_vertices = rotate(w1_vertices, step, center)
        w1 = draw_square(w1_vertices, color="red")
        w2_vertices = rotate(w2_vertices, step, center)
        w2 = draw_square(w2_vertices, color="red")
        w3_vertices = rotate(w3_vertices, step, center)
        w3 = draw_square(w3_vertices, color="red")
        w4_vertices = rotate(w4_vertices, step, center)
        w4 = draw_square(w4_vertices, color="red")
        time.sleep(0.01)
        root.update()
    global current_angle
    current_angle += angle

#instantiate tk objects
robot = draw_square(r_vertices)
w1 = draw_square(w1_vertices, color="red")
w2 = draw_square(w2_vertices, color="red")
w3 = draw_square(w3_vertices, color="red")
w4 = draw_square(w4_vertices, color="red")


movefor(200)
rotatefor(-65)
movefor(100)
rotatefor(65)
movefor(100)
rotatefor(90)
movefor(-100)
rotatefor(-90)
movefor(100)


root.mainloop()
