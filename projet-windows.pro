# Inclure les modules Core et Gui
QT          += core
QT          += gui
QT          += widgets #permet de faire un include <widgets>
QT          += serialport #permet de faire un include <serialport> RS232

# version de QT 6.9.2
# Date : Septembre 2025

# Nom de l executable : Balance_KERN_rs232.exe
TARGET = "Balance_KERN_rs232"

TEMPLATE = app

#qmake option
CONFIG += release
CONFIG += qt
CONFIG += thread
CONFIG -= debug

MOC_DIR      = moc
OBJECTS_DIR  = obj
DESTDIR      = release
UI_DIR       = ui

HEADERS     += fenetre_parametres.h
HEADERS     += fenetre_rs232.h
HEADERS     += threadtpg300.h
HEADERS     += tpg300.h
#HEADERS     += *.h

SOURCES     += fenetre_parametres.cpp
SOURCES     += fenetre_rs232.cpp
SOURCES     += fonctions_dialogues.cpp
SOURCES     += main.cpp
SOURCES     += send_receive.cpp
SOURCES     += threadtpg300.cpp
SOURCES     += tpg300.cpp
#SOURCES     += *.cpp

FORMS       += fenetre_parametres.ui
FORMS       += fenetre_rs232.ui
FORMS       += tpg300.ui
#FORMS       += *.ui



