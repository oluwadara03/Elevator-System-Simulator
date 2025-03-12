#include "SimulatorGUI.h"
#include "SafetySystem.h"
#include <QGridLayout>
#include <QPalette>
#include <QApplication>
#include <QStyleFactory>
#include <QIntValidator>

// Constructor, initializes GUI with safety system and custom styling
SimulatorGUI::SimulatorGUI(QWidget *parent) : QMainWindow(parent), currentTimestep(0), state(State::Idle) {
    safetySystem = new SafetySystem();
    setupUI();
    connectSignals();
    setWindowTitle("Elevator Simulator");
    resize(1200, 800);

    QPalette palette;
    palette.setColor(QPalette::Button, QColor("#ADD8E6"));
    palette.setColor(QPalette::Window, QColor("#E6E6FA"));
    palette.setColor(QPalette::ButtonText, QColor("#333333"));
    palette.setColor(QPalette::WindowText, QColor("#333333"));
    setPalette(palette);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
}

// Destructor, cleans up safety system
SimulatorGUI::~SimulatorGUI() {
    delete safetySystem;
}

// Sets up the user interface with widgets and layout
void SimulatorGUI::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QGridLayout *mainLayout = new QGridLayout(centralWidget);
    mainLayout->setSpacing(15);

    numFloorsCombo = new QComboBox(this);
    for (int i = 1; i <= 5; ++i) numFloorsCombo->addItem(QString::number(i));
    numFloorsCombo->setStyleSheet("QComboBox { background-color: #D8BFD8; border-radius: 5px; padding: 5px; }");

    numElevatorsCombo = new QComboBox(this);
    for (int i = 1; i <= 5; ++i) numElevatorsCombo->addItem(QString::number(i));
    numElevatorsCombo->setStyleSheet("QComboBox { background-color: #D8BFD8; border-radius: 5px; padding: 5px; }");

    numPassengersSlider = new QSlider(Qt::Horizontal, this);
    numPassengersSlider->setRange(1, 10);
    numPassengersSlider->setValue(1);
    numPassengersSlider->setStyleSheet("QSlider::groove:horizontal { background: #ADD8E6; height: 8px; border-radius: 4px; } "
                                       "QSlider::handle:horizontal { background: #FFB6C1; width: 20px; border-radius: 10px; }");
    numPassengersValueLabel = new QLabel("1", this);

    initializeButton = new QPushButton("Initialize", this);
    initializeButton->setStyleSheet("QPushButton { background-color: #FFB6C1; color: #333333; border-radius: 10px; padding: 8px; } "
                                    "QPushButton:hover { background-color: #FFD1DC; }");

    mainLayout->addWidget(new QLabel("Floors:"), 0, 0);
    mainLayout->addWidget(numFloorsCombo, 0, 1);
    mainLayout->addWidget(new QLabel("Elevators:"), 1, 0);
    mainLayout->addWidget(numElevatorsCombo, 1, 1);
    mainLayout->addWidget(new QLabel("Passengers:"), 2, 0);
    mainLayout->addWidget(numPassengersSlider, 2, 1);
    mainLayout->addWidget(numPassengersValueLabel, 2, 2);
    mainLayout->addWidget(initializeButton, 3, 0, 1, 2);

    passengerSelectCombo = new QComboBox(this);
    passengerSelectCombo->setStyleSheet("QComboBox { background-color: #D8BFD8; border-radius: 5px; padding: 5px; }");

    startFloorEdit = new QLineEdit(this);
    startFloorEdit->setValidator(new QIntValidator(1, 5, this));
    startFloorEdit->setText("1");
    startFloorEdit->setStyleSheet("QLineEdit { background-color: #F0F8FF; border: 1px solid #ADD8E6; border-radius: 5px; padding: 5px; }");

    destFloorEdit = new QLineEdit(this);
    destFloorEdit->setValidator(new QIntValidator(1, 5, this));
    destFloorEdit->setText("1");
    destFloorEdit->setStyleSheet("QLineEdit { background-color: #F0F8FF; border: 1px solid #ADD8E6; border-radius: 5px; padding: 5px; }");

    timestepSlider = new QSlider(Qt::Horizontal, this);
    timestepSlider->setRange(1, 100);
    timestepSlider->setValue(1);
    timestepSlider->setStyleSheet("QSlider::groove:horizontal { background: #ADD8E6; height: 8px; border-radius: 4px; } "
                                  "QSlider::handle:horizontal { background: #FFB6C1; width: 20px; border-radius: 10px; }");
    timestepValueLabel = new QLabel("1", this);

    openDoorCheck = new QCheckBox("Open Door", this);
    closeDoorCheck = new QCheckBox("Close Door", this);
    obstructDoorCheck = new QCheckBox("Obstruct", this);

    setPassengerButton = new QPushButton("Set Passenger", this);
    setPassengerButton->setStyleSheet("QPushButton { background-color: #B0C4DE; color: #333333; border-radius: 10px; padding: 8px; } "
                                      "QPushButton:hover { background-color: #C7D6E8; }");

    mainLayout->addWidget(new QLabel("Passenger ID:"), 4, 0);
    mainLayout->addWidget(passengerSelectCombo, 4, 1);
    mainLayout->addWidget(new QLabel("Start Floor:"), 5, 0);
    mainLayout->addWidget(startFloorEdit, 5, 1);
    mainLayout->addWidget(new QLabel("Destination Floor:"), 6, 0);
    mainLayout->addWidget(destFloorEdit, 6, 1);
    mainLayout->addWidget(new QLabel("Timestep:"), 7, 0);
    mainLayout->addWidget(timestepSlider, 7, 1);
    mainLayout->addWidget(timestepValueLabel, 7, 2);
    mainLayout->addWidget(openDoorCheck, 8, 0);
    mainLayout->addWidget(closeDoorCheck, 8, 1);
    mainLayout->addWidget(obstructDoorCheck, 9, 0);
    mainLayout->addWidget(setPassengerButton, 10, 0, 1, 2);

    startButton = new QPushButton("Start", this); startButton->setFixedSize(80, 80);
    startButton->setStyleSheet("QPushButton { background-color: #98FB98; color: #333333; border-radius: 40px; } "
                               "QPushButton:hover { background-color: #B0FFB0; }");
    pauseButton = new QPushButton("Pause", this); pauseButton->setFixedSize(80, 80);
    pauseButton->setStyleSheet("QPushButton { background-color: #FFD700; color: #333333; border-radius: 40px; } "
                               "QPushButton:hover { background-color: #FFE766; }");
    stopButton = new QPushButton("Stop", this); stopButton->setFixedSize(80, 80);
    stopButton->setStyleSheet("QPushButton { background-color: #FF9999; color: #333333; border-radius: 40px; } "
                              "QPushButton:hover { background-color: #FFB3B3; }");
    timestepLabel = new QLabel("Timestep: 0", this);
    timestepLabel->setStyleSheet("QLabel { font-size: 20px; color: #FF69B4; }");

    mainLayout->addWidget(startButton, 0, 2, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(pauseButton, 1, 2, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(stopButton, 2, 2, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(timestepLabel, 3, 2, 1, 1, Qt::AlignCenter);

    fireButton = new QPushButton("Fire Alert", this);
    fireButton->setStyleSheet("QPushButton { background-color: #FFA07A; color: #333333; border-radius: 10px; padding: 8px; } "
                              "QPushButton:hover { background-color: #4A4A4A; }");
    powerOutButton = new QPushButton("Power Failure", this);
    powerOutButton->setStyleSheet("QPushButton { background-color: #FFA07A; color: #333333; border-radius: 10px; padding: 8px; } "
                                  "QPushButton:hover { background-color: #4A4A4A; }");
    elevatorSelectCombo = new QComboBox(this);
    elevatorSelectCombo->setStyleSheet("QComboBox { background-color: #D8BFD8; border-radius: 5px; padding: 5px; }");
    helpButton = new QPushButton("Help", this);
    helpButton->setStyleSheet("QPushButton { background-color: #FFA07A; color: #333333; border-radius: 10px; padding: 8px; } "
                              "QPushButton:hover { background-color: #4A4A4A; }");
    overloadButton = new QPushButton("Overload", this);
    overloadButton->setStyleSheet("QPushButton { background-color: #FFA07A; color: #333333; border-radius: 10px; padding: 8px; } "
                                  "QPushButton:hover { background-color: #4A4A4A; }");

    mainLayout->addWidget(fireButton, 0, 3);
    mainLayout->addWidget(powerOutButton, 1, 3);
    mainLayout->addWidget(new QLabel("Elevator:"), 2, 3);
    mainLayout->addWidget(elevatorSelectCombo, 3, 3);
    mainLayout->addWidget(helpButton, 4, 3);
    mainLayout->addWidget(overloadButton, 5, 3);

    logConsole = new LogConsole(this);
    logConsole->setStyleSheet("QTextEdit { background-color: #F0F8FF; color: #333333; border-radius: 10px; padding: 10px; font-family: 'Courier New'; }");
    mainLayout->addWidget(logConsole, 0, 4, 11, 2);

    startButton->setEnabled(false);
    pauseButton->setEnabled(false);
    stopButton->setEnabled(false);
    setPassengerButton->setEnabled(false);
    fireButton->setEnabled(false);
    powerOutButton->setEnabled(false);
    helpButton->setEnabled(false);
    overloadButton->setEnabled(false);

    connect(numPassengersSlider, &QSlider::valueChanged, this, [this](int value) {
        numPassengersValueLabel->setText(QString::number(value));
    });
    connect(timestepSlider, &QSlider::valueChanged, this, [this](int value) {
        timestepValueLabel->setText(QString::number(value));
    });
}

// Connects button and timer signals to their slots
void SimulatorGUI::connectSignals() {
    connect(startButton, &QPushButton::clicked, this, &SimulatorGUI::startSimulation);
    connect(pauseButton, &QPushButton::clicked, this, &SimulatorGUI::pauseSimulation);
    connect(stopButton, &QPushButton::clicked, this, &SimulatorGUI::stopSimulation);
    connect(initializeButton, &QPushButton::clicked, this, &SimulatorGUI::submitSimulationSettings);
    connect(setPassengerButton, &QPushButton::clicked, this, &SimulatorGUI::submitPassengerSettings);
    connect(&timer, &QTimer::timeout, this, &SimulatorGUI::advanceTimestep);
    connect(fireButton, &QPushButton::clicked, this, &SimulatorGUI::triggerFire);
    connect(powerOutButton, &QPushButton::clicked, this, &SimulatorGUI::triggerPowerOutage);
    connect(helpButton, &QPushButton::clicked, this, &SimulatorGUI::triggerHelp);
    connect(overloadButton, &QPushButton::clicked, this, &SimulatorGUI::triggerOverload);
}

// Initializes simulation with elevators, passengers, and floors
void SimulatorGUI::initializeSimulation() {
    elevators.clear();
    passengers.clear();
    floors.clear();
    obstacleCount.clear();
    for (int i = 0; i < numElevators; ++i) {
        elevators.emplace_back(i + 1, logConsole, 1, i % 2 == 0);
        obstacleCount.push_back(0);
    }
    passengers.resize(numPassengers);
    for (int i = 0; i < numPassengers; ++i) {
        passengers[i] = Passenger(i + 1);
    }
    for (int i = 0; i < numFloors; ++i) {
        floors.emplace_back(i + 1);
    }
}

// Logs an event with the current timestep
void SimulatorGUI::logEvent(const QString &message) {
    logConsole->appendLog("Timestep " + QString::number(currentTimestep) + ": " + message + "\n");
}

void SimulatorGUI::startSimulation() {
    if (state == State::Ready || state == State::Paused) {
        state = State::Running;
        timer.start(1000);
        startButton->setEnabled(false);
        pauseButton->setEnabled(true);
        stopButton->setEnabled(true);
        fireButton->setEnabled(true);
        powerOutButton->setEnabled(true);
        helpButton->setEnabled(true);
        overloadButton->setEnabled(true);
        logEvent(state == State::Paused ? "Simulation resumed" : "Simulation started");
    }
}

void SimulatorGUI::pauseSimulation() {
    if (state == State::Running) {
        state = State::Paused;
        timer.stop();
        startButton->setEnabled(true);
        pauseButton->setEnabled(false);
        logEvent("Simulation paused");
    }
}

// Stops simulation and resets state
void SimulatorGUI::stopSimulation() {
    if (state == State::Running || state == State::Paused) {
        state = State::Stopped;
        timer.stop();
        currentTimestep = 0;
        timestepLabel->setText("Timestep: 0");
        startButton->setEnabled(false);
        pauseButton->setEnabled(false);
        stopButton->setEnabled(false);
        fireButton->setEnabled(false);
        powerOutButton->setEnabled(false);
        helpButton->setEnabled(false);
        overloadButton->setEnabled(false);
        logConsole->clear();
        logEvent("Simulation stopped");
        state = State::Idle;
    }
}

// Submits simulation settings and prepares for start
void SimulatorGUI::submitSimulationSettings() {
    if (state == State::Idle) {
        state = State::Configuring;
        logEvent("Configuring simulation...");
    }
    numFloors = numFloorsCombo->currentText().toInt();
    numElevators = numElevatorsCombo->currentText().toInt();
    numPassengers = numPassengersSlider->value();

    passengerSelectCombo->clear();
    for (int i = 1; i <= numPassengers; ++i) passengerSelectCombo->addItem(QString::number(i));
    startFloorEdit->setValidator(new QIntValidator(1, numFloors, this));
    destFloorEdit->setValidator(new QIntValidator(1, numFloors, this));
    elevatorSelectCombo->clear();
    for (int i = 1; i <= numElevators; ++i) elevatorSelectCombo->addItem(QString::number(i));

    initializeSimulation();

    state = State::Ready;
    startButton->setEnabled(true);
    setPassengerButton->setEnabled(true);
    logEvent("Simulation initialized with " + QString::number(numFloors) + " floors, " +
             QString::number(numElevators) + " elevators, and " + QString::number(numPassengers) + " passengers");
}

void SimulatorGUI::submitPassengerSettings() {
    if (state == State::Ready || state == State::Configuring) {
        int id = passengerSelectCombo->currentText().toInt();
        int start = startFloorEdit->text().toInt();
        int dest = destFloorEdit->text().toInt();
        int ts = timestepSlider->value();
        bool openDoor = openDoorCheck->isChecked();
        bool closeDoor = closeDoorCheck->isChecked();
        bool obstruct = obstructDoorCheck->isChecked();

        if (id > 0 && id <= static_cast<int>(passengers.size()) && start <= numFloors && dest <= numFloors) {
            passengers[id - 1].update(start, dest, ts, openDoor, closeDoor, obstruct);
            logEvent("Passenger " + QString::number(id) + " set: Start Floor " + QString::number(start) +
                     ", Dest Floor " + QString::number(dest) + ", Timestep " + QString::number(ts));
        }
    }
}

// Advances simulation by one timestep, handling passenger and elevator logic
void SimulatorGUI::advanceTimestep() {
    if (state != State::Running) return;
    currentTimestep++;
    timestepLabel->setText("Timestep: " + QString::number(currentTimestep));

    for (auto &passenger : passengers) {
        if (passenger.getTimestepRequest() == currentTimestep && !passenger.getIsOnElevator()) {
            logEvent("Passenger " + QString::number(passenger.getId()) + " requests elevator from floor " +
                     QString::number(passenger.getStartFloor()) + " to " + QString::number(passenger.getDestFloor()));
            floors[passenger.getStartFloor() - 1].requestElevator(passenger.getGoingUp());

            bool assigned = false;
            int bestElevatorIndex = -1;
            int minDistance = numFloors + 1;

            for (size_t i = 0; i < elevators.size(); ++i) {
                auto &elevator = elevators[i];
                int distance = abs(elevator.getCurrentFloor() - passenger.getStartFloor());
                bool isIdleOrClosed = (elevator.getState() == Elevator::Idle || elevator.getState() == Elevator::DoorsClosed);
                bool canServe = !elevator.checkCapacity() &&
                                (elevator.getCurrentFloor() == passenger.getStartFloor() ||
                                 (isIdleOrClosed && distance < minDistance) ||
                                 (elevator.getIsGoingUp() == passenger.getGoingUp() &&
                                  ((passenger.getGoingUp() && elevator.getCurrentFloor() < passenger.getStartFloor()) ||
                                   (!passenger.getGoingUp() && elevator.getCurrentFloor() > passenger.getStartFloor()))));

                if (canServe) {
                    if (distance < minDistance) {
                        minDistance = distance;
                        bestElevatorIndex = i;
                    }
                }
            }

            if (bestElevatorIndex != -1) {
                auto &elevator = elevators[bestElevatorIndex];
                passenger.setIsOnElevator(true);
                passenger.setElevatorNum(elevator.getId() - 1);
                elevator.setNumPassengers(elevator.getNumPassengers() + 1);
                elevator.setTargetFloor(passenger.getStartFloor());
                elevator.setState(Elevator::Moving);
                logEvent("Passenger " + QString::number(passenger.getId()) + " assigned to Elevator " +
                         QString::number(elevator.getId()) + " at floor " + QString::number(elevator.getCurrentFloor()) +
                         ", heading " + (elevator.getIsGoingUp() ? "up" : "down") + " to floor " +
                         QString::number(passenger.getStartFloor()));
                assigned = true;
            }

            if (!assigned) {
                QString reason = "All elevators are either full, in emergency, or too far/moving in wrong direction";
                logEvent("No available elevator for Passenger " + QString::number(passenger.getId()) + ": " + reason);
            }
        }
    }

    for (auto &elevator : elevators) {
        if (elevator.getState() == Elevator::Moving) {
            if (!elevator.getMovementLogged()) {
                logEvent("Elevator " + QString::number(elevator.getId()) + " moving " +
                         (elevator.getIsGoingUp() ? "up" : "down") + " from floor " +
                         QString::number(elevator.getCurrentFloor()) + " to target floor " +
                         QString::number(elevator.getTargetFloor()));
                elevator.setMovementLogged(true);
            }
            if (elevator.moveOneFloor()) {
                logEvent("Elevator " + QString::number(elevator.getId()) + " arrived at target floor " +
                         QString::number(elevator.getCurrentFloor()));
                elevator.setState(Elevator::Arrived);
            }
        } else if (elevator.getState() == Elevator::Arrived) {
            elevator.setState(Elevator::DoorsOpening);
            elevator.openDoors();
            logEvent("Elevator " + QString::number(elevator.getId()) + " at floor " +
                     QString::number(elevator.getCurrentFloor()) + " opening doors");
            QTimer::singleShot(1000, [&elevator, this]() {
                elevator.setState(Elevator::DoorsOpen);
                elevator.displayMessage("Floor " + QString::number(elevator.getCurrentFloor()));
                logEvent("Elevator " + QString::number(elevator.getId()) + " doors fully open at floor " +
                         QString::number(elevator.getCurrentFloor()));
            });
        } else if (elevator.getState() == Elevator::DoorsOpen) {
            for (auto &passenger : passengers) {
                if (passenger.getIsOnElevator() && passenger.getElevatorNum() == elevator.getId() - 1) {
                    if (passenger.getPressOpenDoor() && elevator.getState() != Elevator::Emergency) {
                        elevator.setState(Elevator::DoorsOpen);
                        logEvent("Passenger " + QString::number(passenger.getId()) + " holds doors open on Elevator " +
                                 QString::number(elevator.getId()));
                    }
                    if (passenger.getPressCloseDoor()) {
                        elevator.setState(Elevator::DoorsClosing);
                        elevator.closeDoors();
                        logEvent("Passenger " + QString::number(passenger.getId()) + " initiates door closing on Elevator " +
                                 QString::number(elevator.getId()));
                    }
                    if (passenger.getObstructDoor()) {
                        elevator.setState(Elevator::DoorsOpen);
                        safetySystem->checkDoorObstacle(elevator, obstacleCount[elevator.getId() - 1], true);
                    }
                    if (elevator.getCurrentFloor() == passenger.getStartFloor() && !passenger.getHasBoarded()) {
                        logEvent("Passenger " + QString::number(passenger.getId()) + " boards Elevator " +
                                 QString::number(elevator.getId()) + " at floor " +
                                 QString::number(elevator.getCurrentFloor()));
                        passenger.setHasBoarded(true);
                        elevator.setTargetFloor(passenger.getDestFloor());
                    }
                    if (elevator.getCurrentFloor() == passenger.getDestFloor()) {
                        passenger.setIsOnElevator(false);
                        passenger.setElevatorNum(-1);
                        elevator.setNumPassengers(elevator.getNumPassengers() - 1);
                        logEvent("Passenger " + QString::number(passenger.getId()) + " exits Elevator " +
                                 QString::number(elevator.getId()) + " at destination floor " +
                                 QString::number(elevator.getCurrentFloor()));
                    }
                    passenger.setCurrentFloor(elevator.getCurrentFloor());
                }
            }
            QTimer::singleShot(10000, [&elevator, this]() {
                if (elevator.getState() == Elevator::DoorsOpen) {
                    elevator.setState(Elevator::DoorsClosing);
                    elevator.closeDoors();
                    logEvent("Elevator " + QString::number(elevator.getId()) + " doors starting to close");
                }
            });
        } else if (elevator.getState() == Elevator::DoorsClosing) {
            QTimer::singleShot(1000, [&elevator, this]() {
                elevator.setState(Elevator::DoorsClosed);
                logEvent("Elevator " + QString::number(elevator.getId()) + " doors fully closed");
                if (elevator.getNumPassengers() > 0) {
                    elevator.setState(Elevator::Moving);
                    logEvent("Elevator " + QString::number(elevator.getId()) + " resuming movement to floor " +
                             QString::number(elevator.getTargetFloor()));
                } else {
                    elevator.setState(Elevator::Idle);
                    logEvent("Elevator " + QString::number(elevator.getId()) + " now idle at floor " +
                             QString::number(elevator.getCurrentFloor()));
                }
            });
        }
    }

    bool allPassengersArrived = true;
    for (const auto &passenger : passengers) {
        if (!passenger.hasArrived()) {
            allPassengersArrived = false;
            break;
        }
    }

    if (allPassengersArrived && !passengers.empty() && state == State::Running) {
        logEvent("All passenger requests fulfilled - elevators returning to floor 1");
        state = State::Returning;
        for (auto &elevator : elevators) {
            if (elevator.getCurrentFloor() != 1 && elevator.getState() == Elevator::Idle) {
                elevator.setTargetFloor(1);
                elevator.setState(Elevator::Moving);
            }
        }
    }

    bool allElevatorsIdleAtFloor1 = true;
    for (const auto &elevator : elevators) {
        if (elevator.getState() != Elevator::Idle || elevator.getCurrentFloor() != 1) {
            allElevatorsIdleAtFloor1 = false;
            break;
        }
    }

    if (state == State::Returning && allElevatorsIdleAtFloor1) {
        logEvent("Simulation complete: All elevators idle at floor 1");
        timer.stop();
        state = State::Finished;
    }
}

// Triggers fire alarm and evacuates elevators to floor 1
void SimulatorGUI::triggerFire() {
    if (state == State::Running) {
        safetySystem->triggerFireAlarm(elevators);
        for (auto &elevator : elevators) {
            elevator.setState(Elevator::DoorsOpening);
            elevator.openDoors();
            logEvent("Elevator " + QString::number(elevator.getId()) + " at floor 1, Doors Opening");
            QTimer::singleShot(1000, [&elevator, this]() {
                elevator.setState(Elevator::DoorsOpen);
                logEvent("Elevator " + QString::number(elevator.getId()) + " at floor 1, Doors Open");
                elevator.displayMessage("Please disembark");
                for (auto &passenger : passengers) {
                    if (passenger.getElevatorNum() == elevator.getId() - 1) {
                        passenger.setIsOnElevator(false);
                        passenger.setCurrentFloor(1);
                        passenger.setElevatorNum(-1);
                        elevator.setNumPassengers(0);
                        logEvent("Passenger " + QString::number(passenger.getId()) + " disembarks Elevator " +
                                 QString::number(elevator.getId()));
                    }
                }
                QTimer::singleShot(10000, [&elevator, this]() {
                    elevator.setState(Elevator::DoorsClosing);
                    elevator.closeDoors();
                    logEvent("Elevator " + QString::number(elevator.getId()) + " doors closing");
                    QTimer::singleShot(1000, [&elevator, this]() {
                        elevator.setState(Elevator::Idle);
                        logEvent("Elevator " + QString::number(elevator.getId()) + " idle (Fire resolved)");
                    });
                });
            });
        }
        stopSimulation();
    }
}

// Triggers power outage and evacuates elevators to floor 1
void SimulatorGUI::triggerPowerOutage() {
    if (state == State::Running) {
        safetySystem->triggerPowerOutage(elevators);
        for (auto &elevator : elevators) {
            elevator.setState(Elevator::DoorsOpening);
            elevator.openDoors();
            logEvent("Elevator " + QString::number(elevator.getId()) + " at floor 1, Doors Opening");
            QTimer::singleShot(1000, [&elevator, this]() {
                elevator.setState(Elevator::DoorsOpen);
                elevator.displayMessage("Please disembark");
                logEvent("Elevator " + QString::number(elevator.getId()) + " at floor 1, Doors Open");
                for (auto &passenger : passengers) {
                    if (passenger.getElevatorNum() == elevator.getId() - 1) {
                        passenger.setIsOnElevator(false);
                        passenger.setCurrentFloor(1);
                        passenger.setElevatorNum(-1);
                        elevator.setNumPassengers(0);
                        logEvent("Passenger " + QString::number(passenger.getId()) + " disembarks Elevator " +
                                 QString::number(elevator.getId()));
                    }
                }
                QTimer::singleShot(10000, [&elevator, this]() {
                    elevator.setState(Elevator::DoorsClosing);
                    elevator.closeDoors();
                    logEvent("Elevator " + QString::number(elevator.getId()) + " doors closing");
                    QTimer::singleShot(1000, [&elevator, this]() {
                        elevator.setState(Elevator::Idle);
                        logEvent("Elevator " + QString::number(elevator.getId()) + " idle (Power outage resolved)");
                    });
                });
            });
        }
        stopSimulation();
    }
}

// Triggers help alarm for selected elevator
void SimulatorGUI::triggerHelp() {
    if (state == State::Running) {
        int elevId = elevatorSelectCombo->currentText().toInt();
        safetySystem->triggerHelpAlarm(elevId);
        int elevIndex = elevId - 1;
        elevators[elevIndex].displayMessage("Connecting to safety service");
        elevators[elevIndex].playAudio("connecting");
        QTimer::singleShot(5000, [this, elevIndex]() {
            logEvent("No response from building safety for Elevator " + QString::number(elevIndex + 1) +
                     ". Initiating 911 call.");
            elevators[elevIndex].displayMessage("Emergency: 911 called");
            elevators[elevIndex].playAudio("warning");
            QTimer::singleShot(5000, [this, elevIndex]() {
                elevators[elevIndex].setState(Elevator::Idle);
                logEvent("Help resolved in Elevator " + QString::number(elevIndex + 1));
            });
        });
    }
}

// Triggers overload for selected elevator
void SimulatorGUI::triggerOverload() {
    if (state == State::Running) {
        int elevId = elevatorSelectCombo->currentText().toInt() - 1;
        elevators[elevId].triggerOverload();
        logEvent("Overload triggered on Elevator " + QString::number(elevId + 1));
    }
}
