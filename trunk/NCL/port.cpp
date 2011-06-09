/*!
*\file NCL/port.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an port entity.
*/

#include "port.h"

Port::Port(QString idParam, QString componentParam)
{
    id = idParam;
    component = componentParam;
    interface = "";
}

Port::Port(QString idParam, QString componentParam, QString interfaceParam)
{
    id = idParam;
    component = componentParam;
    interface = " interface=\""+interfaceParam+"\"";
}


QString Port::getPort()
{
    port = "\t\t<port id=\""+id+"\" component=\""+component+"\""+interface+"/>\n";
    return port;
}

void Port::setInterface(QString interfaceParam)
{
    interface = " interface=\""+interfaceParam+"\"";
}

