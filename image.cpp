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
*\file image.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create,remove and modify images.
*/


#include "arrow.h"
#include "image.h"
#include <iostream>

using namespace std;

Arrow *arrowAsociadoAux;
Arrow *arrowAux;
Arrow * currentArrowAux;
bool itemIsSuspPoints=false;


/*!
 *\brief creates the Image
 *\param QPixmap pixTmp
 */
Image::Image(QPixmap pixTmp)
{
    setPixmap(pixTmp);
    myType=Other;
}


/*!
 *\brief creates the Image and initialize values
 *\param QPixmap pixTmp
 *\param TypeImage typeImage
 */
Image::Image(QPixmap pixTmp,TypeImage typeImage)
{   
    setTableList = new QTableWidget();
    pressItem =false;
    pressMenu=false;
    haveRombo = false;
    setPixmap(pixTmp);

    if(typeImage==TypeMedia){
        setFlag(QGraphicsItem::ItemIsMovable, false);
        setFlag(QGraphicsItem::ItemIsSelectable, false);
    }else if(typeImage==Diamond){
        setFlag(QGraphicsItem::ItemIsMovable, false);
        setFlag(QGraphicsItem::ItemIsSelectable, false);
        setFlag(QGraphicsItem::ItemIgnoresParentOpacity, true);
    }else if(typeImage==BotonInteract){
        setAcceptHoverEvents(true);
    }else{
        makeMenu();
        setAcceptHoverEvents(true);
        setFlag(QGraphicsItem::ItemIsSelectable, false);
        setFlag(QGraphicsItem::ItemIsFocusable, false);
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setFlag(QGraphicsItem::ItemIgnoresParentOpacity, true);        
    }
    haveAssociatedArrow=false;
    myType=typeImage;
    widthUnionRomboTempLine=0;
    isChildrenOfInteract=false;
    pressItemUpdateScene =false;
    infiniteInteract = false;
}


/*!
 *\brief creates the Image with associated arrow and initialize values
 *\param QPixmap pixTmp
 *\param QGraphicsItem *arrow
 *\param TypeImage typeImage
 */
Image::Image(QPixmap pixTmp,QGraphicsItem *arrow,TypeImage typeImage)
{   
    setTableList = new QTableWidget();
    pressItem =false;
    pressMenu=false;
    haveRombo = false;
    setAcceptHoverEvents(true);
    arrowAsociado=qgraphicsitem_cast<Arrow *>(arrow);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, false);
    setFlag(QGraphicsItem::ItemIgnoresParentOpacity, true);
    setPixmap(pixTmp);
    haveAssociatedArrow=true;
    isChildrenOfInteract = false;
    myType=typeImage;
    widthUnionRomboTempLine=0;
    makeMenu();
    pressItemUpdateScene = false;
    infiniteInteract = false;
}


/*!
 *\brief creates a new menu for each Image
 *\return void
 */
void Image::makeMenu()
{
    menuInteractivity = new QMenu();
    QAction *adaptarAMedia = new QAction("Adaptar al Media",menuInteractivity);
    menuInteractivity->addAction(adaptarAMedia);

    QAction *removeInteract = new QAction("Eliminar Interactividad",menuInteractivity);
    menuInteractivity->addAction(removeInteract);

    QAction *editButton = new QAction("Editar boton",menuInteractivity);
    menuInteractivity->addAction(editButton);

    connect(adaptarAMedia,SIGNAL(triggered()),this,SLOT(adaptarAMedia()));
    connect(removeInteract,SIGNAL(triggered()),this,SLOT(removeInteract()));
    connect(editButton,SIGNAL(triggered()),this,SLOT(editButtonInteract()));

    menuTimeLineNoInfinit = new QMenu();
    QAction *sinTiempo = new QAction("Sin fin de tiempo",menuTimeLineNoInfinit);
    menuTimeLineNoInfinit->addAction(sinTiempo);

    QAction *addProperties = new QAction("Acciones...",menuTimeLineNoInfinit);
    menuTimeLineNoInfinit->addAction(addProperties);

    connect(sinTiempo,SIGNAL(triggered()),this,SLOT(suspensionPoints()));

    menuTimeLineInfinit = new QMenu();
    QAction *conTiempo = new QAction("Poner fin de tiempo",menuTimeLineInfinit);
    menuTimeLineInfinit->addAction(conTiempo);
    menuTimeLineInfinit->addAction(addProperties);

    connect(conTiempo,SIGNAL(triggered()),this,SLOT(suspensionPoints()));

    menuTimeLineInit = new QMenu();
    menuTimeLineInit->addAction(addProperties);

    connect(addProperties,SIGNAL(triggered()),this,SLOT(emitSignalProperties()));

    menuInteractivityInfinit = new QMenu();
    QAction *conTiempoInteractivity = new QAction("Poner fin de tiempo",menuInteractivityInfinit);
    menuInteractivityInfinit->addAction(conTiempoInteractivity);
    connect(conTiempoInteractivity,SIGNAL(triggered()),this,SLOT(suspensionPointsInteractivity()));
}


/*!
 *\brief returns X and Y position the left limit of the image
 *\return QPointF*
 */
QPointF* Image::arrives()
{
    qreal posRecEjey = scenePos().y();
    qreal altoRec = boundingRect().height();
    qreal ejex;
    if(myType == SuspensionPoints)
        ejex = scenePos().x();
    else
        ejex = scenePos().x() + boundingRect().width() / 2;
    qreal ejey=posRecEjey+(altoRec/2);
    QPointF *pos = new QPointF(ejex,ejey);
    return pos;
}


/*!
 *\brief returns X and Y position the right limit of the image
 *\return QPointF*
 */
QPointF* Image::send()
{
    qreal anchoRec = boundingRect().width() / 2;
    qreal posRecEjey = scenePos().y();
    qreal altoRec = boundingRect().height();
    qreal ejex= scenePos().x()+anchoRec;
    qreal ejey=posRecEjey+(altoRec/2);
    QPointF *pos = new QPointF(ejex,ejey);
    return pos;
}


/*!
 *\brief sets X position of suspension points with scene width
 *\return void
 */
