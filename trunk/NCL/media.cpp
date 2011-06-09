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


