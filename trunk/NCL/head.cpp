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