void Image::UpdatePosSuspensionPoints()
{
    Arrow *arrowtItem;
    QList<QGraphicsItem *> TodosItems = scene()->items();    
    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 6){//is Arrow
            arrowtItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if(arrowtItem->getMyType() == Arrow::TempLine)
                if(arrowtItem->getEndItem()->getMyType() == SuspensionPoints){
                    arrowtItem->getEndItem()->setX(scene()->width()- arrowtItem->getEndItem()->boundingRect().width() - arrowtItem->getEndItem()->parentItem()->scenePos().x());
                }
            if(arrowtItem->getMyType() == Arrow::InteractLine)
                if(arrowtItem->getEndItem()->getMyType() == SuspensionPoints){
                    arrowtItem->getEndItem()->setX(scene()->width()-arrowtItem->getEndItem()->boundingRect().width() - arrowtItem->getEndItem()->parentItem()->scenePos().x());      
                    qreal longitud = (arrowtItem->line().x2()-arrowtItem->line().x1());
                    qreal medioDeLinea= arrowtItem->line().x1() + longitud/2 -(arrowtItem->getButton()->boundingRect().width()/2) + arrowtItem->pen().widthF()/2;
                    arrowtItem->getButton()->setX(medioDeLinea - arrowtItem->getButton()->parentItem()->scenePos().x());
                    arrowtItem->getEndItem()->moveAfterInteractivity(false);
                }
        }
    }
}


/*!
 *\brief returns the line number of the first arrow that follows to the interactivity arrow(and of course this first arrow must are asociated with interactivity arrow)
 *\return int
 */
int Image::getFirstLineNumber()
{
    int currentLineNumber;
    int minLineNumber  = -1;
    bool firstTime =true;
    QList<QGraphicsItem *> AllChildremsAux;
    QList<QGraphicsItem *> AllChildrems = arrowAsociado->childItems();
    Arrow *arrowtItem;
    if(AllChildrems.size()>=1){
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::UnionLineTempInteract){
                    AllChildremsAux = arrowtItem->childItems();
                    for(int j = 0; j < AllChildremsAux.size();j++){
                        arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildremsAux.at(j));
                        if(arrowtItem->getMyType() == Arrow::TempLine){
                            break;
                        }
                    }

                    if(arrowtItem->getMyType() == Arrow::TempLine){
                        if(firstTime){                           
                            currentLineNumber = arrowtItem->line().y1() / LINESIZE;
                            minLineNumber = currentLineNumber;
                            firstTime =false;
                        }else{
                            currentLineNumber = arrowtItem->line().y1() / LINESIZE;
                            if(currentLineNumber < minLineNumber)
                                minLineNumber = currentLineNumber;
                        }
                    }
                }
            }
        }
    }
    return minLineNumber;
}


/*!
 *\brief remove the current interactivity arrow and all her childrens
 *\return void
 */
void Image::removeInteract()
{
    int cantLineUp = 0;
    int lineNumber;
    Arrow *arrowItem;
    Image *startIt;
    Image *endIt;

    if(haveAssociatedArrow){
        arrowItem =  qgraphicsitem_cast<Arrow *>(arrowAsociado);
        cantLineUp = arrowItem->recursiveCountItems(arrowItem, 0);
        lineNumber = getFirstLineNumber();        
        if(lineNumber != -1)
            emit removeInteractUpLines(lineNumber,cantLineUp);
        startIt = arrowItem->getStartItem();
        endIt = arrowItem->getEndItem();
        if(myType == InitInteractivityTermination){
            scene()->removeItem(arrowItem->getButton());
            scene()->removeItem(arrowItem);
            scene()->removeItem(endIt);
            scene()->removeItem(startIt);
        }else{
            scene()->removeItem(arrowItem->getButton());
            scene()->removeItem(arrowItem);
            scene()->removeItem(startIt);
            scene()->removeItem(endIt);
        }
    }
}


/*!
 *\brief updates the position of all diamonds children the \a arrowtItemP
 *\param QGraphicsLineItem *arrowtItemP
 *\param bool infinitePos
 *\param qreal posXDiamond
 *\return void
 */
void Image::correctDiamond(QGraphicsLineItem *arrowtItemP,bool infinitePos, qreal posXDiamond)
{
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;
    if(AllChildrems.size()>=1){
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){
                    if(infinitePos){
                        arrowtItem->getEndItem()->getDiamond()->setY(arrowtItem->getStartItem()->getDiamond()->scenePos().y() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().y());
                        arrowtItem->getEndItem()->getDiamond()->setX( 10);
                    }else{                        
                        arrowtItem->getEndItem()->getDiamond()->setY(arrowtItem->getStartItem()->getDiamond()->scenePos().y() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().y());
                        arrowtItem->getEndItem()->getDiamond()->setX( 10);
                    }
                }else if(arrowtItem->getMyType() == Arrow::InteractLine){
                    return;
                }
                correctDiamond(arrowtItem,infinitePos,posXDiamond);
            }
        }
    }else{
        return;
    }
}


/*!
 *\brief resize the interactivity arrow whit the size of the TempLine(i.e. assign the size of the timeline to interactivity arrow)
 *\return void
 */
void Image::adaptarAMedia()
{
    arrowAsociadoAux = qgraphicsitem_cast<Arrow *>(arrowAsociado);
    Arrow *parentArrow =qgraphicsitem_cast<Arrow *>(arrowAsociadoAux->parentItem());
    if(parentArrow->getEndItem()->getMyType() == SuspensionPoints){
        QImage image(QDir::currentPath()+"/images/puntosSuspensivos2.png");
        QPixmap pixTmp(QPixmap::fromImage(image));
        arrowAsociadoAux->getEndItem()->setPixmap(pixTmp);
        arrowAsociadoAux->getEndItem()->setPos(scene()->width()-boundingRect().width() - arrowAsociadoAux->getEndItem()->parentItem()->scenePos().x(),(arrowAsociadoAux->getStartItem()->arrives()->y()-(arrowAsociadoAux->getEndItem()->boundingRect().height()/2) - parentItem()->scenePos().y()));
        arrowAsociadoAux->getEndItem()->setMyType(SuspensionPoints);
        addRemoveInfiniteInteract(arrowAsociado, true);
        correctDiamond(arrowAsociadoAux,true,scene()->width()-boundingRect().width());
    }
    arrowAsociadoAux->getStartItem()->setX(parentArrow->getStartItem()->scenePos().x() - arrowAsociadoAux->getStartItem()->parentItem()->scenePos().x());
    arrowAsociadoAux->getEndItem()->setX(parentArrow->getEndItem()->scenePos().x() - arrowAsociadoAux->getStartItem()->parentItem()->scenePos().x());
    arrowAsociadoAux->updatePosition();
    qreal longitud = (arrowAsociadoAux->line().x2()-arrowAsociadoAux->line().x1());
    qreal medioDeLinea= arrowAsociadoAux->line().x1() + longitud/2 -(arrowAsociadoAux->getButton()->boundingRect().width()/2) + arrowAsociadoAux->pen().widthF()/2;
    arrowAsociadoAux->getButton()->setX(medioDeLinea - arrowAsociadoAux->getButton()->parentItem()->scenePos().x());
    moveAfterInteractivity(false);
    adaptMaxItem();
}


