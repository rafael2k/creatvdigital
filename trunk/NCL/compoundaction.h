/*!
*\file NCL/compoundaction.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a compoundAction entity.
*/

#ifndef COMPOUNDACTION_H
#define COMPOUNDACTION_H

#include "simpleaction.h"

/*!
* \class CompoundAction
* \brief class to create a compoundAction entity.
*/


class CompoundAction
{
private:
    QString compoundAction;
    QString operatorC;
    QString delay;
    QString simpleAction;
    QString subCompoundAction;

public:
    CompoundAction(QString operatorC, SimpleAction simpleAction);
    CompoundAction(QString operatorC, CompoundAction compoundAction);
    void addSimpleAction(SimpleAction simpleAction);
    void addCompoundAction(CompoundAction compoundAction);
    void setDelay(QString delay);
    QString getCompoundAction();
};

#endif // COMPOUNDACTION_H
