QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = ElevatorSimulator
TEMPLATE = app

SOURCES += \
    ControlPanel.cpp \
    Elevator.cpp \
    Floor.cpp \
    Main.cpp \
    Passenger.cpp \
    SafetySystem.cpp \
    SimulatorGUI.cpp \
    LogConsole.cpp \
    AudioDisplay.cpp

HEADERS += \
    ControlPanel.h \
    Elevator.h \
    Floor.h \
    LogConsole.h \
    Passenger.h \
    SafetySystem.h \
    SimulatorGUI.h \
    AudioDisplay.h
