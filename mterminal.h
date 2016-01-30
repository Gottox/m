#ifndef MTERMINAL_H
#define MTERMINAL_H

#include <QObject>
#include <QTextCursor>

class MTerminal : public QObject
{
    Q_OBJECT
public:
    explicit MTerminal(QTextCursor &cursor, QObject *parent = 0);

private:
    QTextCursor cursor;

signals:

public slots:
    void onReceivedData(const char *data, int length);
};

#endif // MTERMINAL_H
