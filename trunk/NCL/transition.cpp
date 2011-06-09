/*!
*\file NCL/transition.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an transition entity.
*/

#include "transition.h"

Transition::Transition(QString idParam, QString typeParam)
{
    id = " id=\""+idParam+"\"";
    type = "type=\""+typeParam+"\"";
    subType = "";
    dur = "";
    startProgress = "";
    endProgress = "";
    direction = "";
    fadeColor = "";
    horRepeat = "";
    vertRepeat = "";
    borderWidth = "";
    borderColor = "";
}


void Transition::setSubType(QString subTypeParam)
{
    subType = " subType=\""+subTypeParam+"\"";
}

void Transition::setDur(QString durParam)
{
    dur = " dur\"="+durParam+"\"";
}

void Transition::setStartProgress(QString startProgressParam)
{
    startProgress = " startProgress=\""+startProgressParam+"\"";
}

void Transition::setEndProgress(QString endProgressParam)
{
    endProgress = " endProgress=\""+endProgressParam+"\"";
}

void Transition::setDirection(QString directionParam)
{
    direction = " direction=\""+directionParam+"\"";
}

void Transition::setFadeColor(QString fadeColorParam)
{
    fadeColor = " fadeColor=\""+fadeColorParam+"\"";
}

void Transition::setHorRepeat(QString horRepeatParam)
{
    horRepeat = "horRepeat=\""+horRepeatParam+"\"";
}

void Transition::setVertRepeat(QString vertRepeatParam)
{
    vertRepeat = "vertRepeat=\""+vertRepeatParam+"\"";
}

void Transition::setBorderWidth(QString borderWidthParam)
{
    borderWidth = "borderWidth=\""+borderWidthParam+"\"";
}

void Transition::setBorderColor(QString borderColorParam)
{
    borderColor = "borderColor=\""+borderColorParam+"\"";
}

QString Transition::getTransition()
{
    transition = "\t\t\t<transition"+id+type+subType+dur+startProgress+endProgress+direction+fadeColor+horRepeat
                 +vertRepeat+borderWidth+borderColor+" >\n";
    return transition;
}

