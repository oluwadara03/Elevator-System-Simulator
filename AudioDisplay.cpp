#include "AudioDisplay.h"
#include <QFile>

// Constructor, initializes soundProcess and logConsole
AudioDisplay::AudioDisplay(LogConsole *console) : QObject(nullptr), logConsole(console) {
    soundProcess = new QProcess(this);
}

// Destructor, cleans up soundProcess
AudioDisplay::~AudioDisplay() {
    delete soundProcess;
}

void AudioDisplay::showFloor(int floor) {
    QString message = "Floor " + QString::number(floor);
    logConsole->appendLog("AudioDisplay: Showing " + message);
}

void AudioDisplay::showMessage(const QString &message) {
    logConsole->appendLog("AudioDisplay: Message - " + message);
}

// Plays a sound file based on the provided sound identifier
// Can update paths as need be
void AudioDisplay::playSound(const QString &sound) {
    QString filePath;
    if (sound == "warning") {
        // Warning sound for elevator obstruction
        filePath = "/home/student/Desktop/ElevatorSimulator/warning.wav";
    } else if (sound == "connecting") {
        // Connecting sound to connecct with help when "Help" button on GUI is pressed
        filePath = "/home/student/Desktop/ElevatorSimulator/connecting.wav";
    } else if (sound == "bell") {
        // Bell sound when doors open or close
        filePath = "/home/student/Desktop/ElevatorSimulator/bell.wav";
    } else {
        logConsole->appendLog("AudioDisplay: Unknown sound - " + sound);
        return;
    }

    // Error handling
    if (!QFile::exists(filePath)) {
        logConsole->appendLog("AudioDisplay: Sound file not found - " + filePath);
        return;
    }

    soundProcess->start("aplay", QStringList() << filePath);
    logConsole->appendLog("AudioDisplay: Playing sound - " + sound);
}
