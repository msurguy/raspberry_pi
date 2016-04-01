import picamera
import time
import numpy
from PIL import Image, ImageDraw, ImageFont


# Video Resolution
VIDEO_HEIGHT = 480
VIDEO_WIDTH = 640

# Cross Hair Image
crossHair = Image.new("RGB", (VIDEO_WIDTH, VIDEO_HEIGHT))
crossHairPixels = crossHair.load()
for x in range (0, VIDEO_WIDTH):
   crossHairPixels[x, 240] = (255, 0, 0)

for x in range(0, VIDEO_HEIGHT):
   crossHairPixels[320, x] = (255, 0, 0)

with picamera.PiCamera() as camera:
   camera.resolution = (VIDEO_WIDTH, VIDEO_HEIGHT)
   camera.framerate = 60
   camera.led = False
   camera.start_preview()

   img = crossHair.copy()
   overlay = camera.add_overlay(img.tostring(), layer = 3, alpha = 100) 

   time.sleep(1)
   try:
      while True:
         text = time.strftime('%H:%M:%S', time.gmtime())
         img = crossHair.copy()
         draw = ImageDraw.Draw(img)
         draw.font = ImageFont.truetype("/usr/share/fonts/truetype/freefont/FreeSerif.ttf", 50)
         draw.text((10, 10), text, (255, 255, 255))
         
         overlay.update(img.tostring())

         time.sleep(1)
   finally:
      camera.remove_overlay(overlay)
