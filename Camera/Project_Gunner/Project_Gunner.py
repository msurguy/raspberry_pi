#
# Project Gunner
# Michael Han
# 2016-04-01
#

import picamera
import time
from HudClass import Hud
from PIL import Image, ImageDraw, ImageFont

# Video Resolution
VIDEO_HEIGHT = 480
VIDEO_WIDTH = 640

timer = 0

HUD = Hud('Project_Gunner_HUD', VIDEO_WIDTH, VIDEO_HEIGHT)

with picamera.PiCamera() as camera:
   camera.resolution = (VIDEO_WIDTH, VIDEO_HEIGHT)
   camera.framerate = 60
   camera.led = False
   camera.start_preview()

   #img = crossHair.copy()
   img = HUD.getBaseHud()
   overlay = camera.add_overlay(img.tostring(), layer = 3, alpha = 100) 

   time.sleep(1)
   try:
      while True:
         #img = HUD.getHud()

         curTime = int(time.clock())
         #HUD.setCompassDirection(az, el)
         if(curTime > timer):
            #HUD.setTime()
            timer = curTime
         
         HUD.setReticle()   
         img = HUD.OutputGUI
         overlay.update(img.tostring())
   finally:
      camera.remove_overlay(overlay)
