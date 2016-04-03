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

# Colors
RED          = (255, 0  , 0  )
GREEN        = (0  , 255, 0  )
BLUE         = (0  , 0  , 255)
YELLOW       = (255, 255, 0  )

# Crosshair Color
CrosshairColor = YELLOW

# Screen resolution
ScreenWidth  = 1920.0
ScreenHeight = 1080.0

class Hud:
   def __init__(self, name, width, height):
      self.Name      = name
      self.__Width   = width
      self.__Height  = height
      self.__BaseGUI = Image.new("RGB", (self.__Width, self.__Height))      
      self.OutputGUI = self.__BaseGUI.copy()

   def setTime(self):
      text           = time.strftime('%H:%M:%S', time.gmtime())
      self.OutputGUI = self.__BaseGUI.copy()
      draw           = ImageDraw.Draw(self.__OutputGUI)
      draw.font      = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 25)
      draw.text((10, 10), text, (255, 255, 255))

   def setReticle(self):
      # Create pixel array to modify
      self.OutputGUI = self.__BaseGUI.copy()
      crosshair      = self.OutputGUI.load()

      # Get the mouse's position
      mouse          = display.Display().screen().root.query_pointer()._data

      # Set the cursor where the mouse is
      x = float( float(mouse["root_x"]) / ScreenWidth) * self.__Width + 1
      y = float( float(mouse["root_y"]) / ScreenHeight) * self.__Height + 1

      if(x - 5 > 0 and x + 5 < self.__Width and y - 5 > 0 and y + 5 < self.__Height):
         # +
         crosshair[x    , y    ] = CrosshairColor
         crosshair[x - 1, y    ] = CrosshairColor
         crosshair[x + 1, y    ] = CrosshairColor
         crosshair[x    , y - 1] = CrosshairColor
         crosshair[x    , y + 1] = CrosshairColor

         # Diamond
         # Top Left
         crosshair[x    , y - 5] = CrosshairColor
         crosshair[x - 1, y - 4] = CrosshairColor
         crosshair[x - 2, y - 3] = CrosshairColor
         crosshair[x - 3, y - 2] = CrosshairColor
         crosshair[x - 4, y - 1] = CrosshairColor
         crosshair[x - 5, y    ] = CrosshairColor
         # Bottom Left
         crosshair[x    , y + 5] = CrosshairColor
         crosshair[x - 1, y + 4] = CrosshairColor
         crosshair[x - 2, y + 3] = CrosshairColor
         crosshair[x - 3, y + 2] = CrosshairColor
         crosshair[x - 4, y + 1] = CrosshairColor
         # Bottom Right
         crosshair[x + 1, y + 4] = CrosshairColor
         crosshair[x + 2, y + 3] = CrosshairColor
         crosshair[x + 3, y + 2] = CrosshairColor
         crosshair[x + 4, y + 1] = CrosshairColor
         crosshair[x + 5, y    ] = CrosshairColor
         # Top Right
         crosshair[x    , y - 5] = CrosshairColor
         crosshair[x + 1, y - 4] = CrosshairColor
         crosshair[x + 2, y - 3] = CrosshairColor
         crosshair[x + 3, y - 2] = CrosshairColor
         crosshair[x + 4, y - 1] = CrosshairColor
      

   def getBaseHud(self):
      return self.__BaseGUI
