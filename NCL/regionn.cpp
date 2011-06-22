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
*\file NCL/regionn.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an region entity.
*/

#include "regionn.h"
#include <iostream>

using namespace std;


Regionn::Regionn(QString idRegion)
{
   region="";
   id=" id=\""+idRegion+"\" ";
   title="";
   left="";
   right="";
   top="";
   bottom="";
   height="";
   width="";
   zIndex="";
   subRegion="";
}


QString Regionn::getRegion()
{
    region = "\t\t\t<region "+id+title+left+right+top+bottom+height+width+zIndex+">\n";
    QString tabs = "\t\t\t";
    region.append(getSubRegiones(subRegiones,tabs));
    region.append("\t\t\t</region>\n");
    return region;
}

QString Regionn::getSubRegiones(QList<Regionn*> lista, QString tabs)
{
    QString res;
    if (lista.isEmpty())
        res = "";
    else
    {
        tabs.append("\t");
        for (int i=0; i < lista.size(); i++)
        {
            Regionn *r = lista.at(i);
            res.append(tabs+"<region id=\""+r->getId()+"\""+r->getTitle()+r->getLeft()+r->getRight()+r->getTop()+r->getBottom()+r->getHeight()+r->getWidth()+r->getZIndex()+">\n"+getSubRegiones(r->getList(),tabs)+tabs+"</region>\n");

        }
    }
    return res;
}

void Regionn::addRegion(Regionn *regionRR)
{
    subRegiones.append(regionRR);
}


void Regionn::setId(QString idRegion)
{
    id=" id=\""+idRegion+"\" ";
}

void Regionn::setTitle(QString titleParam)
{
    title = " title=\""+titleParam+"\"";
}

void Regionn::setLeft(QString leftParam)
{
    left = " left=\""+leftParam+"\"";
}

void Regionn::setRight(QString rightParam)
{
    right = " right=\""+rightParam+"\"";
}

void Regionn::setTop(QString topParam)
{
    top = " top=\""+topParam+"\"";
}

void Regionn::setBottom(QString bottomParam)
{
    bottom = " bottom=\""+bottomParam+"\"";
}

void Regionn::setHeight(QString heightParam)
{
    height = " height=\""+heightParam+"\"";
}

void Regionn::setWidth(QString widthParam)
{
    width = " width=\""+widthParam+"\"";
}

void Regionn::setZIndex(QString zIndexParam)
{
    zIndex = " zIndex=\""+zIndexParam+"\"";
}

QList<Regionn*> Regionn::getList()
{
    return subRegiones;
}

QString Regionn::getId()
{
    QString idR = id;
    idR.remove("\"");
    idR.remove("id=");
    idR.remove(" ");
    return idR;
}


QString Regionn::getTitle()
{
    return title;
}

QString Regionn::getLeft()
{
    return left;
}

QString Regionn::getRight()
{

    return right;
}

QString Regionn::getTop()
{
    return top;
}

QString Regionn::getBottom()
{
    return bottom;
}

QString Regionn::getHeight()
{
    return height;
}

QString Regionn::getWidth()
{
    return width;
}

QString Regionn::getZIndex()
{
   return zIndex;
}

