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
*\file NCL/body.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a body entity.
*/

#ifndef BODY_H
#define BODY_H

#include "port.h"
#include "property.h"
#include "media.h"
#include "context.h"
#include "switch.h"
#include "link.h"
#include "meta.h"
#include "metadata.h"


/*!
* \class Body
* \brief class to create a body entity.
*/


class Body
{
private:
    QString body;
    QString id;
    QString port;
    QString property;
    QString media;
    QString context;
    QString switchS;
    QString link;
    QString meta;
    QString metadata;

public:
    Body();
    void addPort(Port *port);
    void addProperty(Property property);
    void addMedia(Media media);
    void addContext(Context context);
    void addSwitch(Switch switchS);
    void addLink(Link *link);
    void addMeta(Meta meta);
    void addMetaData(MetaData metaData);
    void setId(QString id);
    QString getBody();

};

#endif // BODY_H
