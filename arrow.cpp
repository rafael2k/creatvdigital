/*!
*\file arrow.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create,remove and modify arrows.
*/


#include "arrow.h"
#include <QtGui>
#include <iostream>

using namespace std;

const qreal Pi = 3.14;

/*!
 *\brief creates the Arrow and initialize values
 *\param QLineF pos
 */
Arrow::Arrow(QLineF pos)
{
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity, true);
    myType=ArrowLineAux;   
    setLine(pos);    
    newLine=pos;    
    myColor=Qt::red;    
}


/*!
 *\brief creates the Arrow with \a startItem and \a endItem like Image type and initialize values
 *\param Image *startItem
 *\param Image *endItem
 *\param TypeArrow typeArrow
 *\param QGraphicsItem *parent
 *\param QGraphicsScene *scene
 */
Arrow::Arrow(Image *startItem, Image *endItem,TypeArrow typeArrow,
         QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity, true);
    myType=typeArrow;
    myStartItem = startItem;
    myEndItem = endItem;   
    if(myType== InteractLine){              
        myColor = Qt::red;
        setPen(QPen(myColor, 3,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
    }else if(myType==UnionDiamondTempLine){
        myColor = Qt::black;
        setPen(QPen(myColor, 2,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
    }else{
        myColor = Qt::black;
        setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
}


/*!
 *\brief creates the Arrow with \a startItem like Arrow type and \a endItem like Image type and initialize values
 *\param Arrow *startItem
 *\param Image *endItem
 *\param TypeArrow typeArrow
 *\param QGraphicsItem *parent
 *\param QGraphicsScene *scene
 */
 Arrow::Arrow(Arrow *startItem, Image *endItem,TypeArrow typeArrow,
      QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsLineItem(parent, scene)
{
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    myStartItemArrow = startItem;
    myEndItem = endItem;
    myType = typeArrow;
    if(myType== UnionInteractiveLine){
        myColor = Qt::red;
        setPen(QPen(myColor, 3,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
}


 /*!
  *\brief this action was reuse an example of Qt
  *\return QRectF
  */
QRectF Arrow::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}


/*!
 *\brief updates position of the arrow
 *\return void
 */
void Arrow::updatePosition()
{
    if(myType == UnionLine || myType == UnionInteractiveLine){     
        QLineF line(myStartItemArrow->line().p2(), mapFromItem(myEndItem,0,0));
        setLine(line);       
    }else if(myType == UnionLineTempInteract){
        QLineF line(mapFromItem(myStartItem, 0,0), mapFromItem(myEndItem,0,0));
        setLine(line);
    }else if(myType == ArrowLineAux){       
        setLine(newLine);
    }else{       
        QLineF line(mapFromItem(myStartItem, 0,0), mapFromItem(myEndItem,0,0));
        setLine(line);
    }
}


/*!
 *\brief this action was reuse an example of Qt
 *\return QPainterPath
 */
QPainterPath Arrow::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}


/*!
 *\brief builds the arrow
 *\param QPainter *painter
 *\param const QStyleOptionGraphicsItem *
 *\param QWidget *
 *\return void
 */
void Arrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *,QWidget *)
{
    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize;

    if(myType==InteractLine || myType== UnionLine || myType== UnionLineTempInteract
       || myType== UnionInteractiveLine || myType== ArrowLineAux || myType== UnionDiamondTempLine){
        arrowSize= 0;
    }else{
        arrowSize = 8;
    }

    painter->setPen(myPen);
    painter->setBrush(myColor);

    if(myType== ArrowLineAux){
        setLine(newLine);
        double angle = ::acos(line().dx() / line().length());
        if (line().dy() >= 0)
            angle = (Pi * 2) - angle;

        QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
        if (isSelected()) {
            QLineF myLine = line();
            myLine.translate(0, 4.0);
            painter->drawLine(myLine);
            myLine.translate(0,-8.0);
            painter->drawLine(myLine);
        }
    }else if(myType== UnionInteractiveLine){

        QPointF p2;      
        QLineF polyLine;

        p2 = myEndItem->scenePos();
        polyLine = QLineF(myStartItemArrow->line().p1(), p2);


        setLine(myEndItem->arrives()->x(),myEndItem->arrives()->y(),myEndItem->arrives()->x(),myStartItemArrow->line().p2().y());

        double angle = ::acos(line().dx() / line().length());
        if (line().dy() >= 0)
            angle = (Pi * 2) - angle;

        QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
        if (isSelected()) {
            QLineF myLine = line();
            myLine.translate(0, 4.0);
            painter->drawLine(myLine);
            myLine.translate(0,-8.0);
            painter->drawLine(myLine);
        }
    }else if(myType== UnionLine){       
        QPointF p2;   
        QLineF polyLine;

        p2 = myEndItem->scenePos();
        polyLine = QLineF(myStartItemArrow->line().p1(), p2);     

        setLine(myEndItem->arrives()->x(),myEndItem->arrives()->y(),myEndItem->arrives()->x(),myStartItemArrow->line().p2().y());

        double angle = ::acos(line().dx() / line().length());
        if (line().dy() >= 0)
            angle = (Pi * 2) - angle;

        QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
        if (isSelected()) {
            QLineF myLine = line();
            myLine.translate(0, 4.0);
            painter->drawLine(myLine);
            myLine.translate(0,-8.0);
            painter->drawLine(myLine);
        }
    }else if(myType == TempLine || myType==InteractLine|| myType==UnionLineTempInteract || myType==UnionDiamondTempLine){
        if (myStartItem->collidesWithItem(myEndItem))
                return;

        QPointF p2;
        QLineF polyLine;

        p2 = myEndItem->scenePos();
        polyLine = QLineF(myStartItem->scenePos(), p2);        

        if(myType==UnionLineTempInteract){
            setLine(myEndItem->arrives()->x(),myEndItem->arrives()->y(),myStartItem->arrives()->x(),myStartItem->send()->y());
        }else
            setLine(myEndItem->arrives()->x(),myEndItem->arrives()->y(),myStartItem->send()->x(),myStartItem->send()->y());//QLineF(intersectPoint, myStartItem->pos()));

        double angle = ::acos(line().dx() / line().length());
        if (line().dy() >= 0)
            angle = (Pi * 2) - angle;

        QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                        cos(angle + Pi / 3) * arrowSize);
        QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                        cos(angle + Pi - Pi / 3) * arrowSize);

        arrowHead.clear();
        arrowHead << line().p1() << arrowP1 << arrowP2;
        painter->drawLine(line());
        painter->drawPolygon(arrowHead);
        if (isSelected()) {
            QLineF myLine = line();
            myLine.translate(0, 4.0);
            painter->drawLine(myLine);
            myLine.translate(0,-8.0);
            painter->drawLine(myLine);
        }
    }
}


/*!
 *\brief returns the total children of the arrow \a arrowtItemP
 *\param Arrow *arrowtItemP
 *\param int totalLong
 *\return int
 */
int Arrow::recursiveCountItems(Arrow *arrowtItemP, int totalLong)
{
    Arrow *arrowtItem;
    QList<QGraphicsItem *> todosHijos = arrowtItemP->childItems();
    if(todosHijos.size()==0){
        if( arrowtItemP->getMyType()==Arrow::TempLine)
            totalLong++;
    }else if(todosHijos.size()>=1){
        if( arrowtItemP->getMyType()==Arrow::TempLine){
            totalLong = totalLong+1;
        }
        for(int i = 0; i < todosHijos.size();i++){
            if(todosHijos.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(todosHijos.at(i));
                totalLong = recursiveCountItems(arrowtItem,totalLong);
            }
        }
    }
    return totalLong;
}


/*!
 *\brief returns the start item of the arrow
 *\return Image*
 */
Image* Arrow::getStartItem()
{
    return myStartItem;
}


/*!
 *\brief returns the end item of the arrow
 *\return Image*
 */
Image* Arrow::getEndItem()
{
    return myEndItem;
}


/*!
 *\brief sets button to arrow
 *\param Image *buttonP
 *\return void
 */
void Arrow::setButton(Image *buttonP)
{
    button=buttonP;
}


/*!
 *\brief returns the button of the InteractLine
 *\return Image*
 */
Image* Arrow::getButton()
{
    return button;
}


/*!
 *\brief sets line \a newLineP to Arrow of the ArrowLineAux type
 *\param QLineF newLineP
 *\return void
 */
void Arrow::setLineAux(QLineF newLineP)
{
    setLine(newLineP);
    newLine=newLineP;
}


/*!
 *\brief returns the item \a startArrow of the arrow
 *\return Arrow*
 */
Arrow *Arrow::getMyStartItemArrow()
{
    return myStartItemArrow;
}


/*!
 *\brief sets position of the UnionLine Arrow
 *\param qreal posXUnionLineP
 *\return void
 */
void Arrow::setPosXUnionLine(qreal posXUnionLineP)
{
    if(myType==UnionLine)
        posXUnionLine =posXUnionLineP;
}


/*!
 *\brief returns x position of the UnionLine
 *\return qreal
 */
qreal Arrow::getPosXUnionLine()
{
    if(myType==UnionLine)
        return posXUnionLine;
        else
            return 0;
}


/*!
 *\brief sets \a posy to children's of \a arrowtItem
 *\param Arrow *arrowtItem
 *\param qreal posy
 *\param qreal originalPosY
 *\return void
 */
void Arrow::setRecursivePos(Arrow *arrowtItem,qreal posy ,qreal originalPosY)
{
    QList<QGraphicsItem *> todosHijos = arrowtItem->childItems();
    int exPosYLine = originalPosY / LINESIZE;
    int posYLineAux =0;

    if(todosHijos.size()>=1){
        for(int i = 0; i < todosHijos.size();i++){
            Arrow *arrowtItem =  qgraphicsitem_cast<Arrow *>(todosHijos.at(i));
            if(arrowtItem->getMyType()==Arrow::UnionInteractiveLine){
                posYLineAux = arrowtItem->getEndItem()->y() / LINESIZE;
                arrowtItem->getEndItem()->setY(((posYLineAux-exPosYLine)*LINESIZE)+posy);
            }else if(arrowtItem->getMyType()==Arrow::TempLine || arrowtItem->getMyType()==Arrow::InteractLine){
                    posYLineAux = arrowtItem->getStartItem()->y() / LINESIZE;
                    arrowtItem->getStartItem()->setY(((posYLineAux-exPosYLine)*LINESIZE)+posy);
                    arrowtItem->getEndItem()->setY(((posYLineAux-exPosYLine)*LINESIZE)+posy);
            }          
            setRecursivePos(arrowtItem,posy, originalPosY);
        }
    }
}


/*!
 *\brief sets duration of media
 *\param QString value
 *\return void
 */
void Arrow::setLongTempLineOriginal(QString value)
{
    longTempLineOriginal =  value;
}


/*!
 *\brief returns the long of the initial arrow
 *\return QString
 */
QString Arrow::getLongTempLineOriginal()
{
    return longTempLineOriginal;
}


/*!
 *\brief sets color to Arrow
 *\param QColor color
 *\return void
 */
void Arrow::setMyColor(QColor color)
{    
    myColor = color;
}
