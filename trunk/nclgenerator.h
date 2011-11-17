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
*\file nclgenerator.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to generate the output ncl code.
*/

#ifndef NCLGENERATOR_H
#define NCLGENERATOR_H
#include <QString>
#include <QFileDialog>
#include <QGraphicsItem>

#include "NCL/media.h"
#include "NCL/descriptor.h"
#include "NCL/descriptorbase.h"
#include "NCL/regionn.h"
#include "NCL/ncl.h"
#include "NCL/regionbase.h"
#include "NCL/connectorbase.h"
#include "NCL/importbase.h"

#include "graphicsrectitem.h"
#include "arrow.h"
#include "graphicsscene.h"
#include "diagramscenehead.h"
#include "diagramscene.h"

#include "QTime"


/*!
 * \class NclGenerator
 * \brief class to generate the output ncl code.
 */
class NclGenerator
{

public:
    /// constructor
    NclGenerator();
    /// creates the file and builds the main structure of the \b ncl document(\b head and \b body)
    void createNCL(GraphicsScene *graphicsScene, DiagramSceneHead *graphicsSceneHead,DiagramScene *graphicsSceneTemporal,QString path,
                   QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                   QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QList<Descriptor*> descriptorList);

private:
    Head *head ;
    Body *body ;
    /// returns a region with all your regions childrens of \a rect
    Regionn* getRegiones(GraphicsRectItem *rect);
    /// returns the Media with name \a nameTempLine
    Media * getMedia(QString nameTempLine,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,QList<Media*> mediaVideoList);
    /// builds the \b regionbase sector
    void MakeRegionBase(GraphicsScene *graphicsScene);
    /// creates the \b links according the arrows and his relations into the \a graphicsSceneTemporal
    void makeLinks(DiagramScene *graphicsSceneTemporal,DiagramSceneHead *graphicsSceneHead,QList<Descriptor*> descriptorList,
                                QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,
                                QList<Media*> mediaTextList,QList<Media*> mediaLuaList,QList<Media*> mediaUriList);
    /// adds the \b explicitDur to medias if they have size arrows different to his original size
    void addExplicitDur(QList<Descriptor*> descriptorList,QString nameTempLineCorriente,QString longTempLine);
    /// adds \b roles to \b ncl document
    void addRoles(Image *boton,QString nameTempLineCorriente,int interfaceNumber);
    /// creates the \b area and assigns it to the media
    void addInterface(QString nameArea,QString beginArea,QString endArea,QString nameTempLineCorriente,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,QList<Media*> mediaVideoList,QList<Media*> mediaLuaList,QList<Media*> mediaUriList);
    /// clears the lists to begin again with a new ncl document
    void clearAllProperties(QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                                     QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QList<Descriptor*> descriptorList);
    /// clears the arealist to begin again with new ncl document
    void clearAreaLists(QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,QList<Media*> mediaLuaList,QList<Media*>);
    /// adds propertyes to medias
    void addProperty(DiagramScene *graphicsSceneTemporal,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,
                     QList<Media*> mediaTextList,QList<Media*> mediaVideoList);

};

#endif // NCLGENERATOR_H
