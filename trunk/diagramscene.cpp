/*!
*\file diagramscene.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to contain and manipulate arrows and images in temporal area.
*/


#include <QtGui>
#include <QMouseEvent>
#include "diagramscene.h"
#include <iostream>

using namespace std;

bool botonInteractividadAux=false;
bool botonDeleteLine=false;


/*!
 *\brief creates the DiagramScene and initialize values
 */
DiagramScene::DiagramScene()
{
    new QGraphicsScene(this);
    canMove=false;
    cantLineTotal=1;
    posNearArrow=-1;
    distTempLineInteractLine=10;
    currentLine=0;
    viewItems = true;
    okItem = false;
    alreadySetColor = false;
}


/*!
 *\brief inserts the first arrow
 *\param QImage currentImage
 *\param QString nameMedia
 *\param qreal MediaDuration
 *\param bool haveDuration
 *\param qreal originalDuration
 *\param bool openProject
 *\param bool infinite
 *\return Arrow*
 */
Arrow* DiagramScene::addFirstImage(QImage currentImage,QString nameMedia,qreal MediaDuration,bool haveDuration,qreal originalDuration,bool openProject,bool infinite)
{
    QString path ="";
    QImage image2(QDir::currentPath()+"/images/linevertical.png");
    QPixmap pixTmp2(QPixmap::fromImage(image2));
    startItem = new Image(pixTmp2,Image::InitTermination);
    startItem->setPos(0,(LINESIZE/2)-(startItem->boundingRect().height()/2)+3);
    startItem->setInfiniteInteract(false);
    addItem(startItem);

    if(!infinite)
        path = "/images/linevertical.png";
    else
        path = "/images/puntosSuspensivos2.png";

    QImage image(QDir::currentPath()+path);
    QPixmap pixTmp(QPixmap::fromImage(image));
    if (path == "/images/linevertical.png")
        endItem = new Image(pixTmp,Image::EndTermination);
    else
        endItem = new Image(pixTmp,Image::SuspensionPoints);
    addItem(endItem);

    endItem->setParentItem(startItem);
    endItem->setPos(endItem->mapFromScene(MediaDuration ,(LINESIZE/2)-(endItem->boundingRect().height()/2)+3).x(),endItem->mapFromScene(MediaDuration ,(LINESIZE/2)-(endItem->boundingRect().height()/2)+3).y());
    endItem->setInfiniteInteract(false);

    sceneWidthPosImage(MediaDuration);

    arrow = new Arrow(startItem, endItem,Arrow::TempLine);

    if(haveDuration){
        arrow->setLongTempLineOriginal(QString::number(originalDuration));
    }else{
        arrow->setLongTempLineOriginal("-1");
    }
    arrow->setZValue(-1000.0);
    addItem(arrow);
    arrow->updatePosition();

    startItem->setTimeLine(arrow);
    endItem->setTimeLine(arrow);


    connect(startItem, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(endItem, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(startItem, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(endItem, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(startItem, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));
    connect(endItem, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));

    emit insertDescription(-1,currentImage,nameMedia,openProject);

    return arrow;
}



/*!
 *\brief return Y position of the nearest arrow after \a posX
 *\param qreal posX
 *\return qreal
 */
qreal DiagramScene::othersTemLineRight(qreal posX)
{
    if(arrowcerca->getMyType()==Arrow::InteractLine)
        posX = arrowcerca->getButton()->scenePos().x();

    qreal posYArrow=arrowcerca->line().y1();
    qreal posYArrowAux=9900000;
    QList<QGraphicsItem *> TodosItems = items();
    Arrow *arrowtItem;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 6 ){//is Arrow
            arrowtItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if(arrowtItem->parentItem()!=0)
                if(arrowtItem->getMyType()==Arrow::TempLine ){
                    if(arrowcerca->line().y1() < arrowtItem->line().y1()){
                        if(arrowtItem->line().x2() >= posX ){
                            if(posYArrow < arrowtItem->line().y1())
                                posYArrow=arrowtItem->line().y1();
                        }else if(((arrowtItem->line().x2() <= posX && arrowtItem->line().x1() >= posX) || arrowtItem->line().p1().x() <= posX ) && posYArrowAux >= arrowtItem->line().y1()){
                            if(arrowtItem->line().y1()-LINESIZE < posYArrowAux)
                                posYArrowAux=arrowtItem->line().y1()-LINESIZE;
                        }

                    }

                }
        }

    }
    if(posYArrowAux == 9900000 && posYArrow == arrowcerca->line().y1())
        posYArrowAux=arrowcerca->line().y1();
    else if(posYArrowAux == 9900000 && posYArrow != arrowcerca->line().y1())
        posYArrowAux = posYArrow;

    return posYArrowAux;
}


/*!
 *\brief accommodates Y position of arrows
 *\param qreal posX
 *\param QImage currentImage
 *\param QString nameMedia
 *\param qreal MediaDuration
 *\param bool haveDuration
 *\return void
 */
