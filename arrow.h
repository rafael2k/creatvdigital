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
*\file arrow.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create,remove and modify arrows.
*/

#ifndef ARROW_H
#define ARROW_H
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "image.h"


/*!
 * \class Arrow
 * \brief class to create,remove and modify arrows.
 */
class Arrow : public QObject,public QGraphicsLineItem
{
    Q_OBJECT

public:
    enum TypeArrow { TempLine, InteractLine, UnionLine,UnionLineTempInteract,UnionInteractiveLine,ArrowLineAux,UnionDiamondTempLine};

    /// creates the Arrow and initialize values
    Arrow(QLineF pos);
    /// creates the Arrow with \a startItem and \a endItem like Image type and initialize values
    Arrow(Image *startItem, Image *endItem,TypeArrow typeArrow,
        QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    /// creates the Arrow with \a startItem like Arrow type and \a endItem like Image type and initialize values
    Arrow(Arrow *startItem, Image *endItem,TypeArrow typeArrow,
        QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    /// updates position of the arrow
    void updatePosition();
    /// sets button to arrow
    void setButton(Image *buttonP);
    /// sets line \a newLineP to Arrow of the ArrowLineAux type
    void setLineAux(QLineF newLineP);
    /// sets \a posy to children's of \a arrowtItem
    void setRecursivePos(Arrow *arrowtItem,qreal posy,qreal originalPosY);
    /// sets position of the UnionLine Arrow
    void setPosXUnionLine(qreal posX);
    /// sets duration of media
    void setLongTempLineOriginal(QString value);
    /// sets color to Arrow
    void setMyColor(QColor color);
    /// this action was reuse an example of Qt
    QRectF boundingRect() const;    
    /// this action was reuse an example of Qt
    QPainterPath shape() const;
    /// returns the start item of the arrow
    Image* getStartItem();
    /// returns the end item of the arrow
    Image* getEndItem();
    /// returns the button of the InteractLine
    Image* getButton();
    /// returns the type of the arrow
    TypeArrow getMyType() const
    { return myType; }   
    /// returns x position of the UnionLine
    qreal getPosXUnionLine();
    /// returns the item \a startArrow of the arrow
    Arrow *getMyStartItemArrow();
    /// returns the long of the initial arrow
    QString getLongTempLineOriginal();
    /// returns the total children of the arrow \a arrowtItemP
    int recursiveCountItems(Arrow *arrowtItemP , int totalLong);

private:
    Arrow *myStartItemArrow;
    Image *myStartItem;
    Image *myEndItem;
    Image *button;
    QColor myColor;
    QPolygonF arrowHead;
    TypeArrow myType;
    QString longTempLineOriginal;
    qreal posXUnionLine;
    QLineF newLine;
    /// builds the arrow
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *);

};

#endif // ARROW_H