/*!
 *\brief emits the \a showWindows signal
 *\return void
 */
void Image::emitSignalProperties()
{
    emit showWindows(this,playList,stopList,pauseList,resumeList,abortList,setList,setTableList);
}


/*!
 *\brief if the image and his children(image of the interactivity arrow) are suspensionsPoints then they changes to vertical line(or EndTermination and EndInteractivityTermination)
 *\return bool
 */
bool Image::childrenInteractInfinite()
{
    bool value = false;
    QList<QGraphicsItem *> todosHijos = timeLine->childItems();
    Arrow *currentArrow;
    for(int i = 0; i < todosHijos.size();i++){
        currentArrow = qgraphicsitem_cast<Arrow *>(todosHijos.at(i));
        if(currentArrow->getMyType() == Arrow::InteractLine){
            if(currentArrow->getEndItem()->getMyType() == SuspensionPoints){
                currentArrow->getEndItem()->suspensionPointsInteractivity();
            }
        }
    }
    return value;
}


/*!
 *\brief changes the image(between suspensionPoint and EndTermination) and updates the position of Image
 *\return void
 */
void Image::suspensionPoints()
{
    if(infinite){
        QImage image(QDir::currentPath()+"/images/puntosSuspensivos2.png");
        QPixmap pixTmp(QPixmap::fromImage(image));
        setPixmap(pixTmp);
        int lineNumber = scenePos().y() / LINESIZE;
        if(parentItem() != 0){
            if(parentItem()->parentItem() == 0)
                setPos(scene()->width() - boundingRect().width() - parentItem()->scenePos().x() ,(lineNumber * LINESIZE) + (LINESIZE/2)-(boundingRect().height()/2)+ 3 - parentItem()->scenePos().y());
            else
                setPos(scene()->width() - boundingRect().width() - parentItem()->scenePos().x() ,(lineNumber * LINESIZE) + (LINESIZE/2)-(boundingRect().height()/2) - parentItem()->scenePos().y());
        }
        if(haveRombo){
            romboAssociated->getAssociatedArrow()->setVisible(false);
            romboAssociated->setVisible(false);
        }

        myType = SuspensionPoints;
        accommodateChildImages(true);
    }else{
        childrenInteractInfinite();
        QImage image(QDir::currentPath()+"/images/linevertical.png");
        QPixmap pixTmp(QPixmap::fromImage(image));
        setPixmap(pixTmp);
        int lineNumber = scenePos().y() / LINESIZE;
        arrowAux =  qgraphicsitem_cast<Arrow *>(timeLine);
        if(arrowAux->parentItem()==0)
                setPos(scene()->width()-77 - parentItem()->scenePos().x(),(lineNumber * LINESIZE) + (LINESIZE/2)-(boundingRect().height()/2)+3 -parentItem()->scenePos().y());
            else
                setPos(scene()->width()-77 - parentItem()->scenePos().x(),arrowAux->getStartItem()->scenePos().y()  -parentItem()->scenePos().y());

        myType = EndTermination;
        if(haveRombo){
            romboAssociated->getAssociatedArrow()->setVisible(true);
            romboAssociated->setVisible(true);
            longUnionRomboTempLine = arrowAux->getStartItem()->getLongUnionDiamondTempLine();
            romboAssociated->setX(scenePos().x() + longUnionRomboTempLine - romboAssociated->parentItem()->scenePos().x() - (romboAssociated->boundingRect().width()/2)  );            
            adaptMaxItem();
        }
        accommodateChildImages(false);
    }
}


/*!
 *\brief updates position the childrens(stop,play,pause,etc) of the image when the image change is from EndTermination to SuspensionPoints or from SuspensionPoints to EndTermination
 *\param bool infinite
 *\return void
 */
void Image::accommodateChildImages(bool infinite)
{
    QList<QGraphicsItem *> AllChildrems = childItems();
    if(infinite){
        if(AllChildrems.size()>=1){
            for(int i = 0; i < AllChildrems.size();i++){
                if(AllChildrems.at(i)->zValue()==1){
                    AllChildrems.at(i)->setPos((boundingRect().width()/2)-(AllChildrems.at(i)->boundingRect().width()/2),-12);
                }else if(AllChildrems.at(i)->zValue()==2){
                    AllChildrems.at(i)->setPos((boundingRect().width()/2)-(AllChildrems.at(i)->boundingRect().width()/2) -12 ,-12);
                }else if(AllChildrems.at(i)->zValue()==3){
                    AllChildrems.at(i)->setPos((boundingRect().width()/2)-(AllChildrems.at(i)->boundingRect().width()/2) -24, -12);
                }else if(AllChildrems.at(i)->zValue()==4){
                    AllChildrems.at(i)->setPos((boundingRect().width()/2)-(AllChildrems.at(i)->boundingRect().width()/2) -36, -12);
                }else if(AllChildrems.at(i)->zValue()==5){
                    AllChildrems.at(i)->setPos((boundingRect().width()/2)-(AllChildrems.at(i)->boundingRect().width()/2) + 12 , -12);
                }else if(AllChildrems.at(i)->zValue()==6){
                    AllChildrems.at(i)->setPos((boundingRect().width()/2)-(AllChildrems.at(i)->boundingRect().width()/2) +24 , -12);
                }
            }
        }
    }else{
        if(AllChildrems.size()>=1){
            for(int i = 0; i < AllChildrems.size();i++){
                if(AllChildrems.at(i)->zValue()==1){
                    AllChildrems.at(i)->setPos(boundingRect().width(), -2);
                }else if(AllChildrems.at(i)->zValue()==2){
                    AllChildrems.at(i)->setPos(boundingRect().width(), 11);
                }else if(AllChildrems.at(i)->zValue()==3){
                    AllChildrems.at(i)->setPos(boundingRect().width(), boundingRect().height() -9);
                }else if(AllChildrems.at(i)->zValue()==4){
                    AllChildrems.at(i)->setPos(-12, boundingRect().height() - 10);
                }else if(AllChildrems.at(i)->zValue()==5){
                    AllChildrems.at(i)->setPos(-12 , -2);
                }else if(AllChildrems.at(i)->zValue()==6){
                    AllChildrems.at(i)->setPos(-4, boundingRect().height());
                }
            }
        }
    }

}


/*!
 *\brief changes the type of end image of the interactivity arrow from suspensionsPoints to EndInteractivityTermination
 *\return void
 */
