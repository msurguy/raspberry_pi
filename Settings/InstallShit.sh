#!/bin/bash

echo Updating the distro
sudo apt-get update
sudo apt-get upgrade
sudo apt-get dist-upgrade
sudo apt-get clean

echo Update the Firmware
sudo rpi-update

echo Installing QT
sudo apt-get install qtcreator
sudo apt-get install qt5-qmake
sudo apt-get install qt5-default
sudo apt-get install gcc
sudo apt-get install cmake
sudo apt-get install git-core

echo Installing Pinta paint app
sudo apt-get install pinta

echo Backing up Epiphany Schema
sudo cp /usr/share/glib-2.0/schemas/org.gnome.epiphany.gschema.xml /usr/share/glib-2.0/schemas/org.gnome.epiphany.gschema.xml_backup

echo Copying modified Epiphany Schema
sudo cp ./org.gnome.epiphany.gschema.xml /usr/share/glib-2.0/schemas/org.gnome.epiphany.gschema.xml

echo Installing libglib2.0-bin
sudo apt-get install libglib2.0-bin

echo Compiling Schemas
sudo glib-compile-schemas /usr/share/glib-2.0/schemas

echo Downloading Chromium
wget https://dl.dropboxusercontent.com/u/87113035/chromium-browser-l10n_48.0.2564.82-0ubuntu0.15.04.1.1193_all.deb
wget https://dl.dropboxusercontent.com/u/87113035/chromium-browser_48.0.2564.82-0ubuntu0.15.04.1.1193_armhf.deb
wget https://dl.dropboxusercontent.com/u/87113035/chromium-codecs-ffmpeg-extra_48.0.2564.82-0ubuntu0.15.04.1.1193_armhf.deb
sudo dpkg -i chromium-codecs-ffmpeg-extra_48.0.2564.82-0ubuntu0.15.04.1.1193_armhf.deb
sudo dpkg -i chromium-browser-l10n_48.0.2564.82-0ubuntu0.15.04.1.1193_all.deb chromium-browser_48.0.2564.82-0ubuntu0.15.04.1.1193_armhf.deb

echo Installing Motion Cam
sudo apt-get install motion

echo Installing Command Line Email client
sudo apt-get install postfix
sudo apt-get install sendemail
sudo apt-get install libio-socket-ssl-perl libnet-ssleay-perl

echo Installing light weight video player
sudo apt-get install omxplayer

echo Installing Mono
sudo apt-get install mono-complete
sudo apt-get install monodevelop