void DiagramScene::insertBodyDownItems(qreal posX,QImage currentImage,QString nameMedia,qreal MediaDuration,bool haveDuration){
    cantLineTotal++;
    if(cantLineTotal>4)
        setSceneRect(QRectF(0, 0, width(), (cantLineTotal+1)*LINESIZE));

    bool insert=false;
    bool interactOK=false;
    update();
    QList<QGraphicsItem *> TodosItems = items();
    qreal auxposy1,auxposy2;    
    qreal posYItem;        
    qreal posYArrow = othersTemLineRight(posX);    
    int numLinea = posYArrow / LINESIZE;
    int currentLinea;

    Arrow *arrowtItem;
    Arrow *arrowtItemParent;

    int numLineArrowCerca = arrowcerca->line().y1() / LINESIZE;

    numLinea++;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type()==6){//item is arrow
            arrowtItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if(arrowtItem->getMyType()==Arrow::TempLine){
                if(!insert){
                    insert=true;
                    auxposy1=(numLinea*LINESIZE)+(LINESIZE/2)-startItem->boundingRect().height()/2;
                    auxposy2=(numLinea*LINESIZE)+(LINESIZE/2)-startItem->boundingRect().height()/2;

                    if(arrowcerca->getMyType()==Arrow::TempLine)
                        insertImage(currentImage,nameMedia,posX,MediaDuration,auxposy1,auxposy2,haveDuration,((MediaDuration* 100)/1000),false,false);
                    else
                        insertImageWithInteract(currentImage,nameMedia,arrowcerca->getButton(),auxposy1,auxposy1,MediaDuration,haveDuration,((MediaDuration* 100)/1000),false,false);
                }

                if(arrowtItem->line().y1() > posYArrow && arrowtItem->parentItem() != 0 ){
                    arrowtItemParent =  qgraphicsitem_cast<Arrow *>(arrowtItem->parentItem());
                    currentLinea = arrowtItemParent->parentItem()->boundingRect().y() / LINESIZE ;
                    interactOK = false;
                    if((arrowtItemParent->getMyType() == Arrow::UnionLineTempInteract && numLineArrowCerca == currentLinea ) || !(arrowtItem->parentItem()->boundingRect().y() > posYArrow)){
                        if(arrowtItem->parentItem()!=0){
                            int numLineaCorriente = arrowtItem->line().y1()/ LINESIZE;
                            numLineaCorriente++;
                            if(numLinea != numLineaCorriente){
                                posYItem = arrowtItem->getStartItem()->scenePos().y() - arrowtItem->getStartItem()->parentItem()->scenePos().y() +LINESIZE/*-(TodosItems.at(i)->boundingRect().height()/2)*/;
                                if(arrowtItem->getMyType()==Arrow::UnionDiamondTempLine){
                                    if (arrowtItem->getStartItem()->getMyType()==Image::Diamond)
                                        arrowtItem->getStartItem()->setY(posYItem);
                                    else
                                        arrowtItem->getEndItem()->setY(arrowtItem->getEndItem()->scenePos().y() - arrowtItem->getEndItem()->parentItem()->scenePos().y() +LINESIZE);

                                    }else{
                                        arrowtItem->getStartItem()->setY(posYItem);
                                        if(arrowtItem->getStartItem()->itemHaveDiamond()){
                                            arrowtItem->getStartItem()->downUpChildrens(arrowtItem,LINESIZE);
                                            arrowtItem->getStartItem()->getDiamond()->setY(arrowtItem->getStartItem()->getDiamond()->scenePos().y() - arrowtItem->getStartItem()->getDiamond()->parentItem()->scenePos().y() + LINESIZE);
                                            arrowtItem->getEndItem()->getDiamond()->setY(arrowtItem->getEndItem()->getDiamond()->scenePos().y() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().y()  + LINESIZE);
                                        }
                                        arrowtItem->updatePosition();
                                    }
                                }
                        }
                    }
                }
            }
        }
    }

}


/*!
 *\brief inserts a new arrow after one interactive arrow
 *\param QImage currentImage
 *\param QString nameMedia
 *\param Image* boton
 *\param qreal posy
 *\param qreal posyEnd
 *\param qreal MediaDuration
 *\param bool haveDuration
 *\param qreal originalDuration
 *\param bool openProject
 *\param bool infinite
 *\return void
 */
