#include "LogConsole.h"

// Constructor, sets up read-only text edit
LogConsole::LogConsole(QWidget *parent) : QTextEdit(parent) {
    setReadOnly(true);
}

// Adds text
void LogConsole::appendLog(const QString &text) {
    QString logEntry = text;
    append(logEntry);
}
