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
*\file ncldocument.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to generate the output ncl code.
*/

#include "ncldocument.h"
#include <iostream>

using namespace std;


/*!
 *\brief constructor
 */
NclDocument::NclDocument()
{
}


/*!
 *\brief creates the file and builds the main structure of the \b ncl document(\b head and \b body)
 *\param GraphicsScene *graphicsScene
 *\param DiagramSceneHead *graphicsSceneHead
 *\param DiagramScene *graphicsSceneTemporal
 *\param QString path
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaLuaList
 *\param QList<Media*> mediaUriList
 *\param QList<Descriptor*> descriptorList
 *\return void
 */
void NclDocument::createNCL(GraphicsScene *graphicsScene, DiagramSceneHead *graphicsSceneHead,DiagramScene *graphicsSceneTemporal,QString path,
                            QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                            QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QList<Descriptor*> descriptorList)
{
    QString fileName;
    QString src;
    QDir dirFile(path);
    if(path.isEmpty())
        return;

    QFile file;
    if(!path.endsWith(".ncl"))
        file.setFileName(path+".ncl");
    else
        file.setFileName(path);

    fileName = path;
    fileName.remove(0, fileName.lastIndexOf('/')+1);
    if(file.open(QIODevice::WriteOnly|QIODevice::Text)){
        head = new Head();
        body = new Body();

        clearAllProperties(mediaVideoList,mediaAudioList, mediaImageList,mediaTextList,mediaLuaList,mediaUriList,descriptorList);
        /****************************Region Base****************************/

        MakeRegionBase(graphicsScene);        

        /****************************Connector Base**************************/
        ImportBase *imporBaseConn = new ImportBase("causalConnBase.ncl", "conEx");
        ConnectorBase *connectorBase = new ConnectorBase(imporBaseConn);
        head->setConnectorBase(connectorBase->getConnectorBase());

        addProperty(graphicsSceneTemporal,mediaAudioList,mediaImageList,mediaTextList,mediaVideoList);
        /****************************LINKS*****************************/
        makeLinks(graphicsSceneTemporal,graphicsSceneHead,descriptorList,mediaVideoList,mediaAudioList,mediaImageList,mediaTextList,mediaLuaList,mediaUriList);

        /****************************Medias************************/
        for (int i=0; i < mediaVideoList.size(); i++)
        {
            src = mediaVideoList.at(i)->getSrc();
            QDir dirAux(mediaVideoList.at(i)->getSrc());
            mediaVideoList.at(i)->setSrc(dirFile.relativeFilePath(dirAux.absolutePath()).remove(0,3));
            body->addMedia(*mediaVideoList.at(i));
            mediaVideoList.at(i)->setSrc(src);
        }
        for (int i=0; i < mediaAudioList.size(); i++)
        {
            src = mediaAudioList.at(i)->getSrc();
            QDir dirAux(mediaAudioList.at(i)->getSrc());
            mediaAudioList.at(i)->setSrc(dirFile.relativeFilePath(dirAux.absolutePath()).remove(0,3));
            body->addMedia(*mediaAudioList.at(i));
            mediaAudioList.at(i)->setSrc(src);
        }
        for (int i=0; i < mediaImageList.size(); i++)
        {
            src = mediaImageList.at(i)->getSrc();
            QDir dirAux(mediaImageList.at(i)->getSrc());
            mediaImageList.at(i)->setSrc(dirFile.relativeFilePath(dirAux.absolutePath()).remove(0,3));
            body->addMedia(*mediaImageList.at(i));
            mediaImageList.at(i)->setSrc(src);
        }
        for (int i=0; i < mediaTextList.size(); i++)
        {
            src = mediaTextList.at(i)->getSrc();
            QDir dirAux(mediaTextList.at(i)->getSrc());
            mediaTextList.at(i)->setSrc(dirFile.relativeFilePath(dirAux.absolutePath()).remove(0,3));
            body->addMedia(*mediaTextList.at(i));
            mediaTextList.at(i)->setSrc(src);
        }
        for (int i=0; i < mediaLuaList.size(); i++)
        {
            src = mediaLuaList.at(i)->getSrc();
            QDir dirAux(mediaLuaList.at(i)->getSrc());
            mediaLuaList.at(i)->setSrc(dirFile.relativeFilePath(dirAux.absolutePath()).remove(0,3));
            body->addMedia(*mediaLuaList.at(i));
            mediaLuaList.at(i)->setSrc(src);
        }
        for (int i=0; i < mediaUriList.size(); i++)
        {
            body->addMedia(*mediaUriList.at(i));
        } 

        /****************************Descriptor Base************************/
        if (descriptorList.size()!=0){
            DescriptorBase *descriptorBase = new DescriptorBase(*descriptorList.at(0));
            for (int i=1; i < descriptorList.size(); i++){
                descriptorBase->addDescriptor(*descriptorList.at(i));
            }
            head->addDescriptorBase(descriptorBase->getDescriptorBase());
        }

        for(int i = 0 ;i< descriptorList.count();i++){
            descriptorList.at(i)->clearAllDescriptorParam();
        }
        /********************************************************************/

        Ncl *ncl = new Ncl(*head,*body);
        ncl->setVersionEncoding("1.0","ISO-8859-1");
        ncl->setId("Cardozo-Schwartz");
        ncl->setXmlns("http://www.ncl.org.br/NCL3.0/EDTVProfile");
        file.write(qPrintable(ncl->getNCL()));
    }
}


