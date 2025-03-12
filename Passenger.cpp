#include "Passenger.h"

// Default constructor, initializes passenger with default values
Passenger::Passenger()
    : id(0), startFloor(1), destFloor(1), timestepReq(1), currentFloor(1),
      isOnElevator(false), pressOpenDoor(false), pressCloseDoor(false),
      obstructDoor(false), goingUp(false), elevatorNum(-1), hasBoarded(false) {}

// Constructor, initializes passenger with specified values
Passenger::Passenger(int id, int startFloor, int destFloor, int timestepReq)
    : id(id), startFloor(startFloor), destFloor(destFloor), timestepReq(timestepReq),
      currentFloor(startFloor), isOnElevator(false), pressOpenDoor(false),
      pressCloseDoor(false), obstructDoor(false), goingUp(destFloor > startFloor),
      elevatorNum(-1), hasBoarded(false) {}

// Sets values used for logging in relation to passenger behavior
void Passenger::setCurrentFloor(int floor) {
    currentFloor = floor;
}
void Passenger::setIsOnElevator(bool check) {
    isOnElevator = check;
}
void Passenger::setElevatorNum(int num) {
    elevatorNum = num;
}
void Passenger::setHasBoarded(bool boarded) {
    hasBoarded = boarded;
}
void Passenger::setPressOpenDoor(bool check) {
    pressOpenDoor = check;
}
void Passenger::setPressCloseDoor(bool check) {
    pressCloseDoor = check;
}
void Passenger::setObstructDoor(bool check) {
    obstructDoor = check;
}

// Updates passenger properties with new values
void Passenger::update(int start, int dest, int ts, bool openDoor, bool closeDoor, bool obstruct) {
    currentFloor = start;
    pressCloseDoor = closeDoor;
    pressOpenDoor = openDoor;
    obstructDoor = obstruct;
    startFloor = start;
    destFloor = dest;
    timestepReq = ts;
    goingUp = (dest > start);
    isOnElevator = false;
    elevatorNum = -1;
    hasBoarded = false;
    if (!isOnElevator) {
        currentFloor = start;
    }
}

// Checks if passenger has reached destination and is off elevator
bool Passenger::hasArrived() const {
    return currentFloor == destFloor && !isOnElevator;
}
