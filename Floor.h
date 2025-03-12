#ifndef FLOOR_H
#define FLOOR_H

// Floor class - Deals with passenger requests
class Floor {
public:
    // Constructor
    Floor(int floorNum);

    // Public Functions in the Floor Class (Getters)
    int getFloorNumber() const { return floorNumber; }
    bool isUpRequested() const { return upRequested; }
    bool isDownRequested() const { return downRequested; }

    // Public Functions in the Floor Class (Actions)
    void clearRequest(bool goingUp);
    void pressUpButton();
    void pressDownButton();
    void requestElevator(bool goingUp);
    void resetButtons();

private:
    // Private variables in the Floor Class
    bool downRequested;
    int floorNumber;
    bool upRequested;
};

#endif // FLOOR_H
