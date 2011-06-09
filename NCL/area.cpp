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
