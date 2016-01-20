#include "mprocesstextbinder.h"

MProcessTextBinder::MProcessTextBinder(MDumbTerminal *terminal)
{
    setTerminal(terminal);
}

MDumbTerminal *MProcessTextBinder::getTerminal() const
{
    return terminal;
}

void MProcessTextBinder::setTerminal(MDumbTerminal *value)
{
    terminal = value;
}
