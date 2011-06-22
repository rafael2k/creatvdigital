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
*\file NCL/context.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an context entity.
*/

#include "context.h"

Context::Context(QString idParam)
{
    id = idParam;
    refer = "";
    port = "";
    property = "";
    media = "";
    subContext = "";
    link = "";
    switchS = "";
}

Context::Context(QString idParam, Port portParam)
{
    id = idParam;
    refer = "";
    port = portParam.getPort();
    property = "";
    media = "";
    subContext = "";
    link = "";
    switchS = "";
}

Context::Context(QString idParam, Property propertyParam)
{
    id = idParam;
    refer = "";
    port = "";
    property = propertyParam.getProperty();
    media = "";
    subContext = "";
    link = "";
    switchS = "";
}
Context::Context(QString idParam, Media mediaParam)
{
    id = idParam;
    refer = "";
    port = "";
    property = "";
    media = mediaParam.getMedia();
    subContext = "";
    link = "";
    switchS = "";
}

Context::Context(QString idParam, Context contextParam)
{
    id = idParam;
    refer = "";
    port = "";
    property = "";
    media = "";
    subContext = contextParam.getContext();
    link = "";
    switchS = "";
}

Context::Context(QString idParam, Link linkParam)
{
    id = idParam;
    refer = "";
    port = "";
    property = "";
    media = "";
    subContext = "";
    link = linkParam.getLink();
    switchS = "";
}

/*Context::Context(QString idParam, Switch switchParam)
{
    id = idParam;
    refer = "";
    port = "";
    property = "";
    media = "";
    subContext = "";
    link = "";
    switchS = switchParam.getSwitch();
}*/


QString Context::getContext()
{
    context = "\t\t<context id=\""+id+"\""+refer+">\n";
    context.append(port);
    context.append(property);
    context.append(media);
    context.append(subContext);
    context.append(link);
    context.append(switchS);
    context.append("\t\t</context>");
    return "hola";
}

void Context::setRefer(QString referParam)
{
    refer = " refer=\""+referParam+"\"";
}

void Context::addPort(Port portParam)
{
    port.append(portParam.getPort());
}

void Context::addProperty(Property propertyParam)
{
    property.append(propertyParam.getProperty());
}

void Context::addMedia(Media mediaParam)
{
    media.append(mediaParam.getMedia());
}

void Context::addContext(Context contextParam)
{
    context.append(contextParam.getContext());
}

void Context::addLink(Link linkParam)
{
    link.append(linkParam.getLink());
}

/*void Context::addSwitch(Switch switchSParam)
{
    switchS.append(switchSParam.getSwitch());
}
*/
