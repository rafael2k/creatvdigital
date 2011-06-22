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
