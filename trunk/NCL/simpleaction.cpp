/*!
*\file NCL/simpleaction.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an simpleAction entity.
*/

#include "simpleaction.h"

SimpleAction::SimpleAction(QString roleParam)
{
    role = roleParam;
    delay = "";
    eventType = "";
    value = "";
    min = "";
    max = "";
    qualifier = "";
    repeat = "";
    repeatDelay = "";

}

QString SimpleAction::getSimpleAction()
{
    simpleAction = "\t\t\t\t<simpleAction role=\""+role+"\""+delay+eventType+value+min+max+qualifier+repeat+repeatDelay+"/>";
    return simpleAction;
}

void SimpleAction::setDelay(QString delayParam)
{
    delay = " delay=\""+delayParam+"\"";
}

void SimpleAction::setEventType(QString eventTypeParam)
{
    eventType = " eventType=\""+eventTypeParam+"\"";
}

void SimpleAction::setValue(QString valueParam)
{
    value = " value=\""+valueParam+"\"";
}

void SimpleAction::setMin(QString minParam)
{
    min = " min=\""+minParam+"\"";
}

void SimpleAction::setMax(QString maxParam)
{
    max = " max=\""+maxParam+"\"";
}

void SimpleAction::setQualifier(QString qualifierParam)
{
    qualifier = " qualifier=\""+qualifierParam+"\"";
}

void SimpleAction::setRepeat(QString repeatParam)
{
    repeat = " repeat=\""+repeatParam+"\"";
}

void SimpleAction::setRepeatDelay(QString repeatDelayParam)
{
    repeatDelay = " repeatDelay=\""+repeatDelayParam+"\"";
}
