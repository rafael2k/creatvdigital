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
*\file image.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create,remove and modify images.
*/

#ifndef IMAGE_H
#define IMAGE_H
#include <QGraphicsPixmapItem>
#include <QtGui>
#include "NCL/descriptorparam.h"

#define LINESIZE 60


/*!
 * \class Image
 * \brief class to create,remove and modify images.
 */
class Image : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    enum TypeImage { InitInteractivityTermination,EndInteractivityTermination,InitTermination,EndTermination,BotonInteract,TypeMedia,Diamond,SuspensionPoints,Other};
    bool haveAssociatedArrow;
    /// creates the Image
    Image(QPixmap pixTmp);
    /// creates the Image and initialize values
    Image(QPixmap pixTmp,TypeImage typeImage);
    /// creates the Image with associated arrow and initialize values
    Image(QPixmap pixTmp,QGraphicsItem *arrow,TypeImage typeImage);
    /// returns X and Y position the left limit of the image
    QPointF* arrives();
    /// returns X and Y position the right limit of the image
    QPointF* send();
    /// returns the associated arrow
    QGraphicsLineItem * getAssociatedArrow();
    /// returns arrow like timeline
    QGraphicsLineItem * getTimeLine();
    /// returns the type of the Image
    TypeImage getMyType() const
    { return myType; }
    /// returns the name of button the remote control
    QString getKeyButton();
    /// returns the \a playList
    QStringList getRoleListPlayList();
    /// returns the \a stopList
    QStringList getRoleListStopList();
    /// returns the \a pauseList
    QStringList getRoleListPauseList();
    /// returns the \a resumeList
    QStringList getRoleListResumeList();
    /// returns the \a abortList
    QStringList getRoleListAbortList();
    /// returns the \a setList
    QStringList getRoleListSetList();
    /// returns the \a setTableList
    QTableWidget* getRoleListsetTableList();
    /// sets the name of button the remote control
    void setKeyButton(QString item);
    /// sets X position of suspension points with scene width
    void UpdatePosSuspensionPoints();
    /// sets lists of roles
    void setRoleList(QStringList playListP,QStringList stopListP,QStringList pauseListP,QStringList resumeListP,QStringList abortListP,QStringList setListP,QTableWidget* setTableP);
    /// sets the associated arrow \a arrow
    void setArrow(QGraphicsLineItem *arrow);
    /// sets the type of the Image
    void setMyType(TypeImage typeImagen);
    /// sets if Image is children of other Image with interactivity arrow associated
    void childrenOfInteract();
    /// sets arrow like timeline
    void setTimeLine(QGraphicsLineItem *arrow);
    /// sets diamond associated to Image
    void setDiamond(Image *diamond);
    /// removes all diamonds childrens of \a arrowtItemP
    void removeDiamonds(QGraphicsLineItem *arrowtItemP);
    /// up or downs the lines \a cantDownUp of all childrens of the \a arrowtItemP
    void downUpChildrens(QGraphicsLineItem *arrowtItemP, qreal cantDownUp);
    /// sets if the Image is infinite interactive
    void setInfiniteInteract(bool value);
    /// adds a new DescriptorParam \a descriptorP to list \a desccriptorParamList
    void addtDescriptorParamToList(DescriptorParam *descriptorP);
    /// returns the associated diamond
    Image* getDiamond();
    /// returns if Image have associated diamond
    bool itemHaveDiamond();
    /// returns if the Image is infinite interactive
    bool getInfiniteInteract();
    /// returns the distance from diamond to Image
    qreal getLongUnionDiamondTempLine();
    /// return the \a desccriptorParamList
    QList<DescriptorParam*> getDescriptorParamList();
    /// clears the list \a desccriptorParamList
    void clearDescriptorParamList();

