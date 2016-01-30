#ifndef MABSTRACTTERMINAL_H
#define MABSTRACTTERMINAL_H

#include <QObject>
#include <QIODevice>
#include <QProcess>

class MAbstractExecutor : public QObject
{
    Q_OBJECT
public:
    explicit MAbstractExecutor(QObject *parent = 0);
    virtual int execute(const QString &exe, const QStringList &args = QStringList()) = 0;
    virtual void resize(int lines, int columns) = 0;

signals:
    void receivedData(const char *data ,int length);
    void finished(int exitCode);
};

#endif // MABSTRACTTERMINAL_H
