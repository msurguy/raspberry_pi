#
# Project Gunner
# Michael Han
# 2016-04-01
#

import numpy
import time
import sys
import os

from PIL import Image, ImageDraw, ImageFont
# sudo apt-get install python-xlib, edit /usr/share/pyshared/Xlib/ext/randr.py and remote the print
from Xlib import display

RED = (255, 0, 0)
ScreenWidth = 1920.0
ScreenHeight = 1080.0

class Hud:
   def __init__(self, name, width, height):
      self.Name = name
      self.__Width = width
      self.__Height = height
      self.__BaseGUI = Image.new("RGB", (self.__Width, self.__Height))
      self.__setGUI()
      
      self.__OutputGUI = self.__BaseGUI.copy()

   def setTime(self):
      text = time.strftime('%H:%M:%S', time.gmtime())
      self.__OutputGUI = self.__BaseGUI.copy()
      draw = ImageDraw.Draw(self.__OutputGUI)
      draw.font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 25)
      draw.text((10, 10), text, (255, 255, 255))

   def setReticle(self):
      # Create pixel array to modify
      self.__OutputGUI = self.__BaseGUI.copy()
      crosshair = self.__OutputGUI.load()

      # Get the mouse's position
      mouse = display.Display().screen().root.query_pointer()._data

      # Set the cursor where the mouse is
      x = float( float(mouse["root_x"]) / ScreenWidth) * self.__Width + 1
      y = float( float(mouse["root_y"]) / ScreenHeight) * self.__Height + 1

      if(x - 1 > 0 and x + 1 < self.__Width and y - 1 > 0 and y + 1 < self.__Height):
         crosshair[x, y] = RED
         crosshair[x - 1, y] = RED
         crosshair[x + 1, y] = RED
         crosshair[x, y - 1] = RED
         crosshair[x, y + 1] = RED
      
   def __setGUI(self):
      return
      
      
      
      

   def getBaseHud(self):
      return self.__BaseGUI

   def getHud(self):
      return self.__OutputGUI
