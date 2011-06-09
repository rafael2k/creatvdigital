/*!
*\file saveproject.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to save and open projects.
*/

#include "saveproject.h"

#include <iostream>
#include <QtDebug>

using namespace std;


/*!
 *\brief assigns the name of project to the file
 *\param QString myFileName
 */
SaveProject::SaveProject(QString myFileName)
{
    file.setFileName(myFileName);
}


/*!
 *\brief saves the datas about the project(like date,description,etc)
 *\param QString projectName
 *\param QDate date
 *\param QString description
 *\return void
 */
void SaveProject::saveProjectDescription(QString projectName,QDate date,QString description,int regionNumber)
{
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
    }else{
        xmlWriter.setDevice(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeComment("Archivo de \"CreaTV Digital\"");
        xmlWriter.writeStartElement("doc");
        xmlWriter.writeStartElement("Project");
        xmlWriter.writeAttribute("name",projectName);
        xmlWriter.writeAttribute("description",description);
        xmlWriter.writeAttribute("date",date.toString("dd-MM-yyyy"));
        xmlWriter.writeAttribute("lastRegionNumber",QString::number(regionNumber));
    }
}


/*!
 *\brief saves the format of the screen chosen
 *\param QString format
 *\param QString width
 *\param QString height
 *\return void
 */
void SaveProject::saveScreenFormat(QString format,QString width,QString height)
{
    xmlWriter.writeAttribute("format",format);

    if(format == "Other"){
        xmlWriter.writeAttribute("width",width);
        xmlWriter.writeAttribute("height",height);
    }
}


/*!
 *\brief saves the list of medias imported
 *\param QTableWidget *videoList
 *\param QTableWidget *audioList
 *\param QListWidget *imageList
 *\param QListWidget *textList
 *\param QListWidget *luaList
 *\param QListWidget *uriList
 *\param QList<QDir*> importVideoList
 *\param QList<QDir*> importAudioList
 *\param QList<QDir*> importImageList
 *\param QList<QDir*> importTextList
 *\param QList<QDir*> importLuaList
 *\param QStringList importUriList
 *\return void
 */
void SaveProject::saveImports(QTableWidget *videoList,QTableWidget *audioList,QListWidget *imageList,QListWidget *textList,QListWidget *luaList,QListWidget *uriList,QList<QDir*> importVideoList,QList<QDir*> importAudioList,QList<QDir*> importImageList,QList<QDir*> importTextList,QList<QDir*> importLuaList,QStringList importUriList)
{
    QString name;
    QString duration;
    QDir dirFile(file.fileName());
    xmlWriter.writeStartElement("Imports");
    xmlWriter.writeStartElement("videoList");
    for(int i = 0; i < videoList->rowCount();i++){
        name = videoList->item(i,0)->text();
        duration = videoList->item(i,1)->text();
        xmlWriter.writeEmptyElement("Video");
        xmlWriter.writeAttribute("name",name);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(importVideoList.at(i)->absolutePath()).remove(0,3));
        xmlWriter.writeAttribute("duration",duration);
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("audioList");
    for(int i = 0; i < audioList->rowCount();i++){
        name = audioList->item(i,0)->text();
        duration = audioList->item(i,1)->text();
        xmlWriter.writeEmptyElement("Audio");
        xmlWriter.writeAttribute("name",name);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(importAudioList.at(i)->absolutePath()).remove(0,3));
        xmlWriter.writeAttribute("duration",duration);
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("imageList");
    for(int i = 0; i < imageList->count();i++){
        name = imageList->item(i)->text();
        xmlWriter.writeEmptyElement("Imagen");
        xmlWriter.writeAttribute("name",name);

        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(importImageList.at(i)->absolutePath()).remove(0,3));
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("textList");
    for(int i = 0; i < textList->count();i++){
        name = textList->item(i)->text();
        xmlWriter.writeEmptyElement("Texto");
        xmlWriter.writeAttribute("name",name);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(importTextList.at(i)->absolutePath()).remove(0,3));
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("luaList");
    for(int i = 0; i < luaList->count();i++){
        name = luaList->item(i)->text();
        xmlWriter.writeEmptyElement("Lua");
        xmlWriter.writeAttribute("name",name);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(importLuaList.at(i)->absolutePath()).remove(0,3));
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeStartElement("uriList");
    for(int i = 0; i < uriList->count();i++){
        name = uriList->item(i)->text();
        xmlWriter.writeEmptyElement("Uri");
        xmlWriter.writeAttribute("name",name);
        xmlWriter.writeAttribute("src",importUriList.at(i));
    }
    xmlWriter.writeEndElement();
    xmlWriter.writeEndElement();
}


/*!
 *\brief saves all medias assigned to a region
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaLuaList
 *\param QList<Media*> mediaUriList
 *\param QTableWidget *mediasUsadosList
 *\return void
 */
void SaveProject::saveMedias(QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QTableWidget *mediasUsadosList)
{
    QString id;
    QString src;
    QString descriptor;
    QString used;
    QString originalDuration;
    QDir dirFile(file.fileName());
    xmlWriter.writeStartElement("Medias");
    for(int i = 0; i < mediaVideoList.count();i++){
        id = mediaVideoList.at(i)->getId();
        src = mediaVideoList.at(i)->getSrc();
        descriptor = mediaVideoList.at(i)->getDescriptor();
        originalDuration = mediaVideoList.at(i)->getOriginalDuration();
        xmlWriter.writeEmptyElement("Media");
        xmlWriter.writeAttribute("id",id);

        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(src).remove(0,3));
        xmlWriter.writeAttribute("descriptor",descriptor);
        xmlWriter.writeAttribute("originalDuration",originalDuration);

        for(int j = 0; j<mediasUsadosList->rowCount();j++){
            if(mediasUsadosList->item(j,0)->text()==id){
                if(mediasUsadosList->item(j,1)->checkState() == Qt::Checked){
                    used = "yes";
                }else{
                    used = "no";
                }
            }
        }
        xmlWriter.writeAttribute("type","Video");
        xmlWriter.writeAttribute("used",used);
    }

    for(int i = 0; i < mediaAudioList.count();i++){
        id = mediaAudioList.at(i)->getId();
        src = mediaAudioList.at(i)->getSrc();
        descriptor = mediaAudioList.at(i)->getDescriptor();
        originalDuration = mediaAudioList.at(i)->getOriginalDuration();
        xmlWriter.writeEmptyElement("Media");
        xmlWriter.writeAttribute("id",id);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(src).remove(0,3));
        xmlWriter.writeAttribute("descriptor",descriptor);
        xmlWriter.writeAttribute("originalDuration",originalDuration);

        for(int j = 0; j<mediasUsadosList->rowCount();j++){
            if(mediasUsadosList->item(j,0)->text()==id){
                if(mediasUsadosList->item(j,1)->checkState() == Qt::Checked){
                    used = "yes";
                }else{
                    used = "no";
                }
            }
        }
        xmlWriter.writeAttribute("type","Audio");
        xmlWriter.writeAttribute("used",used);
    }

    for(int i = 0; i < mediaImageList.count();i++){
        id = mediaImageList.at(i)->getId();
        src = mediaImageList.at(i)->getSrc();
        descriptor = mediaImageList.at(i)->getDescriptor();
        xmlWriter.writeEmptyElement("Media");
        xmlWriter.writeAttribute("id",id);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(src).remove(0,3));
        xmlWriter.writeAttribute("descriptor",descriptor);

        for(int j = 0; j<mediasUsadosList->rowCount();j++){
            if(mediasUsadosList->item(j,0)->text()==id){
                if(mediasUsadosList->item(j,1)->checkState() == Qt::Checked){
                    used = "yes";
                }else{
                    used = "no";
                }
            }
        }
        xmlWriter.writeAttribute("type","Imagen");
        xmlWriter.writeAttribute("used",used);
    }

    for(int i = 0; i < mediaTextList.count();i++){
        id = mediaTextList.at(i)->getId();
        src = mediaTextList.at(i)->getSrc();
        descriptor = mediaTextList.at(i)->getDescriptor();
        xmlWriter.writeEmptyElement("Media");
        xmlWriter.writeAttribute("id",id);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(src).remove(0,3));
        xmlWriter.writeAttribute("descriptor",descriptor);

        for(int j = 0; j<mediasUsadosList->rowCount();j++){
            if(mediasUsadosList->item(j,0)->text()==id){
                if(mediasUsadosList->item(j,1)->checkState() == Qt::Checked){
                    used = "yes";
                }else{
                    used = "no";
                }
            }
        }
        xmlWriter.writeAttribute("type","Texto");
        xmlWriter.writeAttribute("used",used);
    }

    for(int i = 0; i < mediaLuaList.count();i++){
        id = mediaLuaList.at(i)->getId();
        src = mediaLuaList.at(i)->getSrc();
        descriptor = mediaLuaList.at(i)->getDescriptor();
        xmlWriter.writeEmptyElement("Media");
        xmlWriter.writeAttribute("id",id);
        xmlWriter.writeAttribute("src",dirFile.relativeFilePath(src).remove(0,3));
        xmlWriter.writeAttribute("descriptor",descriptor);

        for(int j = 0; j<mediasUsadosList->rowCount();j++){
            if(mediasUsadosList->item(j,0)->text()==id){
                if(mediasUsadosList->item(j,1)->checkState() == Qt::Checked){
                    used = "yes";
                }else{
                    used = "no";
                }
            }
        }
        xmlWriter.writeAttribute("type","Lua");
        xmlWriter.writeAttribute("used",used);
    }

    for(int i = 0; i < mediaUriList.count();i++){
        id = mediaUriList.at(i)->getId();
        src = mediaUriList.at(i)->getSrc();
        descriptor = mediaUriList.at(i)->getDescriptor();
        xmlWriter.writeEmptyElement("Media");
        xmlWriter.writeAttribute("id",id);
        xmlWriter.writeAttribute("src",src);
        xmlWriter.writeAttribute("descriptor",descriptor);

        for(int j = 0; j<mediasUsadosList->rowCount();j++){
            if(mediasUsadosList->item(j,0)->text()==id){
                if(mediasUsadosList->item(j,1)->checkState() == Qt::Checked){
                    used = "yes";
                }else{
                    used = "no";
                }
            }
        }

        xmlWriter.writeAttribute("type","Uri");
        xmlWriter.writeAttribute("used",used);
    }
    xmlWriter.writeEndElement();
}