void Image::suspensionPointsInteractivity()
{
    arrowAsociadoAux = qgraphicsitem_cast<Arrow *>(arrowAsociado);
    QImage image(QDir::currentPath()+"/images/linevertical.png");
    QPixmap pixTmp(QPixmap::fromImage(image));
    setPixmap(pixTmp);
    setPos(scene()->width()-77 -parentItem()->scenePos().x(),arrowAsociadoAux->getStartItem()->scenePos().y() - arrowAsociadoAux->getStartItem()->parentItem()->scenePos().y()/*distTempLineInteractLine + (lineNumber * LINESIZE) + (LINESIZE/2)-(boundingRect().height()/2)+3 - parentItem()->scenePos().y()*/);
    myType = EndInteractivityTermination;    
    addRemoveInfiniteInteract(arrowAsociado, false);
    moveAfterInteractivity(true);
    adaptMaxItem();
}


/*!
 *\brief redefined action of \b QGraphicsPixmapItem
 *\param QGraphicsSceneContextMenuEvent *event
 *\return void
 */
void Image::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    emit closeEventsButton();
    if (myType == EndTermination) {
       infinite = true;
       menuTimeLineNoInfinit->exec(event->screenPos());
    }else if (myType == SuspensionPoints) {
       infinite = false;
       if(haveAssociatedArrow){
           arrowAsociadoAux = qgraphicsitem_cast<Arrow *>(arrowAsociado);
           if(arrowAsociadoAux->getMyType() == Arrow::InteractLine)
                menuInteractivityInfinit->exec(event->screenPos());
           else
                menuTimeLineInfinit->exec(event->screenPos());
       }else{
           menuTimeLineInfinit->exec(event->screenPos());
       }
    }else if (myType == InitTermination) {
       menuTimeLineInit->exec(event->screenPos());
    }else if ( myType == InitInteractivityTermination || myType == EndInteractivityTermination) {
       menuInteractivity->exec(event->screenPos());
    }
    pressMenu=true;
}


/*!
 *\brief searches the nearest position of children's Images
 *\return void
 */
void Image::theNearestChild()
{
    QList<QGraphicsItem *> todosHijos = timeLine->childItems();
    Arrow *currentArrow = qgraphicsitem_cast<Arrow *>(timeLine);
    currentArrowAux =qgraphicsitem_cast<Arrow *>(timeLine);;
    theLowestPos = currentArrow->getEndItem()->arrives()->x();
    theLowestEndPos = currentArrow->getStartItem()->send()->x();
    difBetweenStartEnd = currentArrow->getEndItem()->arrives()->x() - currentArrow->getStartItem()->send()->x();

    for(int i = 0; i < todosHijos.size();i++){
        currentArrow = qgraphicsitem_cast<Arrow *>(todosHijos.at(i));
        if(currentArrow->getMyType() == Arrow::InteractLine){
            if(currentArrow->getStartItem()->scenePos().x() < theLowestPos)
                theLowestPos = currentArrow->getStartItem()->scenePos().x();
            if(currentArrow->getEndItem()->scenePos().x() > theLowestEndPos)
                theLowestEndPos = currentArrow->getEndItem()->scenePos().x();
        }else{
            if(currentArrow->line().x2() < theLowestPos)
                theLowestPos = currentArrow->line().x2();
            if(currentArrow->line().x2() > theLowestEndPos)
                theLowestEndPos = currentArrow->line().x2();
        }
    }

    if(currentArrow->getMyType() != Arrow::InteractLine){
        theLowestPos = theLowestPos - boundingRect().width()/2;
        theLowestEndPos = theLowestEndPos - boundingRect().width()/2;
    }

    if(todosHijos.size() == 0)
        theLowestPos = -1;
}


/*!
 *\brief sets the \a valueInfinite to all childrens of \a arrowtItemP to indicate that the items are children of a finite or infinite interactivity
 *\param QGraphicsLineItem *arrowtItemP
 *\param bool valueInfinite
 *\return void
 */
void Image::addRemoveInfiniteInteract(QGraphicsLineItem *arrowtItemP, bool valueInfinite)
{
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;    
    if(AllChildrems.size()>=1){
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){
                    arrowtItem->getStartItem()->setInfiniteInteract(valueInfinite);
                    arrowtItem->getEndItem()->setInfiniteInteract(valueInfinite);
                }else if(arrowtItem->getMyType() == Arrow::InteractLine){
                    if(arrowtItem->getEndItem()->getMyType() == SuspensionPoints)
                        return;
                }
                addRemoveInfiniteInteract(arrowtItem,valueInfinite);
            }
        }
    }else{
        return;
    }
}


/*!
 *\brief updates the X position of each diamond children of \a arrowtItemP
 *\param QGraphicsLineItem *arrowtItemP
 *\return void
 */
void Image::changeParent(QGraphicsLineItem *arrowtItemP)
{   
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;
    if(AllChildrems.size()>=1){       
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow               
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){
                    arrowtItem->getStartItem()->getDiamond()->setX(arrowtItem->getStartItem()->scenePos().x() - longUnionRomboTempLine - arrowtItem->getStartItem()->getDiamond()->parentItem()->scenePos().x());
                    if(!infiniteInteract)
                        arrowtItem->getEndItem()->getDiamond()->setX(arrowtItem->getEndItem()->scenePos().x()  + longUnionRomboTempLine - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().x() - (arrowtItem->getEndItem()->getDiamond()->boundingRect().width()/2));
                } else if(arrowtItem->getMyType() == Arrow::InteractLine){
                    return;
                }
                changeParent(arrowtItem);
            }
        }
    }else{
        return;
    }
}


/*!
 *\brief removes all diamonds childrens of \a arrowtItemP
 *\param QGraphicsLineItem *arrowtItemP
 *\return void
 */
void Image::removeDiamonds(QGraphicsLineItem *arrowtItemP)
{   
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;
    if(AllChildrems.size()>=1){      
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow               
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){                  
                    scene()->removeItem(arrowtItem->getStartItem()->getDiamond());
                    scene()->removeItem(arrowtItem->getEndItem()->getDiamond());
                } else if(arrowtItem->getMyType() == Arrow::InteractLine){
                    return;
                }
                removeDiamonds(arrowtItem);
            }
        }
    }else{
        return;
    }
}


/*!
 *\brief up or downs the lines \a cantDownUp of all childrens of the \a arrowtItemP
 *\param QGraphicsLineItem *arrowtItemP
 *\param qreal cantDownUp
 *\return void
 */
