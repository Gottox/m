#ifndef MDUMBTERMINAL_H
#define MDUMBTERMINAL_H

#include <QObject>
#include <QProcess>
#include <QTextBlock>
#include <QTextCursor>

class MDumbTerminal : public QObject
{
    Q_OBJECT
public:
    explicit MDumbTerminal(QTextCursor cmdCursor, QObject *parent = 0);

    void exec();
private:
    QProcess *process;
    QTextCursor cmdCursor;
    QTextCursor outCursor;
    QTextBlockFormat outputFormat;
    void addOutput(QString text);

signals:

public slots:
    void onReadyReadStandardError();
    void onReadyReadStandardOutput();
    void onFinished(int exitStatus);
protected:
    void insertOutputblock();
};

#endif // MDUMBTERMINAL_H
