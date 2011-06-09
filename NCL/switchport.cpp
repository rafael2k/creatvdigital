/*!
*\file NCL/switchport.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an switchPort entity.
*/

#include "switchport.h"

SwitchPort::SwitchPort(QString idParam, Mapping mappingParam)
{
    id = idParam;
    mapping = mappingParam.getMapping();
}

QString SwitchPort::getSwitchPort()
{
    swicthPort = "\t\t\t<swithPort id=\""+id+">";
    swicthPort.append(mapping);
    return swicthPort;
}

void SwitchPort::addMapping(Mapping mappingParam)
{
    mapping.append(mappingParam.getMapping());
}
