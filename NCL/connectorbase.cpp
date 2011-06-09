/*!
*\file NCL/connectorbase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an connectorBase entity.
*/

#include "connectorbase.h"

ConnectorBase::ConnectorBase()
{
    id = "";
    importBase = "";
    causalConnector = "";
}


ConnectorBase::ConnectorBase(ImportBase *importBaseParam)
{
    id = "";
    importBase = importBaseParam->getImportBase();
    causalConnector = "";
}

ConnectorBase::ConnectorBase(CausalConnector causalConnectorParam)
{
    id = "";
    importBase = "";
    causalConnector = causalConnectorParam.getCausalConector();
}

QString ConnectorBase::getConnectorBase()
{
    connectorBase = "\t\t<connectorBase"+id+">\n";
    connectorBase.append(importBase);
    connectorBase.append(causalConnector);
    connectorBase.append("\t\t</connectorBase>\n");
    return connectorBase;
}

void ConnectorBase::addImporBase(ImportBase importBaseParam)
{
    importBase.append(importBaseParam.getImportBase());
}

void ConnectorBase::addCausalConnector(CausalConnector causalConnectorParam)
{
    causalConnector.append(causalConnectorParam.getCausalConector());
}

void ConnectorBase::setId(QString idParam)
{
    id = " id=\""+idParam+"\"";
}