/*!
 *\brief returns the list of all regions childrens of \a rect
 *\param GraphicsRectItem *rect
 *\return QList<Regionn*>
 */
QList<Regionn*> NclDocument::getRegiones(GraphicsRectItem *rect)
{
    QList<Regionn*> regiones ;
    QList<QGraphicsItem *> lista = rect->childItems();
    GraphicsRectItem *rectItem;
    Regionn *region;

    for(int i =0 ; i < lista.size();i++){
        if(lista.at(i)->type() == 5){ // item is rectangulo
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
            region = new Regionn(rectItem->getName());
            region->setWidth(rectItem->getWidthRecNCL());
            region->setHeight(rectItem->getHeighRecNCL());
            region->setLeft(rectItem->getXRecNCL());
            region->setTop(rectItem->getYRecNCL());
            region->setZIndex(QString::number(rectItem->zValue()));

            if (rectItem->childItems().size() == 0){
                regiones.append(region);
            }else{
                for(int j = 0 ; j < getRegiones(rectItem).size() ; j++){
                    region->addRegion(getRegiones(rectItem).at(j));
                    regiones.append(region);
                }
            }
        }
    }
    return regiones;
}


/*!
 *\brief builds the \b regionbase sector
 *\param GraphicsScene *graphicsScene
 *\return void
 */
void NclDocument::MakeRegionBase(GraphicsScene *graphicsScene)
{
    QList<QGraphicsItem *> lista = graphicsScene->items();
    RegionBase *regionBase;
    int regionNumber = 0;
    GraphicsRectItem *rectItem;
    Regionn *region;

    if (lista.count()!=0){
        for(int i = 0; i < lista.count();i++){
            if(lista.at(i)->type() == 5){ //item is rectangulo
                rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
                if(rectItem->parentItem() == 0){
                    region = new Regionn(rectItem->getName());
                    region->setWidth(rectItem->getWidthRecNCL());
                    region->setHeight(rectItem->getHeighRecNCL());
                    region->setLeft(rectItem->getXRecNCL());
                    region->setTop(rectItem->getYRecNCL());
                    region->setZIndex(QString::number(rectItem->zValue()));

                    regionNumber++;

                    if(rectItem->childItems().size() > 0 ){
                        for(int j = 0 ; j < getRegiones(rectItem).size() ; j++)
                            region->addRegion(getRegiones(rectItem).at(j));
                    }
                    if (regionNumber == 1){
                        regionBase = new RegionBase(*region);                       
                    }else{
                        regionBase->addRegion(*region);
                    }
                }
            }
        }
        if (regionNumber == 0)
            head->addRegionBase("");
        else
            head->addRegionBase(regionBase->getRegionBase());
    }
}


