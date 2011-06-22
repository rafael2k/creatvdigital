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
*\file diagramscene.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to contain and manipulate arrows and images in temporal area.
*/

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QGraphicsScene>
#include "diagramscenehead.h"
#include "arrow.h"
#include "image.h"
#include <QGraphicsPixmapItem>
#include <QList>
#include <QTableWidgetItem>
#include <QGraphicsSceneMouseEvent>


QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
QT_END_NAMESPACE


/*!
 * \class DiagramScene
 * \brief class to contain and manipulate arrows and images in temporal area.
 */
class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:   
    /// creates the DiagramScene and initialize values
    DiagramScene();      
    /// enable or disable variable to delete arrows
    void deleteLine(bool activado);
    /// enable or disable variable to add interactivity
    void setButtonInteractividad(bool value);
    /// accommodates Y position of arrows
    void insertBodyDownItems(qreal posX,QImage currentImage,QString nameMedia,qreal MediaDuration,bool haveDuration);

    /// inserts the first arrow
    Arrow* addFirstImage(QImage currentImage,QString nameMedia,qreal MediaDuration,bool haveDuration, qreal originalDuration,bool openProject,bool infinite);
    /// shows or hides all diamonds
    void ViewDiamonds(bool view);

    /// sets the number of lines that the scene have
    void setCantLineTotal(int cant);
    /// sets the nearest arrow
    void setNearArrow(Arrow *nearArrow);
    /// inserts a new arrow after one \a TempLine
    void insertImage(QImage currentImage,QString nameMedia,qreal PosX,qreal mediaDuration,qreal posY,qreal posYItem2,bool haveDuration,qreal originalDuration,bool openProject,bool infinite);
    /// inserts a new arrow after one interactive arrow
    void insertImageWithInteract(QImage currentImage,QString nameMedia,Image* boton,qreal posy,qreal posyEnd,qreal MediaDuration,bool haveDuration,qreal originalDuration,bool openProject,bool infinite);
    /// inserts a new interactivity arrow
    void insertInteractivity(qreal posXBegin,qreal posYBegin, qreal posXEnd, qreal posYEnd,QString nameButton,bool infinite);
    /// returns true if the buttonInteractividad is pressed
    bool getButtonInteractividad();
    /// returns true if the buttonDeleteLine is pressed
    bool getButtonDeleteLine();
    /// returns the nearest arrow of \a posXY
    Arrow* searchArrowNearMause(QPointF posXY);

private:    
    Arrow *arrowLineAux;
    Arrow *arrow;
    Arrow *unionArrow;
    Arrow *unionInteractiveArrow;
    Arrow *arrowcerca;
    Arrow *beginArrow;
    Arrow *endArrow;
    Image *startItem;
    Image* endItem;
    Image* boton;
    Image* beginRombo;
    Image* endRombo;        
    bool canMove;
    bool alreadySetColor;
    bool viewItems;
    bool okItem;
    qreal posNearArrow;    
    qreal distTempLineInteractLine;         
    int cantLineTotal;
    int currentLine;
    /// return Y position of the nearest arrow after \a posX
    qreal othersTemLineRight(qreal posX);
    /// returns true if the parameter is correct
    bool correctParameters(QPointF pos,Arrow *nearArrow);
    /// creates the start item of the interactivity arrow
    void interactiveButton(bool activated,QPointF pos);
    /// converts all items in transparent
    void makeTransparent(int lineExeption, bool transparent);
    /// deletes line number \a lineNumber  and all their childrens
    void deleteLineNumber(int lineNumber);
    /// up all items found under \a lineNumber, the amount rises \a cantLineUp
    void upToLineNumber(int lineNumber,int cantLineUp);
    /// lowers items the amount \a cantLineDown
    void downFromLineNumber(int cantLineDown,qreal linePosX,Arrow *arrow);
    /// updates position of all arrows
    void updateArrows();
    /// add diamonds to arrow \a arrowP
    void checkUnionDiamondTempLine(Arrow *arrowcercaP,Arrow *arrowP, Arrow *unionArrowP);
    /// enlarges the scene until position \a imagePosX
    void sceneWidthPosImage(qreal imagePosX);    
    /// returns interactivity arrow children of \a parentArrow
    Arrow* searchInteract(Arrow *parentArrow);
    /// returns the nearest arrow of \a posXY without interactivity
    Arrow* searchArrowWithoutInteractNearMause(QPointF posXY);

    QGraphicsTextItem *textItem;
    QTime currentTime;


signals:
    /// this signal is emitted when a new arrow is inserted
    void insertDescription(int lineNumber,QImage imageCorrienteP,QString nameMediaP,bool openProject);
    /// this signal is emitted when arrows are deleted
    void removeLineBetween(int fromLineNumber,int toLineNumber);
    /// this signal is emitted when the media is dropped in DiagramScene
    void diagramSceneDrop(qreal posX);
    /// this signal is emitted for select new key for button \a button
    void selectedBoton(Image *button,Image *startItemP, Image * endItemP);
    /// this signal is emitted when an Image is selected
    void showWindows2(Image *boton,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList,QTableWidget* setTableList);
    /// this signal is emitted when mouse is hover enter an Image
    void showEventsButton2(QPointF posWindow,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList);
    /// this signal is emitted when mouse is moving
    void mouseMove(QPointF point);
    /// this signal is emitted when mouse is hover leave an Image
    void closeEventsButton2();
    /// this signal is emitted when the object dropped in a RecItem is from a wrong place
    void outElement();
    /// this signal is emitted when we select change key of button the remote control
    void setButton(Image* boton);

private slots:    
    /// emits the \a showWindows2 signal
    void showWindowsSlot2(Image *boton,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList,QTableWidget* setTableList);
    /// emits the \a showEventsButton2 signal
    void showEventsButtonSlot2(QPointF posWindow,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList);
    /// emits the \a closeEventsButton2 signal
    void closeEventsButtonSlot2();
    /// emits the \a removeLineBetween signal and updates the size of the scene
    void removeAndUpLines(int lineNumber, int cantLineUp);
    /// emits the \a setButton signal
    void setButtonSlot(Image* boton);

public slots:
   /// sets \okItem in true
   void setTrueOkItemDrop();
   /// sets \okItem in false
   void setFlaseOkItemDrop();

protected:
    /// redefined action of \b QGraphicsScene
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /// redefined action of \b QGraphicsScene
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /// redefined action of \b QGraphicsScene
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    /// redefined action of \b QGraphicsScene
    void dropEvent( QGraphicsSceneDragDropEvent * event );
    /// redefined action of \b QGraphicsScene
    void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
    /// redefined action of \b QGraphicsScene
    void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
    /// redefined action of \b QGraphicsScene
    void dragLeaveEvent ( QGraphicsSceneDragDropEvent * mouseEvent );

};

#endif // DIAGRAMSCENE_H
