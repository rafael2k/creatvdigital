/*!
*\file ncldocument.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to generate the output ncl code.
*/

#ifndef NCLDOCUMENT_H
#define NCLDOCUMENT_H
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
 * \class NclDocument
 * \brief class to generate the output ncl code.
 */
class NclDocument
{

public:
    /// constructor
    NclDocument();
    /// creates the file and builds the main structure of the \b ncl document(\b head and \b body)
    void createNCL(GraphicsScene *graphicsScene, DiagramSceneHead *graphicsSceneHead,DiagramScene *graphicsSceneTemporal,QString path,
                   QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                   QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QList<Descriptor*> descriptorList);

private:
    Head *head ;
    Body *body ;
    /// returns the list of all regions childrens of \a rect
    QList<Regionn*> getRegiones(GraphicsRectItem *rect);
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

#endif // NCLDOCUMENT_H
