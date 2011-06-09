/*!
*\file diagramscenehead.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to describe medias.
*/

#ifndef DIAGRAMSCENEHEAD_H
#define DIAGRAMSCENEHEAD_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include "image.h"


/*!
 * \class DiagramSceneHead
 * \brief class to describe medias.
 */
class DiagramSceneHead : public QGraphicsScene
{
    Q_OBJECT

public:
    /// creates the DiagramSceneHead and initialize values
    DiagramSceneHead();
    /// returns the name of media located into position \a numLineAux
    QString NameMediaInLineNumber(int numLineAux);
    /// returns all name of medias
    QStringList getNameMedias();
    /// eliminates the media located between line number \a fromLineNumber and \a toLineNumber
    void removeLineBetween(int fromLineNumber,int toLineNumber);
    /// returns the Image of media located into position \a numLineAux
    Image * MediaInLineNumber(int numLineAux);

public slots:
    /// inserts a new media with her description (​​image and name)
    void insertDescriptionMedia(int lineNumber,QImage imageCorrienteP,QString nameMedia,bool openProject);

private:
     Image *descriptionMedia;
     Image *descriptionMediaAux;
     int cantImages;
     QGraphicsTextItem *textItem;
     /// down the items from position \a lineNumber
     void downFromLineNumber(int lineNumber);



signals:
    /// this signal is emitted when a media is selected in DiagramSceneHead
    void showWindowPropertiesMedia(QString windowTitle,Image* media);
    
protected:
    /// redefined action of \b QGraphicsScene
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

};

#endif // DiagramSceneHead_H
