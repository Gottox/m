#include "mptyexecutor.h"
#include <QDebug>

MPtyExecutor::MPtyExecutor(QObject *parent) : MAbstractExecutor(parent), process()
{
}

int MPtyExecutor::execute(const QString &exe, const QStringList &args)
{
    qDebug() << exe << args;
    this->process.setFlowControlEnabled(true);
    connect(&this->process, SIGNAL(receivedData(const char*,int)), this, SLOT(onReceivedData(const char*,int)));
    connect(&this->process, SIGNAL(finished(int)), this, SLOT(onFinished(int)));

    qDebug() << this->process.start(exe, args, QStringList() << "TERM=xterm", 0, false);
}

void MPtyExecutor::resize(int lines, int columns)
{
    this->process.setWindowSize(lines, columns);
}

void MPtyExecutor::onReceivedData(const char *data, int length)
{
    emit receivedData(data, length);
}

void MPtyExecutor::onFinished(int exitCode)
{
    emit finished(exitCode);
}
