#I'm new to python, so the code kind of sucks. have mercy upon my soul
#the comments are for Nicola

####################################
# Prerequisites:
# - Python3 (it can be used with Python2 with some editing)
# - tkinter graphics package
# - Python Imaging Library (PIL)
# - the basic python packages
###################################

import time
from tkinter import *
from tkinter import font as tkfont
import random
import math
from PIL import Image
from PIL import ImageTk
import io
from urllib.request import urlopen


class GUI():
    #initialize tkinter pointer & GUI
    tk = Tk()
    canvas = Canvas(tk, width=1000, height=800)
    canvas.pack()

    #fonts
    title_font = tkfont.Font(family="Helvetica", size=20)
    subtitle_font = tkfont.Font(family="Helvetica", size=15, weight="bold")
    normal_font = tkfont.Font(family="Helvetica", size=13)
    small_font = tkfont.Font(family="Helvetica", size=10)
    really_small_font = tkfont.Font(family="Helvetica", size=7)

    canvas_id = []
    buttons_id = []

#displays some stupid text
    def initialize(self):
        self.canvas.create_text((1000-53)/2, 20, text="Victim evacuation simulator (RoboCup rcj rescue line).", font=self.title_font, fill="red")

        self.buttons_id.append(Button(GUI.tk, text="-->", command=self.begin))
        self.buttons_id[0].place(x = (1000-130)/2, y = 50)

        self.canvas_id.append(self.canvas.create_text(140, 110, text="What this simulator-ish is:", font=self.subtitle_font))
        self.canvas_id.append(self.canvas.create_text(400, 140, text="A free, open-source simulator for ... (it's written in really large characters in the title above)", font=self.normal_font))
        self.canvas_id.append(self.canvas.create_text(466, 160, text="the code is available on git (BitBucket hosting) at https://bitbucket.org/rescuea_galilei_20172018/rescuea. ", font=self.normal_font))
        self.canvas_id.append(self.canvas.create_text(418, 180, text="You are of course allowed to review and edit the code, and any improvement is quite welcome.", font=self.normal_font))
        self.canvas_id.append(self.canvas.create_text(445, 200, text="PLEASE don't break it (i.e. if you don't understand something, don't touch it). You also aren't allowed ", font=self.normal_font))
        self.canvas_id.append(self.canvas.create_text(455, 220, text="to transform it into an evil AI (by mistake or on purpose); feel free to turn it into a billion dollar invention, ", font=self.normal_font))
        self.canvas_id.append(self.canvas.create_text(430, 240, text="so long as you give us a cut. I'm aware the formatting is awful, and I'll try to fix it someday. I hope.", font=self.normal_font))

        self.canvas_id.append(self.canvas.create_text(150, 300, text="What it most definitely isn't:", font=self.subtitle_font))
        self.canvas_id.append(self.canvas.create_text(367, 330, text="Skynet. But we are trying really hard. I'm not sure it would be that effective though:", font=self.normal_font))

        #image classified as button for practicality
        url = "https://imgs.xkcd.com/comics/skynet.png "
        fin = urlopen(url)
        s = io.BytesIO(fin.read())
        pil_image = Image.open(s)
        tk_image = ImageTk.PhotoImage(pil_image)
        label = Label(self.tk, image=tk_image)
        self.buttons_id.append(label)
        self.buttons_id[1].place(x = (15), y = 360)
        self.canvas_id.append(self.canvas.create_text((1000-53)/2, 680, text="Image credit: XKCD webcomic https://xkcd.com/1046/", font=self.really_small_font))

        self.canvas_id.append(self.canvas.create_text((1000-53)/2, 750, text="Made mostly by Luigi Massacci, No Rights Reserved", font=self.small_font))

        self.tk.mainloop()

#instantiates basic objects
    def begin(self):
        self.clear()
        room = Room()
        robot = Robot()

        room.draw_room()
        room.draw_victims()
        robot.draw_robot()

