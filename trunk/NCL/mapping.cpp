/*!
*\file NCL/mapping.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an mapping entity.
*/

#include "mapping.h"

Mapping::Mapping(QString componentParam)
{
    component = componentParam;
    interface = "";
}

Mapping::Mapping(QString componentParam, QString interfaceParam)
{
    component = componentParam;
    interface = " interface=\""+interfaceParam+"\"";
}

QString Mapping::getMapping()
{
    mapping = "\t\t\t\t<mapping component=\""+component+interface+"/>\n";
    return mapping;
}

void Mapping::setInterface(QString interfaceParam)
{
    interface = " interface=\""+interfaceParam+"\"";
}


