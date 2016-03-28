import picamera
import time
import numpy

# Defines for script
DEF_PYTHON_COMP = 3.2

# Cross Hair Array
crosshairArray = numpy.zeros((480, 640, 3), dtype=numpy.uint8)
crosshairArray[240, :, :] = 0xff
crosshairArray[:, 320, :] = 0xff

# Blank Screen
blankArray = numpy.zeros((480, 640, 3), dtype=numpy.uint8)

overlayOn = True

with picamera.PiCamera() as camera:
   camera.resolution = (640, 480)
   camera.framerate = 60
   camera.led = False
   camera.start_preview()

   if DEF_PYTHON_COMP == 2.7:
      overlay = camera.add_overlay(numpy.getbuffer(crosshairArray), layer = 3, alpha = 64)
   else:
      overlay = camera.add_overlay(memoryview(crosshairArray), layer = 3, alpha = 20) 

   time.sleep(1)
   try:
      while True:
         # Turn overlay off if it's on
         if overlayOn:
            if DEF_PYTHON_COMP == 2.7:
               overlay.update(numpy.getbuffer(blankArray))
            else:
               overlay.update(memoryview(blankArray))
         else:
            if DEF_PYTHON_COMP == 2.7:
               overlay.update(numpy.getbuffer(crosshairArray))
            else:
               overlay.update(memoryview(crosshairArray))

         overlayOn = not overlayOn

         print('Overlay is: ', overlayOn)
         time.sleep(1)
   finally:
       camera.remove_overlay(overlay)
