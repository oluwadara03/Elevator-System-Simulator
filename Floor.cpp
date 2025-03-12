#include "Floor.h"

// Constructor, initializes floor properties
Floor::Floor(int floorNumber) : floorNumber(floorNumber), upRequested(false), downRequested(false) {}

// Passengers can request to go down or up in a building
void Floor::pressDownButton() {
    downRequested = true;
}
void Floor::pressUpButton() {
    upRequested = true;
}

// Resets both request buttons
void Floor::resetButtons() {
    upRequested = false;
    downRequested = false;
}

void Floor::requestElevator(bool goingUp) {
    if (goingUp) {
        pressUpButton();
    } else {
        pressDownButton();
    }
}

void Floor::clearRequest(bool goingUp) {
    if (goingUp) {
        upRequested = false;
    } else {
        downRequested = false;
    }
}