void DiagramScene::insertImageWithInteract(QImage currentImage,QString nameMedia, Image* boton,qreal posy,qreal posyEnd,qreal MediaDuration,bool haveDuration, qreal originalDuration,bool openProject,bool infinite)
{
    QString path ="";
    int lineNumberRombo;
    qreal posYRombo;
    qreal longUnionRomboTempLine;
    Arrow *parentArrowCerca;
    QImage image2(QDir::currentPath()+"/images/linevertical.png");
    QPixmap pixTmp2(QPixmap::fromImage(image2));

    int numLinea = posy / LINESIZE;
    emit insertDescription(numLinea-1,currentImage,nameMedia,openProject);

    startItem = new Image(pixTmp2,boton,Image::InitTermination);
    addItem(startItem);
    startItem->childrenOfInteract();

    if(!infinite)
        path = "/images/linevertical.png";
    else
        path = "/images/puntosSuspensivos2.png";

    QImage image(QDir::currentPath()+path);
    QPixmap pixTmp(QPixmap::fromImage(image));
    if (path == "/images/linevertical.png")
        endItem = new Image(pixTmp,Image::EndTermination);
    else
        endItem = new Image(pixTmp,Image::SuspensionPoints);

    addItem(endItem);

    parentArrowCerca =  qgraphicsitem_cast<Arrow *>(arrowcerca->parentItem());

    if(parentArrowCerca->getStartItem()->getInfiniteInteract() || arrowcerca->getEndItem()->getMyType() == Image::SuspensionPoints){
        startItem->setInfiniteInteract(true);
        endItem->setInfiniteInteract(true);
    }else{
        startItem->setInfiniteInteract(false);
        endItem->setInfiniteInteract(false);
    }

    qreal posBoton = boton->scenePos().x()+boton->boundingRect().width()/2 - startItem->boundingRect().width()/2 ;    

    startItem->setParentItem(boton);
    startItem->setPos(startItem->mapFromScene(posBoton,posy).x(),startItem->mapFromScene(posBoton,posy).y());
    startItem->setArrow(parentArrowCerca);

    endItem->setParentItem(boton);
    endItem->setParentItem(startItem);
    endItem->setPos(endItem->mapFromScene(posBoton+MediaDuration,posyEnd).x(),endItem->mapFromScene(posBoton+MediaDuration,posyEnd).y());

    arrow = new Arrow(startItem, endItem,Arrow::TempLine);

    if(haveDuration){        
        arrow->setLongTempLineOriginal(QString::number(originalDuration));
    }else
        arrow->setLongTempLineOriginal("-1");

    arrow->setZValue(-1);
    addItem(arrow);
    arrow->updatePosition();    

    unionArrow = new Arrow(boton,startItem,Arrow::UnionLineTempInteract);
    addItem(unionArrow);
    unionArrow->updatePosition();

    connect(startItem, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(endItem, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(startItem, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(endItem, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(startItem, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));
    connect(endItem, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));    

    unionArrow->setParentItem(arrowcerca);
    arrow->setParentItem(unionArrow);

    startItem->setTimeLine(arrow);
    endItem->setTimeLine(arrow);

    /*--------insert Rombo---------------*/

    QImage imageRombo(QDir::currentPath()+"/images/rombo.png");
    QPixmap pixTmpRombo(QPixmap::fromImage(imageRombo));
    beginRombo = new Image(pixTmpRombo,Image::Diamond);
    addItem(beginRombo);

    endRombo = new Image(pixTmpRombo,Image::Diamond);
    addItem(endRombo);

    lineNumberRombo = posy / LINESIZE;
    posYRombo = (lineNumberRombo*LINESIZE)+(LINESIZE/2)-beginRombo->boundingRect().height()/2;

    if(parentArrowCerca->getStartItem()->itemHaveDiamond())
        longUnionRomboTempLine = (arrowcerca->boundingRect().width()/2) + parentArrowCerca->getStartItem()->getLongUnionDiamondTempLine() - beginRombo->boundingRect().width() / 2;
    else
        longUnionRomboTempLine = arrowcerca->boundingRect().width()/2 - beginRombo->boundingRect().width() / 2;

        beginRombo->setParentItem(arrowcerca->getStartItem());
        beginRombo->setPos(beginRombo->mapFromScene(startItem->scenePos().x()-longUnionRomboTempLine,posYRombo).x(),beginRombo->mapFromScene(startItem->scenePos().x()-longUnionRomboTempLine,posYRombo).y());

        if(arrowcerca->getEndItem()->getMyType() == Image::SuspensionPoints){
            endRombo->setParentItem(arrowcerca->getEndItem());
            endRombo->setPos(endRombo->mapFromScene(arrowcerca->getEndItem()->scenePos().x()+arrowcerca->getEndItem()->boundingRect().width()/2,posYRombo).x(),endRombo->mapFromScene(arrowcerca->getEndItem()->scenePos().x()+arrowcerca->getEndItem()->boundingRect().width()/2,posYRombo).y());
            sceneWidthPosImage(arrowcerca->getEndItem()->scenePos().x()+arrowcerca->getEndItem()->boundingRect().width()/2);            
        }else if(parentArrowCerca->getStartItem()->getInfiniteInteract()){
            endRombo->setParentItem(arrowcerca->getEndItem());
            endRombo->setPos(endRombo->mapFromScene(parentArrowCerca->getEndItem()->getDiamond()->scenePos().x(),posYRombo).x(),endRombo->mapFromScene(parentArrowCerca->getEndItem()->getDiamond()->scenePos().x(),posYRombo).y());
            sceneWidthPosImage(arrowcerca->getEndItem()->scenePos().x()+arrowcerca->getEndItem()->boundingRect().width()/2);
        }else {
            endRombo->setParentItem(arrowcerca->getEndItem());
            endRombo->setPos(endRombo->mapFromScene(endItem->scenePos().x()+longUnionRomboTempLine - (endRombo->boundingRect().width()/2),posYRombo).x(),endRombo->mapFromScene(endItem->scenePos().x()+longUnionRomboTempLine - (endRombo->boundingRect().width()/2),posYRombo).y());
            sceneWidthPosImage(endItem->scenePos().x()+arrowcerca->boundingRect().width());
        }

    beginArrow = new Arrow(beginRombo, startItem,Arrow::UnionDiamondTempLine);
    endArrow = new Arrow(endItem, endRombo,Arrow::UnionDiamondTempLine);

    addItem(beginArrow);
    beginArrow->updatePosition();
    addItem(endArrow);
    endArrow->updatePosition();

    if(!viewItems){
        beginRombo->setOpacity(0);
        beginArrow->setOpacity(0);
        endRombo->setOpacity(0);
        endArrow->setOpacity(0);
    }

    beginArrow->setParentItem(unionArrow);
    endArrow->setParentItem(unionArrow);

    beginRombo->setArrow(beginArrow);
    endRombo->setArrow(endArrow);

    startItem->setDiamond(beginRombo);
    endItem->setDiamond(endRombo);

}


/*!
 *\brief returns interactivity arrow children of \a parentArrow
 *\param Arrow *parentArrow
 *\return Arrow*
 */
Arrow* DiagramScene::searchInteract(Arrow *parentArrow)
{
    if(parentArrow->getMyType() != Arrow::InteractLine){
        Arrow *currentArrow =  qgraphicsitem_cast<Arrow *>(parentArrow->parentItem());
        parentArrow = searchInteract(currentArrow);
    }else{
        return parentArrow;
    }
    return parentArrow;
}


/*!
 *\brief add diamonds to arrow \a arrowP
 *\param Arrow *arrowcercaP
 *\param Arrow *arrowP
 *\param Arrow *unionArrowP
 *\return void
 */
void DiagramScene::checkUnionDiamondTempLine(Arrow *arrowcercaP,Arrow *arrowP, Arrow *unionArrowP)
{
    int lineNumberRombo;
    qreal posYRombo;

    if(arrowcercaP->getStartItem()->itemHaveDiamond()){
        qreal longLine;
        QImage imageRombo(QDir::currentPath()+"/images/rombo.png");
        QPixmap pixTmpRombo(QPixmap::fromImage(imageRombo));
        beginRombo = new Image(pixTmpRombo,Image::Diamond);
        addItem(beginRombo);

        endRombo = new Image(pixTmpRombo,Image::Diamond);
        addItem(endRombo);

        Arrow *interactArrow = searchInteract(arrowcercaP);

        longLine = arrowcercaP->getStartItem()->getLongUnionDiamondTempLine();
        lineNumberRombo = arrowP->getStartItem()->scenePos().y() / LINESIZE;
        posYRombo = (lineNumberRombo*LINESIZE)+(LINESIZE/2)-beginRombo->boundingRect().height()/2;

        beginRombo->setParentItem(interactArrow->getStartItem());
        beginRombo->setPos(beginRombo->mapFromScene(arrowP->getStartItem()->scenePos().x()-longLine,posYRombo).x(),beginRombo->mapFromScene(arrowP->getStartItem()->scenePos().x()-arrowcerca->boundingRect().width()/2,posYRombo).y());

        longLine = longLine - endRombo->boundingRect().width() /2;
        endRombo->setParentItem(interactArrow->getEndItem());

        if(arrowcercaP->getEndItem()->getInfiniteInteract()){
            endRombo->setPos(endRombo->mapFromScene(arrowcercaP->getEndItem()->getDiamond()->scenePos().x(),posYRombo).x(),endRombo->mapFromScene(arrowcercaP->getEndItem()->getDiamond()->scenePos().x(),posYRombo).y());
        }else{
            endRombo->setPos(endRombo->mapFromScene(arrowP->getEndItem()->scenePos().x()+longLine,posYRombo).x(),endRombo->mapFromScene(arrowP->getEndItem()->scenePos().x()+longLine,posYRombo).y());
        }

        arrowP->getStartItem()->setDiamond(beginRombo);
        arrowP->getEndItem()->setDiamond(endRombo);

        beginArrow = new Arrow(beginRombo, arrowP->getStartItem(),Arrow::UnionDiamondTempLine);
        endArrow = new Arrow(arrowP->getEndItem(), endRombo,Arrow::UnionDiamondTempLine);

        addItem(beginArrow);
        beginArrow->updatePosition();
        addItem(endArrow);
        endArrow->updatePosition();

        beginRombo->setArrow(beginArrow);
        endRombo->setArrow(endArrow);

        if(!viewItems){
            beginRombo->setOpacity(0);
            beginArrow->setOpacity(0);
            endRombo->setOpacity(0);
            endArrow->setOpacity(0);
        }

        sceneWidthPosImage(endRombo->scenePos().x());

        beginArrow->setParentItem(unionArrowP);
        endArrow->setParentItem(unionArrowP);
    }
}


/*!
 *\brief inserts a new arrow after one \a TempLine
 *\param QImage currentImage
 *\param QString nameMedia
 *\param qreal posX
 *\param qreal mediaDuration
 *\param qreal posY
 *\param qreal posYItem2
 *\param bool haveDuration
 *\param qreal originalDuration
 *\param bool openProject
 *\param bool infinite
 *\return void
 */
void DiagramScene::insertImage(QImage currentImage,QString nameMedia,qreal posX,qreal mediaDuration,qreal posY,qreal posYItem2,bool haveDuration,qreal originalDuration,bool openProject,bool infinite)
{
    QString path = "";
    int numLinea = posY / LINESIZE;

    emit insertDescription(numLinea-1,currentImage,nameMedia,openProject);

    QImage image2(QDir::currentPath()+"/images/linevertical.png");
    QPixmap pixTmp2(QPixmap::fromImage(image2));
    startItem = new Image(pixTmp2,arrowcerca,Image::InitTermination);
    addItem(startItem);    


    if(!infinite)
        path = "/images/linevertical.png";
    else
        path = "/images/puntosSuspensivos2.png";

    QImage image(QDir::currentPath()+path);
    QPixmap pixTmp(QPixmap::fromImage(image));
    if (path == "/images/linevertical.png")
        endItem = new Image(pixTmp,Image::EndTermination);
    else
        endItem = new Image(pixTmp,Image::SuspensionPoints);

    if(arrowcerca->getStartItem()->getInfiniteInteract()){
        startItem->setInfiniteInteract(true);
        endItem->setInfiniteInteract(true);
    }else{
        startItem->setInfiniteInteract(false);
        endItem->setInfiniteInteract(false);
    }

    addItem(endItem);

    connect(startItem, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(endItem, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(startItem, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(endItem, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(startItem, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));
    connect(endItem, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));

    posX = posX - startItem->boundingRect().width()/2;

    startItem->setParentItem(arrowcerca->getStartItem());
    startItem->setPos(startItem->mapFromScene(posX,posY).x(),startItem->mapFromScene(posX,posY).y());

    endItem->setParentItem(startItem);
    endItem->setPos(endItem->mapFromScene(posX+mediaDuration/*-longArrowHead*/,posYItem2).x(),endItem->mapFromScene(posX+mediaDuration,posYItem2).y());

    sceneWidthPosImage(posX+mediaDuration);

    arrow = new Arrow(startItem, endItem,Arrow::TempLine);

    if(haveDuration){
        arrow->setLongTempLineOriginal(QString::number(originalDuration));
    }else
        arrow->setLongTempLineOriginal("-1");

    arrow->setZValue(-1);
    addItem(arrow);
    arrow->updatePosition();

    unionArrow = new Arrow(arrowcerca,startItem,Arrow::UnionLine);
    addItem(unionArrow);
    unionArrow->updatePosition();    

    unionArrow->setParentItem(arrowcerca);
    arrow->setParentItem(unionArrow);
    unionArrow->setPosXUnionLine(unionArrow->line().x2() - arrowcerca->line().x2());

    checkUnionDiamondTempLine(arrowcerca,arrow,unionArrow);

    startItem->setTimeLine(arrow);
    endItem->setTimeLine(arrow);

}


/*!
 *\brief returns true if the parameter is correct
 *\param QPointF pos
 *\param Arrow *arrowCerca
 *\return bool
 */
bool DiagramScene::correctParameters(QPointF pos,Arrow *arrowCerca)
{
    if(posNearArrow !=-1){
        if(arrowCerca->line().x2() < pos.x() && pos.x() < arrowCerca->line().x1() && arrowCerca->line().y1()+(LINESIZE/2) > pos.y() && pos.y()>arrowCerca->line().y1())
            return true;
        else
            return false;
    }else
        return false;
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{   
    if(botonInteractividadAux){
        QPointF pos = mouseEvent->scenePos();
        interactiveButton(true,pos);
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}


/*!
 *\brief converts all items in transparent
 *\param int lineExeption
 *\param bool transparent
 *\return void
 */
void DiagramScene::makeTransparent(int lineExeption, bool transparent)
{
    QList<QGraphicsItem *> TodosItems = items();
    if(lineExeption==-1){
        for(int i = 0; i < TodosItems.size();i++){
            if(TodosItems.at(i)->opacity()!=0){
                if(transparent)
                    TodosItems.at(i)->setOpacity(0.4);
                    else
                        TodosItems.at(i)->setOpacity(1);
            }
        }
    }else{
        int numLineAux = 0;
        Arrow *arrowItem;
        Image *currentImage;

        for(int i = 0; i < TodosItems.size();i++){
            if(TodosItems.at(i)->type() == 6){//is arrow
                numLineAux = TodosItems.at(i)->boundingRect().y() / LINESIZE;
                arrowItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
                if(arrowItem->getMyType() == Arrow::UnionLine)
                   numLineAux = arrowItem->getEndItem()->scenePos().y() /LINESIZE;
            }else if(TodosItems.at(i)->type() == 7){//is imagen
                currentImage =  qgraphicsitem_cast<Image *>(TodosItems.at(i));
                numLineAux = currentImage->scenePos().y() / LINESIZE;
            }

            if(TodosItems.at(i)->opacity()!=0){
                if( numLineAux == lineExeption)
                    TodosItems.at(i)->setOpacity(1);
                    else
                        TodosItems.at(i)->setOpacity(0.4);
                }
        }
    }
}


/*!
 *\brief enable or disable variable to delete arrows
 *\param bool activado
 *\return void
 */
void DiagramScene::deleteLine(bool activado)
{
    botonDeleteLine=activado;
    currentLine = -1;

    if(activado){
        makeTransparent(-1,true);
    }else{
        makeTransparent(-1,false);       
    }
}


/*!
 *\brief lowers items the amount \a cantLineDown
 *\param int cantLineDown
 *\param qreal linePosX
 *\param Arrow *arrow
 *\return void
 */
void DiagramScene::downFromLineNumber(int cantLineDown,qreal linePosX,Arrow *arrow)
{
    QList<QGraphicsItem *> TodosItems = items();
    int lineNumberCorriente = 0;
    qreal posYArrow = othersTemLineRight(linePosX);
    int newLineNumber = posYArrow / LINESIZE;
    newLineNumber++;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->isVisible()){
            if(TodosItems.at(i)->type() == 7 ){//is imagen
                if(TodosItems.at(i)->parentItem()!=0){
                    if(TodosItems.at(i)->parentItem()->type()!= 3){
                        lineNumberCorriente =TodosItems.at(i)->y() / LINESIZE;
                        if(lineNumberCorriente >= newLineNumber)
                            TodosItems.at(i)->setY(TodosItems.at(i)->y()+(cantLineDown*LINESIZE));
                    }
                 }else{
                     lineNumberCorriente =TodosItems.at(i)->y() / LINESIZE;
                     if(lineNumberCorriente >= newLineNumber)
                         TodosItems.at(i)->setY(TodosItems.at(i)->y()+(cantLineDown*LINESIZE));
                 }
             }
        }
    }

    arrow->setRecursivePos(arrow,(newLineNumber*LINESIZE) +25,arrow->line().y1());
}


/*!
 *\brief creates the start item of the interactivity arrow
 *\param bool activated
 *\param QPointF pos
 *\return void
 */
void DiagramScene::interactiveButton(bool activated,QPointF pos)
{
    botonInteractividadAux =activated;
    if (activated){
        canMove=false;
        arrowcerca = searchArrowWithoutInteractNearMause(pos);

        if(correctParameters(pos,arrowcerca)){
            arrowLineAux = new Arrow(QLineF(pos.x(),arrowcerca->line().y1()+distTempLineInteractLine,
                                             pos.x(),arrowcerca->line().y1()+distTempLineInteractLine));
            arrowLineAux->setPen(QPen(Qt::red, 3,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));

            addItem(arrowLineAux);
            arrowLineAux->updatePosition();
            canMove=true;

            QImage image2(QDir::currentPath()+"/images/linevertical.png");
            QPixmap pixTmp2(QPixmap::fromImage(image2));
            startItem = new Image(pixTmp2,Image::InitInteractivityTermination);
            addItem(startItem);
            startItem->setParentItem(arrowcerca->getStartItem());
            startItem->setPos(startItem->mapFromScene(arrowLineAux->line().p1().x()-(startItem->boundingRect().width()),arrowLineAux->line().p1().y()-(startItem->boundingRect().height()/2)).x(),startItem->mapFromScene(arrowLineAux->line().p1().x()-(startItem->boundingRect().width()),arrowLineAux->line().p1().y()-(startItem->boundingRect().height()/2)).y());
        }
    }

}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(botonDeleteLine){
        int lineMouseEvent = mouseEvent->scenePos().y() / LINESIZE;
        if(currentLine != lineMouseEvent){
            currentLine = lineMouseEvent;
            makeTransparent(currentLine,false);
        }
    }

    if(canMove){
        if(arrowcerca->getEndItem()->scenePos().x() >= mouseEvent->scenePos().x() && arrowcerca->getStartItem()->scenePos().x() <= mouseEvent->scenePos().x()
            && (mouseEvent->scenePos().x() >= arrowLineAux->line().p1().x())){
            QLineF newLine(arrowLineAux->line().p1().x(),arrowLineAux->line().p1().y(), mouseEvent->scenePos().x(),arrowLineAux->line().p1().y());
            arrowLineAux->setLineAux(newLine);
        }
    }

    emit mouseMove(mouseEvent->scenePos());
    QGraphicsScene::mouseMoveEvent(mouseEvent);

}


/*!
 *\brief updates position of all arrows
 *\return void
 */
void DiagramScene::updateArrows()
{
    QList<QGraphicsItem *> TodosItems = items();
    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->isVisible())
            if(TodosItems.at(i)->type() == 6){//is arrow
                Arrow *arrowItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
                arrowItem->updatePosition();
            }
    }
}


/*!
 *\brief up all items found under \a lineNumber, the amount rises \a cantLineUp
 *\param int lineNumber
 *\param int cantLineUp
 *\return void
 */
void DiagramScene::upToLineNumber(int lineNumber,int cantLineUp)
{
    QList<QGraphicsItem *> TodosItems = items();
    int lineAux;
    int parentLineNumber;

    Arrow *currentArrow;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 6){//is arrow
            currentArrow =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if(currentArrow->parentItem() != 0){
                if(currentArrow->getMyType() == Arrow::TempLine){
                    lineAux = currentArrow->line().y1() / LINESIZE;
                    parentLineNumber = currentArrow->parentItem()->parentItem()->boundingRect().y() / LINESIZE ;
                    if((lineNumber < lineAux) && !( lineNumber < parentLineNumber) ){
                        currentArrow->getStartItem()->setY(currentArrow->getStartItem()->scenePos().y() - currentArrow->getStartItem()->parentItem()->scenePos().y() - (cantLineUp*LINESIZE));

                        if(currentArrow->getStartItem()->itemHaveDiamond()){
                           currentArrow->getStartItem()->downUpChildrens(currentArrow,-(cantLineUp*LINESIZE));
                           currentArrow->getStartItem()->getDiamond()->setY(currentArrow->getStartItem()->getDiamond()->scenePos().y() - currentArrow->getStartItem()->getDiamond()->parentItem()->scenePos().y() - (cantLineUp*LINESIZE));
                           currentArrow->getEndItem()->getDiamond()->setY(currentArrow->getEndItem()->getDiamond()->scenePos().y() - currentArrow->getEndItem()->getDiamond()->parentItem()->scenePos().y() - (cantLineUp*LINESIZE));
                        }

                    }
                }
            }
        }
    }
}


