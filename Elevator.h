#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QString>
#include "LogConsole.h"

// Elevator class - Functions of eleevators in the Simulator
class Elevator {
public:
    // Enum for Elevator states - all possible states of the elevators
    enum State { Idle, Moving, Arrived, DoorsOpening, DoorsOpen, DoorsClosing, DoorsClosed, Emergency };

    // Constructor
    Elevator(int id, LogConsole *console, int initialFloor = 1, bool goingUp = true);

    // Public Functions in the Elevator Class (Getters)
    int getId() const { return id; }
    int getCurrentFloor() const { return currentFloor; }
    int getTargetFloor() const { return targetFloor; }
    int getNumPassengers() const { return numPassengers; }
    bool getIsGoingUp() const { return isGoingUp; }
    State getState() const { return state; }
    bool getMovementLogged() const { return movementLogged; }
    bool checkCapacity() const { return numPassengers >= maxCapacity; }

    // Public Functions in the Elevator Class (Setters)
    void setNumPassengers(int num) { numPassengers = num; }
    void setTargetFloor(int floor);
    void setState(State s) { state = s; }
    void setMovementLogged(bool logged) { movementLogged = logged; }

    // Public Functions in the Elevator Class (Actions)
    bool moveOneFloor();
    void openDoors();
    void closeDoors();
    void displayMessage(const QString &message);
    void playAudio(const QString &sound);
    void triggerOverload();

private:
    // Private variables in the Elevator Class
    int id;
    int currentFloor;
    int targetFloor;
    LogConsole *logConsole;
    State state;
    bool movementLogged;
    int numPassengers;
    bool isGoingUp;
    // Maximum number of people allowed in 1 elevator at a time
    const int maxCapacity = 10;
    bool isOverloaded;
};

#endif // ELEVATOR_H
