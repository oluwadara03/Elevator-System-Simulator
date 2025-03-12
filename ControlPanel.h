#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QVector>

// ControlPanel class - Allows the Elevator Administrator to control the main things
class ControlPanel {
public:
    // Constructor
    ControlPanel(int numFloors);

    // Public Functions in the ControlPanel Class (Getters)
    bool getOpenDoorButton() const { return openDoorButton; }
    bool getCloseDoorButton() const { return closeDoorButton; }
    bool getHelpButton() const { return helpButton; }
    const QVector<bool>& getFloorButtons() const { return floorButtons; }

    // Public Functions in the ControlPanel Class (Actions)
    void pressOpenDoor();
    void pressCloseDoor();
    void pressHelp();
    void selectFloor(int floor);
    void reset();

private:
    // Private variables in the ControlPanel Class
    QVector<bool> floorButtons;
    bool openDoorButton;
    bool closeDoorButton;
    bool helpButton;
};

#endif // CONTROLPANEL_H
