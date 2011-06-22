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
*\file NCL/media.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an media entity.
*/

#include "media.h"

#include <iostream>

using namespace std;

Media::Media(QString idParam, QString originalDurationParam)
{
    id = idParam;
    src = "";
    refer = "";
    instance = "";
    type = "";
    descriptor = "";
    property = "";
    area = "";
    originalDuration = originalDurationParam;
}

Media::Media(QString idParam,QString originalDurationParam, Property propertyParam)
{
    id = idParam;
    src = "";
    refer = "";
    instance = "";
    type = "";
    descriptor = "";
    property = propertyParam.getProperty();
    area = "";
    originalDuration = originalDurationParam;
}

Media::Media(QString idParam,QString originalDurationParam, Area areaParam)
{
    id = idParam;
    src = "";
    refer = "";
    instance = "";
    type = "";
    descriptor = "";
    property = "";
    area = areaParam.getArea();
    originalDuration = originalDurationParam;
}

QString Media::getMedia()
{
    media = "\t\t<media id=\""+id+"\""+src+refer+instance+type+descriptor+">\n";
    media.append(area);
    media.append(property);
    media.append("\t\t</media>\n");
    return media;
}

void Media::setSrc(QString srcParam)
{
    src = " src=\""+srcParam+"\"";
}

void Media::setRefer(QString referParam)
{
    refer = " refer=\""+referParam+"\"";
}

void Media::setInstance(QString instanceParam)
{
    instance = " instance=\""+instanceParam+"\"";
}

void Media::setType(QString typeParam)
{
    type = " type=\""+typeParam+"\"";
}

void Media::setDescriptor(QString descriptorParam)
{
    descriptor = " descriptor=\""+descriptorParam+"\"";
}

void Media::addProperty(Property *propertyParam)
{
    property.append("\t"+propertyParam->getProperty());
}

QString Media::getProperty()
{
    return property;
}

void Media::addArea(Area *areaParam)
{
    area.append("\t"+areaParam->getArea());
}

QString Media::getSrc()
{
    QString srcR = src;
    srcR.remove("\"");
    srcR.remove(" src=");
    return srcR;
}

QString Media::getId()
{
    return id;
}

QString Media::getType()
{
    QString typeR = type;
    typeR.remove("\"");
    typeR.remove(" type=");
    return typeR;
}

QString Media::getDescriptor()
{
    QString descriptorR = descriptor;
    descriptorR.remove("\"");
    descriptorR.remove(" descriptor=");
    return descriptorR;
}

QString Media::getOriginalDuration()
{
    return originalDuration;
}

void Media::clearAreas()
{
    area = "";
}

void Media::clearProperty()
{
   property.clear();
}