/*!
 *\brief deletes line number \a lineNumber  and all their childrens
 *\param int lineNumber
 *\return void
 */
void DiagramScene::deleteLineNumber(int lineNumber)
{
    QList<QGraphicsItem *> TodosItems = items();
    int lineAux =-1;
    int cantLineUp = 0;
    Arrow *arrowItem;

    if(lineNumber == 0){
        for(int i = 0; i < TodosItems.size();i++){
            if(TodosItems.at(i)->type() == 6){//is arrow
                arrowItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
                lineAux = arrowItem->line().y1() / LINESIZE;
                if(lineAux == 0){
                    if(arrowItem->getMyType() == Arrow::TempLine){
                        cantLineUp = arrowItem->recursiveCountItems(arrowItem, 0);
                        removeItem(arrowItem->getStartItem());
                        removeItem(arrowItem->getEndItem());
                        removeItem(arrowItem);
                        break;
                    }
                }
            }
        }
    }else{
        for(int i = 0; i < TodosItems.size();i++){
            if(TodosItems.at(i)->type() == 6){//is arrow
                arrowItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
                lineAux = arrowItem->line().y1() / LINESIZE;
                if(lineNumber == lineAux){
                    if(arrowItem->getMyType() == Arrow::TempLine){
                        if(arrowItem->getStartItem()->itemHaveDiamond()){
                            arrowItem->getEndItem()->removeDiamonds(arrowItem);
                            removeItem(arrowItem->getStartItem()->getDiamond());
                            removeItem(arrowItem->getEndItem()->getDiamond());
                        }
                        cantLineUp = arrowItem->recursiveCountItems(arrowItem, 0);
                        removeItem(arrowItem->getStartItem());
                        removeItem(arrowItem->getEndItem());
                        removeItem(arrowItem->parentItem());
                    }
                }
            }
        }
    }

    upToLineNumber(lineNumber,cantLineUp);
    updateArrows();
    emit removeLineBetween(lineNumber,lineNumber+cantLineUp);

    cantLineTotal= cantLineTotal-cantLineUp;

    if(cantLineTotal <= 0)
        cantLineTotal = 1;

    if(cantLineTotal>4)
        setSceneRect(QRectF(0, 0, width(), (cantLineTotal+1)*LINESIZE));
    else
        setSceneRect(QRectF(0, 0, width(), 5*LINESIZE));
}


