#include <QApplication>
#include <QTextEdit>
#include "mshell.h"
#include <QDebug>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    app.setCursorFlashTime(0);

    MShell *txt = new MShell();

    txt->show();
    return app.exec();
}
