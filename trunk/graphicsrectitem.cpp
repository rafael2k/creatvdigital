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
*\file graphicsrectitem.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create,remove and modify rectangles.
*/


#include <iostream>
#include "graphicsrectitem.h"
#include "graphicsscene.h"
using namespace std;

qreal corregirPolX =0;
qreal corregirPolY=0;


/*!
 *\brief creates the GraphicsRectItem and initialize values
 *\param QMenu *menu
 */
GraphicsRectItem::GraphicsRectItem(QMenu *menu)
{
    myPos2=pos();
    myMenu = menu;
    myPolygon=createPath();
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setAcceptHoverEvents(true);
    myHoverPoint=-1;
    mySelPoint=-1;
    myHandlerWidth=2.0;
    setAcceptHoverEvents(true);
    setBrush(Qt::white);
    setAcceptDrops(TRUE);
    insertItem=false;
    pressInsertItem=false;
    contMoveX=0;
    contMoveY=0;    
    movMouseX=0;
    movMouseY=0;
    setOpacity(0.8);
    okItem = false;
}


/*!
 *\brief creates the GraphicsRectItem
 *\param QPolygonF pologonF
 *\param GraphicsRectItem *poligon
 */
GraphicsRectItem::GraphicsRectItem(QPolygonF pologonF,GraphicsRectItem *poligon)
{
    okItem = false;
    new QGraphicsPolygonItem(pologonF,poligon,0);
}


/*!
 *\brief this action was reuse an example of Qt
 *\return QPolygonF
 */
QPolygonF GraphicsRectItem::createPath()
{
    qreal dx=myPos2.x();
    qreal dy=myPos2.y();
    QPainterPath path;
    QPolygonF polygon;
    path.moveTo(0, 0);
    path.lineTo(dx,0);
    path.lineTo(dx,dy);
    path.lineTo(0,dy);
    path.lineTo(0,0);
    polygon = path.toFillPolygon();
    return polygon;
}


/*!
 *\brief this action was reuse an example of qt
 *\param QPointF pos
 *\return QPointF
 */
QPointF GraphicsRectItem::onGrid(QPointF pos)
{
        GraphicsScene* myScene = dynamic_cast<GraphicsScene*>(scene());
        QPointF result = myScene->onGrid(pos);
        return result;
}


/*!
 *\brief sets position of the rectangle
 *\param QPointF newPos
 *\return void
 */
void GraphicsRectItem::setPos2(QPointF newPos)
{    
    prepareGeometryChange();
    myPos2=mapFromScene(newPos);
    myPolygon=createPath();
    setPolygon(myPolygon);
}


/*!
 *\brief sets X and Y position
 *\param qreal xP
 *\param qreal yP
 *\return void
 */
void GraphicsRectItem::setPosistionXY(qreal xP,qreal yP)
{
    prepareGeometryChange();   
    setX(xP);
    setY(yP);
    update();
    myPolygon=createPath();
    setPolygon(myPolygon);
}


/*!
 *\brief corrects the position of the rectangle
 *\return void
 */
void GraphicsRectItem::correctPoligon()
{
    prepareGeometryChange();
    setPos(corregirPolX,corregirPolY);
    update();
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem (builds the rectangle)
 *\param QPainter *painter
 *\param const QStyleOptionGraphicsItem *
 *\param QWidget *
 *\return void
 */
void GraphicsRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *)
{
    painter->setPen(pen());
    painter->setBrush(brush());
    painter->drawPolygon(polygon());
    // selected
    if(isSelected()){
        // Rect
        QPen selPen=QPen(Qt::DashLine);
        selPen.setColor(Qt::black);
        QBrush selBrush=QBrush(Qt::NoBrush);
        painter->setBrush(selBrush);
        painter->setPen(selPen);
        painter->drawRect(QRectF(QPointF(0,0),myPos2));
        // Draghandles
        selBrush=QBrush(Qt::cyan,Qt::SolidPattern);
        selPen=QPen(Qt::cyan);
        painter->setBrush(selBrush);
        painter->setPen(selPen);
        QPointF point;
        for(int i=0;i<8;i++){
            if(i<3) point=QPointF(myPos2.x()/2*i,0);
            if(i==3) point=QPointF(myPos2.x(),myPos2.y()/2);
            if(i>3 && i<7) point=QPointF(myPos2.x()/2*(i-4),myPos2.y());
            if(i==7) point=QPointF(0,myPos2.y()/2);
            if(i==myHoverPoint){
                painter->setBrush(QBrush(Qt::red));
            }
            // Rect around valid point
            painter->drawRect(QRectF(point-QPointF(2,2),point+QPointF(2,2)));
            if(i==myHoverPoint){
                painter->setBrush(selBrush);
            }
        }// foreach
    }// if
}