/*!
 *\brief adds the \b explicitDur to medias if they have size arrows different to his original size
 *\param QList<Descriptor*> descriptorList
 *\param QString nameTempLineCorriente
 *\param QString longTempLine
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\return void
 */
void NclDocument::addExplicitDur(QList<Descriptor*> descriptorList,QString nameTempLineCorriente,QString longTempLine)
{
    QString mediaName;    
    for(int i = 0; i < descriptorList.size();i++){
        mediaName = descriptorList.at(i)->getId().remove("descriptor-");
        if(nameTempLineCorriente == mediaName){
            descriptorList.at(i)->setExplicitDur(longTempLine);
            break;
        }
    }
}


/*!
 *\brief returns the Media with name \a nameTempLine
 *\param QString nameTempLine
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaVideoList
 */
Media * NclDocument::getMedia(QString nameTempLine,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,QList<Media*> mediaVideoList)
{
    Media* returnMedia;
    for (int i=0; i < mediaVideoList.size(); i++){
        if(mediaVideoList.at(i)->getId() == nameTempLine){
            returnMedia = mediaVideoList.at(i);
        }
    }
    for (int i=0; i < mediaAudioList.size(); i++){
        if(mediaAudioList.at(i)->getId() == nameTempLine){
            returnMedia = mediaAudioList.at(i);
        }
    }
    for (int i=0; i < mediaImageList.size(); i++){
        if(mediaImageList.at(i)->getId() == nameTempLine){
            returnMedia = mediaImageList.at(i);
        }
    }
    for (int i=0; i < mediaTextList.size(); i++){
        if(mediaTextList.at(i)->getId() == nameTempLine){
            returnMedia = mediaTextList.at(i);
        }
    }
    return returnMedia;
}


/*!
 *\brief adds propertyes to medias
 *\param DiagramScene *graphicsSceneTemporal
 *\param DiagramSceneHead *graphicsSceneHead
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaVideoList
 *\return void
 */
void NclDocument::addProperty(DiagramScene *graphicsSceneTemporal,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,
                 QList<Media*> mediaTextList,QList<Media*> mediaVideoList)
{
    QList<QGraphicsItem *> AllItems = graphicsSceneTemporal->items();
    Image *imageItem;
    Media *currentMedia;
    QString currentName;
    Property *property;
    for(int j = 0; j < AllItems.size();j++){
        if(AllItems.at(j)->type() == 7){//is image
            imageItem =  qgraphicsitem_cast<Image *>(AllItems.at(j));
            if(imageItem->getMyType() == Image::InitTermination || imageItem->getMyType() == Image::EndTermination || imageItem->getMyType() == Image::BotonInteract
                || imageItem->getMyType() == Image::SuspensionPoints){

                if(imageItem->getRoleListSetList().size() > 0){
                    for(int i = 0; i < imageItem->getRoleListsetTableList()->rowCount();i++){
                        currentName = imageItem->getRoleListsetTableList()->item(i,0)->text();
                        currentMedia = getMedia(currentName,mediaAudioList,mediaImageList,mediaTextList, mediaVideoList);                        
                        property = new Property(imageItem->getRoleListsetTableList()->item(i,1)->text());
                        if(!currentMedia->getProperty().contains(imageItem->getRoleListsetTableList()->item(i,1)->text()))
                            currentMedia->addProperty(property);
                    }
                }
            }
        }
    }
}



/*!
 *\brief adds \b roles to \b ncl document
 *\param Image *boton
 *\param QString nameTempLineCorriente
 *\return void
 */
