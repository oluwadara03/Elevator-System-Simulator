#ifndef PASSENGER_H
#define PASSENGER_H

// Passenger class - Deals with passengers directly
class Passenger {
public:
    // Constructors
    Passenger();
    Passenger(int id, int startFloor = 1, int destFloor = 1, int timestepReq = 1);

    // Public Functions in the Passenger Class (Getters)
    int getId() const { return id; }
    int getStartFloor() const { return startFloor; }
    int getDestFloor() const { return destFloor; }
    int getTimestepRequest() const { return timestepReq; }
    int getCurrentFloor() const { return currentFloor; }
    bool getIsOnElevator() const { return isOnElevator; }
    bool getPressOpenDoor() const { return pressOpenDoor; }
    bool getPressCloseDoor() const { return pressCloseDoor; }
    bool getObstructDoor() const { return obstructDoor; }
    bool getGoingUp() const { return goingUp; }
    int getElevatorNum() const { return elevatorNum; }
    bool getHasBoarded() const { return hasBoarded; }

    // Public Functions in the Passenger Class (Setters)
    void setCurrentFloor(int floor);
    void setIsOnElevator(bool check);
    void setPressOpenDoor(bool check);
    void setPressCloseDoor(bool check);
    void setObstructDoor(bool check);
    void setElevatorNum(int num);
    void setHasBoarded(bool boarded);

    // Public Functions in the Passenger Class (Actions)
    void update(int start, int dest, int ts, bool openDoor, bool closeDoor, bool obstruct);
    bool hasArrived() const;

private:
    // Private variables in the Passenger Class
    int id;
    int startFloor;
    int destFloor;
    int timestepReq;
    int currentFloor;
    bool isOnElevator;
    bool goingUp;
    int elevatorNum;
    bool hasBoarded;
    bool pressOpenDoor;
    bool pressCloseDoor;
    bool obstructDoor;
};

#endif // PASSENGER_H
