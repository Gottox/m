#include "mdumbterminal.h"
#include <QDebug>
#include "mprocesstextbinder.h"

enum UserState {
    USER_STATE_NONE,
    USER_STATE_OUTPUT
};

MDumbTerminal::MDumbTerminal(QTextCursor cmdCursor, QObject *parent) : QObject(parent)
{
    this->cmdCursor = cmdCursor;
    this->outputFormat.setBackground(QBrush(QColor("#300")));
}

void MDumbTerminal::insertOutputblock()
{
    this->outCursor.insertBlock(this->outputFormat);
    this->outCursor.block().setUserData(new MProcessTextBinder(this));
    this->outCursor.block().setUserState(USER_STATE_OUTPUT);
}

void MDumbTerminal::exec()
{
    QString shell = qgetenv("SHELL").constData();
    if(shell.isEmpty())
        shell = "/bin/sh";

    QString cmd = this->cmdCursor.selectedText();

    this->process = new QProcess(this);
    this->process->start(shell, QStringList() << "-c" << cmd);
    qDebug() << this->process->arguments();
    connect(this->process, SIGNAL(readyReadStandardOutput()), this, SLOT(onReadyReadStandardOutput()));:
    connect(this->process, SIGNAL(readyReadStandardError()), this, SLOT(onReadyReadStandardError()));
    connect(this->process, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
    this->outCursor = QTextCursor(this->cmdCursor);
    this->outCursor.beginEditBlock();
    this->outCursor.movePosition(QTextCursor::EndOfBlock);
    insertOutputblock();
    this->outCursor.insertBlock(QTextBlockFormat());
    this->outCursor.movePosition(QTextCursor::Up);
    this->outCursor.setCharFormat(QTextCharFormat());
    this->outCursor.endEditBlock();
}

void MDumbTerminal::addOutput(QString text)
{
    this->outCursor.beginEditBlock();
    if(this->outCursor.block().userState() != USER_STATE_OUTPUT) {
        //insertOutputblock();
    }
    this->outCursor.insertText(text);
    this->outCursor.endEditBlock();
}

void MDumbTerminal::onReadyReadStandardError()
{
    addOutput(this->process->readAllStandardError());
}

void MDumbTerminal::onReadyReadStandardOutput()
{
    addOutput(this->process->readAllStandardOutput());
}

void MDumbTerminal::onFinished(int exitStatus)
{
    this->outCursor.select(QTextCursor::LineUnderCursor);
    if(!this->outCursor.hasSelection()) {
        this->outCursor.deletePreviousChar();
    }
}

