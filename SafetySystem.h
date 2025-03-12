#ifndef SAFETY_SYSTEM_H
#define SAFETY_SYSTEM_H

#include <vector>
#include "Elevator.h"

// SafetySystem class - Handles safety scenarios
class SafetySystem {
public:
    // Constructor
    SafetySystem();

    // Public Functions in the SafetySystem Class
    void checkDoorObstacle(Elevator& elevator, int& obstacleCount, bool obstructed);
    void triggerFireAlarm(std::vector<Elevator>& elevators);
    void triggerHelpAlarm(int elevatorId);
    void triggerPowerOutage(std::vector<Elevator>& elevators);


private:
    // Private variables in the SafetySystem Class
    bool fireAlarmActive;
    bool powerOutageActive;
};

#endif // SAFETY_SYSTEM_H