void Image::downUpChildrens(QGraphicsLineItem *arrowtItemP, qreal cantDownUp)
{   
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;
    if(AllChildrems.size()>=1){      
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow               
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){
                    arrowtItem->getStartItem()->getDiamond()->setY(arrowtItem->getStartItem()->getDiamond()->scenePos().y() - arrowtItem->getStartItem()->getDiamond()->parentItem()->scenePos().y() + cantDownUp);
                    arrowtItem->getEndItem()->getDiamond()->setY(arrowtItem->getEndItem()->getDiamond()->scenePos().y() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().y()  + cantDownUp);
                }else if(arrowtItem->getMyType() == Arrow::InteractLine){
                    return;
                }
                downUpChildrens(arrowtItem,cantDownUp);
            }
        }
    }else{
        return;
    }
}


/*!
 *\brief redefined action of \b QGraphicsPixmapItem
 *\param QGraphicsSceneMouseEvent *event
 *\return void
 */
void Image::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(myType==Other)
        return;
    if(event -> buttons() & Qt::LeftButton){
        if (pressMenu){
            pressItem = false;
            pressMenu = false;
        }else{
            pressItem = true;
            if(myType == InitTermination){
                if(haveAssociatedArrow){
                    arrowAsociadoAux =qgraphicsitem_cast<Arrow *>(arrowAsociado);
                    textItem  = scene()->addText(NULL);
                    textItem->setPos(event->scenePos().x(), arrowAsociadoAux->getStartItem()->scenePos().y() - (arrowAsociadoAux->getStartItem()->boundingRect().height() /2));
                    QTime timeaux(0,0,0);
                    currentTime = timeaux.addMSecs((scenePos().x() - arrowAsociadoAux->getStartItem()->scenePos().x()) *100);
                    textItem->setPlainText(currentTime.toString("hh:mm:ss:zzz"));
                    removeText = true;
                }else
                    removeText = false;
            }else
                removeText = false;
            if(myType == InitTermination || myType == InitInteractivityTermination || myType == EndInteractivityTermination)
                pressItemUpdateScene = true;
            else
                pressItemUpdateScene = false;

            if(myType == InitTermination || myType == EndTermination)
                theNearestChild();            
            if(haveRombo){
                if(myType == InitTermination){
                    longUnionRomboTempLine = scenePos().x()  - romboAssociated->scenePos().x();
                }else if(myType == EndTermination){
                    longUnionRomboTempLine = romboAssociated->scenePos().x() - scenePos().x();
                }
                arrowAux =  qgraphicsitem_cast<Arrow *>(timeLine);
            }           
        }
    }else
        pressItem = false;

    if (event -> buttons() & Qt::LeftButton  && myType == BotonInteract) {
        emit showWindows(this,playList,stopList,pauseList,resumeList,abortList,setList,setTableList);
    }

}


/*!
 *\brief redefined action of \b QGraphicsPixmapItem
 *\param QGraphicsSceneMouseEvent *event
 *\return void
 */
void Image::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{   
    if(myType==Diamond)
        return;
    if(isChildrenOfInteract)
        return;
    if(event->scenePos().x() <= -1)
        return;
    if(myType==Other)
        return;

    if(pressItem){
       if(haveAssociatedArrow){
           arrowAsociadoAux =qgraphicsitem_cast<Arrow *>(arrowAsociado);
           if(arrowAsociadoAux->getMyType()==Arrow::TempLine){
               if(arrowAsociadoAux->getEndItem()->scenePos().x() >= event->scenePos().x() && arrowAsociadoAux->getStartItem()->scenePos().x() <= event->scenePos().x() ){
                   if(myType == InitTermination){
                       prepareGeometryChange();
                       setX(event->scenePos().x() - parentItem()->scenePos().x());
                       textItem->setPos(event->scenePos().x(), arrowAsociadoAux->getStartItem()->scenePos().y() - (arrowAsociadoAux->getStartItem()->boundingRect().height() /2));
                       QTime timeaux(0,0,0);
                       currentTime = timeaux.addMSecs((event->scenePos().x() - arrowAsociadoAux->getStartItem()->scenePos().x()) *100);
                       textItem->setPlainText(currentTime.toString("hh:mm:ss:zzz"));
                       if(haveRombo){
                           romboAssociated->setX(event->scenePos().x()- longUnionRomboTempLine - romboAssociated->parentItem()->scenePos().x());
                           if(!infiniteInteract)
                               arrowAux->getEndItem()->getDiamond()->setX(arrowAux->getEndItem()->scenePos().x()  + longUnionRomboTempLine -arrowAux->getEndItem()->getDiamond()->parentItem()->scenePos().x() - (arrowAux->getEndItem()->getDiamond()->boundingRect().width()/2));
                           changeParent(arrowAux);
                        }
                   }
               }
           }else if(arrowAsociadoAux->getMyType()==Arrow::InteractLine || arrowAsociadoAux->getMyType()==Arrow::UnionInteractiveLine){
               arrowAux = qgraphicsitem_cast<Arrow *>(arrowAsociadoAux->parentItem());
               if(arrowAux->getEndItem()->scenePos().x() >= event->scenePos().x() && arrowAux->getStartItem()->scenePos().x() <= event->scenePos().x() ){
                   if(myType == InitInteractivityTermination){
                       if(event->scenePos().x() <= arrowAsociadoAux->getEndItem()->scenePos().x()){
                           prepareGeometryChange();
                           setX(event->scenePos().x() - parentItem()->scenePos().x());
                           moveAfterInteractivity(false);
                           arrowAsociadoAux->updatePosition();
                           qreal longitud = (arrowAsociadoAux->line().x2()-arrowAsociadoAux->line().x1());
                           qreal medioDeLinea= arrowAsociadoAux->line().x1() + longitud/2 -(arrowAsociadoAux->getButton()->boundingRect().width()/2) + arrowAsociadoAux->pen().widthF()/2;
                           arrowAsociadoAux->getButton()->setX(medioDeLinea - arrowAsociadoAux->getButton()->parentItem()->scenePos().x());
                        }
                    }else if(myType == EndInteractivityTermination){
                        if(event->scenePos().x() >= arrowAsociadoAux->getStartItem()->scenePos().x()){
                            prepareGeometryChange();
                            setX(event->scenePos().x() - parentItem()->scenePos().x());                                        
                            arrowAsociadoAux->updatePosition();
                            qreal longitud = (arrowAsociadoAux->line().x2()-arrowAsociadoAux->line().x1());
                            qreal medioDeLinea= arrowAsociadoAux->line().x1() + longitud/2 -(arrowAsociadoAux->getButton()->boundingRect().width()/2) + arrowAsociadoAux->pen().widthF()/2;
                            arrowAsociadoAux->getButton()->setX(medioDeLinea - arrowAsociadoAux->getButton()->parentItem()->scenePos().x());
                            moveAfterInteractivity(false);
                        }
                    }
                }
           }
       }else{
           if(parentItem()==0){
               if(myType == InitTermination){
                   prepareGeometryChange();
                   setX(event->scenePos().x());
               }
            }else{
                if(myType == EndTermination){
                    if(event->scenePos().x() >= theLowestEndPos){
                        prepareGeometryChange();
                        setX(event->scenePos().x() - parentItem()->scenePos().x());
                        if(!infiniteInteract){
                            if(haveRombo){
                                romboAssociated->setX(longUnionRomboTempLine + event->scenePos().x() - romboAssociated->parentItem()->scenePos().x());
                                moveImageFinalScene(romboAssociated->scenePos().x());
                            }else{
                                moveImageFinalScene(event->scenePos().x());
                            }
                        }
                    }
                }else if( myType == SuspensionPoints) {
                    if(event->scenePos().x() >= theLowestEndPos){
                        prepareGeometryChange();
                        setX(event->scenePos().x() - parentItem()->scenePos().x());
                        moveImageFinalScene(event->scenePos().x());
                        itemIsSuspPoints =true;
                    }
                }
            }
        }
    }
}