void NclDocument::addRoles(Image *boton,QString nameTempLineCorriente,int interfaceNumber)
{
    QString nameAux ="";
    BindParam *bindParam;
    Bind *bind;
    Link *link1;


    if(boton->getRoleListSetList().size() > 0){
        if(boton->getMyType() == Image::BotonInteract){          
            bindParam = new BindParam("keyCode",boton->getKeyButton());
            bind = new Bind("onSelection",nameTempLineCorriente,bindParam);
            if(interfaceNumber != -1)
                bind->setInterface("area"+QString::number(interfaceNumber));
            link1 = new Link("conEx#onKeySelectionSet",bind);
        }else if(boton->getMyType() == Image::EndTermination){            
            bind = new Bind("onEnd",nameTempLineCorriente);
            link1 = new Link("conEx#onEndSet",bind);
        }else if(boton->getMyType() == Image::InitTermination){           
            bind = new Bind("onBegin",nameTempLineCorriente);
            link1 = new Link("conEx#onBeginSet",bind);           
        }

        for(int i = 0; i < boton->getRoleListsetTableList()->rowCount();i++){            
            if(nameAux != boton->getRoleListsetTableList()->item(i,0)->text()){              
                nameAux = boton->getRoleListsetTableList()->item(i,0)->text();
                link1->setId("LSet"+nameAux);               
            }
            bindParam = new BindParam("varSet",boton->getRoleListsetTableList()->item(i,2)->text());
            bind = new Bind("set",boton->getRoleListsetTableList()->item(i,0)->text(),bindParam);
            bind->setInterface(boton->getRoleListsetTableList()->item(i,1)->text());
            link1->addBind(bind);            
        }
        body->addLink(link1);
    }

    if(boton->getRoleListStopList().size() > 0){
        if(boton->getMyType() == Image::BotonInteract){
            bindParam = new BindParam("keyCode",boton->getKeyButton());
            bind = new Bind("onSelection",nameTempLineCorriente,bindParam);
            if(interfaceNumber != -1)
                bind->setInterface("area"+QString::number(interfaceNumber));
            link1 = new Link("conEx#onKeySelectionStop",bind);
        }else if(boton->getMyType() == Image::EndTermination){
            bind = new Bind("onEnd",nameTempLineCorriente);
            link1 = new Link("conEx#onEndStop",bind);
        }else if(boton->getMyType() == Image::InitTermination){
            bind = new Bind("onBegin",nameTempLineCorriente);
            link1 = new Link("conEx#onBeginStop",bind);
        }

        for(int i = 0; i < boton->getRoleListStopList().size();i++){            
            nameAux = boton->getRoleListStopList().at(i);
            link1->setId("LStop"+nameAux);
            bind = new Bind("stop",nameAux);
            link1->addBind(bind);
        }
        body->addLink(link1);
    }

    if(boton->getRoleListPlayList().size() > 0){
        if(boton->getMyType() == Image::BotonInteract){
            bindParam = new BindParam("keyCode",boton->getKeyButton());
            bind = new Bind("onSelection",nameTempLineCorriente,bindParam);
            if(interfaceNumber != -1)
                bind->setInterface("area"+QString::number(interfaceNumber));
            link1 = new Link("conEx#onKeySelectionStart",bind);
        }else if(boton->getMyType() == Image::EndTermination){
            bind = new Bind("onEnd",nameTempLineCorriente);
            link1 = new Link("conEx#onEndStart",bind);
        }else if(boton->getMyType() == Image::InitTermination){
            bind = new Bind("onBegin",nameTempLineCorriente);
            link1 = new Link("conEx#onBeginStart",bind);
        }

        for(int i = 0; i < boton->getRoleListPlayList().size();i++){
            nameAux = boton->getRoleListPlayList().at(i);
            link1->setId("Lstart"+nameAux);
            bind = new Bind("start",nameAux);
            link1->addBind(bind);
        }
        body->addLink(link1);
    }

    if(boton->getRoleListAbortList().size() > 0){
        if(boton->getMyType() == Image::BotonInteract){
            bindParam = new BindParam("keyCode",boton->getKeyButton());
            bind = new Bind("onSelection",nameTempLineCorriente,bindParam);
            if(interfaceNumber != -1)
                bind->setInterface("area"+QString::number(interfaceNumber));
            link1 = new Link("conEx#onKeySelectionAbort",bind);
        }else if(boton->getMyType() == Image::EndTermination){
            bind = new Bind("onEnd",nameTempLineCorriente);
            link1 = new Link("conEx#onEndAbort",bind);
        }else if(boton->getMyType() == Image::InitTermination){
            bind = new Bind("onBegin",nameTempLineCorriente);
            link1 = new Link("conEx#onBeginAbort",bind);
        }

        for(int i = 0; i < boton->getRoleListAbortList().size();i++){
            nameAux = boton->getRoleListAbortList().at(i);
            link1->setId("Labort"+nameAux);
            bind = new Bind("abort",nameAux);
            link1->addBind(bind);
        }
        body->addLink(link1);
    }

    if(boton->getRoleListPauseList().size() > 0){
        if(boton->getMyType() == Image::BotonInteract){
            bindParam = new BindParam("keyCode",boton->getKeyButton());
            bind = new Bind("onSelection",nameTempLineCorriente);
            if(interfaceNumber != -1)
                bind->setInterface("area"+QString::number(interfaceNumber));
            link1 = new Link("conEx#onKeySelectionPause",bind);
        }else if(boton->getMyType() == Image::EndTermination){
            bind = new Bind("onEnd",nameTempLineCorriente);
            link1 = new Link("conEx#onEndPause",bind);
        }else if(boton->getMyType() == Image::InitTermination){
            bind = new Bind("onBegin",nameTempLineCorriente);
            link1 = new Link("conEx#onBeginPause",bind);
        }

        for(int i = 0; i < boton->getRoleListPauseList().size();i++){            
            nameAux = boton->getRoleListPauseList().at(i);
            link1->setId("Lpause"+nameAux);
            bind = new Bind("pause",nameAux);
            link1->addBind(bind);
        }
        body->addLink(link1);
    }

    if(boton->getRoleListResumeList().size() > 0){
        if(boton->getMyType() == Image::BotonInteract){
            bindParam = new BindParam("keyCode",boton->getKeyButton());
            bind = new Bind("onSelection",nameTempLineCorriente,bindParam);
            if(interfaceNumber != -1)
                bind->setInterface("area"+QString::number(interfaceNumber));
            link1 = new Link("conEx#onKeySelectionResume",bind);
        }else if(boton->getMyType() == Image::EndTermination){
            bind = new Bind("onEnd",nameTempLineCorriente);
            link1 = new Link("conEx#onEndResume",bind);
        }else if(boton->getMyType() == Image::InitTermination){
            bind = new Bind("onBegin",nameTempLineCorriente);
            link1 = new Link("conEx#onBeginResume",bind);
        }

        for(int i = 0; i < boton->getRoleListResumeList().size();i++){            
            nameAux = boton->getRoleListResumeList().at(i);
            link1->setId("Lresume"+nameAux);
            bind = new Bind("resume",nameAux);
            link1->addBind(bind);
        }
        body->addLink(link1);
    }
}


