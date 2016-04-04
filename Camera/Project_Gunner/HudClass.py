
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
GRAY         = (100, 100, 100)

# GUI Colors
CrosshairColor = YELLOW
GuiColor       = RED
GuiColor2      = GRAY

# Screen resolution
ScreenWidth  = 1920.0
ScreenHeight = 1080.0

# Compass constants
xLRLimit     = 50                     # X's Left and Right limits
xCenterLimit = 30                     # X's Center limits to change y
yCenterLimit = 20
yTopLimit    = 20
yBottomLimit = 30
xLeftLimit   = 30
xRightLimit  = 40
azDiagLimit  = yBottomLimit - yTopLimit
elDiagLimit  = azDiagLimit + 3
fontHeight   = 14
fontWidth    = int(fontHeight * .7)

class Hud:
   def __init__(self, name, width, height):
      self.Name        = name
      self.__Width     = width
      self.__MidWidth  = width / 2
      self.__Height    = height
      self.__MidHeight = height /2
      self.__BaseGUI   = Image.new("RGB", (self.__Width, self.__Height))      
      self.OutputGUI   = self.__BaseGUI.copy()

      # Set the GUI once so it doesn't have be done every frame
      self.setBaseGUI()
      
   def setTime(self):
      text           = time.strftime('%H:%M:%S', time.gmtime())
      draw           = ImageDraw.Draw(self.OutputGUI)
      draw.font      = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 25)
      draw.text((10, 10), text, (255, 255, 255))

   def setCompassDirection(self, az, el):
      # Error correction
      if(az < 0 or az > 360):
         if (az < 0):
            az = 0
         else:
            az = 360
      if(el < -180 or el > 180):
         if (el < -180):
            el = -180
         else:
            el = 180

      #Set Az
      text = str(az)
      if(az < 10):
         first  = str(0)
         second = str(0)
         third  = text[0] 
      elif(az < 100):
         first  = str(0)
         second = text[0]
         third  = text[1]
      else:
         first  = text[0]
         second = text[1]
         third  = text[2]
      fifth = "\xb0"
      offset = 5
      self.OutputGUI = self.__BaseGUI.copy()
      draw = ImageDraw.Draw(self.OutputGUI)
      draw.font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", fontHeight)
      draw.text( (self.__MidWidth - fontWidth - offset, yTopLimit - 10), first, GuiColor) 
      draw.text( (self.__MidWidth - offset, yTopLimit - 10), second, GuiColor)
      draw.text( (self.__MidWidth + fontWidth - offset, yTopLimit - 10), third, GuiColor)
      draw.text( (self.__MidWidth + fontWidth + offset, yTopLimit - 10), fifth, GuiColor)

      #Set El
      text = str(abs(el))
      if(abs(el) < 10):
         second  = str(0)
         third   = str(0)
         fourth  = text[0] 
      elif(abs(el) < 100):
         second  = str(0)
         third   = text[0]
         fourth  = text[1]
      else:
         second  = text[0]
         third   = text[1]
         fourth  = text[2]
      if(el < 0):
         first   = "-"
      else:
         first   = ""
      offset = 11
      draw.text( (xLeftLimit - (2*fontWidth) - offset + 2, self.__MidHeight - 7), first, GuiColor) 
      draw.text( (xLeftLimit - fontWidth - offset, self.__MidHeight - 7), second, GuiColor)
      draw.text( (xLeftLimit - offset, self.__MidHeight - 7), third, GuiColor)
      draw.text( (xLeftLimit + fontWidth - offset, self.__MidHeight - 7), fourth, GuiColor)
      draw.text( (xLeftLimit + fontWidth - offset + 8, self.__MidHeight - 7), fifth, GuiColor)
      
   def setReticle(self):

      # Get the mouse's position
      mouse          = display.Display().screen().root.query_pointer()._data

      # Set the cursor where the mouse is
      x = float( float(mouse["root_x"]) / ScreenWidth) * self.__Width + 1
      y = float( float(mouse["root_y"]) / ScreenHeight) * self.__Height + 1

      # Sets the compass direction as the mouse's azimuth
      az = (mouse["root_x"] / ScreenWidth) * 360
      el = -1 * ((mouse["root_y"] / ScreenHeight) * 360 - 180)
      self.setCompassDirection(az, el)
      
      # Create pixel array to modify
      crosshair      = self.OutputGUI.load()
      
      if(x - 5 > 0 and x + 5 < self.__Width and y - 5 > 0 and y + 5 < self.__Height):
      #if False:
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

   def setBaseGUI(self):
      GUI     = self.__BaseGUI.load()
      xOffset = 2
      yOffset = 3
      
      # Azimuth GUI at top
      # '   ------------     -----------   '
      for x in range(xLRLimit, self.__MidWidth - xCenterLimit):
         GUI[x, yTopLimit]                     = GuiColor
         GUI[x, yTopLimit + 1]                 = GuiColor
         GUI[x - xOffset, yTopLimit + yOffset] = GuiColor2
      for x in range( self.__MidWidth + xCenterLimit, self.__Width - xLRLimit):
         GUI[x, yTopLimit]                     = GuiColor
         GUI[x, yTopLimit + 1]                 = GuiColor
         GUI[x + xOffset, yTopLimit + yOffset] = GuiColor2
      # '               \___/              '
      for x in range(0, azDiagLimit):
         GUI[self.__MidWidth - xCenterLimit + x, yTopLimit + x]                     = GuiColor
         GUI[self.__MidWidth - xCenterLimit + x, yTopLimit + x + 1]                 = GuiColor
         if x < azDiagLimit:
            GUI[self.__MidWidth - xCenterLimit + x, yTopLimit + x + 2]                 = GuiColor
         GUI[self.__MidWidth - xCenterLimit + x - xOffset, yTopLimit + x + yOffset] = GuiColor2
      for x in range( self.__MidWidth - xCenterLimit + azDiagLimit, self.__MidWidth + xCenterLimit - azDiagLimit):
         GUI[x, yBottomLimit]                                                       = GuiColor
         GUI[x, yBottomLimit + 1]                                                   = GuiColor
      for x in range( self.__MidWidth - xCenterLimit + azDiagLimit - xOffset, self.__MidWidth + xCenterLimit - azDiagLimit + xOffset):
         GUI[x, yBottomLimit + yOffset]                                             = GuiColor2
      for x in range(0, azDiagLimit + 1):
         GUI[self.__MidWidth + xCenterLimit - x, yTopLimit + x]                     = GuiColor
         GUI[self.__MidWidth + xCenterLimit - x, yTopLimit + x + 1]                 = GuiColor
         if x < azDiagLimit:
            GUI[self.__MidWidth + xCenterLimit - x, yTopLimit + x + 2]              = GuiColor
         GUI[self.__MidWidth + xCenterLimit - x + xOffset, yTopLimit + x + yOffset] = GuiColor2
      # ' \                               /'
      for x in range(0, azDiagLimit):
         GUI[xLRLimit - x, yTopLimit - x]                                           = GuiColor
         GUI[xLRLimit - x, yTopLimit - x + 1]                                       = GuiColor
         if x > 0:
            GUI[xLRLimit - x, yTopLimit - x + 2]                                       = GuiColor
         GUI[xLRLimit - x - xOffset, yTopLimit - x + yOffset]                       = GuiColor2
      for x in range(0, azDiagLimit):
         GUI[self.__Width - xLRLimit + x, yTopLimit - x]                            = GuiColor
         GUI[self.__Width - xLRLimit + x, yTopLimit - x + 1]                        = GuiColor
         if x > 0:
            GUI[self.__Width - xLRLimit + x, yTopLimit - x + 2]                        = GuiColor
         GUI[self.__Width - xLRLimit + x + xOffset, yTopLimit - x + yOffset]        = GuiColor2

      # Elevation GUI at left
      # '   ------------     -----------   '
      for x in range(xLRLimit, self.__MidHeight - yCenterLimit):
         GUI[xLeftLimit, x]                     = GuiColor
         GUI[xLeftLimit + 1, x]                 = GuiColor
         GUI[xLeftLimit + yOffset, x - xOffset] = GuiColor2
      for x in range( self.__MidHeight + yCenterLimit, self.__Height - xLRLimit):
         GUI[xLeftLimit, x]                     = GuiColor
         GUI[xLeftLimit + 1, x]                 = GuiColor
         GUI[xLeftLimit + yOffset, x + xOffset] = GuiColor2
      # '               \___/              '
      for x in range(0, elDiagLimit):
         GUI[xLeftLimit + x, self.__MidHeight - yCenterLimit + x]                     = GuiColor
         GUI[xLeftLimit + x + 1, self.__MidHeight - yCenterLimit + x]                 = GuiColor
         if x < elDiagLimit:
            GUI[xLeftLimit + x + 2, self.__MidHeight - yCenterLimit + x]              = GuiColor
         GUI[xLeftLimit + x + yOffset, self.__MidHeight - yCenterLimit + x - xOffset] = GuiColor2
      for x in range( self.__MidHeight - yCenterLimit + elDiagLimit, self.__MidHeight + yCenterLimit - elDiagLimit):
         GUI[xRightLimit + elDiagLimit - azDiagLimit, x]                                                        = GuiColor
         GUI[xRightLimit + 1 + elDiagLimit - azDiagLimit, x]                                                    = GuiColor
      for x in range( self.__MidHeight - yCenterLimit + elDiagLimit - xOffset, self.__MidHeight + yCenterLimit - elDiagLimit + xOffset):
         GUI[xRightLimit + yOffset + elDiagLimit - azDiagLimit, x]                                              = GuiColor2
      for x in range(0, elDiagLimit + 1):
         GUI[xLeftLimit + x, self.__MidHeight + yCenterLimit - x]                     = GuiColor
         GUI[xLeftLimit + x + 1, self.__MidHeight + yCenterLimit - x]                 = GuiColor
         if x < elDiagLimit:
            GUI[xLeftLimit + x + 2, self.__MidHeight + yCenterLimit - x]              = GuiColor
         GUI[xLeftLimit + x + yOffset, self.__MidHeight + yCenterLimit - x + xOffset] = GuiColor2
      # ' \                               /'
      for x in range(0, elDiagLimit):
         GUI[xLeftLimit - x, xLRLimit - x]                                            = GuiColor
         GUI[xLeftLimit - x + 1, xLRLimit - x]                                        = GuiColor
         if x > 0:
            GUI[xLeftLimit - x + 2, xLRLimit - x]                                     = GuiColor
         GUI[xLeftLimit - x + yOffset, xLRLimit - x - xOffset]                        = GuiColor2
      for x in range(0, elDiagLimit):
         GUI[xLeftLimit - x, self.__Height - xLRLimit + x]                            = GuiColor
         GUI[xLeftLimit - x + 1, self.__Height - xLRLimit + x]                        = GuiColor
         if x > 0:
            GUI[xLeftLimit - x + 2, self.__Height - xLRLimit + x]                     = GuiColor
         GUI[xLeftLimit - x + yOffset, self.__Height - xLRLimit + x + xOffset]        = GuiColor2
