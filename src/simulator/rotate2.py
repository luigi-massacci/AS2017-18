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
CANVAS_MID_X = vertices[0][0] + WIDTH/2
CANVAS_MID_Y = vertices[3][1] + HEIGHT/2


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

def draw_square(points, color="blue"):
    return canvas.create_polygon(points, fill=color)

def move(item, distance):
    for x in range (0, abs(distance)):
        step = 1
        if distance < 0:
            step = -step
        canvas.move(item, step, 0)

        root.update()
        time.sleep(0.01)
    for i in range(0, 4):
        vertices[i][0] = vertices[i][0]+ distance

def rotatefor(item, angle):
    for i in range(0, abs(angle+1)):
        step = i
        if angle < 0:
            step = -step
        canvas.delete(item)

        item = draw_square(rotate(vertices, step, [CANVAS_MID_X, CANVAS_MID_Y]), color="blue")
        time.sleep(0.1)
        root.update()

item = draw_square(vertices)
move(item, 200)
move(item, -60)
CANVAS_MID_X = vertices[0][0] + WIDTH/2
CANVAS_MID_Y = vertices[3][1] + HEIGHT/2
rotatefor(item, -65)




























root.mainloop()