/*!
 *\brief creates the \b area and assigns it to the media
 *\param QString nameArea
 *\param QString beginArea
 *\param QString endArea
 *\param QString nameTempLineCorriente
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaLuaList
 *\param QList<Media*> mediaUriList
 *\return void
 */
void NclDocument::addInterface(QString nameArea,QString beginArea,QString endArea,QString nameTempLineCorriente,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,
                               QList<Media*> mediaTextList,QList<Media*> mediaVideoList,QList<Media*> mediaLuaList,QList<Media*> mediaUriList)
{
    Area *area = new Area(nameArea);
    area->setBegin(beginArea+"s");
    area->setEnd(endArea+"s");

    for (int i=0; i < mediaVideoList.size(); i++){
        if(mediaVideoList.at(i)->getId() == nameTempLineCorriente){
            mediaVideoList.at(i)->addArea(area);
        }
    }
    for (int i=0; i < mediaAudioList.size(); i++){
        if(mediaAudioList.at(i)->getId() == nameTempLineCorriente){
            mediaAudioList.at(i)->addArea(area);
        }
    }
    for (int i=0; i < mediaImageList.size(); i++){
        if(mediaImageList.at(i)->getId() == nameTempLineCorriente){
            mediaImageList.at(i)->addArea(area);
        }
    }
    for (int i=0; i < mediaTextList.size(); i++){
        if(mediaTextList.at(i)->getId() == nameTempLineCorriente){
            mediaTextList.at(i)->addArea(area);
        }
    }
    for (int i=0; i < mediaLuaList.size(); i++){
        if(mediaLuaList.at(i)->getId() == nameTempLineCorriente){
            mediaLuaList.at(i)->addArea(area);
        }
    }
    for (int i=0; i < mediaUriList.size(); i++){
        if(mediaUriList.at(i)->getId() == nameTempLineCorriente){
            mediaUriList.at(i)->addArea(area);
        }
    }
}


