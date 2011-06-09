/*!
*\file graphicsrectitem.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create,remove and modify rectangles.
*/

#ifndef DIAGRAMTEXTITEM_H
#define DIAGRAMTEXTITEM_H

#include <QGraphicsRectItem>
#include <QPen>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QtGui>
#include "NCL/media.h"

QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE



/*!
 * \class GraphicsRectItem
 * \brief class to create,remove and modify rectangles.
 */
class GraphicsRectItem : public QObject,public QGraphicsPolygonItem
{
    Q_OBJECT

public:   
    /// creates the GraphicsRectItem and initialize values
    GraphicsRectItem(QMenu *contextMenu);
    /// creates the GraphicsRectItem
    GraphicsRectItem(QPolygonF pologonF,GraphicsRectItem *poligon);    

    QString xNCL;
    QString yNCL;
    QString hNCL;
    QString wNCL;

    QPointF myPos2;

    /// returns the width in \b ncl format
    QString getWidthRecNCL();
    /// returns the heigh in \b ncl format
    QString getHeighRecNCL();
    /// returns the X position in \b ncl format
    QString getXRecNCL();
    /// returns the Y position in \b ncl format
    QString getYRecNCL();
    /// returns the name of rectangle
    QString getName();
    /// returns the list of name of all rectangles
    QStringList getMedias();
    /// returns the width the rectangle
    qreal getWidthRec();
    /// returns the height the rectangle
    qreal getHeightRec();

    /// sets position of the rectangle
    void setPos2(QPointF newPos);
    /// emits the \a selectedChange signal
    void throwSignal();
    /// change z value of rectangle
    void sendToBack();
    /// removes the selected items
    void deleteItem();
    /// adds a new media to the list of medias of the rectangle
    void addMedia(QString media);
    /// sets the height of the rectangle
    void setHeight(qreal height);
    /// sets the width of the rectangle
    void setWidth(qreal width);
    /// sets the height of the rectangle in \b ncl format
    void setHeighNCL(QString alto);
    /// sets the width of the rectangle in \b ncl format
    void setWidthNCL(QString ancho);
    /// sets the X position of the rectangle in \b ncl format
    void setXNCL(QString x);
    /// sets the Y position of the rectangle in \b ncl format
    void setYNCL(QString ancho);
    /// sets the name of the rectangle
    void setName(QString name);
    /// sets the \a prop value to permit create a new rectangle
    void setInsertItem(bool prop);    
    /// adds new image to rectangle (unused)
    void addImage(QImage image);
    /// adds the name of the media to rectangle (unused)
    void addText(QString nombre);    
    /// corrects the position of the rectangle
    void correctPoligon();
    /// sets X and Y position
    void setPosistionXY(qreal x,qreal y);
    /// eliminates one media \a row the list of medias
    void removeMedia(int row);    

signals:    
    /// this signal is emitted when a rectangle is selected
    void selectedChange(GraphicsRectItem *item, bool subRegion);
    /// this signal is emitted when an object is dropped over rectangle
    void dropItem(GraphicsRectItem *item);
    /// this signal is emitted when a rectangle is moved
    void itemSelected(GraphicsRectItem *item);
    /// this signal is emitted when a rectangle is moved
    void mouseMoveX(qreal point1, qreal point2);
    /// this signal is emitted when a rectangle is moved
    void mouseMoveY(qreal point1, qreal point2);    
    /// this signal is emitted when mouse is hover leave an rectangle
    void closeMediasRegion();
    /// this signal is emitted when mouse is released over the rectangle
    void setDataNcl();
    /// this signal is emitted when the object dropped in the rectangle from a wrong place
    void outElement();

private:
    QMenu *myMenu;
    QStringList medias;    
    int myHoverPoint,mySelPoint;    
    QString name;    
    bool insertItem;
    bool pressInsertItem;
    bool okItem;
    qreal myHandlerWidth;
    qreal contMoveX;
    qreal contMoveY;
    qreal movMouseX;
    qreal movMouseY;
    QPolygonF myPolygon;
    /// this action was reuse an example of qt
    QPointF onGrid(QPointF pos);
    /// checks if \a press_point is over corner the rectangle
    bool hasClickedOn(QPointF press_point, QPointF point) const;

protected:
    /// this action was reuse an example of Qt
    QPolygonF createPath();
    /// redefined action of \b QGraphicsPolygonItem (builds the rectangle)
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *);
    /// redefined action of \b QGraphicsPolygonItem
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void dropEvent(QGraphicsSceneDragDropEvent *event);
    /// redefined action of \b QGraphicsPolygonItem
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
   //void showMediasRegion(QPointF posWindow, QList<Media*> medias);

public slots:
    /// sets \okItem in true
    void setTrueOkItemDrop();
    /// sets \okItem in false
    void setFlaseOkItemDrop();

};


#endif
