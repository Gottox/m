#ifndef MEDITOR_H
#define MEDITOR_H

#include <QTextEdit>
#include <QTextFragment>
#include <QList>
#include "mdumbterminal.h"

class MShell : public QTextEdit
{
    Q_OBJECT
public:
    explicit MShell(QWidget *parent = 0);
    virtual void keyPressEvent(QKeyEvent *);
    bool commitCurrentLine(bool moveCursor);
    bool commit(QTextCursor &, int resetPos);

private:
    QTextCharFormat cmdlineFormat;
    QTextBlockFormat cleanFormat;

signals:

public slots:
};

#endif // MEDITOR_H
