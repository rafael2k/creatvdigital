/*!
*\file NCL/compoundaction.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an compoundAction entity.
*/

#include "compoundaction.h"

CompoundAction::CompoundAction(QString operatorCParam, SimpleAction simpleActionParam)
{
    operatorC = operatorCParam;
    simpleAction = simpleActionParam.getSimpleAction();
    subCompoundAction = "";
    delay = "";
}

CompoundAction::CompoundAction(QString operatorCParam, CompoundAction compoundActionParam)
{
    operatorC = operatorCParam;
    simpleAction = "";
    subCompoundAction = compoundActionParam.getCompoundAction();
    delay = "";
}

QString CompoundAction::getCompoundAction()
{
    compoundAction = "\t\t\t\t\t<compoundSAction operator=\""+operatorC+"\""+delay+">\n";
    compoundAction.append(simpleAction);
    compoundAction.append(subCompoundAction);
    compoundAction.append("\t\t\t\t\t</compoundSAction>\n");
    return compoundAction;
}

void CompoundAction::addSimpleAction(SimpleAction simpleActionParam)
{
    simpleAction.append(simpleActionParam.getSimpleAction());
}

void CompoundAction::addCompoundAction(CompoundAction compoundActionAction)
{
    subCompoundAction.append("\t"+compoundActionAction.getCompoundAction());
}


void CompoundAction::setDelay(QString delayParam)
{
    delay = delayParam;
}
