#include "mshell.h"
#include <QShortcut>
#include <QDebug>
#include <QKeyEvent>
#include <QTextBlock>
#include <QTextCursor>
#include <QTextDocumentFragment>
#include "mptyexecutor.h"
#include "mterminal.h"

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
    QString cmd = cursor.selectedText();
    cursor.beginEditBlock();
    cursor.setCharFormat(this->cmdlineFormat);
    cursor.setPosition(cursor.selectionEnd());
    cursor.clearSelection();

    cursor.movePosition(QTextCursor::EndOfLine);
    cursor.setCharFormat(QTextCharFormat());
    cursor.insertBlock();
    if(resetPos != -1) {
        QTextCursor userCursor(cursor);
        userCursor.setPosition(resetPos);
        this->setTextCursor(userCursor);
    }
    cursor.endEditBlock();

    MAbstractExecutor *executor = new MPtyExecutor(this);
    MTerminal *terminal = new MTerminal(cursor, executor);
    executor->resize(this->rows(), this->columns());
    connect(executor, SIGNAL(receivedData(const char*,int)), terminal, SLOT(onReceivedData(const char*,int)));
    executor->execute("/bin/sh", QStringList() << "/bin/sh" << "-c" << cmd);
    connect(executor, SIGNAL(finished(int,QProcess::ExitStatus)), executor, SLOT(deleteLater()));
    return true;
}

int MShell::columns()
{
    return this->width() / this->fontMetrics().width("m");
}

int MShell::rows()
{
    return this->height() / this->fontMetrics().height();
}
