#ifndef MPROCESSTEXTBINDER_H
#define MPROCESSTEXTBINDER_H

#include <QObject>
#include <QTextBlockUserData>

class MDumbTerminal;

class MProcessTextBinder : public QTextBlockUserData {
public:
    MProcessTextBinder(MDumbTerminal *terminal);
    MDumbTerminal *getTerminal() const;
    void setTerminal(MDumbTerminal *value);

private:
    MDumbTerminal *terminal;
};

#endif // MPROCESSTEXTBINDER_H
