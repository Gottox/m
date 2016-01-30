#include "mterminal.h"
#include <qdebug.h>

MTerminal::MTerminal(QTextCursor &cursor, QObject *parent) : QObject(parent), cursor(cursor)
{
}

void MTerminal::onReceivedData(const char *data, int length)
{
    QString text(QByteArray(data, length));
    this->cursor.insertText(text);
}