/*!
 *\brief saves the \b descriptor and his attributes
 *\param QList<Descriptor*> &descriptorList
 *\return void
 */
void SaveProject::saveDescriptiors(QList<Descriptor*> &descriptorList)
{
    QString descriptor;
    QString id;
    QString player;
    QString explicitDur;
    QString region;
    QString freeze;
    QString moveLeft;
    QString moveRight;
    QString moveUp;
    QString moveDown;
    QString focusIndex;
    QString focusBorderColor;
    QString focusBorderWidth;
    QString focusBorderTransparency;
    QString focusSrc;
    QString focusSelSrc;
    QString selBorderColor;
    QString transIn;
    QString transOut;
    QString descriptorParam;

    xmlWriter.writeStartElement("Descriptors");
    for(int i = 0; i < descriptorList.count();i++){
        descriptor = descriptorList.at(i)->getDescriptor();
        id = descriptorList.at(i)->getId();
        explicitDur = descriptorList.at(i)->getExplicitDur();
        region = descriptorList.at(i)->getRegion();
        moveLeft = descriptorList.at(i)->getMoveLeft();
        moveRight = descriptorList.at(i)->getMoveRight();
        moveUp = descriptorList.at(i)->getMoveUp();
        moveDown  = descriptorList.at(i)->getMoveDown();
        focusIndex = descriptorList.at(i)->getFocusIndex();
        focusBorderColor = descriptorList.at(i)->getFocusBorderColor();
        focusBorderWidth = descriptorList.at(i)->getFocusBorderWidth();
        focusBorderTransparency = descriptorList.at(i)->getFocusBorderTransparency();
        focusSrc = descriptorList.at(i)->getFocusSrc();
        focusSelSrc = descriptorList.at(i)->getFocusSelSrc();
        selBorderColor = descriptorList.at(i)->getSelBorderColor();
        descriptorParam = descriptorList.at(i)->getDescriptorParam();

        xmlWriter.writeStartElement("Descriptor");
        xmlWriter.writeAttribute("id", id);
        xmlWriter.writeAttribute("explicitDur", explicitDur);
        xmlWriter.writeAttribute("region", region);
        xmlWriter.writeAttribute("moveLeft", moveLeft);
        xmlWriter.writeAttribute("moveRight", moveRight);
        xmlWriter.writeAttribute("moveUp", moveUp);
        xmlWriter.writeAttribute("moveDown", moveDown);
        xmlWriter.writeAttribute("focusIndex", focusIndex);
        xmlWriter.writeAttribute("focusBorderColor", focusBorderColor);
        xmlWriter.writeAttribute("focusBorderWidth", focusBorderWidth);
        xmlWriter.writeAttribute("focusBorderTransparency", focusBorderTransparency);
        xmlWriter.writeAttribute("focusSrc", focusSrc);
        xmlWriter.writeAttribute("focusSelSrc", focusSelSrc);
        xmlWriter.writeAttribute("selBorderColor", selBorderColor);
        xmlWriter.writeAttribute("descriptorParam", descriptorParam);

        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
}


/*!
 *\brief saves all regions
 *\param QList<QGraphicsItem*> regions
 *\return void
 */
void SaveProject::saveRectangles(QList<QGraphicsItem*> regions)
{
    QString name;
    QGraphicsItem *item;
    GraphicsRectItem *rectItem;
    xmlWriter.writeStartElement("Regions");
    for(int i = regions.size()-1; i > -1;i--){
        item = regions.at(i);
        if(item->type()==5){
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(item);
            name = rectItem->getName();
            xmlWriter.writeStartElement("Region");
            xmlWriter.writeAttribute("name",name);

            if (item->parentItem() != 0){
                GraphicsRectItem *parent =  qgraphicsitem_cast<GraphicsRectItem *>(item->parentItem());
                xmlWriter.writeAttribute("parent",parent->getName());
            }

            if(rectItem->getXRecNCL()=="")
                xmlWriter.writeAttribute("x",QString::number(item->x()));
            else
                xmlWriter.writeAttribute("x",rectItem->getXRecNCL());

            if(rectItem->getYRecNCL()=="")
                xmlWriter.writeAttribute("y",QString::number(item->y()));
            else
                xmlWriter.writeAttribute("y",rectItem->getYRecNCL());

            if(rectItem->getWidthRecNCL()=="")
                xmlWriter.writeAttribute("width",QString::number(rectItem->getWidthRec()));
            else
                xmlWriter.writeAttribute("width",rectItem->getWidthRecNCL());

            if(rectItem->getHeighRecNCL()=="")
                xmlWriter.writeAttribute("height",QString::number(rectItem->getHeightRec()));
            else
                xmlWriter.writeAttribute("height",rectItem->getHeighRecNCL());

            xmlWriter.writeAttribute("zIndex",QString::number(item->zValue()));

            for(int i = 0;i<rectItem->getMedias().count();i++){
                xmlWriter.writeEmptyElement("Media");
                xmlWriter.writeAttribute("id",rectItem->getMedias().at(i));
            }
            xmlWriter.writeEndElement();
        }
    }
    xmlWriter.writeEndElement();
}


/*!
 *\brief saves all arrows(and images) and their relations
 *\param DiagramScene *graphicsSceneTemporal
 *\param DiagramSceneHead *graphicsSceneHead
 *\return void
 */
void SaveProject::saveTimeLines(DiagramScene *graphicsSceneTemporal,DiagramSceneHead *graphicsSceneHead)
{
    QList<QGraphicsItem *> allItems = graphicsSceneTemporal->items();
    Image *imageItem;
    Arrow *arrowItem;
    int lineNumber;

    xmlWriter.writeStartElement("TemporalArea");
    xmlWriter.writeStartElement("TimeLineList");
    for(int i = allItems.size()-1; i > -1;i--){
        if(allItems.at(i)->type() == 7 ){//is imagen
            imageItem =  qgraphicsitem_cast<Image *>(allItems.at(i));
            if(imageItem->getMyType() == Image::InitTermination){
                lineNumber = imageItem->scenePos().y() / LINESIZE;

                xmlWriter.writeEmptyElement("TimeLine");
                xmlWriter.writeAttribute("nameMedia",graphicsSceneHead->NameMediaInLineNumber(lineNumber));

                if(imageItem->parentItem() != 0){
                    lineNumber = imageItem->parentItem()->scenePos().y() / LINESIZE;
                    xmlWriter.writeAttribute("parent",graphicsSceneHead->NameMediaInLineNumber(lineNumber));
                    arrowItem =  qgraphicsitem_cast<Arrow *>(imageItem->getTimeLine()->parentItem());
                    if(arrowItem->getMyType() == Arrow::UnionLineTempInteract)
                        xmlWriter.writeAttribute("typeParent","Interactivity");
                    else
                        xmlWriter.writeAttribute("typeParent","TimeLine");
                }else
                    xmlWriter.writeAttribute("parent","noParent");

                xmlWriter.writeAttribute("posXBegin",QString::number(imageItem->scenePos().x()));
                xmlWriter.writeAttribute("posYBegin",QString::number(imageItem->scenePos().y()));

                arrowItem = qgraphicsitem_cast<Arrow *>(imageItem->getTimeLine());

                xmlWriter.writeAttribute("longTempLineOriginal",arrowItem->getLongTempLineOriginal());                
            }else if(imageItem->getMyType() == Image::EndTermination){
                xmlWriter.writeAttribute("posXEnd",QString::number(imageItem->scenePos().x()));
                xmlWriter.writeAttribute("posYEnd",QString::number(imageItem->scenePos().y()));
            }else if(imageItem->getMyType() == Image::SuspensionPoints){
                xmlWriter.writeAttribute("posXEnd",QString::number(imageItem->scenePos().x()));
                xmlWriter.writeAttribute("posYEnd",QString::number(imageItem->scenePos().y()));
                xmlWriter.writeAttribute("infiniteTimeLine","true");
            }else if(imageItem->getMyType() == Image::InitInteractivityTermination){
                lineNumber = imageItem->scenePos().y() / LINESIZE;

                xmlWriter.writeEmptyElement("InteractivityLine");
                xmlWriter.writeAttribute("nameMedia",graphicsSceneHead->NameMediaInLineNumber(lineNumber));

                xmlWriter.writeAttribute("posXBegin",QString::number(imageItem->scenePos().x()));
                xmlWriter.writeAttribute("posYBegin",QString::number(imageItem->scenePos().y()));
            }else if(imageItem->getMyType() == Image::BotonInteract){
                xmlWriter.writeAttribute("nameButton",imageItem->getKeyButton());
            }else if(imageItem->getMyType() == Image::EndInteractivityTermination){
                xmlWriter.writeAttribute("posXEnd",QString::number(imageItem->scenePos().x()));
                xmlWriter.writeAttribute("posYEnd",QString::number(imageItem->scenePos().y()));
            }
        }
    }    
    xmlWriter.writeEndElement();
    saveButtonProperties(graphicsSceneTemporal);
}


/*!
 *\brief saves the \b ncl properties of each image
 *\param DiagramScene *graphicsSceneTemporal
 *\return void
 */
void SaveProject::saveButtonProperties(DiagramScene *graphicsSceneTemporal)
{
    QList<QGraphicsItem *> allItems = graphicsSceneTemporal->items();
    Image *imageItem;

    xmlWriter.writeStartElement("RoleList");
    for(int i = allItems.size()-1; i > -1;i--){
        if(allItems.at(i)->type() == 7){//is imagen
            imageItem =  qgraphicsitem_cast<Image *>(allItems.at(i));
            if(imageItem->getMyType() == Image::InitTermination || imageItem->getMyType() == Image::EndTermination || imageItem->getMyType() == Image::BotonInteract){
                xmlWriter.writeStartElement("Button");
                xmlWriter.writeAttribute("posXButton",QString::number(imageItem->scenePos().x()));
                xmlWriter.writeAttribute("posYButton",QString::number(imageItem->scenePos().y()));

                if(imageItem->getMyType() == Image::InitTermination)
                    xmlWriter.writeAttribute("typeButton","InitTermination");
                if(imageItem->getMyType() == Image::EndTermination )
                    xmlWriter.writeAttribute("typeButton","EndTermination");
                if(imageItem->getMyType() == Image::BotonInteract)
                    xmlWriter.writeAttribute("typeButton","BotonInteract");

                for(int i = 0 ; i< imageItem->getRoleListPlayList().count();i++){
                    xmlWriter.writeEmptyElement("playList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListPlayList().at(i));
                }
                for(int i = 0 ; i< imageItem->getRoleListStopList().count();i++){
                    xmlWriter.writeEmptyElement("stopList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListStopList().at(i));
                }
                for(int i = 0 ; i< imageItem->getRoleListPauseList().count();i++){
                    xmlWriter.writeEmptyElement("pauseList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListPauseList().at(i));
                }
                for(int i = 0 ; i< imageItem->getRoleListResumeList().count();i++){
                    xmlWriter.writeEmptyElement("resumeList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListResumeList().at(i));
                }
                for(int i = 0 ; i< imageItem->getRoleListAbortList().count();i++){
                    xmlWriter.writeEmptyElement("abortList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListAbortList().at(i));
                }
                for(int i = 0 ; i< imageItem->getRoleListSetList().count();i++){
                    xmlWriter.writeEmptyElement("setList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListSetList().at(i));
                }
                for(int i = 0; i < imageItem->getRoleListsetTableList()->rowCount();i++){
                    xmlWriter.writeEmptyElement("setTableList");
                    xmlWriter.writeAttribute("nameMedia",imageItem->getRoleListsetTableList()->item(i,0)->text());
                    xmlWriter.writeAttribute("propertie",imageItem->getRoleListsetTableList()->item(i,1)->text());
                    xmlWriter.writeAttribute("value",imageItem->getRoleListsetTableList()->item(i,2)->text());
                }
                xmlWriter.writeEndElement();
            }
        }
    }
    xmlWriter.writeEndElement();
}


/*!
 *\brief writes the final of the document and close the file
 *\return void
 */
void SaveProject::endSaveFile()
{
    xmlWriter.writeEndDocument();
    file.close();
}


/*!
 *\brief open the file to reading
 *\return void
 */
void SaveProject::openFile()
{
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){

    }else{
        xmlReader.setDevice(&file);
        srcList.clear();
    }
}


/*!
 *\brief saves the properties of media
 *\param DiagramSceneHead *graphicsSceneHead
 *\return void
 */
void SaveProject::saveDescriptorsParam(DiagramSceneHead *graphicsSceneHead)
{
    QList<QGraphicsItem *> allItems = graphicsSceneHead->items();
    Image *imageItem;
    int lineNumber;

    xmlWriter.writeStartElement("DescriptorsParams");
    for(int i = 0; i < allItems.size();i++){
        if(allItems.at(i)->type() == 7 ){//is imagen
            imageItem =  qgraphicsitem_cast<Image *>(allItems.at(i));
            if(imageItem->getMyType() == Image::TypeMedia){
                lineNumber = imageItem->scenePos().y() / LINESIZE;
                xmlWriter.writeStartElement("MediaName");
                xmlWriter.writeAttribute("nameMedia",graphicsSceneHead->NameMediaInLineNumber(lineNumber));
                xmlWriter.writeAttribute("lineNumber",QString::number(lineNumber));

                for(int j=0; j < imageItem->getDescriptorParamList().count(); j++){
                    xmlWriter.writeEmptyElement("DescriptorParam");
                    xmlWriter.writeAttribute("name",imageItem->getDescriptorParamList().at(j)->getName());
                    xmlWriter.writeAttribute("value",imageItem->getDescriptorParamList().at(j)->getValue());
                }
                xmlWriter.writeEndElement();
            }
        }
    }
    xmlWriter.writeEndElement();
}


/*!
 *\brief recuperates the datas about the project(like date,description,etc)
 *\param QString &projectName
 *\param QString &projectDescription
 *\param QDate &projectDate
 *\return void
 */
void SaveProject::openDescriptionProject(QString &projectName, QString &projectDescription, QDate &projectDate, int &regionNumber)
{
    QStringList values;
    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="Project"){
                projectName = xmlReader.attributes().value("name").toString();
                projectDescription = xmlReader.attributes().value("description").toString();  
                regionNumber = xmlReader.attributes().value("lastRegionNumber").toString().toInt();

                values = xmlReader.attributes().value("date").toString().split("-");
                int year = ((QString) values.at(2)).toInt();
                int month = ((QString) values.at(1)).toInt();
                int day = ((QString) values.at(0)).toInt();
                projectDate.setDate(year,month,day);
                continue;
            }
        }
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief recuperates the format of the screen chosen
 *\param QString &format
 *\param int &width
 *\param int &height
 *\return void
 */
void SaveProject::openScreenFormat(QString &format,int &width,int &height)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    while(!xmlReader.atEnd()){
        xmlReader.readNext();

        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="Project"){
                format = xmlReader.attributes().value("format").toString();
                if(format == "Other"){
                    width = xmlReader.attributes().value("width").toString().toInt();
                    height = xmlReader.attributes().value("height").toString().toInt();
                }
                continue;
            }
        }
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief recuperates the list of the imported medias
 *\param QTableWidget &videoList
 *\param QList<QDir*> &importVideoList
 *\param QTableWidget &audioList
 *\param QList<QDir*> &importAudioList
 *\param QListWidget &imageList
 *\param QList<QDir*> &importImageList
 *\param QListWidget &textList
 *\param QList<QDir*> &importTextList
 *\param QListWidget &luaList
 *\param QList<QDir*> &importLuaList
 *\param  QListWidget &uriList
 *\param QStringList &importUriList
 *\return void
 */
void SaveProject::openImports(QTableWidget &videoList, QList<QDir*> &importVideoList,QTableWidget &audioList, QList<QDir*> &importAudioList, QListWidget &imageList, QList<QDir*> &importImageList,QListWidget &textList, QList<QDir*> &importTextList ,QListWidget &luaList,QList<QDir*> &importLuaList, QListWidget &uriList,QStringList &importUriList)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);

    QDir *dir;
    QString name;
    QString src;
    QString correctSrc = "";
    QString duration;
    QString aux;
    int listIndex = 0;

    QTableWidgetItem *item;
    QListWidgetItem *itemList;

    videoList.clear();
    importVideoList.clear();
    audioList.clear();
    importAudioList.clear();
    imageList.clear();
    importImageList.clear();
    textList.clear();
    importTextList.clear();

    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="videoList"){
                listIndex = 0;
                continue;
            }
            if(xmlReader.name()=="Video"){
                listIndex++;
                name = xmlReader.attributes().value("name").toString();
                src = xmlReader.attributes().value("src").toString();
                duration = xmlReader.attributes().value("duration").toString();

                aux = file.fileName().remove(file.fileName().lastIndexOf("/")+1,file.fileName().count());
                QDir dirAux(aux);
                src = dirAux.absoluteFilePath(src);

                src = getSrc(src,name,"Video",correctSrc,duration);

                dir = new QDir(src);
                importVideoList.append(dir);
                videoList.setRowCount(listIndex);

                item = new QTableWidgetItem();
                item->setText(name);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                item->setToolTip(src);

                videoList.setItem(listIndex-1,0,item);

                item = new QTableWidgetItem();
                item->setText(duration);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                videoList.setItem(listIndex-1,1,item);
                continue;
            }

            if(xmlReader.name()=="audioList"){
                listIndex = 0;
                continue;
            }

            if(xmlReader.name()=="Audio"){
                listIndex++;
                name = xmlReader.attributes().value("name").toString();
                src = xmlReader.attributes().value("src").toString();
                duration = xmlReader.attributes().value("duration").toString();

                aux = file.fileName().remove(file.fileName().lastIndexOf("/")+1,file.fileName().count());
                QDir dirAux(aux);
                src = dirAux.absoluteFilePath(src);

                src = getSrc(src,name,"Audio",correctSrc,duration);

                dir = new QDir(src);
                importAudioList.append(dir);

                audioList.setRowCount(listIndex);

                item = new QTableWidgetItem();
                item->setText(name);
                item->setToolTip(src);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                audioList.setItem(listIndex-1,0,item);

                item = new QTableWidgetItem();
                item->setText(duration);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                audioList.setItem(listIndex-1,1,item);
                continue;
            }

            if(xmlReader.name()=="imageList"){
                listIndex = 0;
                continue;
            }

            if(xmlReader.name()=="Imagen"){
                listIndex++;


                name = xmlReader.attributes().value("name").toString();
                src = xmlReader.attributes().value("src").toString();

                aux = file.fileName().remove(file.fileName().lastIndexOf("/")+1,file.fileName().count());
                QDir dirAux(aux);
                src = dirAux.absoluteFilePath(src);

                src = getSrc(src,name,"Imagen",correctSrc,"0");

                dir = new QDir(src);
                importImageList.append(dir);

                itemList = new QListWidgetItem();
                itemList->setText(name);
                itemList->setToolTip(src);

                imageList.insertItem(listIndex-1,itemList);
                continue;
            }

            if(xmlReader.name()=="textList"){
                listIndex = 0;
                continue;
            }

            if(xmlReader.name()=="Texto"){
                listIndex++;
                name = xmlReader.attributes().value("name").toString();
                src = xmlReader.attributes().value("src").toString();

                aux = file.fileName().remove(file.fileName().lastIndexOf("/")+1,file.fileName().count());
                QDir dirAux(aux);
                src = dirAux.absoluteFilePath(src);

                src = getSrc(src,name,"Texto",correctSrc,"0");

                QDir *dir = new QDir(src);
                importTextList.append(dir);

                itemList = new QListWidgetItem();
                itemList->setText(name);
                itemList->setToolTip(src);

                textList.insertItem(listIndex-1,itemList);
                continue;
            }

            if(xmlReader.name()=="luaList"){
                listIndex = 0;
                continue;
            }

            if(xmlReader.name()=="Lua"){
                listIndex++;
                name = xmlReader.attributes().value("name").toString();
                src = xmlReader.attributes().value("src").toString();

                aux = file.fileName().remove(file.fileName().lastIndexOf("/")+1,file.fileName().count());
                QDir dirAux(aux);
                src = dirAux.absoluteFilePath(src);

                src = getSrc(src,name,"Lua",correctSrc,"0");

                QDir *dir = new QDir(src);
                importLuaList.append(dir);

                itemList = new QListWidgetItem();
                itemList->setText(name);
                itemList->setToolTip(src);

                luaList.insertItem(listIndex-1,itemList);
                continue;
            }

            if(xmlReader.name()=="uriList"){
                listIndex = 0;
                continue;
            }

            if(xmlReader.name()=="Uri"){
                listIndex++;
                name = xmlReader.attributes().value("name").toString();
                src = xmlReader.attributes().value("src").toString();

                importUriList.append(src);

                itemList = new QListWidgetItem();
                itemList->setText(name);
                itemList->setToolTip(src);

                uriList.insertItem(listIndex-1,itemList);
                continue;
            }
        }
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief verifys if file path \a srs is present in the file systems. If is not present emit a signal \a fileNotFound to chose a new path
 *\param QString src
 *\param QString name
 *\param QString type
 *\param QString &correctSrc
 *\param QString duration
 *\return QString
 */
QString SaveProject::getSrc(QString src, QString name, QString type, QString &correctSrc, QString duration)
{
    QString srcAux;
    QFile *file = new QFile(src);
    QDir dir(this->file.fileName());
    if(!file->exists()){
        if(correctSrc != ""){
            file = new QFile(correctSrc+name);
            if(!file->exists()){
                srcList.append(src);
                src = emit fileNotFound(name, src, type, duration);
                srcList.append(src);
                srcAux = src;
                correctSrc = srcAux.remove(src.lastIndexOf('/')+1,src.count());
            }else{
                srcList.append(src);
                srcList.append(correctSrc+name);
                src = correctSrc+name;
            }
        }else{
            srcList.append(src);
            src = emit fileNotFound(name, src, type, duration);
            srcList.append(src);
            srcAux = src;
            correctSrc = srcAux.remove(src.lastIndexOf('/')+1,src.count());
        }

    }


    return src;
}

/*!
 *\brief recuperates the medias assigned to a region
 *\param QList<Media*> &mediaVideoList
 *\param QList<Media*> &mediaAudioList
 *\param QList<Media*> &mediaImageList
 *\param QList<Media*> &mediaTextList
 *\param QList<Media*> &mediaLuaList
 *\param QList<Media*> &mediaUriList
 *\param QTableWidget &mediasUsadosList
 *\return void
 */
void SaveProject::openMedias(QList<Media*> &mediaVideoList,QList<Media*> &mediaAudioList,QList<Media*> &mediaImageList,QList<Media*> &mediaTextList,QList<Media*> &mediaLuaList,QList<Media*> &mediaUriList,QTableWidget &mediasUsadosList)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    Media *media;
    QString id;
    QString src;
    QString descriptor;
    QString type;
    QString used;
    QString originalDuration;
    QString duration;
    QTableWidgetItem *item;
    QString correctSrc = "";
    QString name = "";
    QString srcAux = "";
    QString aux;

    while(!xmlReader.atEnd()){
        xmlReader.readNext();

        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="Medias") continue;
            if(xmlReader.name()=="Media"){
                id = xmlReader.attributes().value("id").toString();;
                src= xmlReader.attributes().value("src").toString();;
                descriptor = xmlReader.attributes().value("descriptor").toString();;
                type = xmlReader.attributes().value("type").toString();;
                used = xmlReader.attributes().value("used").toString();;
                originalDuration = xmlReader.attributes().value("originalDuration").toString();
                duration = originalDuration;


                aux = file.fileName().remove(file.fileName().lastIndexOf("/")+1,file.fileName().count());
                QDir dirAux(aux);
                src = dirAux.absoluteFilePath(src);


                src = getNewSrc(src);

                srcAux = src;
                name = srcAux.remove(0,src.lastIndexOf('/')+1);

                QString srcAux;
                QFile *file = new QFile(src);
                if(!file->exists()){
                    if(correctSrc != ""){
                        file = new QFile(correctSrc+name);
                        if(!file->exists()){
                            srcList.append(src);
                            src = emit fileNotFound(name, src, type, duration);
                            srcList.append(src);
                            srcAux = src;
                            correctSrc = srcAux.remove(src.lastIndexOf('/')+1,src.count());
                        }else{
                            srcList.append(src);
                            srcList.append(correctSrc+name);
                            src = correctSrc+name;
                        }
                    }else{
                        srcList.append(src);
                        src = emit fileNotFound(name, src, type, duration);
                        srcList.append(src);
                        srcAux = src;
                        correctSrc = srcAux.remove(src.lastIndexOf('/')+1,src.count());
                    }
                }

                media = new Media(id,duration);
                media->setSrc(src);
                media->setDescriptor(descriptor);
                //media->setType(type);

                if(type == "Video"){
                    mediaVideoList.append(media);
                }
                if(type == "Audio"){
                    mediaAudioList.append(media);
                }
                if(type == "Imagen"){
                    mediaImageList.append(media);
                }
                if(type == "Texto"){
                    mediaTextList.append(media);
                }
                if(type == "Lua"){
                    mediaLuaList.append(media);
                }
                if(type == "Uri"){
                    mediaUriList.append(media);
                }

                mediasUsadosList.setRowCount(mediasUsadosList.rowCount()+1);
                int index = mediasUsadosList.rowCount()-1;

                item = new QTableWidgetItem();
                item->setText(id);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                item->setToolTip(src);

                mediasUsadosList.setItem(index,0,item);

                item = new QTableWidgetItem();
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                if(used == "yes"){
                    item->setCheckState(Qt::Checked);
                    mediasUsadosList.setItem(index, 1, item);
                }else{
                    item->setCheckState(Qt::Unchecked);
                    mediasUsadosList.setItem(index, 1, item);
                }

                item = new QTableWidgetItem();
                item->setText(duration);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                item->setToolTip(src);
                mediasUsadosList.setItem(index,2,item);

                item = new QTableWidgetItem();
                item->setText(type);
                item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                item->setToolTip(src);
                mediasUsadosList.setItem(index,3,item);
            }
        }
        if(xmlReader.isEndElement() && xmlReader.name() == "Medias") break;
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief opens the \b descriptor with his attributes to assign to a \a descriptorList
 *\param QList<Descriptor*> &descriptorList
 *\return void
 */
