/***************************************************************************
 *   CreaTV Digital - Herramienta para la creación de aplicaciones NCL para
 *   el middleware GINGA de Televisión Digital Terrestre
 *
 *  Copyright © 2010, 2011
 *        -Cardozo, Sergio A. (yojajo@gmail.com)
 *        -Schwartz, Sebastian M. (seba.schwartz.7@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

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