/*!
 *\brief creates the \b links according the arrows and his relations into the \a graphicsSceneTemporal
 *\param DiagramScene *graphicsSceneTemporal
 *\param DiagramSceneHead *graphicsSceneHead
 *\param QList<Descriptor*> descriptorList
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaLuaList
 *\param QList<Media*> mediaUriList
 *\return void
 */
void NclDocument::makeLinks(DiagramScene *graphicsSceneTemporal,DiagramSceneHead *graphicsSceneHead,QList<Descriptor*> descriptorList,
                            QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                            QList<Media*> mediaLuaList,QList<Media*> mediaUriList)
{
    int interfaceNumber = 0;
    qreal longTempLine =0;
    qreal posStartTempLine =0;
    qreal posStartInParentTempLine =0;
    qreal posEndInParentTempLine =0;
    QString nameTempLineCorriente = 0;
    QString nameTempLineParent = 0;
    QList<QGraphicsItem *> TodosItems = graphicsSceneTemporal->items();
    QList<QGraphicsItem *> AllChildremsAux;
    Arrow *arrowItem;
    Arrow *arrowItemParent;
    int numLineAux;   
    QString currentTime;
    QString timeAux;
    QString timeAuxBegin;
    QString timeAuxEnd;
    QString timeParent;

    for(int i = 0; i < TodosItems.size();i++){
        if(TodosItems.at(i)->type() == 6){//is arrow
            numLineAux = TodosItems.at(i)->boundingRect().y() / LINESIZE;
             arrowItem =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
            if(arrowItem->getMyType() == Arrow::TempLine){ //is tempLine
                if(arrowItem->parentItem() == 0){//Have port
                    nameTempLineCorriente = graphicsSceneHead->NameMediaInLineNumber(numLineAux);
                    longTempLine = arrowItem->getEndItem()->x();
                    posStartTempLine = arrowItem->getStartItem()->pos().x();

                    currentTime = QString::number((longTempLine * 100)/1000);

                    Port *port = new Port("Port-"+nameTempLineCorriente,nameTempLineCorriente);
                    body->addPort(port);

                    if(arrowItem->getEndItem()->getMyType() != Image::SuspensionPoints)
                        if(arrowItem->getLongTempLineOriginal() == "-1" || currentTime != arrowItem->getLongTempLineOriginal())//checks if the arrow size never changed
                            addExplicitDur(descriptorList,nameTempLineCorriente,currentTime);

                    addRoles(arrowItem->getEndItem(),nameTempLineCorriente,-1);
                    addRoles(arrowItem->getStartItem(),nameTempLineCorriente,-1);
                }else{// is tempLine comon
                    nameTempLineCorriente = graphicsSceneHead->NameMediaInLineNumber(numLineAux);
                    arrowItemParent = qgraphicsitem_cast<Arrow *>(arrowItem->parentItem());                    
                    if(arrowItemParent->getMyType() != Arrow::UnionLineTempInteract){// the tempLne is children of the other tempLine*/
                        BindParam *bindParam;
                        Bind *bind;
                        Bind *bind2;
                        Link *link1;

                        longTempLine = arrowItem->getEndItem()->x();
                        arrowItemParent = qgraphicsitem_cast<Arrow *>(arrowItem->parentItem()->parentItem());
                        numLineAux = arrowItemParent->boundingRect().y() / LINESIZE;
                        nameTempLineParent = graphicsSceneHead->NameMediaInLineNumber(numLineAux);
                        posStartInParentTempLine = arrowItem->getStartItem()->x();

                        currentTime = QString::number((longTempLine * 100)/1000);

                        timeAux = QString::number((posStartInParentTempLine * 100)/1000);

                        timeParent = QString::number((arrowItemParent->getEndItem()->x() * 100)/1000);

                        if("0" == timeAux){
                            bind = new Bind("onBegin",nameTempLineParent);
                            bind2 = new Bind("start",nameTempLineCorriente);
                            link1 = new Link("conEx#onBeginStart",bind);
                            link1->addBind(bind2);
                            link1->setId("LonBegin"+nameTempLineCorriente);
                        }else if(timeAux == timeParent){
                            bind = new Bind("onEnd",nameTempLineParent);
                            bind2 = new Bind("start",nameTempLineCorriente);
                            link1 = new Link("conEx#onEndStart",bind);
                            link1->addBind(bind2);
                            link1->setId("LonEnd"+nameTempLineCorriente);
                        }else{
                            bindParam = new BindParam("delay",timeAux+"s");
                            bind = new Bind("onBegin",nameTempLineParent);
                            bind2 = new Bind("start",nameTempLineCorriente,bindParam);
                            link1 = new Link("conEx#onBeginStartDelay",bind);
                            link1->addBind(bind2);
                            link1->setId("LonBegin"+nameTempLineCorriente);
                        }
                        body->addLink(link1);

                        if(arrowItem->getEndItem()->getMyType() != Image::SuspensionPoints)
                            if(arrowItem->getLongTempLineOriginal() == "-1" || currentTime != arrowItem->getLongTempLineOriginal())//checks if the arrow size never changed
                                addExplicitDur(descriptorList,nameTempLineCorriente,currentTime);

                        addRoles(arrowItem->getEndItem(),nameTempLineCorriente,-1);
                        addRoles(arrowItem->getStartItem(),nameTempLineCorriente,-1);
                    }
                }
            }else if(arrowItem->getMyType() == Arrow::InteractLine){//is InteractLine
                qreal longTempLineAux;
                BindParam *bindParam;
                Bind *bind;
                Link *link1;
                bool intoLongInteract =false;
                longTempLine = arrowItem->getEndItem()->x();
                nameTempLineCorriente = graphicsSceneHead->NameMediaInLineNumber(numLineAux);
                arrowItemParent = qgraphicsitem_cast<Arrow *>(arrowItem->parentItem());
                posStartInParentTempLine = arrowItem->getStartItem()->x();//
                posEndInParentTempLine = arrowItemParent->getEndItem()->x();//posStartInParentTempLine + longTempLine;

                currentTime = QString::number((longTempLine * 100)/1000);

                timeAuxBegin = QString::number((posStartInParentTempLine * 100)/1000);                
                timeAuxEnd = QString::number((longTempLine * 100)/1000);

                QList<QGraphicsItem *> TodosItems = arrowItem->childItems();

                if(TodosItems.size() > 1){
                    bindParam = new BindParam("keyCode",arrowItem->getButton()->getKeyButton());
                    bind = new Bind("onSelection",nameTempLineCorriente,bindParam);
                }

                if(posStartInParentTempLine != 0 || QString::number(longTempLine) != QString::number(posEndInParentTempLine)){
                    interfaceNumber++;
                    if(TodosItems.size() > 1)
                        bind->setInterface("area"+QString::number(interfaceNumber));
                    addInterface("area"+QString::number(interfaceNumber),timeAuxBegin,timeAuxEnd,nameTempLineCorriente,mediaAudioList,mediaImageList,mediaTextList,mediaVideoList,mediaLuaList,mediaUriList);
                    intoLongInteract =true;
                }

                if(TodosItems.size() > 1)
                    link1 = new Link("conEx#onKeySelectionStart",bind);


                int numLineCorriente =0;
                QString nameAux;
                Arrow *arrowtItemCorriente;
                Arrow *arrowtItemCorrienteAux;
                for(int i = 0; i < TodosItems.size();i++){
                    arrowtItemCorriente =  qgraphicsitem_cast<Arrow *>(TodosItems.at(i));
                    if(arrowtItemCorriente->getMyType() == Arrow::UnionLineTempInteract){
                        AllChildremsAux = arrowtItemCorriente->childItems();
                        for(int j = 0; j < AllChildremsAux.size();j++){
                            arrowtItemCorrienteAux =  qgraphicsitem_cast<Arrow *>(AllChildremsAux.at(j));
                            if(arrowtItemCorrienteAux->getMyType() == Arrow::TempLine){
                                break;
                            }
                        }

                        if(arrowtItemCorrienteAux->getMyType() == Arrow::TempLine){                          
                            numLineCorriente = arrowtItemCorrienteAux->boundingRect().y() / LINESIZE;
                            longTempLineAux = arrowtItemCorrienteAux->getEndItem()->x();
                            nameAux = graphicsSceneHead->NameMediaInLineNumber(numLineCorriente);

                            currentTime = QString::number((longTempLineAux * 100)/1000);

                            bind = new Bind("start",nameAux);
                            link1->addBind(bind);

                            if(arrowtItemCorrienteAux->getEndItem()->getMyType() != Image::SuspensionPoints)
                                if(arrowtItemCorrienteAux->getLongTempLineOriginal() == "-1" || currentTime != arrowtItemCorrienteAux->getLongTempLineOriginal())//checks if the arrow size never changed
                                    addExplicitDur(descriptorList,nameAux,currentTime);

                            addRoles(arrowtItemCorrienteAux->getEndItem(),nameAux,-1);
                            addRoles(arrowtItemCorrienteAux->getStartItem(),nameAux,-1);

                        }
                    }
                }
                if(TodosItems.size() > 1){
                    link1->setId("L"+nameTempLineCorriente);
                    body->addLink(link1);
                }
                if(intoLongInteract)
                    addRoles(arrowItem->getButton(),nameTempLineCorriente,interfaceNumber);
                else
                    addRoles(arrowItem->getButton(),nameTempLineCorriente,-1);
            }
        }
     }
}