void SaveProject::openDescriptiors(QList<Descriptor*> &descriptorList)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    QString descriptor;
    QString id;
    QString player;
    QString explicitDur;
    QString region;
    QString freeze;
    QString moveLeft;
    QString moveRight;
    QString moveUp;
    QString moveDown;
    QString focusIndex;
    QString focusBorderColor;
    QString focusBorderWidth;
    QString focusBorderTransparency;
    QString focusSrc;
    QString focusSelSrc;
    QString selBorderColor;
    QString transIn;
    QString transOut;
    QString descriptorParam;

    descriptorList.clear();
    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="Descriptors") continue;
            if(xmlReader.name()=="Descriptor"){
                id = xmlReader.attributes().value("id").toString();
                explicitDur = xmlReader.attributes().value("explicitDur").toString();
                region = xmlReader.attributes().value("region").toString();
                moveLeft = xmlReader.attributes().value("moveLeft").toString();
                moveRight = xmlReader.attributes().value("moveRight").toString();
                moveUp = xmlReader.attributes().value("moveUp").toString();
                moveDown = xmlReader.attributes().value("moveDown").toString();
                focusIndex = xmlReader.attributes().value("focusIndex").toString();
                focusBorderColor = xmlReader.attributes().value("focusBorderColor").toString();
                focusBorderWidth = xmlReader.attributes().value("focusBorderWidth").toString();
                focusBorderTransparency = xmlReader.attributes().value("focusBorderTransparency").toString();
                focusSrc = xmlReader.attributes().value("focusSrc").toString();
                focusSelSrc = xmlReader.attributes().value("focusSelSrc").toString();
                selBorderColor = xmlReader.attributes().value("selBorderColor").toString();
                descriptorParam = xmlReader.attributes().value("descriptorParam").toString();

                Descriptor *descriptor = new Descriptor(id);

                if(explicitDur != "")
                    descriptor->setExplicitDur(explicitDur);
                if(region != "")
                    descriptor->setRegion(region);
                if(moveLeft != "")
                    descriptor->setMoveLeft(moveLeft);
                if(moveRight != "")
                    descriptor->setMoveRight(moveRight);
                if(moveUp != "")
                    descriptor->setMoveUp(moveUp);
                if(moveDown != "")
                    descriptor->setMoveDown(moveDown);
                if(focusIndex != "")
                    descriptor->setFocusIndex(focusIndex);
                if(focusBorderColor != "")
                    descriptor->setFocusBorderColor(focusBorderColor);
                if(focusBorderWidth != "")
                    descriptor->setFocusBorderWidth(focusBorderWidth);
                if(focusBorderTransparency != "")
                    descriptor->setFocusBorderTransparency(focusBorderTransparency);
                if(focusSrc != "")
                    descriptor->setFocusSrc(focusSrc);
                if(focusSelSrc != "")
                    descriptor->setFocusSelSrc(focusSelSrc);
                if(selBorderColor != "")
                    descriptor->setSelBorderColor(selBorderColor);                
                descriptorList.append(descriptor);
                continue;
            }
        }
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief recuperates all regions
 *\param GraphicsScene &graphicsScene
 *\param int screenSizeX
 *\param int screenSizeY
 *\return void
 */
