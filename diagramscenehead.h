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
