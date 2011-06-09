/*!
*\file NCL/connectorparam.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an connectorParam entity.
*/


#include "connectorparam.h"

ConnectorParam::ConnectorParam(QString nameParam)
{
    name = nameParam;
    type = "";
}

ConnectorParam::ConnectorParam(QString nameParam, QString typeParam)
{
    name = nameParam;
    type = " type=\""+typeParam+"\"";
}

QString ConnectorParam::getConnectorParam()
{
    connectorParam = "\t\t\t\t<connectorParam name=\""+name+"\""+type+"/>\n";
    return connectorParam;
}

void ConnectorParam::setType(QString typeParam)
{
    type = typeParam;
}
