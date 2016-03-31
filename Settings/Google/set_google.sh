#!/bin/bash

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