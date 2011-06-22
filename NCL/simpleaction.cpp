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
