#!/bin/bash

echo Update the Firmware
sudo rpi-update

echo Installing QT
sudo apt-get install qt4-dev-tools
sudo apt-get install qtcreator
sudo apt-get install gcc
sudo apt-get install cmake
sudo apt-get install git-core

echo Installing Pinta paint app
sudo apt-get install pinta