/*!
 *\brief checks if \a press_point is over corner the rectangle
 *\param QPointF press_point
 *\param QPointF point
 *\return bool
 */
bool GraphicsRectItem::hasClickedOn(QPointF press_point, QPointF point) const {
        return (
                (press_point.x() >= point.x()+10 - myHandlerWidth || press_point.x() >= point.x()-10 - myHandlerWidth) &&\
                (press_point.x() <  point.x()-10 + myHandlerWidth || press_point.x() <  point.x()+10 + myHandlerWidth) &&\
                (press_point.y() >= point.y()+10 - myHandlerWidth || press_point.y() >= point.y()-10 - myHandlerWidth) &&\
                (press_point.y() <  point.y()-10 + myHandlerWidth || press_point.y() <  point.y()+10 + myHandlerWidth)
        );
}


/*!
 *\brief emits the \a selectedChange signal
 *\return void
 */
void GraphicsRectItem::throwSignal()
{
    emit selectedChange(this,true);
}


/*!
 *\brief removes the selected items
 *\return void
 */
void GraphicsRectItem::deleteItem()
{
    foreach (QGraphicsItem *item, scene()->selectedItems()) {
        scene()->removeItem(item);
    }
}


/*!
 *\brief change z value of rectangle
 *\return void
 */
void GraphicsRectItem::sendToBack()
{
    if (scene()->selectedItems().isEmpty())
        return;

    QGraphicsItem *selectedItem = scene()->selectedItems().first();
    QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();
    qreal zValue = 0;
    foreach (QGraphicsItem *item, overlapItems) {
        if (item->zValue() <= zValue )
            zValue = item->zValue() - 0.1;
    }
    selectedItem->setZValue(zValue);
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneDragDropEvent *event
 *\return void
 */
void GraphicsRectItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->source() != 0 ){
        if(okItem){
            emit dropItem(this);
            QGraphicsPolygonItem::dropEvent(event);
        }else{
            emit outElement();
        }
    }else{
        emit outElement();
    }

}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneMouseEvent *event
 *\return void
 */
void GraphicsRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    corregirPolX= event->pos().x();
    corregirPolY= event->pos().y();
    pressInsertItem=false;

    if(!insertItem){
        setBrush(Qt::black);
        movMouseX=mapToScene(event->pos()).x();
        movMouseY=mapToScene(event->pos()).y();

        if(isSelected()){
                if (event -> buttons() & Qt::LeftButton) {
                        QPointF mouse_point = event -> pos();
                        QPointF point;
                        for(mySelPoint=0;mySelPoint<8;mySelPoint++){
                                if(mySelPoint<3) point=QPointF(myPos2.x()/2*mySelPoint,0);
                                if(mySelPoint==3) point=QPointF(myPos2.x(),myPos2.y()/2);
                                if(mySelPoint>3 && mySelPoint<7) point=QPointF(myPos2.x()/2*(mySelPoint-4),myPos2.y());
                                if(mySelPoint==7) point=QPointF(0,myPos2.y()/2);
                                if(hasClickedOn(mouse_point,point)) break;
                        }//for
                        if(mySelPoint==8) mySelPoint=-1;
                        else event->accept();
                }
        }

        setPen(QPen(Qt::green,2,Qt::SolidLine));
        pressInsertItem=true;
    }
    throwSignal();
    QGraphicsPolygonItem::mousePressEvent(event);    
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneMouseEvent *event
 *\return void
 */
void GraphicsRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{    
    if(pressInsertItem){
        QPointF posFromItem= mapFromItem(this,event->pos());

        contMoveX=  mapToScene(event->pos()).x() - movMouseX;
        movMouseX=mapToScene(event->pos()).x();

        contMoveY=  mapToScene(event->pos()).y() - movMouseY;
        movMouseY=mapToScene(event->pos()).y();

        if ((event -> buttons() & Qt::LeftButton)&&(mySelPoint>-1)) {
            prepareGeometryChange();
            switch (mySelPoint) {
                    case 0:     /*arribaIzquierda*/
                            myPos2.setX(myPos2.x()-contMoveX);
                            myPos2.setY(myPos2.y()-contMoveY);
                            setX(x()+contMoveX);
                            setY(y()+contMoveY);
                            break;
                    case 1:     /*arribaMedio*/
                            setPos(pos().x(),y()+contMoveY);
                            myPos2.setY(myPos2.y()-contMoveY);
                            break;
                    case 2:     /*arribaDerecha*/
                            myPos2.setX(myPos2.x()+contMoveX);
                            setPos(pos().x(),y()+contMoveY);
                            myPos2.setY(myPos2.y()-contMoveY);
                            break;
                    case 3:     /*derechaMedio*/
                            myPos2.setX(posFromItem.x());
                            break;
                    case 6:     /*abajoDerecha*/
                            myPos2.setX(myPos2.x()+contMoveX);
                            myPos2.setY(myPos2.y()+contMoveY);
                            break;
                    case 5:     /*abajoMedio*/
                            myPos2.setY(posFromItem.y());
                            break;
                    case 4:     /*abajoIzquierda*/
                            myPos2.setY(myPos2.y()+contMoveY);
                            setPos(x()+contMoveX,pos().y());
                            myPos2.setX(myPos2.x()-contMoveX);
                            break;
                    case 7:     /*izquierdaMedio*/
                            setX(x()+contMoveX);
                            myPos2.setX(myPos2.x()-contMoveX);
                            break;
                    default:
                            break;
            }
            update();
            myPolygon=createPath();
            setPolygon(myPolygon);
        }else{
            QGraphicsItem::mouseMoveEvent( event );
        }
        emit mouseMoveX(scenePos().x(),scenePos().x()+getWidthRec());
        emit mouseMoveY(scenePos().y(),scenePos().y()+getHeightRec());
        emit itemSelected(this);
    }
 }


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneHoverEvent* event
 *\return void
 */
void GraphicsRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    setBrush(Qt::gray);   
    QGraphicsItem::hoverEnterEvent( event );
    QPointF posSceneXY;
    posSceneXY.setX(event->screenPos().x()+boundingRect().width()-event->pos().x()+2);
    posSceneXY.setY(event->screenPos().y());  
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneHoverEvent *event
 *\return void
 */
void GraphicsRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    if(!insertItem){
        QPointF mouse_point = event -> pos();
        QPointF point;
        for(mySelPoint=0;mySelPoint<8;mySelPoint++){
            if(mySelPoint<3) point=QPointF(myPos2.x()/2*mySelPoint,0);
            if(mySelPoint==3) point=QPointF(myPos2.x(),myPos2.y()/2);
            if(mySelPoint>3 && mySelPoint<7) point=QPointF(myPos2.x()/2*(mySelPoint-4),myPos2.y());
            if(mySelPoint==7) point=QPointF(0,myPos2.y()/2);
            if(hasClickedOn(mouse_point,point)) break;
        }//for
        if(mySelPoint==8) mySelPoint=-1;
        else event->accept();

        QCursor q;

        switch (mySelPoint) {
                case 0:
                        q.setShape(Qt::SizeFDiagCursor);
                        break;
                case 1:
                        q.setShape(Qt::SizeVerCursor);
                        break;
                case 2:
                        q.setShape(Qt::SizeBDiagCursor);
                        break;
                case 3:
                        q.setShape(Qt::SizeHorCursor);
                        break;
                case 6:
                        q.setShape(Qt::SizeFDiagCursor);
                        break;
                case 5:
                        q.setShape(Qt::SizeVerCursor);
                        break;
                case 4:
                        q.setShape(Qt::SizeBDiagCursor);
                        break;
                case 7:
                        q.setShape(Qt::SizeHorCursor);
                        break;
                default:
                        q.setShape(Qt::SizeAllCursor);
                        break;
        }
         setCursor(q);
    }
    QGraphicsItem::hoverMoveEvent( event );
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneHoverEvent *event
 *\return void
 */
void GraphicsRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(Qt::white);
    QGraphicsItem::hoverLeaveEvent( event );
    emit closeMediasRegion();
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneMouseEvent *event
 *\return void
 */
void GraphicsRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setBrush(Qt::white);
    emit setDataNcl();
    QGraphicsPolygonItem::mouseReleaseEvent( event );
}


/*!
 *\brief redefined action of \b QGraphicsPolygonItem
 *\param QGraphicsSceneContextMenuEvent *event
 *\return void
 */
void GraphicsRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myMenu->exec(event->screenPos());
}


/*!
 *\brief returns the width the rectangle
 *\return qreal
 */
qreal GraphicsRectItem::getWidthRec()
{
    return boundingRect().width();
}


/*!
 *\brief returns the height the rectangle
 *\return qreal
 */
qreal GraphicsRectItem::getHeightRec()
{
    return boundingRect().height();
}


/*!
 *\brief sets the height of the rectangle
 *\param qreal height
 *\return void
 */
void GraphicsRectItem::setHeight(qreal height)
{
   prepareGeometryChange();
   myPos2.setY(height-2);
   update();
   myPolygon=createPath();
   setPolygon(myPolygon);
}


/*!
 *\brief sets the width of the rectangle
 *\param qreal width
 *\return void
 */
void GraphicsRectItem::setWidth(qreal width)
{
   prepareGeometryChange();
   myPos2.setX(width-2);
   update();
   myPolygon=createPath();
   setPolygon(myPolygon);
}


/*!
 *\brief sets the \a prop value to permit create a new rectangle
 *\param bool prop
 *\return void
 */
