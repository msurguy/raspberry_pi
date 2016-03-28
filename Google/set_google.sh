#!/bin/bash

echo Backing up Epiphany Schema
sudo cp /usr/share/glib-2.0/schemas/org.gnome.epiphany.gschema.xml /usr/share/glib-2.0/schemas/org.gnome.epiphany.gschema.xml_backup

echo Copying modified Epiphany Schema
sudo cp ./org.gnome.epiphany.gschema.xml /usr/share/glib-2.0/schemas/org.gnome.epiphany.gschema.xml

echo Installing libglib2.0-bin
sudo apt-get install libglib2.0-bin

echo Compiling Schemas
sudo glib-compile-schemas /usr/share/glib-2.0/schemas
