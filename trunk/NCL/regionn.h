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
*\file NCL/regionn.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a region entity.
*/

#ifndef REGION_H
#define REGION_H

#include <QString>
#include <QList>

/*!
* \class Regionn
* \brief class to create a region entity.
*/

class Regionn
{

private:
    QString region;
    QString id;
    QString title;
    QString left;
    QString right;
    QString top;
    QString bottom;
    QString height;
    QString width;
    QString zIndex;
    QString subRegion;
    QList<Regionn*> subRegiones;



public:
    Regionn(QString idRegion);
    QString getRegion();
    void addRegion(Regionn *region);
    void setId(QString id);
    void setTitle(QString title);
    void setLeft(QString left);
    void setRight(QString right);
    void setTop(QString top);
    void setBottom(QString bottom);
    void setHeight(QString height);
    void setWidth(QString width);
    void setZIndex(QString zIndex);
    QString getSubRegiones(QList<Regionn*> lista, QString tabs);
    QList<Regionn*> getList();
    QString getId();

    QString getTitle();
    QString getLeft();
    QString getRight();
    QString getTop();
    QString getBottom();
    QString getHeight();
    QString getWidth();
    QString getZIndex();


};

#endif // REGION_H
