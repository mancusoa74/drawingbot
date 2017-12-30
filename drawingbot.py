import turtle
import math
import random
import time
#--------------------------

CHANGE_COLOR_DELAY = 5 #pen change color delay in seconds

class DrawingRobot():
	# 297 x 210 mm
	def __init__(self, screen_w=842, screen_h=595, paper_w=297, paper_h=210, speed=6, pensize=5):
		super(DrawingRobot,self).__init__()
		self.__drawing_commands__ = []
		self.screen_w = screen_w
		self.screen_h = screen_h
		self.paper_w = paper_w
		self.paper_h = paper_h

		turtle.setup (screen_w, screen_h, startx=0, starty=0)
		turtle.shape('triangle')
		turtle.color('orange')
		turtle.bgcolor("white")
		#turtle.pencolor('purple')
		turtle.pensize(pensize)
		turtle.speed(speed)
		turtle.left(90)

	def __mm2pix__(self, mm):
		factor = min ((self.screen_w / self.paper_w), (self.screen_h / self.paper_h))
		return math.ceil(mm * factor)

	def forward(self, mm):
		pix = self.__mm2pix__(mm)
		turtle.forward(pix)
		self.__record_command__("forward({});".format(mm))

	def backward(self, mm):
		pix = self.__mm2pix__(mm)
		turtle.backward(pix)
		self.__record_command__("backward({});".format(mm))

	def right(self, angle):
		turtle.right(angle)
		self.__record_command__("right({});".format(angle))

	def left(self, angle):
		turtle.left(angle)
		self.__record_command__("left({});".format(angle))

	def penup(self):
		turtle.penup()
		self.__record_command__("penup();")

	def pendown(self):
		turtle.pendown()
		self.__record_command__("pendown();")

	def pencolor(self, color):
		turtle.pencolor(color)
		self.__record_command__("penup();\ndelay({});\npendown();".format(CHANGE_COLOR_DELAY * 1000))

	def __record_command__(self, command):
		self.__drawing_commands__.append(command)

	def dump_commands(self):
		print("/* Auto generated drawingbot commands */");
		print("/* Paste them into your drawingbot sketch */")
		for cmd in self.__drawing_commands__:
			print(cmd)
		print("/* End Auto generated drawing bot commands */")

	#aliases for Italian users
	indietro = backward
	destra = right
	sinistra = left
	penna_su = penup
	penna_giu = pendown
	penna_colore = pencolor
    

#create your drawing here
def drawing():
	dr = DrawingRobot()
	dr.pendown()
	for i in range(1,20):
	    dr.forward(i * 6)
	    dr.right(90)
	    if i % 4 == 0:
	    	dr.pencolor((random.random(), random.random(), random.random()))
	dr.penup();
	dr.dump_commands()
	turtle.done()


if __name__ == "__main__":
	drawing()