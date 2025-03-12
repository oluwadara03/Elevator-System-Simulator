#ifndef SIMULATORGUI_H
#define SIMULATORGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSlider>
#include <QCheckBox>
#include <QTimer>
#include <vector>
#include "Elevator.h"
#include "Passenger.h"
#include "Floor.h"
#include "LogConsole.h"

// Forward declaration
class SafetySystem;

// SimulatorGUI class inherits QMainWindow Class - Manages the simmulator and GUI
class SimulatorGUI : public QMainWindow {
    Q_OBJECT
public:
    // Enum for Simulator states
    enum class State { Idle, Configuring, Ready, Running, Paused, Stopped, Finished, Returning };

    // Constructor
    explicit SimulatorGUI(QWidget *parent = nullptr);

    // Destructor
    ~SimulatorGUI();

    // Public Functions in the SimulatorGUI Class
    void logEvent(const QString &message);

private slots:
    // Private Slots in the SimulatorGUI Class
    void triggerFire();
    void triggerPowerOutage();
    void triggerHelp();
    void triggerOverload();
    void startSimulation();
    void pauseSimulation();
    void stopSimulation();
    void submitSimulationSettings();
    void submitPassengerSettings();
    void advanceTimestep();

private:
    // Private Functions in the SimulatorGUI Class
    void setupUI();
    void connectSignals();
    void initializeSimulation();

    // Private variables in the SimulatorGUI Class (UI Elements) - In place of a UI file
    QComboBox *numFloorsCombo;
    QComboBox *numElevatorsCombo;
    QComboBox *passengerSelectCombo;
    QComboBox *elevatorSelectCombo;
    QLineEdit *startFloorEdit;
    QLineEdit *destFloorEdit;
    QSlider *timestepSlider;
    QCheckBox *openDoorCheck;
    QCheckBox *closeDoorCheck;
    QCheckBox *obstructDoorCheck;
    QPushButton *setPassengerButton;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *stopButton;
    QPushButton *fireButton;
    QPushButton *powerOutButton;
    QPushButton *helpButton;
    QPushButton *overloadButton;
    QPushButton *initializeButton;
    QSlider *numPassengersSlider;
    QLabel *timestepLabel;
    QLabel *numPassengersValueLabel;
    QLabel *timestepValueLabel;

    // Private variables in the SimulatorGUI Class (Simulation Data)
    LogConsole *logConsole;
    QTimer timer;
    int currentTimestep;

    std::vector<Elevator> elevators;
    std::vector<Passenger> passengers;
    std::vector<Floor> floors;
    std::vector<int> obstacleCount;
    int numFloors, numElevators, numPassengers;

    SafetySystem *safetySystem;
    State state;
};

#endif // SIMULATORGUI_H