void SaveProject::openRectangles(GraphicsScene &graphicsScene, int screenSizeX,int screenSizeY)
{
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    bool mediaRegions = false;
    QString name = "";
    QString parentName = "";
    QString ejeX = "";
    QString ejeY = "";
    QString width = "";
    QString height = "";
    QString percent;
    bool xPercent = false;
    bool yPercent = false;
    bool wPercent = false;
    bool hPercent = false;
    qreal x = 0;
    qreal y = 0;
    qreal w = 0;
    qreal h = 0;
    int i = 0;
    QString id = "";
    qreal z;
    GraphicsRectItem *rectItem;

    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="Regions"){
                mediaRegions = true;
                continue;
            }
            if(xmlReader.name()=="Region"){
                i++;
                name = xmlReader.attributes().value("name").toString();
                bool ok,okay;
                okay=true;
                ejeX = xmlReader.attributes().value("x").toString();
                okay&=ok;
                ejeY = xmlReader.attributes().value("y").toString();
                okay&=ok;
                z=xmlReader.attributes().value("zIndex").toString().toDouble(&ok);;
                okay&=ok;
                width = xmlReader.attributes().value("width").toString();
                okay&=ok;
                height = xmlReader.attributes().value("height").toString();
                okay&=ok;
                parentName = xmlReader.attributes().value("parent").toString();
                okay&=ok;

                if(parentName!=""){
                    foreach (QGraphicsItem *itemScene, graphicsScene.items()) {
                        if(itemScene->type() == 5){
                            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(itemScene);
                            if (rectItem->getName()==parentName){

                                if(ejeX.contains("%")){
                                    rectItem->setXNCL(ejeX);
                                    percent = ejeX.remove("%");
                                    x = (percent.toInt()*rectItem->getWidthRec())/100;
                                    xPercent = true;
                                }else{
                                    x = ejeX.toDouble();
                                    xPercent = false;
                                }

                                if(ejeY.contains("%")){
                                    rectItem->setYNCL(ejeY);
                                    percent = ejeY.remove("%");
                                    y = (percent.toInt()*rectItem->getHeightRec())/100;
                                    yPercent = true;
                                }else{
                                    y = ejeY.toDouble();
                                    yPercent = false;
                                }

                                if(width.contains("%")){
                                    rectItem->setWidthNCL(width);
                                    percent = width.remove("%");
                                    w = (percent.toInt()*rectItem->getWidthRec())/100;
                                    wPercent = true;
                                }else{
                                    w = width.toDouble();
                                    wPercent = false;
                                }

                                if(height.contains("%")){
                                    rectItem->setHeighNCL(height);
                                    percent = height.remove("%");
                                    h = (percent.toInt()*rectItem->getHeightRec())/100;
                                    hPercent = true;
                                }else{
                                    h = height.toDouble();
                                    hPercent = false;
                                }

                                graphicsScene.insertItem(name,x,y,w,h,z,rectItem);

                                if(xPercent)
                                    ejeX = ejeX+"%";
                                if(yPercent)
                                    ejeY = ejeY+"%";
                                if(wPercent)
                                    width = width+"%";
                                if(hPercent)
                                    height = height+"%";

                                graphicsScene.getSelected()->setXNCL(ejeX);
                                graphicsScene.getSelected()->setYNCL(ejeY);
                                graphicsScene.getSelected()->setWidthNCL(width);
                                graphicsScene.getSelected()->setHeighNCL(height);

                                parentName = "";
                            }
                        }
                     }
                }else{
                    if(ejeX.contains("%")){
                        percent = ejeX.remove("%");
                        x = (percent.toInt()*screenSizeX)/100;
                        xPercent = true;
                    }else{
                        x = ejeX.toDouble();
                        xPercent = false;
                    }

                    if(ejeY.contains("%")){
                        percent = ejeY.remove("%");
                        y = (percent.toInt()*screenSizeX)/100;
                        yPercent = true;
                    }else{
                        y = ejeY.toDouble();
                        yPercent = false;
                    }

                    if(width.contains("%")){
                        wPercent = true;
                        percent = width.remove("%");
                        w = (percent.toInt()*screenSizeX)/100;
                    }else{
                        w = width.toDouble();
                        wPercent = false;
                    }

                    if(height.contains("%")){
                        percent = height.remove("%");
                        h = (percent.toInt()*screenSizeY)/100;
                        hPercent = true;
                    }else{
                        h = height.toDouble();
                        hPercent = false;
                    }

                    graphicsScene.insertItem(name,x,y,w,h,z,0);

                    if(xPercent)
                        ejeX = ejeX+"%";
                    if(yPercent)
                        ejeY = ejeY+"%";
                    if(wPercent)
                        width = width+"%";
                    if(hPercent)
                        height = height+"%";

                    graphicsScene.getSelected()->setXNCL(ejeX);
                    graphicsScene.getSelected()->setYNCL(ejeY);
                    graphicsScene.getSelected()->setWidthNCL(width);
                    graphicsScene.getSelected()->setHeighNCL(height);
                }
            }
            if(xmlReader.name()=="Media" && mediaRegions){
                id = xmlReader.attributes().value("id").toString();
                graphicsScene.getSelected()->addMedia(id);
            }
            continue;
        }
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief recuperates the arrows(and images) and builds the timeLine view
 *\param DiagramScene *graphicsSceneTemporal
 *\param QTableWidget *mediasUsadosList
 *\return void
 */
