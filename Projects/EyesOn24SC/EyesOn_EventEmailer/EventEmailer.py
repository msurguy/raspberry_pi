#
# Event Emailer for Eyes On 24 Security Camera
# Michael Han
# 2016-07-03
#

import time
import sys
import os

# Parse the command line arguments
eventNum = sys.argv[1]
year = sys.argv[2]
month = sys.argv[3]
day = sys.argv[4]
hour = sys.argv[5]
minute = sys.argv[6]
second = sys.argv[7]

# Email account settings for Outlook.com
#smtp = "smtp-mail.outlook.com:587"
#emailUN = "eyeson24sc@outlook.com"
#emailPW = "darkCRASH0524*@"
#fromAddress = "eyeson24sc@outlook.com"

# Email account settings for Gmail.com
smtp = "smtp.gmail.com:587"
emailUN = "eyeson24sc@gmail.com"
emailPW = "darkCRASH0524*@"
fromAddress = "EyesOn24 SecurityCam <eyeson24sc@gmail.com>"

# Settings for the email client
emailClient = "sendEmail"
toAddress = "mike.han.83@gmail.com"
emailSubject = "Alert: Movement Detected at " + hour + ":" + minute + ":" + second
emailBody = "Movement detected at " + hour + ":" + minute + ":" + second
TLS = "-o tls=yes"

# Create the path to the video
videoLocation = "/home/pi/Desktop/CamPictures/motion/Events/"
videoLocation += month + "-" + day + "-" + year + "/"
#videoLocation += "Event_" + eventNum + "_" + hour + ":" + minute + ":" + second + ".avi"
videoLocation += "Event_" + eventNum + ".avi"

# Create the path to the image
pictureLocation = "/home/pi/Desktop/CamPictures/motion/motionImage.jpg"

#
# Create the command string
#
cmd = "echo Sending Email | "

# Add the email client to command
cmd += emailClient + " "

# Add the from address
cmd += "-f '" + fromAddress + "' "

# Add the to address
cmd += "-t " + toAddress + " "

# Add the picture attachment to command
cmd += "-a " + pictureLocation + " "

# Add the video attachment to command
#cmd += "-a " + videoLocation + " "

# Add the Subject to the email
cmd += "-u '" + emailSubject + "' "

# Add the Body Message
cmd += "-m '" + emailBody + "' " + videoLocation + " "

# Add the SMTP settings
cmd += "-s " + smtp + " "

# Add the user name
cmd += "-xu " + emailUN + " "

# Add the password
cmd += "-xp " + emailPW + " "

# Add TLS
cmd += TLS

print cmd
os.system(cmd)
