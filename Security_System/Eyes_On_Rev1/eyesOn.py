# import libraries
import time
import os

while True: # do forever
   os.system('fswebcam -r 640x480 --save /home/pi/Desktop/SecurityCam/image.jpg')
   print('Took image');
   time.sleep(1);
