#ifndef MLOCALTERMINAL_H
#define MLOCALTERMINAL_H

#include <QObject>
#include "mabstractexecutor.h"
#include <Pty.h>

class MPtyExecutor : public MAbstractExecutor
{
    Q_OBJECT
public:
    explicit MPtyExecutor(QObject *parent = 0);

private:
    Konsole::Pty process;
    ~MPtyExecutor()
    {
        qDebug("Destroyed");
    }

public:
    int execute(const QString &exe, const QStringList &args);
    void resize(int lines, int columns);

private slots:
    void onReceivedData(const char *data,int length);
    void onFinished(int exitCode);
};

#endif // MLOCALTERMINAL_H
