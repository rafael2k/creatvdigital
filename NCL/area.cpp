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
*\file NCL/area.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an area entity.
*/


#include "area.h"

Area::Area(QString idParam)
{
    id = idParam;
    coords = "";
    begin = "";
    end = "";
    text = "";
    position = "";
    first = "";
    last = "";
    label = "";
}


QString Area::getArea()
{
    area = "\t\t\t<area id=\""+id+"\""+coords+begin+end+text+position+first+last+label+"/>\n";
    return area;
}

void Area::setCoords(QString coordsParam)
{
    coords = " coords=\""+coordsParam+"\"";
}

void Area::setBegin(QString beginParam)
{
    begin = " begin=\""+beginParam+"\"";
}

void Area::setEnd(QString endParam)
{
    end = " end=\""+endParam+"\"";
}

void Area::setText(QString textParam)
{
    text = " text=\""+textParam+"\"";
}

void Area::setPosition(QString positionParam)
{
    position = " position=\""+positionParam+"\"";
}

void Area::setFirst(QString firstParam)
{
    first = " first=\""+firstParam+"\"";
}

void Area::setLast(QString lastParam)
{
    last = " last=\""+lastParam+"\"";
}

void Area::setLabel(QString labelParam)
{
    label = " label=\""+labelParam+"\"";
}
