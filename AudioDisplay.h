#ifndef AUDIODISPLAY_H
#define AUDIODISPLAY_H

#include <QObject>
#include <QProcess>
#include "LogConsole.h"

// AudioDisplay class inherits QObject Class - Allows for audio and textual messages to passengers
class AudioDisplay : public QObject {
    Q_OBJECT
public:
    // Constructor
    AudioDisplay(LogConsole *console);

    // Destructor
    ~AudioDisplay();

    // Public Functions in the AudioDisplay Class
    void showFloor(int floor);
    void showMessage(const QString &message);
    void playSound(const QString &sound);

private:
    // Private variables in the AudioDisplay Class
    QProcess *soundProcess;
    LogConsole *logConsole;
};

#endif // AUDIODISPLAY_H