void SaveProject::openTimeLines(DiagramScene *graphicsSceneTemporal , QTableWidget *mediasUsadosList)
{
    QString nameMedia,parent,typeParent,posXBegin,posYBegin,itemHaveRombo,posXEnd,posYEnd,posXButton,posYButton,nameButton,originalDuration,infiniteTimeLine;
    bool infinite;
    Arrow *firstArrow;
    int linesAmount = 1;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    QImage image;
    qreal duration;
    qreal widthItem = 2.5;
    Arrow* arrowCerca;
    bool haveOriginalDuration;
    bool thereAreArrows = false;

    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="TemporalArea") continue;
            else if(xmlReader.name()=="TimeLineList") continue;
            else if(xmlReader.name()=="TimeLine"){
                infiniteTimeLine ="";
                nameMedia = xmlReader.attributes().value("nameMedia").toString();
                parent = xmlReader.attributes().value("parent").toString();
                posXBegin = xmlReader.attributes().value("posXBegin").toString();
                posYBegin =  xmlReader.attributes().value("posYBegin").toString();
                itemHaveRombo = xmlReader.attributes().value("itemHaveRombo").toString();
                posXEnd = xmlReader.attributes().value("posXEnd").toString();
                posYEnd= xmlReader.attributes().value("posYEnd").toString();
                infiniteTimeLine = xmlReader.attributes().value("infiniteTimeLine").toString();
                image = getImage(mediasUsadosList,nameMedia);
                originalDuration = xmlReader.attributes().value("longTempLineOriginal").toString();

                thereAreArrows = true;

                if(infiniteTimeLine == "")
                    infinite = false;
                else
                    infinite = true;

                if(originalDuration == "-1")
                    haveOriginalDuration = false;
                else
                    haveOriginalDuration = true;

                if(parent == "noParent"){
                    duration = posXEnd.toDouble() - posXBegin.toDouble() ;
                    firstArrow = graphicsSceneTemporal->addFirstImage(image,nameMedia,duration,haveOriginalDuration,originalDuration.toDouble(),true,infinite);
                }else{
                    typeParent = xmlReader.attributes().value("typeParent").toString();
                    if(typeParent == "TimeLine"){
                        duration = posXEnd.toDouble() - posXBegin.toDouble() ;
                        graphicsSceneTemporal->setNearArrow(graphicsSceneTemporal->searchArrowNearMause(QPointF(posXBegin.toDouble(),posYBegin.toDouble())));
                        graphicsSceneTemporal->insertImage(image,nameMedia,posXBegin.toDouble()+widthItem,duration,posYBegin.toDouble(),posYEnd.toDouble(),haveOriginalDuration,originalDuration.toDouble(),true,infinite);
                    }else if(typeParent == "Interactivity"){
                        duration = posXEnd.toDouble() - posXBegin.toDouble() ;
                        arrowCerca =  graphicsSceneTemporal->searchArrowNearMause(QPointF(posXBegin.toDouble()-2,posYBegin.toDouble()));
                        graphicsSceneTemporal->setNearArrow(arrowCerca);
                        graphicsSceneTemporal->insertImageWithInteract(image,nameMedia,arrowCerca->getButton(),posYBegin.toDouble(),posYEnd.toDouble(),duration,haveOriginalDuration,originalDuration.toDouble(),true,infinite);
                    }
                }

            }else if(xmlReader.name()=="InteractivityLine"){
                infiniteTimeLine ="";
                nameMedia = xmlReader.attributes().value("nameMedia").toString();
                parent = xmlReader.attributes().value("parent").toString();
                posXBegin = xmlReader.attributes().value("posXBegin").toString();
                posYBegin =  xmlReader.attributes().value("posYBegin").toString();
                posXEnd = xmlReader.attributes().value("posXEnd").toString();
                posYEnd= xmlReader.attributes().value("posYEnd").toString();

                posXButton = xmlReader.attributes().value("posXButton").toString();
                posYButton = xmlReader.attributes().value("posYButton").toString();
                nameButton = xmlReader.attributes().value("nameButton").toString();

                infiniteTimeLine = xmlReader.attributes().value("infiniteTimeLine").toString();

                if(infiniteTimeLine == "")
                    infinite = false;
                else
                    infinite = true;

                graphicsSceneTemporal->setNearArrow(graphicsSceneTemporal->searchArrowNearMause(QPointF(posXBegin.toDouble(),posYBegin.toDouble())));
                graphicsSceneTemporal->insertInteractivity(posXBegin.toDouble(),posYBegin.toDouble(),posXEnd.toDouble(),posYEnd.toDouble(),nameButton,infinite);
            }
        }
    }
    xmlReader.clear();
    file.close();
    if(thereAreArrows){
        openButtonProperties(graphicsSceneTemporal);

        linesAmount = firstArrow->recursiveCountItems(firstArrow, 0);
        graphicsSceneTemporal->setSceneRect(QRectF(0, 0, graphicsSceneTemporal->width(), (linesAmount+1) * LINESIZE));
        graphicsSceneTemporal->setCantLineTotal(linesAmount);
    }
}


