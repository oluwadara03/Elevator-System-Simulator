#include "ControlPanel.h"

// Constructor, initializes buttons and floor button array
ControlPanel::ControlPanel(int numFloors) : openDoorButton(false), closeDoorButton(false), helpButton(false) {
    floorButtons = QVector<bool>(numFloors, false);
}

// Close, open and help buttons implementation
void ControlPanel::pressCloseDoor() {
    closeDoorButton = true;
}
void ControlPanel::pressOpenDoor() {
    openDoorButton = true;
}
void ControlPanel::pressHelp() {
    helpButton = true;
}

void ControlPanel::selectFloor(int floor) {
    int maxFloors = floorButtons.size();
    if (floor >= 0 && floor < maxFloors) {
        floorButtons[floor] = true;
    }
}

// Resets all buttons to unpressed state
void ControlPanel::reset() {
    openDoorButton = false;
    closeDoorButton = false;
    helpButton = false;
    for (int i = 0; i < floorButtons.size(); ++i) {
        floorButtons[i] = false;
    }
}