/*!
 *\brief emits the \a removeLineBetween signal and updates the size of the scene
 *\param int lineNumber
 *\param int cantLineUp
 *\return void
 */
void DiagramScene::removeAndUpLines(int lineNumber, int cantLineUp)
{
    upToLineNumber(lineNumber,cantLineUp);
    updateArrows();
    emit removeLineBetween(lineNumber,lineNumber+cantLineUp);

    cantLineTotal= cantLineTotal-cantLineUp;
    if(cantLineTotal>4)
        setSceneRect(QRectF(0, 0, width(), (cantLineTotal+1)*LINESIZE));
    else
        setSceneRect(QRectF(0, 0, width(), 5*LINESIZE));
}


/*!
 *\brief inserts a new interactivity arrow
 *\param qreal posXBegin
 *\param qreal posYBegin
 *\param qreal posXEnd
 *\param qreal posYEnd
 *\param QString nameButton
 *\param bool infinite
 *\return void
 */
void DiagramScene::insertInteractivity(qreal posXBegin,qreal posYBegin, qreal posXEnd, qreal posYEnd,QString nameButton,bool infinite)
{
    QString path = "";
    QString nameButtonAux = nameButton;
    QImage image2(QDir::currentPath()+"/images/linevertical.png");
    QPixmap pixTmp2(QPixmap::fromImage(image2));
    startItem = new Image(pixTmp2,Image::InitInteractivityTermination);

    addItem(startItem);
    startItem->setParentItem(arrowcerca->getStartItem());
    startItem->setPos(startItem->mapFromScene(posXBegin,posYBegin).x(),startItem->mapFromScene(posXBegin,posYBegin).y());

    if(!infinite)
        path = "/images/linevertical.png";
    else
        path = "/images/puntosSuspensivos2.png";

    QImage image(QDir::currentPath()+path);
    QPixmap pixTmp(QPixmap::fromImage(image));
    if (path == "/images/linevertical.png")
        endItem = new Image(pixTmp,Image::EndInteractivityTermination);
    else
        endItem = new Image(pixTmp,Image::SuspensionPoints);

    addItem(endItem);
    endItem->setParentItem(arrowcerca->getStartItem());
    endItem->setPos(endItem->mapFromScene(posXEnd,posYEnd).x(),endItem->mapFromScene(posXEnd,posYEnd).y());

    arrow = new Arrow(startItem, endItem,Arrow::InteractLine);
    addItem(arrow);
    arrow->updatePosition();

    canMove=false;
    botonInteractividadAux=false;

    if(nameButton == "*")
        nameButton = "asterisco";
    else if(nameButton == "#")
        nameButton = "numeral";

    QImage imageBoton("icons/interactividad/"+nameButton+".png");
    imageBoton = imageBoton.scaled(20,20 , Qt::IgnoreAspectRatio, Qt::FastTransformation);
    QPixmap pixTmpBoton(QPixmap::fromImage(imageBoton));
    boton = new Image(pixTmpBoton,Image::BotonInteract);

    qreal longitud = (arrow->line().x2()-arrow->line().x1());
    qreal medioDeLinea= arrow->line().x1() + longitud/2;

    addItem(boton);
    boton->setParentItem(arrowcerca->getStartItem());
    boton->setPos(boton->mapFromScene(medioDeLinea - (boton->boundingRect().width()/2) +arrow->pen().widthF()/2,arrow->line().y1()+LINESIZE/2).x(),boton->mapFromScene(medioDeLinea - (boton->boundingRect().width()/2) +arrow->pen().widthF()/2,arrow->line().y1()+LINESIZE/3).y());

    boton->setKeyButton(nameButtonAux);

    connect(startItem, SIGNAL(removeInteractUpLines(int,int)),this, SLOT(removeAndUpLines(int, int)));
    connect(endItem, SIGNAL(removeInteractUpLines(int,int)),this, SLOT(removeAndUpLines(int, int)));
    connect(boton, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(boton, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(boton, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));
    connect(startItem, SIGNAL(setButton(Image*)),this, SLOT(setButtonSlot(Image*)));
    connect(endItem, SIGNAL(setButton(Image*)),this, SLOT(setButtonSlot(Image*)));

    arrow->setButton(boton);

    endItem->setArrow(arrow);
    startItem->setArrow(arrow);
    unionInteractiveArrow = new Arrow(arrow,boton,Arrow::UnionInteractiveLine);

    addItem(unionInteractiveArrow);
    unionInteractiveArrow->updatePosition();

    arrow->setParentItem(arrowcerca);
    unionInteractiveArrow->setParentItem(arrow);
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(canMove){
        QImage image(QDir::currentPath()+"/images/linevertical.png");
        QPixmap pixTmp(QPixmap::fromImage(image));
        endItem = new Image(pixTmp,Image::EndInteractivityTermination);
        addItem(endItem);
        endItem->setParentItem(arrowcerca->getStartItem());
        endItem->setPos(endItem->mapFromScene(arrowLineAux->line().p2().x(),arrowLineAux->line().p2().y()-(endItem->boundingRect().height()/2)).x(),endItem->mapFromScene(arrowLineAux->line().p2().x(),arrowLineAux->line().p2().y()-(endItem->boundingRect().height()/2)).y());

        removeItem(arrowLineAux);

        arrow = new Arrow(startItem, endItem,Arrow::InteractLine);
        addItem(arrow);
        arrow->updatePosition();

        canMove=false;
        botonInteractividadAux=false;

       //enlazo la linea de interaccion con el boton
        QImage imageBoton(QDir::currentPath()+"/images/14_rectangle.png");
        imageBoton = imageBoton.scaled(20,20 , Qt::IgnoreAspectRatio, Qt::FastTransformation);
        QPixmap pixTmpBoton(QPixmap::fromImage(imageBoton));
        boton = new Image(pixTmpBoton,Image::BotonInteract);

        qreal longitud = (arrow->line().x2()-arrow->line().x1());
        qreal medioDeLinea= arrow->line().x1() + longitud/2;

        addItem(boton);
        boton->setParentItem(arrowcerca->getStartItem());
        boton->setPos(boton->mapFromScene(medioDeLinea - (boton->boundingRect().width()/2) +arrow->pen().widthF()/2,arrow->line().y1()+LINESIZE/2).x(),boton->mapFromScene(medioDeLinea - (boton->boundingRect().width()/2) +arrow->pen().widthF()/2,arrow->line().y1()+LINESIZE/3).y());

        connect(startItem, SIGNAL(removeInteractUpLines(int,int)),this, SLOT(removeAndUpLines(int, int)));
        connect(endItem, SIGNAL(removeInteractUpLines(int,int)),this, SLOT(removeAndUpLines(int, int)));
        connect(boton, SIGNAL(showWindows(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
        connect(boton, SIGNAL(showEventsButton(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
        connect(boton, SIGNAL(closeEventsButton()),this, SLOT(closeEventsButtonSlot2()));
        connect(startItem, SIGNAL(setButton(Image*)),this, SLOT(setButtonSlot(Image*)));
        connect(endItem, SIGNAL(setButton(Image*)),this, SLOT(setButtonSlot(Image*)));

        arrow->setButton(boton);
        endItem->setArrow(arrow);
        startItem->setArrow(arrow);

        unionInteractiveArrow = new Arrow(arrow,boton,Arrow::UnionInteractiveLine);
        addItem(unionInteractiveArrow);
        unionInteractiveArrow->updatePosition();

        arrow->setParentItem(arrowcerca);
        unionInteractiveArrow->setParentItem(arrow);

       /******************SELECT NEW SIMBOL FOR BOTON********************************/
       emit selectedBoton(boton , startItem, endItem);

   }else if(botonDeleteLine){
       deleteLineNumber(currentLine);
       deleteLine(false);
       currentLine = -1;
   }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


/*!
 *\brief returns the nearest arrow of \a posXY
 *\param QPointF posXY
 *\return Arrow*
 */
Arrow* DiagramScene::searchArrowNearMause(QPointF posXY)
{
    posNearArrow=-1;
    QList<QGraphicsItem *> TodosItems = items();
    Arrow *arrowAux = NULL;
    Arrow *arrowtItem;
    qreal menorDistancia = 9900000;
    qreal distancia;

    for(int i = 1; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type()==6){// is arrow
            arrowtItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if((arrowtItem->getMyType()==Arrow::TempLine)&& arrowtItem->isVisible()){
                if(posXY.x() <= arrowtItem->getEndItem()->arrives()->x() && posXY.x() >= arrowtItem->getStartItem()->scenePos().x()){
                    distancia = posXY.y()-arrowtItem->line().y1();
                    if(distancia>0){
                        if(distancia < menorDistancia){
                            posNearArrow=i-1;
                            menorDistancia=distancia;
                            arrowAux=arrowtItem;
                        }
                    }
                }
            }else if(arrowtItem->getMyType()==Arrow::UnionInteractiveLine){
                if(posXY.x() < arrowtItem->getEndItem()->scenePos().x() + arrowtItem->getEndItem()->boundingRect().width() && posXY.x() > arrowtItem->getEndItem()->scenePos().x()){
                    distancia = posXY.y()-arrowtItem->getEndItem()->arrives()->y();
                    if(distancia>0){
                        if(distancia < menorDistancia){
                            posNearArrow=i-1;
                            menorDistancia=distancia;
                            arrowAux =  qgraphicsitem_cast<Arrow *>(arrowtItem->parentItem());
                        }
                    }
                }
            }
        }
    }
    return arrowAux;
}


/*!
 *\brief returns the nearest arrow of \a posXY without interactivity
 *\param QPointF posXY
 *\return Arrow*
 */
Arrow* DiagramScene::searchArrowWithoutInteractNearMause(QPointF posXY)
{
    posNearArrow=-1;
    QList<QGraphicsItem *> TodosItems = items();
    Arrow *arrowAux;
    qreal distancia;
    qreal menorDistancia = 9900000;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type()==6){
            Arrow *arrowtItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if(arrowtItem->getMyType()==Arrow::TempLine){
                if(posXY.x() < arrowtItem->getEndItem()->scenePos().x() && posXY.x() > arrowtItem->getStartItem()->scenePos().x()){
                    distancia = posXY.y()-arrowtItem->line().y1();
                    if(distancia>0){
                        if(distancia < menorDistancia){
                            posNearArrow=i;
                            menorDistancia=distancia;
                            arrowAux=arrowtItem;
                        }
                    }
                }
            }
        }
    }
    return arrowAux;
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneDragDropEvent * mouseEvent
 *\return void
 */
void DiagramScene::dropEvent ( QGraphicsSceneDragDropEvent * mouseEvent )
{
    removeItem(arrowLineAux);
    removeItem(textItem);

    if(mouseEvent->source() != 0 ){
        if(okItem){
            if (posNearArrow != -1){
                if(mouseEvent->scenePos().x() >= arrowcerca->getStartItem()->scenePos().x() + 2.5)
                    emit diagramSceneDrop(mouseEvent->scenePos().x());
                else
                    emit diagramSceneDrop(arrowcerca->getStartItem()->scenePos().x() + 2.5);
            }else if(items().size()==0){
                emit diagramSceneDrop(-10);
            }
        }else{
            emit outElement();
        }
    }else{
        emit outElement();
    }
    if(arrowcerca!=NULL){
        if(arrowcerca->getMyType() == Arrow::TempLine){
            arrowcerca->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            arrowcerca->setMyColor(Qt::black);
        }else{
            arrowcerca->setPen(QPen(Qt::red, 3,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
            arrowcerca->setMyColor(Qt::red);
        }
    }
    QGraphicsScene::dropEvent(mouseEvent);
}


/*!
 *\brief sets \okItem in true
 *\return void
 */
void DiagramScene::setTrueOkItemDrop()
{
    okItem = true;
}


/*!
 *\brief sets \okItem in false
 *\return void
 */
void DiagramScene::setFlaseOkItemDrop()
{
    okItem = false;
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneDragDropEvent * mouseEvent
 *\return void
 */
void DiagramScene::dragEnterEvent ( QGraphicsSceneDragDropEvent * mouseEvent )
{
    textItem  = addText(NULL);
    arrowLineAux = new Arrow(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
    arrowLineAux->setPen(QPen(Qt::red, 2,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    addItem(arrowLineAux);
    beginArrow = NULL;
    alreadySetColor=false;
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneDragDropEvent * mouseEvent
 *\return void
 */
void DiagramScene::dragMoveEvent ( QGraphicsSceneDragDropEvent * mouseEvent )
{
    QGraphicsItem *swichAux = itemAt(mouseEvent->scenePos());
    if(swichAux==NULL){
        arrowLineAux->setVisible(true);
        textItem->setVisible(true);
        arrowcerca = searchArrowNearMause(mouseEvent->scenePos());
        if(arrowcerca!=NULL){
            if(arrowcerca->getEndItem()->scenePos().x() >= mouseEvent->scenePos().x() && arrowcerca->getStartItem()->scenePos().x() <= mouseEvent->scenePos().x() ){
                if(!arrowLineAux->isVisible()){
                    arrowLineAux->setVisible(true);
                    textItem->setVisible(true);
                }if(arrowcerca!=beginArrow){
                    if(beginArrow!=NULL){
                        if(beginArrow->getMyType() == Arrow::TempLine){
                            beginArrow->setMyColor(Qt::black);
                            beginArrow->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                        }else{
                            beginArrow->setMyColor(Qt::red);
                            beginArrow->setPen(QPen(Qt::red, 3,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
                        }
                    }
                    alreadySetColor =false;
                }
                if(!alreadySetColor){
                    if(arrowcerca->getMyType() == Arrow::TempLine){
                        arrowcerca->setMyColor(Qt::blue);
                        arrowcerca->setPen(QPen(Qt::blue, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    }else{
                        arrowcerca->setMyColor(Qt::blue);
                        arrowcerca->setPen(QPen(Qt::blue, 10,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
                    }
                    alreadySetColor=true;
                }

                textItem->setPos(mouseEvent->scenePos().x(), arrowcerca->getStartItem()->scenePos().y() - (arrowcerca->getStartItem()->boundingRect().height() /2));
                QTime timeaux(0,0,0);

                currentTime = timeaux.addMSecs((mouseEvent->scenePos().x()  - arrowcerca->getStartItem()->scenePos().x()) *100);
                textItem->setPlainText(currentTime.toString("hh:mm:ss:zzz"));

                QLineF newLine(mouseEvent->scenePos().x(),arrowcerca->line().p1().y()+distTempLineInteractLine, mouseEvent->scenePos().x(),arrowcerca->line().p1().y()-distTempLineInteractLine);
                arrowLineAux->setLineAux(newLine);
                arrowLineAux->setPen(QPen(Qt::red, 2,Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                beginArrow = arrowcerca;

                emit mouseMove(mouseEvent->scenePos());
            }
        }else{
             arrowLineAux->setVisible(false);
             textItem->setVisible(false);
             if(beginArrow!=NULL){
                    if(beginArrow->getMyType() == Arrow::TempLine){
                        beginArrow->setMyColor(Qt::black);
                        beginArrow->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    }else{
                        beginArrow->setMyColor(Qt::red);
                        beginArrow->setPen(QPen(Qt::red, 3,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
                    }
                }
                alreadySetColor =false;
        }
    }else{
        arrowLineAux->setVisible(false);
        textItem->setVisible(false);
    }
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneDragDropEvent * mouseEvent
 *\return void
 */
void DiagramScene::dragLeaveEvent ( QGraphicsSceneDragDropEvent * mouseEvent )
{
    if(arrowcerca!=NULL){
        if(arrowcerca->getMyType() == Arrow::TempLine){
            arrowcerca->setMyColor(Qt::black);
            arrowcerca->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        }else{
            arrowcerca->setMyColor(Qt::red);
            arrowcerca->setPen(QPen(Qt::red, 3,Qt::DashDotDotLine, Qt::RoundCap, Qt::RoundJoin));
        }
    }
    removeItem(arrowLineAux);
    removeItem(textItem);
    QGraphicsScene::dragLeaveEvent(mouseEvent);
}


/*!
 *\brief enable or disable variable to add interactivity
 *\param bool valor
 *\return void
 */
void DiagramScene::setButtonInteractividad(bool valor)
{
    botonInteractividadAux=valor;
}


/*!
 *\brief returns true if the buttonInteractividad is pressed
 *\return bool
 */
bool DiagramScene::getButtonInteractividad()
{
    return botonInteractividadAux;
}


/*!
 *\brief enlarges the scene until position \a imagePosX
 *\param qreal imagePosX
 *\return void
 */
void DiagramScene::sceneWidthPosImage(qreal imagePosX)
{
    if((width()) < imagePosX){
        setSceneRect(QRectF(0, 0, imagePosX +50 , height()));
        startItem->UpdatePosSuspensionPoints();
    }
}


/*!
 *\brief returns true if the buttonDeleteLine is pressed
 *\return bool
 */
bool DiagramScene::getButtonDeleteLine(){
    return botonDeleteLine;
}


/*!
 *\brief emits the \a showWindows2 signal
 *\param Image* boton
 *\param QStringList playList
 *\param QStringList stopList
 *\param QStringList pauseList
 *\param QStringList resumeList
 *\param QStringList abortList
 *\param QStringList setList
 *\param QTableWidget* setTableList
 *\return void
 */
void DiagramScene::showWindowsSlot2(Image* boton,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList,QTableWidget* setTableList)
{
    emit showWindows2(boton,playList,stopList,pauseList,resumeList,abortList,setList,setTableList);
}


/*!
 *\brief emits the \a showEventsButton2 signal
 *\param QPointF posWindow
 *\param QStringList playList
 *\param QStringList stopList
 *\param QStringList pauseList
 *\param QStringList resumeList
 *\param QStringList abortList
 *\param QStringList setList
 *\return void
 */
void DiagramScene::showEventsButtonSlot2(QPointF posWindow,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList)
{
    emit showEventsButton2(posWindow,playList,stopList,pauseList,resumeList,abortList,setList);
}


/*!
 *\brief emits the \a closeEventsButton2 signal
 *\return void
 */
void DiagramScene::closeEventsButtonSlot2()
{
    emit closeEventsButton2();
}


/*!
 *\brief shows or hides all diamonds
 *\param bool view
 *\return void
 */
void DiagramScene::ViewDiamonds(bool view)
{
    viewItems = view;
    QList<QGraphicsItem *> AllItems = items();
    Arrow *arrowtItem;
    if(AllItems.size()>=1){       
        for(int i = 0; i < AllItems.size();i++){            
            if(AllItems.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllItems.at(i));
                if(arrowtItem->getMyType() == Arrow::UnionDiamondTempLine){
                    if(arrowtItem->getStartItem()->getMyType() == Image::Diamond){
                        if(view){                           
                            arrowtItem->setOpacity(1);
                            arrowtItem->getStartItem()->setOpacity(1);
                        }else{                            
                            arrowtItem->setOpacity(0);
                            arrowtItem->getStartItem()->setOpacity(0);
                        }
                    }else{
                        if(view){
                            arrowtItem->setOpacity(1);
                            arrowtItem->getEndItem()->setOpacity(1);
                        }else{
                            arrowtItem->setOpacity(0);
                            arrowtItem->getEndItem()->setOpacity(0);
                        }
                    }
                }
            }
        }
    }
}


/*!
 *\brief sets the nearest arrow
 *\param Arrow *nearArrow
 *\return void
 */
void DiagramScene::setNearArrow(Arrow *nearArrow){
    arrowcerca = nearArrow;
}


/*!
 *\brief emits the \a setButton signal
 *\param Image* boton
 *\return void
 */
void DiagramScene::setButtonSlot(Image* boton)
{
    emit setButton(boton);
}


/*!
 *\brief sets the number of lines that the scene have
 *\param int cant
 *\return void
 */
void DiagramScene::setCantLineTotal(int cant)
{
    cantLineTotal = cant;
}
