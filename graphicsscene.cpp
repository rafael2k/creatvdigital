/*!
*\file graphicsscene.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to contain and manipulate rectangles in space area.
*/


#include "graphicsscene.h"
#include <QtGui>
#include <iostream>

using namespace std;

/*!
 *\brief creates the GraphicsScene and initialize values
 *\param QMenu *itemMenu
 */
GraphicsScene::GraphicsScene(QMenu *itemMenu)
{
    regionName = 0;
    myMenu = itemMenu;
    subRegion = false;
    buttonPressed = false;
    canEnlarge=false;
    myGrid=10.0;
    new QGraphicsScene(this);
    setSceneRect(QRect(0, 0, 2500, 1660));
}


/*!
 *\brief this action was reuse an example of Qt
 *\param QPointF pos
 *\return QPointF
 */
QPointF GraphicsScene::onGrid(QPointF pos)
{
    qreal x = qRound(pos.x()/myGrid)*myGrid;
    qreal y = qRound(pos.y()/myGrid)*myGrid;
    QPointF result = QPointF(x,y);
    return result;
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(buttonPressed && mouseEvent->button()==Qt::LeftButton){
        insertedDrawItem = new GraphicsRectItem( myMenu);


        insertedDrawItem->setName(QString::number(getGetRegionName(regionName)));


        insertedDrawItem->setPen(QPen(Qt::green,2,Qt::SolidLine));
        insertedDrawItem->setBrush(Qt::black);

        connect(insertedDrawItem, SIGNAL(selectedChange(GraphicsRectItem*,bool)),this, SLOT(itemSelectecdSlot(GraphicsRectItem*,bool)));
        connect(insertedDrawItem, SIGNAL(itemSelected(GraphicsRectItem*)),this, SIGNAL(itemSelected(GraphicsRectItem*)));
        connect(insertedDrawItem, SIGNAL(dropItem(GraphicsRectItem*)),this, SLOT(dropItemSlot(GraphicsRectItem*)));
        //connect(insertedDrawItem, SIGNAL(showMediasRegion(QPointF,QList<Media*>)),this, SLOT(showMediasRegion2(QPointF,QList<Media*>)));
        //connect(insertedDrawItem, SIGNAL(closeMediasRegion()),this, SLOT(closeMediasRegion2()));
        connect(insertedDrawItem, SIGNAL(setDataNcl()),this, SIGNAL(setDataNcl()));
        connect(insertedDrawItem, SIGNAL(outElement()),this,SIGNAL(outElement()));

        addItem(insertedDrawItem);        
        insertedDrawItem->setPos(mouseEvent->scenePos());
        canEnlarge=true;
        setPropItems(true);
    }else{
        setPropItems(false);
    }    
    QGraphicsScene::mousePressEvent(mouseEvent);
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    canEnlarge=false;
    if(!buttonPressed){
        setPropItems(false);
    }else{
        if (mouseEvent->button()==Qt::LeftButton){
            if (!subRegion)
                itemSelectecdSlot(insertedDrawItem,false);

            subRegion = false;
            insertedDrawItem->setBrush(Qt::white);
            clearSelection();

            insertedDrawItem->setSelected(true);
            insertedDrawItem->setXNCL(QString::number(insertedDrawItem->x()));
            insertedDrawItem->setYNCL(QString::number(insertedDrawItem->y()));
            insertedDrawItem->setWidthNCL(QString::number(insertedDrawItem->getWidthRec()));
            insertedDrawItem->setHeighNCL(QString::number(insertedDrawItem->getHeightRec()));
        }
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


/*!
 *\brief emits the \a addChildTreeItem or \a addRootTreeItem or \a itemSelected signal
 *\param GraphicsRectItem *item
 *\param bool subRegionP
 *\return void
 */
void GraphicsScene::itemSelectecdSlot(GraphicsRectItem *item, bool subRegionP)
{
    if(buttonPressed ){
        if (subRegionP){
            insertedDrawItem->setParentItem(item);
            insertedDrawItem->correctPoligon();
            subRegion = true;
            emit addChildTreeItem(QString::number(regionName), item->getName());
            regionName++;
        }else{
            subRegion = false;
            emit addRootTreeItem(QString::number(regionName));
            regionName++;
        }
     }else{
        insertedDrawItem = item;
        emit itemSelected(item);
     }
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(canEnlarge){
        insertedDrawItem->setPos2(mouseEvent->scenePos());
        emit itemSelected(insertedDrawItem);
        emit mouseMoveX(insertedDrawItem->scenePos().x(),insertedDrawItem->scenePos().x()+insertedDrawItem->getWidthRec());
        emit mouseMoveY(insertedDrawItem->scenePos().y(),insertedDrawItem->scenePos().y()+insertedDrawItem->getHeightRec());
    }
    emit mouseMove(mouseEvent->scenePos());
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}


/*!
 *\brief sets cursor and flag of all rectangles
 *\param bool prop
 *\return void
 */
void GraphicsScene::setPropItems(bool prop)
{
    QList<QGraphicsItem *> lista = items();
    for(int i = 0; i < lista.size();i++){
        if(lista.at(i)->type() == 5){ //item is rectangulo
            GraphicsRectItem *rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
            if(prop){
               rectItem->setCursor(Qt::CrossCursor);
               rectItem->setInsertItem(prop);
            }else{
               rectItem->setCursor(Qt::ArrowCursor);
               rectItem->setInsertItem(prop);
            }
        }
    }
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneWheelEvent *mouseEvent
 *\return void
 */
void GraphicsScene::wheelEvent(QGraphicsSceneWheelEvent *mouseEvent)
{
    if(mouseEvent->modifiers()==Qt::ControlModifier){
        int i =  mouseEvent->delta();
        qreal factor;
        if(i>=0){
            factor = i/100.0;
        }else {
            factor = -100.0/i; // negative Richtung ...
        }
        emit zoom(factor);
        mouseEvent->setAccepted(true);
        return;
    }
    QGraphicsScene::wheelEvent(mouseEvent);
}


/*!
 *\brief returns selected rectangle
 *\return GraphicsRectItem*
 */
GraphicsRectItem* GraphicsScene::getSelected()
{
    return insertedDrawItem;
}


/*!
 *\brief emits the \a itemDrop signal
 *\param GraphicsRectItem *item
 *\return void
 */
void GraphicsScene::dropItemSlot(GraphicsRectItem *item)
{
    insertedDrawItem = item;
    emit itemDrop(item);
}


/*!
 *\brief sets \a buttonPressed value with \a press
 *\param bool press
 *\return void
 */
void GraphicsScene::setButtonPressed(bool press)
{
    buttonPressed = press;
}


/*!
 *\brief inserts a new rectangle
 *\param QString name
 *\param qreal axisX
 *\param qreal axisY
 *\param qreal width
 *\param qreal height
 *\param qreal z
 *\param GraphicsRectItem *parentItem
 *\return void
 */
void GraphicsScene::insertItem(QString name,qreal axisX, qreal axisY,qreal width,qreal height,qreal z,GraphicsRectItem *parentItem)
{
    insertedDrawItem = new GraphicsRectItem( myMenu);
    insertedDrawItem->setName(name);  

    connect(insertedDrawItem, SIGNAL(selectedChange(GraphicsRectItem*,bool)),this, SLOT(itemSelectecdSlot(GraphicsRectItem*,bool)));
    connect(insertedDrawItem, SIGNAL(itemSelected(GraphicsRectItem*)),this, SIGNAL(itemSelected(GraphicsRectItem*)));
    connect(insertedDrawItem, SIGNAL(dropItem(GraphicsRectItem*)),this, SLOT(dropItemSlot(GraphicsRectItem*)));
    //connect(insertedDrawItem, SIGNAL(showMediasRegion(QPointF,QList<Media*>)),this, SLOT(showMediasRegion2(QPointF,QList<Media*>)));
    //connect(insertedDrawItem, SIGNAL(closeMediasRegion()),this, SLOT(closeMediasRegion2()));
    connect(insertedDrawItem, SIGNAL(setDataNcl()),this, SIGNAL(setDataNcl()));  

    addItem(insertedDrawItem);
    insertedDrawItem->setZValue(z);
    insertedDrawItem->setWidth(width);
    insertedDrawItem->setHeight(height);
    insertedDrawItem->setPosistionXY(axisX,axisY);
    insertedDrawItem->setParentItem(parentItem);

    setPropItems(true);

    subRegion = false;
    insertedDrawItem->setBrush(Qt::white);

    if (parentItem == 0){
        itemSelectecdSlot(insertedDrawItem,false);
        emit addRootTreeItem(name);
    }else{
        emit addChildTreeItem(name, parentItem->getName());
    }

    insertedDrawItem->setSelected(true);
    insertedDrawItem->setPen(QPen(Qt::green,2,Qt::SolidLine));
    insertedDrawItem->setBrush(Qt::white);
    insertedDrawItem->setXNCL(QString::number(insertedDrawItem->x()));
    insertedDrawItem->setYNCL(QString::number(insertedDrawItem->y()));
    insertedDrawItem->setWidthNCL(QString::number(insertedDrawItem->getWidthRec()));
    insertedDrawItem->setHeighNCL(QString::number(insertedDrawItem->getHeightRec()));
}


/*!
 *\brief sets the automatic name \a number of the regions
 *\param int number
 *\return void
 */
void GraphicsScene::setRegionName(int number)
{
    regionName = number;
}


/*!
 *\brief gets the last automatic name of the regions
 *\return int
 */
int GraphicsScene::getRegionName()
{
    return regionName;
}


/*!
 *\brief returns a new automatic name to a region
 *\param int &x
 *\return int
 */
int GraphicsScene::getGetRegionName(int &x)
{
    if(existRegion(x)){
        x++;
        return getGetRegionName(x);
    }else{
        return x;
    }
}


/*!
 *\brief verifies if the region name \a x already exist
 *\param int x
 *\return bool
 */
bool GraphicsScene::existRegion(int x)
{
    bool exist = false;
    for (int i = 0; i < items().count(); i++){
        if(items().at(i)->type() == 5){ //is a graphiscsrectitem
            GraphicsRectItem *rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(items().at(i));
            if(rectItem->getName() == QString::number(x)){
                exist = true;
            }
        }
    }
    return exist;
}


/*
 *\brief emits the \a showMediasRegion signal
 *\param QPointF posWindow
 *\param QList<Media*> medias
 *\return void
 */
/*void GraphicsScene::showMediasRegion2(QPointF posWindow, QList<Media*> medias)
{
    emit showMediasRegion(posWindow,medias);
}*/


/*
 *\brief emits the \a closeMediasRegion signal
 *\return void
 */
/*void GraphicsScene::closeMediasRegion2()
{
    emit closeMediasRegion();;
}*/