/*!
 *\brief redefined action of \b QGraphicsPixmapItem
 *\param QGraphicsSceneMouseEvent *event
 *\return void
 */
void Image::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{    
    if(myType==Other)
        return;

    pressItem=false;    
    if(itemIsSuspPoints){
        adaptMaxItemAux();
        itemIsSuspPoints=false;
    }   

    if(myType == SuspensionPoints){
        setX(scene()->width()-boundingRect().width() - parentItem()->scenePos().x());
    }else if(myType == InitTermination){
        if(haveAssociatedArrow && removeText)
            scene()->removeItem(textItem);

        arrowAux =  qgraphicsitem_cast<Arrow *>(timeLine);
        if(arrowAux->getEndItem()->getMyType() == SuspensionPoints){
            arrowAux->getEndItem()->setX(scene()->width()- arrowAux->getEndItem()->boundingRect().width() - arrowAux->getEndItem()->parentItem()->scenePos().x());
            lastInteractUpdateScene();
        }
    }

    if(pressItemUpdateScene){     
        adaptMaxItem();
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}


/*!
 *\brief redefined action of \b QGraphicsPixmapItem
 *\param QGraphicsSceneHoverEvent *event
 *\return void
 */
void Image::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if((myType == BotonInteract || myType ==InitTermination || myType == EndTermination || myType == SuspensionPoints) &&
       this->scenePos().x()-1 <= event->scenePos().x() && event->scenePos().x() <= this->scenePos().x()+boundingRect().width() && event->scenePos().y() >=this->scenePos().y() &&
       event->scenePos().y() <= this->scenePos().y()+boundingRect().height()){
        posSceneXY.setX(event->screenPos().x()+boundingRect().width()-event->pos().x()+2);
        posSceneXY.setY(event->screenPos().y());
        emit showEventsButton(posSceneXY,playList,stopList,pauseList,resumeList,abortList,setList);
    }
    QGraphicsPixmapItem::hoverEnterEvent(event);
}


/*!
 *\brief redefined action of \b QGraphicsPixmapItem
 *\param QGraphicsSceneHoverEvent *event
 *\return void
 */
void Image::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{    
    if((myType == BotonInteract || myType ==InitTermination || myType == EndTermination || myType == SuspensionPoints)
        && (event->screenPos().x() != 0 && event->screenPos().y() != 0)) {       
        emit closeEventsButton();
    }
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}


/*!
 *\brief updates the width of the scene according to the position of interactivities arrows
 *\return void
 */
void Image::lastInteractUpdateScene()
{
    QList<QGraphicsItem *> todosHijos = timeLine->childItems();
    Arrow *currentArrow;
    for(int i = 0; i < todosHijos.size();i++){
        currentArrow = qgraphicsitem_cast<Arrow *>(todosHijos.at(i));
        if(currentArrow->getMyType() == Arrow::InteractLine){
            moveImageFinalScene(currentArrow->getEndItem()->scenePos().x() +10 );
        }
    }
}


/*!
 *\brief updates the size scene when X position of Image is higher than scene width
 *\return void
 */
void Image::adaptMaxItem()
{
    qreal maxPosItem = 0;
    Arrow *arrowtItem;
    if(myType == InitInteractivityTermination || myType == EndInteractivityTermination || myType == SuspensionPoints){
        maxPosItem = updateSizeScene(arrowAsociado,0);
    }else if(myType == InitTermination || myType == EndTermination){
        arrowtItem =  qgraphicsitem_cast<Arrow *>(timeLine);
        maxPosItem = updateSizeScene(timeLine,0);
        if(arrowtItem->getEndItem()->itemHaveDiamond()){
            if(arrowtItem->getEndItem()->getDiamond()->isVisible() && !arrowtItem->getEndItem()->getInfiniteInteract()){
                if(arrowtItem->getEndItem()->getDiamond()->scenePos().x() > maxPosItem)
                    maxPosItem = arrowtItem->getEndItem()->getDiamond()->scenePos().x();
            }else{
                if(arrowtItem->getEndItem()->scenePos().x() > maxPosItem)
                        maxPosItem = arrowtItem->getEndItem()->scenePos().x();
            }
        }else if(arrowtItem->getEndItem()->scenePos().x() > maxPosItem)
            maxPosItem = arrowtItem->getEndItem()->scenePos().x();
    }
    moveImageFinalScene(maxPosItem);
}


/*!
 *\brief updates the size scene when X position of Image(with type SuspensionPoints) is higher than scene width
 *\return void
 */
void Image::adaptMaxItemAux()
{
    qreal maxPosItem = 0;
    Arrow *arrowtItem;    
    if(myType == SuspensionPoints){
        arrowtItem =  qgraphicsitem_cast<Arrow *>(timeLine);
        maxPosItem = updateSizeScene(timeLine,0);
        if(arrowtItem->getEndItem()->itemHaveDiamond()){
            if(arrowtItem->getEndItem()->getDiamond()->isVisible()){
                if(arrowtItem->getEndItem()->getDiamond()->scenePos().x() > maxPosItem)
                    maxPosItem = arrowtItem->getEndItem()->getDiamond()->scenePos().x();
            }else{
                if(arrowtItem->getEndItem()->scenePos().x() > maxPosItem)
                        maxPosItem = arrowtItem->getEndItem()->scenePos().x();
            }
        }else if(arrowtItem->getEndItem()->scenePos().x() > maxPosItem)
            maxPosItem = arrowtItem->getEndItem()->scenePos().x();
    }
    moveImageFinalScene(maxPosItem);
}


