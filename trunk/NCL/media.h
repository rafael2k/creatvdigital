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
*\file NCL/media.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a media entity.
*/


#ifndef MEDIA_H
#define MEDIA_H

#include "area.h"
#include "property.h"

/*!
* \class Media
* \brief class to create a media entity.
*/

class Media
{
private:
    QString media;
    QString id;
    QString src;
    QString refer;
    QString instance;
    QString type;
    QString descriptor;
    QString property;
    QString area;
    QString originalDuration;

public:
    Media(QString id, QString originalDuration);
    Media(QString id, QString originalDuration, Property property);
    Media(QString id, QString originalDuration, Area area);
    void setId(QString id);
    void setSrc(QString src);
    void setRefer(QString refer);
    void setInstance(QString instance);
    void setType(QString type);
    void setDescriptor(QString descriptor);
    void addProperty(Property *property);
    void addArea(Area *area);
    QString getProperty();
    QString getSrc();
    QString getId();
    QString getMedia();
    QString getType();
    QString getDescriptor();
    QString getOriginalDuration();
    void clearAreas();
    void clearProperty();
};

#endif // MEDIA_H

