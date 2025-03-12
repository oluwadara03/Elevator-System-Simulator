#include "SafetySystem.h"

// Constructor, initializes safety system flags
SafetySystem::SafetySystem() : fireAlarmActive(false), powerOutageActive(false) {}

// Triggers fire alarm, sends all elevators to floor 1
void SafetySystem::triggerFireAlarm(std::vector<Elevator>& elevators) {
    fireAlarmActive = true;
    for (auto& elevator : elevators) {
        elevator.setTargetFloor(1);
        if (elevator.getCurrentFloor() != 1) {
            elevator.setState(Elevator::Moving);
        }
    }
}

// Triggers power outage, sends all elevators to floor 1
void SafetySystem::triggerPowerOutage(std::vector<Elevator>& elevators) {
    powerOutageActive = true;
    for (auto& elevator : elevators) {
        elevator.setTargetFloor(1);
        if (elevator.getCurrentFloor() != 1) {
            elevator.setState(Elevator::Moving);
        }
    }
}

// Triggers the alarm if the passenger presses the help button
void SafetySystem::triggerHelpAlarm(int elevatorId) {
    (void)elevatorId;
}

// Checks for door obstruction and triggers emergency if exceeded
void SafetySystem::checkDoorObstacle(Elevator& elevator, int& obstacleCount, bool obstructed) {
    if (obstructed) {
        obstacleCount++;
        if (obstacleCount >= 3) {
            elevator.setState(Elevator::Emergency);
            elevator.playAudio("warning");
            elevator.displayMessage("Door obstructed too many times - Emergency mode");
        }
    } else {
        obstacleCount = 0;
    }
}
