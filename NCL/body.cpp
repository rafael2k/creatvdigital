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