private:
    TypeImage myType;
    QGraphicsLineItem *arrowAsociado;
    QGraphicsLineItem *timeLine;

    QString nameTeclaBoton;
    QStringList playList;
    QStringList stopList;
    QStringList pauseList;
    QStringList resumeList;
    QStringList abortList;
    QStringList setList;
    QTableWidget* setTableList;

    QMenu *menuInteractivity;
    QMenu *menuInteractivityInfinit;
    QMenu *menuTimeLineInfinit;
    QMenu *menuTimeLineNoInfinit;
    QMenu *menuTimeLineInit;

    bool infinite;
    bool pressItem;
    bool pressMenu;
    bool isChildrenOfInteract;
    bool infiniteInteract;
    bool removeText;
    bool haveRombo;
    bool pressItemUpdateScene;

    QPoint posSceneXY;

    qreal widthUnionRomboTempLine;
    qreal theLowestPos;
    qreal theLowestEndPos;
    qreal difBetweenStartEnd;
    qreal longUnionRomboTempLine;

    Image *romboAssociated;
    Image *parentTemp;

    QGraphicsTextItem *textItem;
    QTime currentTime;

    QList<DescriptorParam*> desccriptorParamList;

    /// searches the nearest position of children's Images
    void theNearestChild();
    /// updates the scene width with the highest position of all children the \a arrowtItemP
    qreal updateSizeScene(QGraphicsLineItem* arrowtItemP ,qreal maxPosItem);
    /// creates a new menu for each Image
    void makeMenu();
    /// updates the scene width with \a imagePosX
    void moveImageFinalScene(qreal imagePosX);
    /// updates the X position of each diamond children of \a arrowtItemP
    void changeParent(QGraphicsLineItem * arrowtItemP);
    /// moves all diamonds childrens of \a arrowtItemP
    void moveDiamondAfterInteract(bool correctDiamond,bool infinite,QGraphicsLineItem* arrowtItemP, qreal longUnionDiamondTempLineP);
    /// searches all interactivities arrows childrens of \a arrowtItemP
    void searchInteract(QGraphicsLineItem* arrowtItemP, qreal longUnionDiamondTempLineP,qreal previousSize);
    /// updates diamonds
    void moveAfterInteractivity(bool correctDiamond);
    /// sets the \a valueInfinite to all childrens of \a arrowtItemP to indicate that the items are children of a finite or infinite interactivity
    void addRemoveInfiniteInteract(QGraphicsLineItem *arrowtItemP, bool valueInfinite);
    /// updates the size scene when X position of Image is higher than scene width
    void adaptMaxItem();
    /// updates the size scene when X position of Image(with type SuspensionPoints) is higher than scene width
    void adaptMaxItemAux();
    /// updates the position of all diamonds children the \a arrowtItemP
    void correctDiamond(QGraphicsLineItem *arrowtItemP, bool infinitePos, qreal posXDiamond);
    /// updates the width of the scene according to the position of interactivities arrows
    void lastInteractUpdateScene();
    /// updates position the childrens(stop,play,pause,etc) of the image when the image change is from EndTermination to SuspensionPoints or from SuspensionPoints to EndTermination
    void accommodateChildImages(bool infinite);
    /// if the image and his children(image of the interactivity arrow) are suspensionsPoints then they changes to vertical line(or EndTermination and EndInteractivityTermination)
    bool childrenInteractInfinite();
    /// returns the line number of the first arrow that follows to the interactivity arrow(and of course this first arrow must are asociated with interactivity arrow )
    int getFirstLineNumber();

signals:
    /// this signal is emitted when we choose change properties of Image
    void showWindows(Image *boton,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList,QTableWidget* setTableList);
    /// this signal is emitted when mouse is hover enter an Image
    void showEventsButton(QPointF posWindow,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList);
    /// this signal is emitted when mouse is hover leave an Image
    void closeEventsButton();
    /// this signal is emitted when we remove the interactivity arrow
    void removeInteractUpLines(int lineNumber,int cantLineUp);    
    /// this signal is emitted when we choose change the key of the remote control
    void setButton(Image* boton);

protected:
    /// redefined action of \b QGraphicsPixmapItem
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /// redefined action of \b QGraphicsPixmapItem
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    /// redefined action of \b QGraphicsPixmapItem
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    /// redefined action of \b QGraphicsPixmapItem
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    /// redefined action of \b QGraphicsPixmapItem
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    /// redefined action of \b QGraphicsPixmapItem
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private slots:
    /// changes the image(between suspensionPoint and EndTermination) and updates the position of Image
    void suspensionPoints();
    /// emits the \a showWindows signal
    void emitSignalProperties();
    /// resize the interactivity arrow whit the size of the TempLine(i.e. assign the size of the timeline to interactivity arrow)
    void adaptarAMedia();
    /// changes the type of end image of the interactivity arrow from suspensionsPoints to EndInteractivityTermination
    void suspensionPointsInteractivity();
    /// remove the current interactivity arrow and all her childrens
    void removeInteract();
    /// emits the \a setButton signal
    void editButtonInteract();

};

#endif // IMAGE_H