/*!
 *\brief updates the scene width with the highest position of all children the \a arrowtItemP
 *\param QGraphicsLineItem* arrowtItemP
 *\param qreal maxPosItem
 *\return qreal
 */
qreal Image::updateSizeScene(QGraphicsLineItem* arrowtItemP ,qreal maxPosItem)
{
    qreal maxAux;
    qreal currentPos;
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;

    if(AllChildrems.size()>=1){
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){
                    if(arrowtItem->getStartItem()->itemHaveDiamond()){
                        if(arrowtItem->getEndItem()->getDiamond()->isVisible() && !arrowtItem->getEndItem()->getInfiniteInteract()){
                            currentPos = arrowtItem->getEndItem()->getDiamond()->scenePos().x();
                            if(currentPos > maxPosItem)
                                maxPosItem = currentPos;
                        }else{
                            currentPos = arrowtItem->getEndItem()->scenePos().x();
                            if(currentPos > maxPosItem)
                                maxPosItem = currentPos;
                        }
                    }else{
                        currentPos = arrowtItem->getEndItem()->scenePos().x();
                        if(currentPos > maxPosItem)
                            maxPosItem = currentPos;
                    }
                }
                maxAux = updateSizeScene(arrowtItem , maxPosItem);
                if(maxAux > maxPosItem)
                    maxPosItem = maxAux;
            }
        }
    }else{
        return 0;
    }

    return maxPosItem;
}


/*!
 *\brief sets the associated arrow \a arrow
 *\param QGraphicsLineItem *arrow
 *\return void
 */
void Image::setArrow(QGraphicsLineItem *arrow)
{
    arrowAsociado=arrow;
    arrowAsociadoAux =qgraphicsitem_cast<Arrow *>(arrowAsociado);
    haveAssociatedArrow=true;
    if(arrowAsociadoAux->getMyType()==Arrow::UnionInteractiveLine){
        setFlag(QGraphicsItem::ItemIsMovable, false);
        setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}


/*!
 *\brief returns the associated arrow
 *\return QGraphicsLineItem *
 */
QGraphicsLineItem * Image::getAssociatedArrow()
{
    return arrowAsociado;
}


/*!
 *\brief sets the name of button the remote control
 *\param QString item
 *\return void
 */
void Image::setKeyButton(QString item)
{
    nameTeclaBoton = item;
}


/*!
 *\brief returns the name of button the remote control
 *\return QString
 */
QString Image::getKeyButton()
{
    return nameTeclaBoton;
}


/*!
 *\brief sets lists of roles
 *\param QStringList playListP
 *\param QStringList stopListP
 *\param QStringList pauseListP
 *\param QStringList resumeListP
 *\param QStringList abortListP
 *\param QStringList setListP
 *\param QTableWidget* setTableP
 *\return void
 */
void Image::setRoleList(QStringList playListP,QStringList stopListP,QStringList pauseListP,QStringList resumeListP,QStringList abortListP,QStringList setListP,QTableWidget* setTableP)
{
    playList = playListP;
    stopList = stopListP;
    pauseList = pauseListP;
    resumeList = resumeListP;
    abortList = abortListP;
    setList = setListP;
    setTableList = new QTableWidget();
    setTableList->setRowCount(setTableP->rowCount());
    setTableList->setColumnCount(3);
    for(int i = 0; i< setTableP->rowCount();i++){
        setTableList->setItem(i,0,setTableP->takeItem(i,0));
        setTableList->setItem(i,1,setTableP->takeItem(i,1));
        setTableList->setItem(i,2,setTableP->takeItem(i,2));
    }
}


/*!
 *\brief returns the \a playList
 *\return QStringList
 */
QStringList Image::getRoleListPlayList()
{
    return playList;
}


/*!
 *\brief returns the \a stopList
 *\return QStringList
 */
QStringList Image::getRoleListStopList()
{
    return stopList;
}


/*!
 *\brief returns the \a pauseList
 *\return QStringList
 */
QStringList Image::getRoleListPauseList()
{
    return pauseList;
}


/*!
 *\brief returns the \a resumeList
 *\return QStringList
 */
QStringList Image::getRoleListResumeList()
{
    return resumeList;
}


/*!
 *\brief returns the \a abortList
 *\return QStringList
 */
QStringList Image::getRoleListAbortList()
{
    return abortList;
}


/*!
 *\brief returns the \a setList
 *\return QStringList
 */
QStringList Image::getRoleListSetList()
{
    return setList;
}


/*!
 *\brief returns the \a setTableList
 *\return QTableWidget *
 */
QTableWidget* Image::getRoleListsetTableList()
{
    return setTableList;
}


/*!
 *\brief sets the type of the Image
 *\param TypeImage typeImagen
 *\return void
 */
void Image::setMyType(TypeImage typeImagen)
{
    myType = typeImagen;
}


/*!
 *\brief sets if Image is children of other Image with interactivity arrow associated
 *\return void
 */
void Image::childrenOfInteract()
{
    isChildrenOfInteract = true;
}


/*!
 *\brief sets arrow like timeline
 *\param QGraphicsLineItem *arrow
 *\return void
 */
void Image::setTimeLine(QGraphicsLineItem *arrow)
{
    timeLine = arrow;
}


/*!
 *\brief returns arrow like timeline
 *\return QGraphicsLineItem *
 */
QGraphicsLineItem * Image::getTimeLine()
{
    return timeLine;
}


/*!
 *\brief updates the scene width with \a imagePosX
 *\param qreal imagePosX
 *\return void
 */
void Image::moveImageFinalScene(qreal imagePosX)
{
    if((scene()->width()-50) < imagePosX){
        scene()->setSceneRect(QRectF(0, 0, imagePosX + 50, scene()->height()));
        UpdatePosSuspensionPoints();               
    }
}


/*!
 *\brief sets diamond associated to Image
 *\param Image *rombo
 *\return void
 */
void Image::setDiamond(Image *diamond)
{
    romboAssociated =diamond;
    haveRombo = true;
}


/*!
 *\brief returns the associated diamond
 *\return Image*
 */
Image* Image::getDiamond()
{
    return romboAssociated;
}


/*!
 *\brief returns if Image have associated diamond
 *\return bool
 */
bool Image::itemHaveDiamond()
{
    return haveRombo;
}


/*!
 *\brief returns the distance from diamond to Image
 *\return qreal
 */
qreal Image::getLongUnionDiamondTempLine()
{
    longUnionRomboTempLine= 0;
    if(haveRombo){
        if(myType == InitTermination)
            longUnionRomboTempLine = scenePos().x() - romboAssociated->scenePos().x();
        else if(myType == EndTermination)
            longUnionRomboTempLine = romboAssociated->scenePos().x()  - scenePos().x();
    }
    return longUnionRomboTempLine;
}


/*!
 *\brief moves all diamonds childrens of \a arrowtItemP
 *\param bool correctDiamond
 *\param bool infinite
 *\param QGraphicsLineItem* arrowtItemP
 *\param qreal longUnionDiamondTempLineP
 *\return void
 */
void Image::moveDiamondAfterInteract(bool correctDiamond,bool infinite,QGraphicsLineItem* arrowtItemP, qreal longUnionDiamondTempLineP)
{
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;
    if(AllChildrems.size()>=1){
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::TempLine){
                    if(infinite && arrowtItem->getEndItem()->getInfiniteInteract())
                        arrowtItem->getEndItem()->getDiamond()->setX(scene()->width() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().x() - (arrowtItem->getEndItem()->getDiamond()->boundingRect().width() * 2));
                    else{
                        arrowtItem->getStartItem()->getDiamond()->setX(arrowtItem->getStartItem()->scenePos().x() - longUnionDiamondTempLineP - arrowtItem->getStartItem()->getDiamond()->parentItem()->scenePos().x());
                        if(!arrowtItem->getEndItem()->getInfiniteInteract()){
                            if(correctDiamond)
                                arrowtItem->getEndItem()->getDiamond()->setY(arrowtItem->getStartItem()->getDiamond()->scenePos().y() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().y());
                            arrowtItem->getEndItem()->getDiamond()->setX(arrowtItem->getEndItem()->scenePos().x()  + longUnionDiamondTempLineP - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().x() - (arrowtItem->getEndItem()->getDiamond()->boundingRect().width()/2));
                        }else
                            arrowtItem->getEndItem()->getDiamond()->setX(scene()->width() - arrowtItem->getEndItem()->getDiamond()->parentItem()->scenePos().x() - (arrowtItem->getEndItem()->getDiamond()->boundingRect().width() * 2));
                    }
                }else if(arrowtItem->getMyType() == Arrow::InteractLine){
                    return;
                }
                moveDiamondAfterInteract(correctDiamond,infinite,arrowtItem,longUnionDiamondTempLineP);
            }
        }
    }else{
        return;
    }
}


