#ifndef LOGCONSOLE_H
#define LOGCONSOLE_H

#include <QTextEdit>

// LogConsole class inherits QTextEdit Class - Sends logs foor the Elevator Administrator's knowledge
class LogConsole : public QTextEdit {
    Q_OBJECT
public:
    // Constructor
    explicit LogConsole(QWidget *parent = nullptr);

    // Public Functions in the LogConsole Class
    void appendLog(const QString &text);
};

#endif // LOGCONSOLE_H
