#ifndef MSHELLCONTEXT_H
#define MSHELLCONTEXT_H

#include <QObject>

class MShellContext : public QObject
{
    Q_OBJECT
public:
    explicit MShellContext(QObject *parent = 0);

private:
    QString cwd;


signals:

public slots:
};

#endif // MSHELLCONTEXT_H
