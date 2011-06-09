/*!
*\file NCL/property.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an property entity.
*/

#include "property.h"

Property::Property(QString nameParam)
{
    name = nameParam;
    value = "";
}

Property::Property(QString nameParam, QString valueParam)
{
    name = nameParam;
    value = " value=\""+valueParam+"\"";
}

QString Property::getProperty()
{
    property = "\t\t<property name=\""+name+"\""+value+"/>\n";
    return property;
}

void Property::setValue(QString valueParam)
{
    value = " value=\""+valueParam+"\"";
}