/*!
 *\brief recuperates and sets the \b ncl properties of each image
 *\param DiagramScene *graphicsSceneTemporal
 *\return void
 */
void SaveProject::openButtonProperties(DiagramScene *graphicsSceneTemporal)
{
    bool thereIsButtom = false;
    QTableWidgetItem *item = new QTableWidgetItem();
    QString posXButton,posYButton,nameMedia,typeButton,property,value;
    QStringList playList;
    QStringList stopList;
    QStringList pauseList;
    QStringList resumeList;
    QStringList abortList;
    QStringList setList;
    QTableWidget *setTable = new QTableWidget();
    QStringList setListNameMedia;
    QStringList setListPropertie;
    QStringList setListValue;
    Image *currentButton;
    QString typeCurrentButton;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    playList.clear();
    stopList.clear();
    pauseList.clear();
    resumeList.clear();
    abortList.clear();
    setList.clear();
    setListNameMedia.clear();
    setListPropertie.clear();
    setListValue.clear();

    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="TemporalArea") continue;
            else if(xmlReader.name()=="RoleList") continue;
            else if(xmlReader.name()=="Button"){                
                playList.clear();
                stopList.clear();
                pauseList.clear();
                resumeList.clear();
                abortList.clear();
                setList.clear();

                posXButton = xmlReader.attributes().value("posXButton").toString();
                posYButton = xmlReader.attributes().value("posYButton").toString();
                typeButton = xmlReader.attributes().value("typeButton").toString();

                thereIsButtom = false;
                if(graphicsSceneTemporal->itemAt(posXButton.toDouble(),posYButton.toDouble()) != 0){
                    if(graphicsSceneTemporal->itemAt(posXButton.toDouble()+1,posYButton.toDouble()+1)->type() == 7){
                        currentButton =  qgraphicsitem_cast<Image *>(graphicsSceneTemporal->itemAt(posXButton.toDouble()+1,posYButton.toDouble()+1));

                        if(currentButton->getMyType() == Image::InitTermination)
                            typeCurrentButton = "InitTermination";
                        else if(currentButton->getMyType() == Image::EndTermination)
                            typeCurrentButton = "EndTermination";
                        else if(currentButton->getMyType() == Image::BotonInteract)
                            typeCurrentButton = "BotonInteract";

                        if(typeButton == typeCurrentButton){
                            thereIsButtom = true;
                        }
                    }
                }
            }else if(xmlReader.name()=="playList"){
                if(thereIsButtom){
                    nameMedia = xmlReader.attributes().value("nameMedia").toString();
                    playList.append(nameMedia);
                }

            }else if(xmlReader.name()=="stopList" ){
                 if(thereIsButtom){
                     nameMedia = xmlReader.attributes().value("nameMedia").toString();
                     stopList.append(nameMedia);
                 }

            }else if(xmlReader.name()=="pauseList" ){
              if(thereIsButtom){
                  nameMedia = xmlReader.attributes().value("nameMedia").toString();
                  pauseList.append(nameMedia);
              }

            }else if(xmlReader.name()=="resumeList"){
               if(thereIsButtom){
                   nameMedia = xmlReader.attributes().value("nameMedia").toString();
                   resumeList.append(nameMedia);
               }

            }else if(xmlReader.name()=="abortList"){
                if(thereIsButtom){
                    nameMedia = xmlReader.attributes().value("nameMedia").toString();
                    abortList.append(nameMedia);
                }

            }else if(xmlReader.name()=="setList"){
                 if(thereIsButtom){
                     nameMedia = xmlReader.attributes().value("nameMedia").toString();
                     setList.append(nameMedia);
                 }

            }else if(xmlReader.name()=="setTableList"){
                if(thereIsButtom){
                    setListNameMedia.append(xmlReader.attributes().value("nameMedia").toString());
                    setListPropertie.append(xmlReader.attributes().value("propertie").toString());
                    setListValue.append(xmlReader.attributes().value("value").toString());
                }
           }

            if(thereIsButtom){
                setTable = new QTableWidget();
                setTable->setRowCount(setListNameMedia.count());
                setTable->setColumnCount(3);

                for(int i = 0 ; i< setListNameMedia.count();i++){
                    item = new QTableWidgetItem();
                    item->setText(setListNameMedia.at(i));
                    setTable->setItem(i,0,item);

                    item = new QTableWidgetItem();
                    item->setText(setListPropertie.at(i));
                    setTable->setItem(i,1,item);

                    item = new QTableWidgetItem();
                    item->setText(setListValue.at(i));
                    setTable->setItem(i,2,item);
                }

                currentButton->setRoleList(playList,stopList,pauseList,resumeList,abortList,setList,setTable);
                addImage(currentButton,playList,stopList,pauseList,resumeList,abortList,setList,graphicsSceneTemporal);
            }
        }
    }
    xmlReader.clear();
    file.close();
}


