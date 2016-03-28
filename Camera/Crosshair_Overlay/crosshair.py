import picamera
import numpy

crosshairArray = numpy.zeros((480, 640, 3), dtype=numpy.uint8)
crosshairArray[240, :, :] = 0xff
crosshairArray[:, 320, :] = 0xff

blankArray = numpy.zeros((480, 640, 3), dtype=numpy.uint8)

with picamera.PiCamera() as camera:
   camera.resolution = (640, 480)
   camera.framerate = 60
   camera.led = False
   camera.start_preview()

   overlay = camera.add_overlay(np.getbuffer(crosshairArray), layer = 3, alpha = 64)

   try:
       while True:
           time.sleep(1)
   finally:
       camera.remove_overlay(overlay)
