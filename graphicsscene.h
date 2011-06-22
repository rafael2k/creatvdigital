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
*\file graphicsscene.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to contain and manipulate rectangles in space area.
*/

#ifndef GraphicsScene_H
#define GraphicsScene_H

#include <QGraphicsScene>
#include "graphicsrectitem.h"
#include <QGraphicsPixmapItem>
#include <QList>
#include <QTableWidgetItem>
#include <QFile>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QPixmap;
class QGraphicsItem;
class QGraphicsScene;
class QTextEdit;
class QGraphicsSceneMouseEvent;
class QMenu;
class QGraphicsSceneContextMenuEvent;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QPolygonF;
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QGraphicsRectItem;
class QColor;
QT_END_NAMESPACE


/*!
 * \class GraphicsScene
 * \brief class to contain and manipulate rectangles in space area.
 */
class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /// creates the GraphicsScene and initialize values
    GraphicsScene(QMenu *itemMenu);
    /// returns selected rectangle
    GraphicsRectItem* getSelected();
    /// this action was reuse an example of Qt
    QPointF onGrid(QPointF pos);
    /// inserts a new rectangle
    void insertItem(QString name,qreal axisX, qreal axisY,qreal width,qreal height,qreal z,GraphicsRectItem *parentItem);
    /// sets the automatic name \a number of the regions
    void setRegionName(int number);
    /// gets the last automatic name of the regions
    int getRegionName();


signals:  
    /// this signal is emitted when an object is dropped over rectangle
    void itemDrop(GraphicsRectItem *item);
    /// this signal is emitted when roll the mouse wheel
    void zoom(const qreal factor);
    /// this signal is emitted when a new rectangle is inserted and rectangle hasn't parent
    void addRootTreeItem(QString number);
    /// this signal is emitted when a new rectangle is inserted and rectangle has parent
    void addChildTreeItem(QString number, QString parentName);
    /// this signal is emitted when a rectangle is selected
    void itemSelected(GraphicsRectItem *item);
    /// this signal is emitted when the mouse is moved
    void mouseMove(QPointF point);
    /// this signal is emitted when the mouse is moved
    void mouseMoveX(qreal point1, qreal point2);
    /// this signal is emitted when the mouse is moved
    void mouseMoveY(qreal point1, qreal point2);    
    void showMediasRegion(QPointF posWindow, QList<Media*> medias);
    /// this signal is emitted when mouse is hover leave a rectangle
    void closeMediasRegion();
    /// this signal is emitted when mouse is released over the rectangle
    void setDataNcl();
    /// this signal is emitted when the object dropped in DiagramScene is from a wrong place
    void outElement();

private:
    GraphicsRectItem *insertedDrawItem;
    qreal myGrid;
    int regionName;
    QMenu *myMenu;    
    bool canEnlarge;
    bool subRegion;
    bool buttonPressed;
    /// sets cursor and flag of all rectangles
    void setPropItems(bool prop);
    /// returns a new automatic name to a region
    int getGetRegionName(int &x);
    /// verifies if the region name \a x already exist
    bool existRegion(int x);

protected:
    /// redefined action of \b QGraphicsScene
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /// redefined action of \b QGraphicsScene
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /// redefined action of \b QGraphicsScene
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /// redefined action of \b QGraphicsScene
    void wheelEvent(QGraphicsSceneWheelEvent *mouseEvent);

private slots:
    /// emits the \a addChildTreeItem or \a addRootTreeItem or \a itemSelected signal
    void itemSelectecdSlot(GraphicsRectItem *item,bool subRegion);
    /// emits the \a itemDrop signal
    void dropItemSlot(GraphicsRectItem *item);
   // emits the \a showMediasRegion signal
   // void showMediasRegion2(QPointF posWindow, QList<Media*> medias);
   // emits the \a closeMediasRegion signal
   // void closeMediasRegion2();

public slots:
    /// sets \a buttonPressed value with \a press
    void setButtonPressed(bool press);

};

#endif // GraphicsScene_H
