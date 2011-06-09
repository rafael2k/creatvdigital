/*!
*\file NCL/body.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an body entity.
*/

#include "body.h"

Body::Body()
{
    id = "";
    port = "";
    property = "";
    media = "";
    context = "";
    switchS = "";
    link = "";
    meta = "";
    metadata = "";
}


QString Body::getBody()
{
    body = "\t<body "+id+">\n";
    body.append(port);
    body.append(property);
    body.append(media);
    body.append(context);
    body.append(switchS);
    body.append(link);
    body.append(meta);
    body.append(metadata);
    body.append("\t</body>\n");
    return body;
}

void Body::addPort(Port *portParam)
{
    port = portParam->getPort();
}

void Body::addProperty(Property propertyParam)
{
    property = propertyParam.getProperty();
}

void Body::addMedia(Media mediaParam)
{
    media.append(mediaParam.getMedia());
}

void Body::addContext(Context contextParam)
{
    context = contextParam.getContext();
}

void Body::addSwitch(Switch switchParam)
{
    switchS = switchParam.getSwitch();
}

void Body::addLink(Link *linkParam)
{
    link.append(linkParam->getLink());
}

void Body::addMeta(Meta metaParam)
{
    meta = metaParam.getMeta();
}

void Body::addMetaData(MetaData metaDataParam)
{
    metadata = metaDataParam.getMetaData();
}

void Body::setId(QString idParam)
{
    id = "id=\""+idParam+"\"";
}
