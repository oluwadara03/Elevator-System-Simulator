#include "Elevator.h"
#include <QDebug>

// Constructor, initializes elevator properties
Elevator::Elevator(int id, LogConsole *console, int initialFloor, bool goingUp)
    : id(id), currentFloor(initialFloor), targetFloor(initialFloor), numPassengers(0),
      isGoingUp(goingUp), state(Idle), movementLogged(false), logConsole(console), isOverloaded(false) {}

// Sets target floor and updates elevator state
void Elevator::setTargetFloor(int floor) {
    if (state != Emergency && currentFloor != floor && !isOverloaded) {
        targetFloor = floor;
        isGoingUp = (targetFloor > currentFloor);
        if (state != Moving) {
            state = Moving;
            movementLogged = false;
        }
    }
}

// Moves elevator one floor towards target, returns true if at target
bool Elevator::moveOneFloor() {
    if (state != Moving || currentFloor == targetFloor) return true;
    if (isGoingUp) {
        currentFloor++;
    } else {
        currentFloor--;
    }
    return currentFloor == targetFloor;
}

// Audio played when doors are opening or closing
void Elevator::openDoors() {
    if (state == DoorsOpening) {
        playAudio("bell");
    }
}
void Elevator::closeDoors() {
    if (state == DoorsClosing) {
        playAudio("bell");
    }
}

void Elevator::displayMessage(const QString &message) {
    logConsole->appendLog("AudioDisplay: Message - " + message + "\n");
}

void Elevator::playAudio(const QString &sound) {
    logConsole->appendLog("AudioDisplay: Playing sound - " + sound + "\n");
}

// Handles overload state and emergency actions
void Elevator::triggerOverload() {
    isOverloaded = true;
    state = Emergency;
    displayMessage("Overload detected! Elevator stopped");
    playAudio("warning");
}