/*!
 *\brief returns the image of media \a nameMedia
 *\param QTableWidget * mediasUsadosList
 *\param QString nameMedia
 *\return QImage
 */
QImage SaveProject::getImage(QTableWidget * mediasUsadosList,QString nameMedia)
{
    QImage image;
    for(int i=0; i<mediasUsadosList->rowCount();i++ ){
        if(mediasUsadosList->item(i,0)->text() == nameMedia){
            image = mediasUsadosList->item(i,0)->icon().pixmap(63,50,QIcon::Normal,QIcon::On).toImage();
            break;
        }
    }
    return image;
}


/*!
 *\brief adds images like properties to another images(butons)
 *\param Image* boton
 *\param QStringList playList
 *\param QStringList stopList
 *\param QStringList pauseList
 *\param QStringList resumeList
 *\param QStringList abortList
 *\param QStringList setList
 *\param DiagramScene *graphicsSceneTemporal
 *\return void
 */
void SaveProject::addImage(Image* boton , QStringList playList,QStringList stopList,QStringList pauseList , QStringList resumeList, QStringList abortList,QStringList setList,DiagramScene *graphicsSceneTemporal)
{
    if(playList.count() > 0){
        if(boton->getMyType() == Image::BotonInteract)
            imageLocation("/icons/start.png",boton,boton->boundingRect().width(), -2,1,graphicsSceneTemporal);
        else if(boton->getMyType() == Image::EndTermination || boton->getMyType() == Image::InitTermination)
            imageLocation("/icons/start.png",boton,boton->boundingRect().width(), -2,1,graphicsSceneTemporal);
        else
            imageLocation("/icons/start.png",boton,(boton->boundingRect().width()/2)-6,-12,1,graphicsSceneTemporal);
    }
    if(stopList.count() > 0){
        if(boton->getMyType() == Image::BotonInteract)
            imageLocation("/icons/stop.png",boton,boton->boundingRect().width(), boton->boundingRect().height() -10,2,graphicsSceneTemporal);
        else if(boton->getMyType() == Image::EndTermination || boton->getMyType() == Image::InitTermination)
            imageLocation("/icons/stop.png",boton,boton->boundingRect().width(), 11,2,graphicsSceneTemporal);
        else
            imageLocation("/icons/stop.png",boton,(boton->boundingRect().width()/2)-18 ,-12,2,graphicsSceneTemporal);
    }

    if(pauseList.count() > 0){
        if(boton->getMyType() == Image::BotonInteract)
            imageLocation("/icons/pause.png",boton,-12, -2,3,graphicsSceneTemporal);
        else if(boton->getMyType() == Image::EndTermination || boton->getMyType() == Image::InitTermination)
            imageLocation("/icons/pause.png",boton,boton->boundingRect().width(), boton->boundingRect().height() -9,3,graphicsSceneTemporal);
        else
            imageLocation("/icons/pause.png",boton,(boton->boundingRect().width()/2)-30, -12,3,graphicsSceneTemporal);
    }

    if(resumeList.count() > 0){
        if(boton->getMyType() == Image::BotonInteract)
            imageLocation("/icons/resume.png",boton,-12, boton->boundingRect().height() - 10,4,graphicsSceneTemporal);
        else if(boton->getMyType() == Image::EndTermination || boton->getMyType() == Image::InitTermination)
            imageLocation("/icons/resume.png",boton,-12, boton->boundingRect().height() - 10,4,graphicsSceneTemporal);
        else
            imageLocation("/icons/resume.png",boton,(boton->boundingRect().width()/2)-42,-12,4,graphicsSceneTemporal);
    }

    if(abortList.count() > 0){
        if(boton->getMyType() == Image::BotonInteract)
            imageLocation("/icons/abort.png",boton,boton->boundingRect().width() - 10 , -12,5,graphicsSceneTemporal);
        else if(boton->getMyType() == Image::EndTermination || boton->getMyType() == Image::InitTermination)
            imageLocation("/icons/abort.png",boton,-12 , -2,5,graphicsSceneTemporal);
        else
            imageLocation("/icons/abort.png",boton,(boton->boundingRect().width()/2)+ 6 , -12,5,graphicsSceneTemporal);
    }

    if(setList.count() > 0){
        if(boton->getMyType() == Image::BotonInteract)
            imageLocation("/icons/set.png",boton,-2, -12,6,graphicsSceneTemporal);
        else if(boton->getMyType() == Image::EndTermination || boton->getMyType() == Image::InitTermination)
            imageLocation("/icons/set.png",boton,-4, boton->boundingRect().height(),6,graphicsSceneTemporal);
        else
            imageLocation("/icons/set.png",boton,(boton->boundingRect().width()/2) +18 , -12,6,graphicsSceneTemporal);
    }
}