void GraphicsRectItem::setInsertItem(bool prop){
    insertItem=prop;
}


/*!
 *\brief adds a new media to the list of medias of the rectangle
 *\param QString mediaIdParam
 *\return void
 */
void GraphicsRectItem::addMedia(QString mediaIdParam)
{
    medias.append(mediaIdParam);
}


/*!
 *\brief sets the name of the rectangle
 *\param QString nameP
 *\return void
 */
void GraphicsRectItem::setName(QString nameP)
{
    name = nameP;
}


/*!
 *\brief returns the name of rectangle
 *\return QString
 */
QString GraphicsRectItem::getName()
{
    return name;
}


/*!
 *\brief adds new image to rectangle (unused yet)
 *\param QImage image
 *\return void
 */
void GraphicsRectItem::addImage(QImage image)
{
    image = image.scaled(50,50 , Qt::IgnoreAspectRatio, Qt::FastTransformation);
    QPixmap pixTmp(QPixmap::fromImage(image));
    ((QGraphicsPixmapItem*)childItems().first())->setPixmap(pixTmp);

    qreal posRecEjeX2 = boundingRect().x();
    qreal posRecEjey2 = boundingRect().y();
    qreal anchoRec2 = boundingRect().width();
    qreal altoRec2 = boundingRect().height();

    QPointF posImagen = childItems().first()->mapFromParent(posRecEjeX2,posRecEjey2);

    qreal anchoImagen =childItems().first()->boundingRect().x()+childItems().first()->boundingRect().width();
    qreal altoImagen=childItems().first()->boundingRect().y()+childItems().first()->boundingRect().height();
    childItems().first()->moveBy(posImagen.x()+(anchoRec2/2)-(anchoImagen/2),posImagen.y()+(altoRec2/2)-(altoImagen/2));

    childItems().first()->update();
}


/*!
 *\brief adds the name of the media to rectangle (unused yet)
 *\param QString nombre
 *\return void
 */
void GraphicsRectItem::addText(QString nombre)
{
    qreal posRecEjeX2 = boundingRect().x();
    qreal posRecEjey2 = boundingRect().y();
    ((QGraphicsTextItem*)childItems().at(1))->setPlainText(nombre);
    QPointF posTexto = childItems().at(1)->mapFromParent(posRecEjeX2,posRecEjey2);
    childItems().at(1)->moveBy(posTexto.x()+10,posTexto.y()+10);
    childItems().at(1)->update();
}


/*!
 *\brief returns the list of name of all rectangles
 *\return QStringList
 */
QStringList GraphicsRectItem::getMedias()
{
    return medias;
}


/*!
 *\brief eliminates one media in row number \a row the list of medias
 *\param int row
 *\return void
 */
void GraphicsRectItem::removeMedia(int row)
{
    medias.removeAt(row);
}


/*!
 *\brief returns the width in \b ncl format
 *\return QString
 */
QString GraphicsRectItem::getWidthRecNCL()
{
    return wNCL;
}


/*!
 *\brief returns the heigh in \b ncl format
 *\return QString
 */
QString GraphicsRectItem::getHeighRecNCL()
{
    return hNCL;
}


/*!
 *\brief returns the X position in \b ncl format
 *\return QString
 */
QString GraphicsRectItem::getXRecNCL()
{
    return xNCL;
}


/*!
 *\brief returns the Y position in \b ncl format
 *\return QString
 */
QString GraphicsRectItem::getYRecNCL()
{
    return yNCL;
}


/*!
 *\brief sets the height of the rectangle in \b ncl format
 *\param QString alto
 *\return void
 */
void GraphicsRectItem::setHeighNCL(QString alto)
{
   hNCL = alto;
}


/*!
 *\brief sets the width of the rectangle in \b ncl format
 *\param QString ancho
 *\return void
 */
void GraphicsRectItem::setWidthNCL(QString ancho)
{
    wNCL = ancho;
}


/*!
 *\brief sets the X position of the rectangle in \b ncl format
 *\param QString x
 *\return void
 */
void GraphicsRectItem::setXNCL(QString x)
{
    xNCL = x;
}


/*!
 *\brief sets the Y position of the rectangle in \b ncl format
 *\param QString y
 *\return void
 */
void GraphicsRectItem::setYNCL(QString y)
{
    yNCL = y;
}

/*!
 *\brief sets \okItem in true
 *\return void
 */
void GraphicsRectItem::setTrueOkItemDrop()
{
    okItem = true;
}


/*!
 *\brief sets \okItem in false
 *\return void
 */
void GraphicsRectItem::setFlaseOkItemDrop()
{
    okItem = false;
}

void GraphicsRectItem::setX(qreal x)
{
    setPos(x,y());
}

void GraphicsRectItem::setY(qreal y)
{
    setPos(x(),y);
}

