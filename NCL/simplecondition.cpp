/*!
*\file NCL/simplecondition.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an simpleCondition entity.
*/

#include "simplecondition.h"

SimpleCondition::SimpleCondition(QString roleParam)
{
    role = roleParam;
    delay = "";
    eventType = "";
    key = "";
    transition = "";
    min = "";
    max = "";
    qualifier = "";
}

QString SimpleCondition::getSimpleCondition()
{
    simpleCondition = "\t\t\t\t<simpleCondition role=\""+role+"\""+delay+eventType+key+transition+min+max+qualifier+"/>";
    return simpleCondition;
}

void SimpleCondition::setDelay(QString delayParam)
{
    delay = " delay=\""+delayParam+"\"";
}

void SimpleCondition::setEventType(QString eventTypeParam)
{
    eventType = " eventType=\""+eventTypeParam+"\"";
}

void SimpleCondition::setKey(QString keyParam)
{
    key = " key=\""+keyParam+"\"";
}

void SimpleCondition::setTransition(QString transitionParam)
{
    transition = " transition=\""+transitionParam+"\"";
}

void SimpleCondition::setMin(QString minParam)
{
    min = " min=\""+minParam+"\"";
}

void SimpleCondition::setMax(QString maxParam)
{
    max = " max=\""+maxParam+"\"";
}

void SimpleCondition::setQualifier(QString qualifierParam)
{
    qualifier = " qualifier=\""+qualifierParam+"\"";
}
