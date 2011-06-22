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
*\file NCL/head.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an head entity.
*/

#include "head.h"

Head::Head()
{
    importedDocumentBase = "";
    ruleBase = "";
    transitionBase = "";
    regionBase = "";
    descriptorBase = "";
    connectorBase = "";
    meta = "";

}

QString Head::getHead()
{
    head = "\t<head>\n";
    head.append(importedDocumentBase);
    head.append(ruleBase);
    head.append(transitionBase);
    head.append(regionBase);
    head.append(descriptorBase);
    head.append(connectorBase);
    head.append(meta);
    head.append("\t</head>\n");
    return head;
}

void Head::setImpotedDocumentBase(QString importedDocumentBaseParam)
{
    importedDocumentBase.append(importedDocumentBaseParam);
}

void Head::setRuleBase(QString ruleBaseParam)
{
    ruleBase = ruleBaseParam;
}

void Head::setTransitionBase(QString transitionBaseParam)
{
    transitionBase = transitionBaseParam;
}

void Head::addRegionBase(QString regionBaseParam)
{
    regionBase.append(regionBaseParam);
}

void Head::addDescriptorBase(QString descriptorBaseParam)
{
    descriptorBase.append(descriptorBaseParam);
}

void Head::setConnectorBase(QString connectorBaseParam)
{
    connectorBase = connectorBaseParam;
}

void Head::addMeta(QString metaParam)
{
    meta = metaParam;
}

void Head::addMetaData(QString metaDataParam)
{
    metaData = metaDataParam;
}