/*!
 *\brief clears the lists to begin again with a new ncl document
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaLuaList
 *\param QList<Media*> mediaUriList
 *\param QList<Descriptor*> descriptorList
 *\return void
 */
void NclDocument::clearAllProperties(QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                                 QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QList<Descriptor*> descriptorList)
{
    for(int i = 0; i < descriptorList.size();i++){
        descriptorList.at(i)->deleteExplicitDur();
    }
    clearAreaLists(mediaVideoList,mediaAudioList, mediaImageList,mediaTextList,mediaLuaList,mediaUriList);
}


/*!
 *\brief clears the area list to begin again with new ncl document
 *\param QList<Media*> mediaVideoList
 *\param QList<Media*> mediaAudioList
 *\param QList<Media*> mediaImageList
 *\param QList<Media*> mediaTextList
 *\param QList<Media*> mediaLuaList
 *\param QList<Media*> mediaUriList
 *\return void
 */
void NclDocument::clearAreaLists(QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,
                                 QList<Media*> mediaLuaList,QList<Media*> mediaUriList)
{
    for(int i = 0 ; i< mediaVideoList.count();i++){
        mediaVideoList.at(i)->clearAreas();
        mediaVideoList.at(i)->clearProperty();
    }
    for(int i = 0 ; i< mediaAudioList.count();i++){
        mediaAudioList.at(i)->clearAreas();
        mediaAudioList.at(i)->clearProperty();
    }
    for(int i = 0 ; i< mediaTextList.count();i++){
        mediaTextList.at(i)->clearAreas();
        mediaTextList.at(i)->clearProperty();
    }
    for(int i = 0 ; i< mediaImageList.count();i++){
        mediaImageList.at(i)->clearAreas();
        mediaImageList.at(i)->clearProperty();
    }
    for(int i = 0 ; i< mediaLuaList.count();i++){
        mediaLuaList.at(i)->clearAreas();
    }
    for(int i = 0 ; i< mediaUriList.count();i++){
        mediaUriList.at(i)->clearAreas();
    }
}