#clears the screen of all present items (items are either text or buttons)
    def clear(self):
        for i in range(0, len(self.canvas_id)):
            self.canvas.delete(self.canvas_id[i])
        for k in range(0, len(self.buttons_id)):
            self.buttons_id[k].destroy()

        del self.canvas_id[:]
        del self.buttons_id[:]

#displays input fields to set simulation parameters
    def parameters(self):
        pass



class Room(GUI):
    #room measures
    zoom = 5
    x_corner = 20
    y_corner = 50
    lastroom_width = 90 * zoom + x_corner
    lastroom_height = 120 * zoom + y_corner

    #victims coord
    vic_radius = 2 * zoom
    w, h = 5, 2
    victims_coord = [[0 for x in range(5)] for y in range(2)]
    random.seed()
    for i in range(0, 5):
        victims_coord[0][i] = random.randint(x_corner+vic_radius, lastroom_width-vic_radius)
    for i in range(0, 5):
        victims_coord[1][i] = random.randint(y_corner+vic_radius, lastroom_height-vic_radius-60)

    #evac coords
    #...

    def draw_room(self):
        GUI.canvas_id.append(GUI.canvas.create_rectangle(self.x_corner, self.y_corner, self.lastroom_width, self.lastroom_height, fill="white"))
    def draw_victims(self):
        for i in range(0, 5):
            GUI.canvas_id.append(GUI.canvas.create_oval(self.victims_coord[0][i]-self.vic_radius, self.victims_coord[1][i]+self.vic_radius, self.victims_coord[0][i]+self.vic_radius, self.victims_coord[1][i]-self.vic_radius, fill="blue"))
    def draw_evac(self):
        pass

class Robot(Room):
    #robot measures
    robot_length = 18 * Room.zoom #believable length, it will probably be shorter
    robot_width =  7 * Room.zoom #believable width, it will probably be larger
    wheel_length = 5 * Room.zoom
    wheel_width = 1 * Room.zoom
    #speed
    #center

    def draw_robot(self):
        #main body
        GUI.canvas_id.append(GUI.canvas.create_polygon(Room.x_corner, Room.lastroom_height-self.wheel_width-20, self.robot_length, Room.lastroom_height-self.wheel_width-20,
                              self.robot_length, Room.lastroom_height-self.robot_width-20, Room.x_corner, Room.lastroom_height-self.robot_width-20, fil="green"))
        #wheels
        GUI.canvas_id.append(GUI.canvas.create_polygon(Room.x_corner, Room.lastroom_height-self.robot_width-20, Room.x_corner + self.wheel_length, Room.lastroom_height-self.robot_width-20,
                              Room.x_corner + self.wheel_length, Room.lastroom_height-self.robot_width-self.wheel_width-20,
                              Room.x_corner, Room.lastroom_height-self.robot_width - self.wheel_width-20, fil="red"))

        GUI.canvas_id.append(GUI.canvas.create_polygon(self.robot_length, Room.lastroom_height-self.robot_width-20, self.robot_length-self.wheel_length, Room.lastroom_height-self.robot_width-20,
                             self.robot_length-self.wheel_length, Room.lastroom_height-self.robot_width-self.wheel_width-20,
                             self.robot_length, Room.lastroom_height-self.robot_width - self.wheel_width -20, fil="red"))

        GUI.canvas_id.append(GUI.canvas.create_polygon(Room.x_corner, Room.lastroom_height-20, Room.x_corner + self.wheel_length, Room.lastroom_height-20,
                             Room.x_corner + self.wheel_length, Room.lastroom_height-self.wheel_width-20,
                             Room.x_corner, Room.lastroom_height- self.wheel_width -20, fil="red"))

        GUI.canvas_id.append(GUI.canvas.create_polygon(self.robot_length, Room.lastroom_height-20, self.robot_length-self.wheel_length, Room.lastroom_height-20,
                            self.robot_length-self.wheel_length, Room.lastroom_height-self.wheel_width-20,
                            self.robot_length, Room.lastroom_height- self.wheel_width-20 , fil="red"))

    def move(self, distance):
        pass
    def rotate(self, angle):
        pass


gui = GUI()
gui.initialize()

gui.tk.mainloop()
