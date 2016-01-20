#include "mshell.h"
#include <QShortcut>
#include <QDebug>
#include <QKeyEvent>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>
MShell::MShell(QWidget *parent) : QTextEdit(parent)
{
    QShortcut *s;
    this->setAcceptRichText(false);
    this->setFont(QFont("Courier"));
    this->setContextMenuPolicy(Qt::NoContextMenu);
    this->setAutoFillBackground(false);
    //this->setCursorWidth(this->fontMetrics().width('m'));
    this->setStyleSheet("MShell { border: none; background: black; color: white; }");
    this->document()->setDocumentMargin(0.0);

    this->cmdlineFormat.setBackground(QBrush(QColor("#006")));
    this->cmdlineFormat.setForeground(QBrush(QColor("#ff0")));
}

void MShell::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Return && !(ev->modifiers() & Qt::ShiftModifier)) {
        if(commitCurrentLine(!(ev->modifiers() & Qt::ControlModifier)))
            return;
    }
    QTextEdit::keyPressEvent(ev);
}

bool MShell::commitCurrentLine(bool moveCursor)
{
    QTextCursor cursor = this->textCursor();
    int position = moveCursor ? -1 : cursor.position();
    if(!cursor.hasSelection())
        cursor.select(QTextCursor::LineUnderCursor);
    return commit(cursor, position);
}

bool MShell::commit(QTextCursor &cursor, int resetPos)
{
    cursor.beginEditBlock();
    cursor.setCharFormat(this->cmdlineFormat);
    MDumbTerminal *terminal = new MDumbTerminal(cursor, this);
    cursor.setPosition(cursor.selectionEnd());
    cursor.clearSelection();

    cursor.movePosition(QTextCursor::EndOfLine);
    if(resetPos != -1)
        cursor.setPosition(resetPos);
    cursor.setCharFormat(QTextCharFormat());
    cursor.endEditBlock();
    this->setTextCursor(cursor);
    terminal->exec();
    return true;
}
