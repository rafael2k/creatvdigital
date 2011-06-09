/*!
*\file diagramscenehead.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to describe medias.
*/


#include "diagramscenehead.h"
#include <iostream>
#include <QtGui>

using namespace std;
qreal borrarPos = 0;


/*!
 *\brief creates the DiagramSceneHead and initialize values
 */
DiagramSceneHead::DiagramSceneHead()
{
    new QGraphicsScene(0, 0, 200, 378,this);
    cantImages=1;
    QImage image(QDir::currentPath()+"/images/puntosSuspensivos2.png");
    image= image.scaled(40,30);
    QPixmap pixTmp(QPixmap::fromImage(image));
    descriptionMediaAux = new Image(pixTmp,Image::TypeMedia);
    addItem(descriptionMediaAux);
    descriptionMediaAux->setPos(width(),0);
    descriptionMediaAux->setPos(width(),LINESIZE);
    descriptionMediaAux->setPos(width(),LINESIZE*2);
    removeItem(descriptionMediaAux);
}


/*!
 *\brief inserts a new media with her description (​​image and name)
 *\param int lineNumber
 *\param QImage imageCorrienteP
 *\param QString nameMedia
 *\param bool openProject
 *\return void
 */
void DiagramSceneHead::insertDescriptionMedia(int lineNumber,QImage imageCorrienteP,QString nameMedia,bool openProject)
{
    qreal posText;
    cantImages++;
    if(cantImages>4)
        setSceneRect(QRectF(0, 0, width(), (cantImages+1)*LINESIZE));

    lineNumber++;    
    if(!openProject)
        downFromLineNumber(lineNumber);

    imageCorrienteP= imageCorrienteP.scaled(40,30);
    QPixmap pixTmp(QPixmap::fromImage(imageCorrienteP));
    descriptionMedia = new Image(pixTmp,Image::TypeMedia);
    descriptionMedia->setPos((width()/2) -(descriptionMedia->boundingRect().width()/2),lineNumber*LINESIZE);
    addItem(descriptionMedia);

    textItem = addText(nameMedia);
    QFont textFont;
    textFont.setPixelSize(12);
    textItem->setFont(textFont);
    posText = (textItem->boundingRect().width() - descriptionMedia->boundingRect().width()) / 2;
    posText = descriptionMedia->scenePos().x() - posText;
    if(posText < 0)
        posText = 0;

    textItem->setPos(posText,descriptionMedia->y()+descriptionMedia->boundingRect().height()-2);
    borrarPos = descriptionMedia->boundingRect().height()-2;
}


/*!
 *\brief eliminates the media located between line number \a fromLineNumber and \a toLineNumber
 *\param int fromLineNumber
 *\param int toLineNumber
 *\return void
 */
void DiagramSceneHead::removeLineBetween(int fromLineNumber,int toLineNumber)
{
    int cantLineRemove =  toLineNumber - fromLineNumber;
    cantImages = cantImages - cantLineRemove;
    if(cantImages>4)
        setSceneRect(QRectF(0, 0, width(), (cantImages+1)*LINESIZE));
    else
        setSceneRect(QRectF(0, 0, width(), 5 * LINESIZE));

    QList<QGraphicsItem *> TodosItems = items();
    int lineAux =-1;
    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->isVisible()){
            if(TodosItems.at(i)->type() == 7){//is imagen
                lineAux = (TodosItems.at(i)->y()+5) / LINESIZE;               
                if(fromLineNumber <= lineAux && lineAux < toLineNumber)
                    removeItem(TodosItems.at(i));
                else if(toLineNumber <= lineAux)
                    TodosItems.at(i)->setY((lineAux-cantLineRemove)*LINESIZE);
            }else if(TodosItems.at(i)->type() == 8){//is text
                lineAux = TodosItems.at(i)->y() / LINESIZE;                
                if(fromLineNumber <= lineAux && lineAux < toLineNumber)
                    removeItem(TodosItems.at(i));
                else if(toLineNumber <= lineAux)
                    TodosItems.at(i)->setY((lineAux-cantLineRemove)*LINESIZE + borrarPos);
            }
        }
    }
    update();
}


/*!
 *\brief down the items from position \a lineNumber
 *\param int lineNumber
 *\return void
 */
void DiagramSceneHead::downFromLineNumber(int lineNumber)
{
    QList<QGraphicsItem *> TodosItems = items();
    int lineAux =-1;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->isVisible()){
            if(TodosItems.at(i)->type() == 7){//is imagen
                lineAux = (TodosItems.at(i)->y()+20) / LINESIZE;                
                if(lineNumber <= lineAux)
                    TodosItems.at(i)->setY((lineAux+1)*LINESIZE);
            }else if(TodosItems.at(i)->type() == 8){//is text
                lineAux = TodosItems.at(i)->y() / LINESIZE;                
                if(lineNumber <= lineAux)
                    TodosItems.at(i)->setY((lineAux+1)*LINESIZE + borrarPos);
            }
        }
    }
}


/*!
 *\brief returns the Image of media located into position \a numLineAux
 *\param int numLineAux
 *\return Image *
 */
Image *DiagramSceneHead::MediaInLineNumber(int numLineAux)
{
    QList<QGraphicsItem *> TodosItems = items();
    int lineAux =-1;
    Image * returnImage = NULL;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 7){//is Image
            lineAux = TodosItems.at(i)->scenePos().y() / LINESIZE;
            if(numLineAux == lineAux){
                returnImage = qgraphicsitem_cast<Image *>(TodosItems.at(i));
                break;
            }
        }
    }
    return returnImage;
}


/*!
 *\brief returns the name of media located into position \a numLineAux
 *\param int numLineAux
 *\return QString
 */
QString DiagramSceneHead::NameMediaInLineNumber(int numLineAux)
{
    QList<QGraphicsItem *> TodosItems = items();
    int lineAux =-1;
    QString returnName = "";

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 8){//is text
            lineAux = TodosItems.at(i)->y() / LINESIZE;
            if(numLineAux == lineAux){
                textItem = qgraphicsitem_cast<QGraphicsTextItem *>(TodosItems.at(i));
                returnName = textItem->toPlainText();
                break;
            }
        }
    }
    return returnName;
}


/*!
 *\brief redefined action of \b QGraphicsScene
 *\param QGraphicsSceneMouseEvent *mouseEvent
 *\return void
 */
void DiagramSceneHead::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent -> buttons() & Qt::LeftButton) {
        int numLine = mouseEvent->scenePos().y() / LINESIZE;
        QString nameMedia = NameMediaInLineNumber(numLine);
        emit showWindowPropertiesMedia(nameMedia,MediaInLineNumber(numLine));
    }
}


/*!
 *\brief returns all name of medias
 *\return QStringList
 */
QStringList DiagramSceneHead::getNameMedias()
{
    QList<QGraphicsItem *> TodosItems = items();
    QStringList returnNames;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 8){//is text
            textItem = qgraphicsitem_cast<QGraphicsTextItem *>(TodosItems.at(i));
            returnNames.append(textItem->toPlainText());
        }
    }
    return returnNames;
}
