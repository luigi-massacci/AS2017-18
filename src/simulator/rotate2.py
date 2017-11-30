from tkinter import *
import math
import time

CANVAS_WIDTH = 800
CANVAS_HEIGHT = 800

WIDTH = 100
HEIGHT = 50

root = Tk()
canvas = Canvas(root, bg="white", height=CANVAS_HEIGHT, width=CANVAS_WIDTH)
canvas.pack()

vertices = [
    [100, 100],
    [100, 100+HEIGHT],
    [100+WIDTH, 100+HEIGHT],
    [100+WIDTH, 100],
]
MID_X = vertices[0][0] + WIDTH/2
MID_Y = vertices[3][1] + HEIGHT/2
current_angle = 0

def draw_square(points, color="blue"):
    return canvas.create_polygon(points, fill=color)

item = draw_square(vertices)
def move(points, distance):
    angle = math.radians(abs(current_angle))
    cos_val = math.cos(angle)
    sin_val = math.sin(angle)
    new_points = []
    for i in range(0, 4):
        vertices[i][0] = vertices[i][0] + cos_val * distance
        vertices[i][1] = vertices[i][1] + sin_val * -distance

    return vertices

def movefor(distance):
    global item
    for i in range(0, abs(distance+1)):
        step = 1
        if distance < 0:
            step = -step
        canvas.delete(item)

        item = draw_square(move(vertices, step), color="blue")
        time.sleep(0.01)
        root.update()
        global MID_X
        global MID_Y
        MID_X = (vertices[3][0] + vertices[1][0])/2
        MID_Y = (vertices[3][1] + vertices[1][1])/2

def rotatefor(angle):
    global item
    for i in range(0, abs(angle+1)):
        step = 1
        if angle < 0:
            step = -step
        canvas.delete(item)

        item = draw_square(rotate(vertices, step, [MID_X, MID_Y]), color="blue")
        time.sleep(0.01)
        root.update()
    global current_angle
    current_angle += angle



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
    global vertices
    vertices = new_points
    return new_points



movefor(100)
rotatefor(-65)
movefor(100)
rotatefor(65)
movefor(100)
rotatefor(90)
movefor(-200)
rotatefor(-90)
movefor(200)






















root.mainloop()