/*!
 *\brief searches all interactivities arrows childrens of \a arrowtItemP
 *\param QGraphicsLineItem* arrowtItemP
 *\param qreal longUnionDiamondTempLineP
 *\param qreal previousSize
 *\return void
 */
void Image::searchInteract(QGraphicsLineItem* arrowtItemP, qreal longUnionDiamondTempLineP,qreal previousSize)
{
    QList<QGraphicsItem *> AllChildrems = arrowtItemP->childItems();
    Arrow *arrowtItem;

    if(AllChildrems.size()>=1){       
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->type() == 6){//is arrow              
                arrowtItem =  qgraphicsitem_cast<Arrow *>(AllChildrems.at(i));
                if(arrowtItem->getMyType() == Arrow::InteractLine){
                    moveDiamondAfterInteract(false,false,arrowtItem , longUnionDiamondTempLineP + (arrowtItem->boundingRect().width()/2) + (previousSize/2));
                    previousSize = longUnionDiamondTempLineP + (arrowtItem->boundingRect().width()/2) + previousSize;
                }
                searchInteract(arrowtItem,longUnionDiamondTempLineP,previousSize);
            }
        }
    }else{
        return ;
    }    
}


/*!
 *\brief updates diamonds
 *\param bool correctDiamond
 *\return void
 */
void Image::moveAfterInteractivity(bool correctDiamond)
{
    if(haveAssociatedArrow){
        Arrow *arrowtItemParent;
        arrowtItemParent =  qgraphicsitem_cast<Arrow *>(arrowAsociado->parentItem());
        qreal previousSizeAux = 0;
        if(correctDiamond){
            if(arrowtItemParent->getEndItem()->itemHaveDiamond()){
                previousSizeAux = arrowtItemParent->getStartItem()->getLongUnionDiamondTempLine()*2;
            }
            moveDiamondAfterInteract(correctDiamond,false,arrowAsociado , ((arrowAsociado->boundingRect().width()/2) - 22)  + (previousSizeAux/2));
        }
        if(arrowtItemParent->getEndItem()->itemHaveDiamond()){
            if(myType == EndInteractivityTermination && arrowtItemParent->getEndItem()->getInfiniteInteract())
                moveDiamondAfterInteract(correctDiamond,true,arrowAsociado , 0);

            searchInteract(arrowAsociado,(arrowAsociado->boundingRect().width()/2) - 11.5,arrowtItemParent->getStartItem()->getLongUnionDiamondTempLine()*2);
        }else
            searchInteract(arrowAsociado,(arrowAsociado->boundingRect().width()/2) - 11.5,0);
    }
}


/*!
 *\brief sets if the Image is infinite interactive
 *\param bool value
 *\return void
 */
void Image::setInfiniteInteract(bool value)
{
// in InitTermination EndTermination
    infiniteInteract = value;
}


/*!
 *\brief returns if the Image is infinite interactive
 *\return bool
 */
bool Image::getInfiniteInteract()
{
// in InitTermination EndTermination
    return infiniteInteract;
}


/*!
 *\brief emits the \a setButton signal
 *\return void
 */
void Image::editButtonInteract()
{
    Arrow *currentArrowAsociado =qgraphicsitem_cast<Arrow *>(arrowAsociado);
    emit setButton(currentArrowAsociado->getButton());
}


/*!
 *\brief adds a new DescriptorParam \a descriptorP to list \a desccriptorParamList
 *\param DescriptorParam *descriptorP
 *\return void
 */
void Image::addtDescriptorParamToList(DescriptorParam *descriptorP){
    desccriptorParamList.append(descriptorP);
}


/*!
 *\brief return the \a desccriptorParamList
 *\return QList<DescriptorParam*>
 */
QList<DescriptorParam*> Image::getDescriptorParamList(){
    return desccriptorParamList;
}


/*!
 *\brief clears the list \a desccriptorParamList
 *\return void
 */
void Image::clearDescriptorParamList(){
    desccriptorParamList.clear();
}

void Image::setX(qreal x)
{
    setPos(x,y());
}

void Image::setY(qreal y)
{
    setPos(x(),y);
}
