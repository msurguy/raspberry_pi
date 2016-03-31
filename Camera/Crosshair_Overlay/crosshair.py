import picamera
import time
import numpy
import TextOverlay


# Video Resolution
txtoverlay = TextOverlay.TextOverlayClass(480, 640)

# Cross Hair Array
crosshairArray = numpy.zeros((txtoverlay.GetHeight(), txtoverlay.GetWidth(), 3), dtype=numpy.uint8)
crosshairArray[240, :, :] = 0xff
crosshairArray[:, 320, :] = 0xff

# Blank Screen
blankArray = numpy.zeros((VIDEO_HEIGHT, VIDEO_WIDTH, 3), dtype=numpy.uint8)

overlayOn = True

with picamera.PiCamera() as camera:
   camera.resolution = (VIDEO_WIDTH, VIDEO_HEIGHT)
   camera.framerate = 60
   camera.led = False
   camera.start_preview()

   overlay = camera.add_overlay(memoryview(crosshairArray), layer = 3, alpha = 20) 

   time.sleep(1)
   try:
      while True:
         # Turn overlay off if it's on
         if overlayOn:
            overlay.update(memoryview(blankArray))
         else:
            overlay.update(memoryview(crosshairArray))

         overlayOn = not overlayOn

         time.sleep(1)
   finally:
       camera.remove_overlay(overlay)