/*!
 *\brief sets the type of the image and location of images added with \a addImage
 *\param QString path
 *\param Image *boton
 *\param qreal posX
 *\param qreal posY
 *\param qreal zvalue
 *\param DiagramScene *graphicsSceneTemporal
 *\return void
 */
void SaveProject::imageLocation(QString path, Image *boton,qreal posX, qreal posY,qreal zvalue,DiagramScene *graphicsSceneTemporal)
{
    Image* playImage;
    QImage image(QDir::currentPath()+path);
    image = image.scaled(12,12);
    QPixmap pixTmp(QPixmap::fromImage(image));
    playImage = new Image(pixTmp);
    graphicsSceneTemporal->addItem(playImage);
    playImage->setParentItem(boton);
    playImage->setPos(posX, posY);
    playImage->setZValue(zvalue);
}


/*!
 *\brief recuperates the properties of media
 *\param DiagramSceneHead *graphicsSceneHead
 *\return void
 */
void SaveProject::openDescriptorsParam(DiagramSceneHead *graphicsSceneHead)
{
    QString nameMedia,name,value,lineNumber;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    xmlReader.setDevice(&file);
    Image *currentImage;
    DescriptorParam *descriptorParam;

    while(!xmlReader.atEnd()){
        xmlReader.readNext();
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="DescriptorsParams") continue;
            else if(xmlReader.name()=="MediaName"){
                nameMedia = xmlReader.attributes().value("nameMedia").toString();
                lineNumber = xmlReader.attributes().value("lineNumber").toString();
                currentImage = graphicsSceneHead->MediaInLineNumber(lineNumber.toInt());
            }else if(xmlReader.name()=="DescriptorParam"){
                name = xmlReader.attributes().value("name").toString();
                value = xmlReader.attributes().value("value").toString();
                descriptorParam = new DescriptorParam(name,value);
                currentImage->addtDescriptorParamToList(descriptorParam);
            }
        }
    }
    xmlReader.clear();
    file.close();
}

/*!
 *\brief gets the new file path of the previos path \a src
 *\param QString src
 *\return QString
 */
QString SaveProject::getNewSrc(QString src)
{
    QString newSrc = src;
    for(int i = 0; i<srcList.count();i = i+2){
        if(src == srcList.at(i))
            newSrc = srcList.at(i+1);
    }
    return newSrc;
}
