/*!
*\file NCL/link.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an link entity.
*/

#include "link.h"

Link::Link(QString xConnectorParam, Bind *bindParam)
{
    id = "";
    xConnector = xConnectorParam;
    bind = bindParam->getBind();
    linkParam = "";
}

Link::Link(QString xConnectorParam, Bind *bindParam, LinkParam *linkParamParam)
{
    id = "";
    xConnector = xConnectorParam;
    bind = bindParam->getBind();
    linkParam = linkParamParam->getLinkParam();
}

QString Link::getLink()
{
    link = "\t\t<link "+id+" xconnector=\""+xConnector+"\">\n";
    link.append(linkParam);
    link.append(bind);
    link.append("\t\t</link>\n");
    return link;
}

void Link::addBind(Bind *bindParam)
{
    bind.append(bindParam->getBind());
}

void Link::setId(QString idParam)
{
    id = "id=\""+idParam+"\"";
}
