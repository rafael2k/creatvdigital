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
