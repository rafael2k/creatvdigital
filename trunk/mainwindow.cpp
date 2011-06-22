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
 *\file mainwindow.cpp
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods implementation to manipulates activities in main window.
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtDebug>
#include "NCL/ncl.h"
#include "phonon/mediaobject.h"

using namespace std;



/*!
 *\brief initializes main window, creates connectors, initiazlizes main variables.
 *\param QWidget* parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    showMaximized();

    setWindowTitle("CreaTVDigital");
    initToolBarIcons();
    initActions();
    initTemporalArea();
    initRegionsArea();
    initDockTools();
    showMaximized();

    screenSizeOtherX = 0;
    screenSizeOtherY = 0;

    initEnable(false);

    saveAsBool = false;
    mediaObject = new Phonon::MediaObject(this);

    widgetPropieties = new QWidget(0,Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);
    widgetMediasRegion = new QWidget(0,Qt::FramelessWindowHint|Qt::WindowSystemMenuHint);

    myFileName.clear();
    changePresent = false;
    nclName.clear();

    buttonRectAct=false;

    graphicsViewTemporalMedias->centerOn(0,0);

    clear = false;
    regionNumber = 0;

    connect(graphicsScene, SIGNAL(itemSelected(GraphicsRectItem*)),this, SLOT(itemSelected(GraphicsRectItem*)));
    connect(graphicsScene, SIGNAL(itemDrop(GraphicsRectItem*)),this, SLOT(dropItem(GraphicsRectItem*)));
    connect(graphicsScene, SIGNAL(addRootTreeItem(QString)),this, SLOT(addRootTreeItem(QString)));
    connect(graphicsScene, SIGNAL(addChildTreeItem(QString,QString)),this, SLOT(addChildTreeItem(QString,QString)));
    connect(graphicsScene, SIGNAL(zoom(const qreal)),this, SLOT(zoom(const qreal)));
    connect(graphicsScene, SIGNAL(mouseMove(QPointF)),horizontalRule,SLOT(mouseMove(QPointF)));
    connect(graphicsScene, SIGNAL(mouseMove(QPointF)),verticalRule,SLOT(mouseMove(QPointF)));
    connect(graphicsScene, SIGNAL(mouseMoveX(qreal,qreal)),horizontalRule,SLOT(rectChange(qreal,qreal)));
    connect(graphicsScene, SIGNAL(mouseMoveY(qreal,qreal)),verticalRule,SLOT(rectChange(qreal,qreal)));
    //connect(graphicsScene, SIGNAL(showMediasRegion(QPointF,QList<Media*>)),this,SLOT(showMediasRegion(QPointF,QList<Media*>)));
    //connect(graphicsScene, SIGNAL(closeMediasRegion()),this,SLOT(closeMediasRegion()));
    connect(graphicsScene, SIGNAL(setDataNcl()),this, SLOT(setDataNcl()));    
    connect(treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)),this, SLOT(selectRegion(QTreeWidgetItem*)));
    connect(treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*,int)),this, SLOT(setShowRegion(QTreeWidgetItem*)));
    connect(ui->actionEliminar, SIGNAL(triggered()),this, SLOT(deleteItem()));
    connect(ui->actionGenerar_Archivo_NCL, SIGNAL(triggered()),this, SLOT(createNCL()));
    connect(ui->actionGuardar, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionGuardar_Como, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionAbrir, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionNavegacion_de_Teclas, SIGNAL(triggered()), this, SLOT(navigation()));
    connect(ui->actionNuevo, SIGNAL(triggered()), this, SLOT(newProject()));
    connect(ui->actionEjecutar_Archivo_NCL, SIGNAL(triggered()), this, SLOT(runNcl()));
    connect(ui->actionEditar_descripcion_del_proyecto, SIGNAL(triggered()), this, SLOT(editProjectDescription()));
    connect(ui->actionSalir, SIGNAL(triggered()), this, SLOT(close()));
    connect(this, SIGNAL(destroyed()), this, SLOT(editProjectDescription()));
    connect(this, SIGNAL(setButtonPressed(bool)),graphicsScene,SLOT(setButtonPressed(bool)));
    connect(videoList, SIGNAL(cellPressed(int,int)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(audioList, SIGNAL(cellPressed(int,int)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(imageList, SIGNAL(itemPressed(QListWidgetItem*)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(textList, SIGNAL(itemPressed(QListWidgetItem*)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(luaList, SIGNAL(itemPressed(QListWidgetItem*)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(uriList, SIGNAL(itemPressed(QListWidgetItem*)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(graphicsSceneTemporal, SIGNAL(outElement()),this,SLOT(outElement()));

    connect(videoList, SIGNAL(cellPressed(int,int)),this,SLOT(setTrueAllOkItemDrop()));
    connect(audioList, SIGNAL(cellPressed(int,int)),this,SLOT(setTrueAllOkItemDrop()));
    connect(imageList, SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(setTrueAllOkItemDrop()));
    connect(textList, SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(setTrueAllOkItemDrop()));
    connect(luaList, SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(setTrueAllOkItemDrop()));
    connect(uriList, SIGNAL(itemPressed(QListWidgetItem*)),this,SLOT(setTrueAllOkItemDrop()));
    /*connect(usedMediasList, SIGNAL(cellPressed(int,int)),,SLOT(setFlaseOkItemDrop()));
    connect(audioList, SIGNAL(cellPressed(int,int)),graphicsSceneTemporal,SLOT(setFlaseOkItemDrop()));
    connect(graphicsSceneHead, SIGNAL(outElement()),this,SLOT(outElement()));*/
    connect(graphicsScene, SIGNAL(outElement()),this,SLOT(outElementRegion()));
}


/*!
 *\brief destructor of de UI.
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/*!
 *\brief initializes the actions of the main window toolbar with icons
 *\return void
 */
void MainWindow::initToolBarIcons()
{
    ui->actionNuevo->setIcon(QIcon("icons/newFile.png"));
    ui->actionAbrir->setIcon(QIcon("icons/open-icon.png"));
    ui->actionGuardar->setIcon(QIcon("icons/save.png"));
    ui->actionGenerar_Archivo_NCL->setIcon(QIcon("icons/generate.png"));
    ui->actionEjecutar_Archivo_NCL->setIcon(QIcon("icons/start.png"));
    ui->actionPALN->setIcon(QIcon("icons/paln.png"));
    ui->actionPALAncho->setIcon(QIcon("icons/pala.png"));
    ui->actionHDTV1080->setIcon(QIcon("icons/HDTVI.png"));
    ui->actionHDTV720->setIcon(QIcon("icons/HDTVP.png"));
    ui->actionRegionPALN->setIcon(QIcon("icons/relPalN.png"));
    ui->actionRegionPALAncho->setIcon(QIcon("icons/relPalA.png"));
    ui->actionRegionHDTV720p->setIcon(QIcon("icons/hd.png"));
    ui->actionRegionHDTV1080i->setIcon(QIcon("icons/hdFull.png"));
}

/*!
 *\brief if \enable value is true, does disable the elements in main window (after to create a project or open ones).
 *\param bool enable
 *\return void
 */
void MainWindow::initEnable(bool enable)
{
    ui->actionGuardar->setEnabled(enable);
    ui->actionGuardar_Como->setEnabled(enable);
    ui->menuVer->setEnabled(enable);
    ui->menuNCL->setEnabled(enable);
    ui->menuHerramientas->setEnabled(enable);
    ui->menuItem->setEnabled(enable);
    tabRegions->setEnabled(enable);
    tabLists->setEnabled(enable);
    editToolBar->setEnabled(enable);
    toolBar->setEnabled(enable);
    graphicsView->setEnabled(enable);
    graphicsViewTemporal->setEnabled(enable);
    graphicsViewTemporalMedias->setEnabled(enable);
    ui->actionGenerar_Archivo_NCL->setEnabled(enable);
    ui->actionEjecutar_Archivo_NCL->setEnabled(enable);
    ui->actionPALN->setEnabled(enable);
    ui->actionPALAncho->setEnabled(enable);
    ui->actionHDTV720->setEnabled(enable);
    ui->actionHDTV1080->setEnabled(enable);
    ui->actionRegionPALN->setEnabled(enable);
    ui->actionRegionPALAncho->setEnabled(enable);
    ui->actionRegionHDTV720p->setEnabled(enable);
    ui->actionRegionHDTV1080i->setEnabled(enable);

    if(enable){
        graphicsScene->setBackgroundBrush(QPixmap(QDir::currentPath()+"/images/backgroundRegions.png"));
        graphicsSceneTemporal->setBackgroundBrush(QPixmap(QDir::currentPath()+"/images/background.png"));
        graphicsSceneHead->setBackgroundBrush(QPixmap(QDir::currentPath()+"/images/background.png"));
        initScreenSize();
    }else{
        graphicsScene->setBackgroundBrush(QColor("lightgray"));
        graphicsSceneTemporal->setBackgroundBrush(QColor("lightgray"));
        graphicsSceneHead->setBackgroundBrush(QColor("lightgray"));
    }
}


/*!
 *\brief initializes the actions of the main window
 *\return void
 */
void MainWindow::initActions()
{
    ui->menuItem->menuAction()->setVisible(false);

    otherAction = new QAction(this);
    otherRegionAction = new QAction(this);

    ui->actionPALN->setCheckable(true);
    ui->actionPALAncho->setCheckable(true);
    ui->actionHDTV720->setCheckable(true);
    ui->actionHDTV1080->setCheckable(true);

    ui->actionRegionPALN->setCheckable(true);
    ui->actionRegionPALAncho->setCheckable(true);
    ui->actionRegionHDTV720p->setCheckable(true);
    ui->actionRegionHDTV1080i->setCheckable(true);

    groupScreens = new QActionGroup(this);
    groupScreens->addAction(ui->actionRegionPALN);
    groupScreens->addAction(ui->actionRegionPALAncho);
    groupScreens->addAction(ui->actionRegionHDTV720p);
    groupScreens->addAction(ui->actionRegionHDTV1080i);

    connect(ui->actionPALN, SIGNAL(toggled(bool)), this, SLOT(setVisiblePALN(bool)));
    connect(ui->actionPALAncho, SIGNAL(toggled(bool)), this, SLOT(setVisiblePALAncho(bool)));
    connect(ui->actionHDTV720, SIGNAL(toggled(bool)), this, SLOT(setVisibleHDTVp(bool)));
    connect(ui->actionHDTV1080, SIGNAL(toggled(bool)), this, SLOT(setVisibleHDTVi(bool)));

    connect(ui->actionRegionPALN, SIGNAL(triggered()), this, SLOT(setSizeScreenPALN()));
    connect(ui->actionRegionPALAncho, SIGNAL(triggered()), this, SLOT(setSizeScreenPALAncho()));
    connect(ui->actionRegionHDTV720p, SIGNAL(triggered()), this, SLOT(setSizeScreenHDTV720p()));
    connect(ui->actionRegionHDTV1080i, SIGNAL(triggered()), this, SLOT(setSizeScreenHDTV1080i()));
}


/*!
 *\brief initializes the screen sizes of the drawing area of regions
 *\return void
 */
void MainWindow::initScreenSize()
{
    QPen *pen = new QPen(Qt::SolidPattern, 2.0,Qt::DashDotLine , Qt::SquareCap,Qt::MiterJoin);
    pen->setColor(QColor(127,127,243,255));

    palN = new QGraphicsRectItem();
    palN->setFlag(QGraphicsItem::ItemIsMovable,false);
    palN->setRect(QRectF(0, 0, 720, 576));
    palN->setPen(*pen);
    graphicsScene->addItem(palN);

    palWeigth = new QGraphicsRectItem();
    palWeigth->setFlag(QGraphicsItem::ItemIsMovable,false);
    palWeigth->setRect(QRectF(0, 0, 1024, 576));
    palWeigth->setPen(*pen);
    graphicsScene->addItem(palWeigth);

    hdtv = new QGraphicsRectItem();
    hdtv->setFlag(QGraphicsItem::ItemIsMovable,false);
    hdtv->setRect(QRectF(0, 0, 1280, 720));
    hdtv->setPen(*pen);
    graphicsScene->addItem(hdtv);

    hdtvHD = new QGraphicsRectItem();
    hdtvHD->setFlag(QGraphicsItem::ItemIsMovable,false);
    hdtvHD->setRect(QRectF(0, 0, 1920, 1080));
    hdtvHD->setPen(*pen);
    graphicsScene->addItem(hdtvHD);

    palNText1 = new QGraphicsTextItem("PALN - 720x576 px");
    palNText1->setDefaultTextColor(QColor(127,127,243,255));
    palNText1->setPos(725,0);
    graphicsScene->addItem(palNText1);

    palNText2 = new QGraphicsTextItem("PALN - 720x576 px");
    palNText2->setDefaultTextColor(QColor(127,127,243,255));
    palNText2->setPos(0,576);
    graphicsScene->addItem(palNText2);

    palWeigthText1 = new QGraphicsTextItem("PALAncho - 1024x576 px");
    palWeigthText1->setDefaultTextColor(QColor(127,127,243,255));
    palWeigthText1->setPos(1029,0);
    graphicsScene->addItem(palWeigthText1);

    palWeigthText2 = new QGraphicsTextItem("PALAncho - 1024x576 px");
    palWeigthText2->setDefaultTextColor(QColor(127,127,243,255));
    palWeigthText2->setPos(130,576);
    graphicsScene->addItem(palWeigthText2);

    hdtvText1 = new QGraphicsTextItem("HDTV 720p - 1280x720 px");
    hdtvText1->setDefaultTextColor(QColor(127,127,243,255));
    hdtvText1->setPos(1285,0);
    graphicsScene->addItem(hdtvText1);

    hdtvText2 = new QGraphicsTextItem("HDTV 720p - 1280x720 px");
    hdtvText2->setDefaultTextColor(QColor(127,127,243,255));
    hdtvText2->setPos(0,720);
    graphicsScene->addItem(hdtvText2);

    hdtvHDText1 = new QGraphicsTextItem("HDTV 1080i - 1920x1080 px");
    hdtvHDText1->setDefaultTextColor(QColor(127,127,243,255));
    hdtvHDText1->setPos(1925,0);
    graphicsScene->addItem(hdtvHDText1);

    hdtvHDText2 = new QGraphicsTextItem("HDTV 1080i - 1920x1080 px");
    hdtvHDText2->setDefaultTextColor(QColor(127,127,243,255));
    hdtvHDText2->setPos(0,1080);
    graphicsScene->addItem(hdtvHDText2);
}


/*!
 *\brief called to add a media from an import list to a region using mouse
 *\param GraphicsRectItem *item
 *\return void
 */
void MainWindow::dropItem(GraphicsRectItem *item)
{
    if(tabRegions->currentIndex() == 1){
        if (videoList->isVisible()){
            addMediaVideoToRegion();
         }else if (audioList->isVisible()){
            addMediaAudioToRegion();
         }else if (imageList->isVisible()){
            addMediaImageToRegion();
         }else if (textList->isVisible()){
            addMediaTextToRegion();
         }
     }else{
         if (luaList->isVisible()){
             addMediaLuaToRegion();
          }else if (uriList->isVisible()){
             addMediaUriToRegion();
          }
     }
     graphicsScene->clearSelection();
     item->setSelected(true);
     itemSelected(item);
}


/*!
 *\brief called when a media is dropped into "timeLine"
 *\param qreal posX
 *\return void
 */
void MainWindow::diagramSceneDrop(qreal posX)
{
    QImage currentImage;
    QString nameMedia;
    qreal MediaDuration = 0;
    bool haveDuration =false;
    QString duration;
    changePresent = true;

    if(mediasRegionList->isVisible()){
        if(mediasRegionList->item(mediasRegionList->currentRow(),1)->checkState() == Qt::Checked){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, tr("Precaucion!"),"El media "+ mediasRegionList->item(mediasRegionList->currentRow(),0)->text() +" ya esta en uso",QMessageBox::Ok);
            return;
        }
    }else{
        if(usedMediasList->item(usedMediasList->currentRow(),1)->checkState() == Qt::Checked){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, tr("Precaucion!"),"El media "+ usedMediasList->item(usedMediasList->currentRow(),0)->text() +" ya esta en uso",
                                            QMessageBox::Ok);
            return;
        }
    }

    if (tabLists->currentIndex()==0){
        currentImage  =  mediasRegionList->item(mediasRegionList->currentRow(),0)->icon().pixmap(63,50,QIcon::Normal,QIcon::On).toImage();
        nameMedia = mediasRegionList->item(mediasRegionList->currentRow(),0)->text();
        setMediaUsedIconOk(nameMedia, true);

        if(mediasRegionList->item(mediasRegionList->currentRow(),3)->text()=="Video" || mediasRegionList->item(mediasRegionList->currentRow(),3)->text()=="Audio"){
            QStringList values;
            values = mediasRegionList->item(mediasRegionList->currentRow(),2)->text().split(":");
            int hour = values.at(0).toInt();
            int min = values.at(1).toInt();
            int secs = values.at(2).toInt();
            int mSecs = values.at(3).toInt();

            duration = QString::number(hourToMSec(hour)+minToMSec(min)+secToMSec(secs)+mSecs);
        }else{
            duration = "0";
        }

        MediaDuration =duration.toDouble();
        MediaDuration = (MediaDuration / 100);

        if(MediaDuration == 0){
            MediaDuration = 50;
            haveDuration =false;
        }else{
            haveDuration =true;
        }

    }else {

        currentImage  =  usedMediasList->item(usedMediasList->currentRow(),0)->icon().pixmap(63,50,QIcon::Normal,QIcon::On).toImage();
        nameMedia = usedMediasList->item(usedMediasList->currentRow(),0)->text();
        setMediaUsedIconOk(nameMedia, true);

        if(usedMediasList->item(usedMediasList->currentRow(),3)->text()=="Video" || usedMediasList->item(usedMediasList->currentRow(),3)->text()=="Audio"){
            QStringList values;
            values = usedMediasList->item(usedMediasList->currentRow(),2)->text().split(":");

            int hour = values.at(0).toInt();
            int min = values.at(1).toInt();
            int secs = values.at(2).toInt();
            int mSecs = values.at(3).toInt();

            duration = QString::number(hourToMSec(hour)+minToMSec(min)+secToMSec(secs)+mSecs);
        }else{
            duration = "0";
        }

        MediaDuration =duration.toDouble();
        MediaDuration = (MediaDuration / 100) ;
        if(MediaDuration == 0){
            MediaDuration = 50;
            haveDuration =false;
        }else{
            haveDuration =true;
        }
    }

    if(posX == -10)
        graphicsSceneTemporal->addFirstImage(currentImage,nameMedia,MediaDuration,haveDuration,((MediaDuration* 100)/1000),false,false);
    else
        graphicsSceneTemporal->insertBodyDownItems(posX,currentImage,nameMedia,MediaDuration,haveDuration);
}


/*!
 *\brief sets the checkBox (with value \a ok)of the table \a usedMediasList and \a mediasRegionList if the media \a name is used in the timelime diagram
 *\param QString name
 *\param bool ok
 *\return void
 */
void MainWindow::setMediaUsedIconOk(QString name, bool ok)
{
    QString nameMedia;
    for(int i = 0; i < mediasRegionList->rowCount();i++){
        nameMedia = mediasRegionList->item(i,0)->text();
        if(nameMedia == name ){
            if (ok)
                mediasRegionList->item(i,1)->setCheckState(Qt::Checked);
            else
                mediasRegionList->item(i,1)->setCheckState(Qt::Unchecked);
            break;
        }
    }

    for(int i = 0; i < usedMediasList->rowCount();i++){
        nameMedia = usedMediasList->item(i,0)->text();
        if(nameMedia == name ){
            if (ok)
                usedMediasList->item(i,1)->setCheckState(Qt::Checked);
            else
                usedMediasList->item(i,1)->setCheckState(Qt::Unchecked);
            break;
        }
    }
}


/*!
 *\brief called to remove Images between \a fromLineNumber and \a toLineNumber and sets unused icon to media
 *\param int fromLineNumber
 *\param int toLineNumber
 *\return void
 */
void MainWindow::removeLineBetweenSlot(int fromLineNumber,int toLineNumber)
{
    QString nameMedia;
    for(int i = fromLineNumber; i < toLineNumber;i++){
        nameMedia= graphicsSceneHead->NameMediaInLineNumber(i);
        setMediaUsedIconOk(nameMedia, false);
    }
    graphicsSceneHead->removeLineBetween(fromLineNumber,toLineNumber);
    deleteLineAction->setChecked(false);
}


/*!
 *\brief sets the movement property and focus property disable when a sub-region is create (\a bool \a prop \a = \a false )
 *\param bool prop
 *\return void
 */
void MainWindow::setPropItems(bool prop)
{
    QList<QGraphicsItem *> Items = graphicsView->items();
    int cont=0;
    changePresent = true;
    foreach (QGraphicsItem *item, Items) {
        cont++;
        if(item->parentItem()==0 && item->type()==5){
            item->setFlag(QGraphicsItem::ItemIsFocusable, prop);
            item->setFlag(QGraphicsItem::ItemIsMovable, prop);
        }
    }
}


/*!
 *\brief called to remove a region of the scene.
 *\return void
 */
void MainWindow::deleteItem()
{
    if (!ui->actionNewRegion->isChecked()){
        foreach (QGraphicsItem *item, graphicsScene->selectedItems()) {
            if(item->type() == 5){ //is graphiscsrectitem
                GraphicsRectItem *rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(item);
                if(rectItem->getMedias().isEmpty()){
                    emit itemSelected(rectItem);
                    graphicsScene->removeItem(item);
                    removeTreeRegion();
                    delete item;
                    changePresent = true;
                }else{
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Acción no posible"),
                                                    "Imposible eliminar, la Region posee medias asociados. Elimine los medias asociados para poder continuar",
                                                    QMessageBox::Ok);
                }
            }
        }
    }
}


/*!
 *\brief called when the Name value of a Region is changed. Set de name value in GrapchisRecItem
 *\param QTableWidgetItem *item
 *\return void
 */
void MainWindow::setNameValue(QTableWidgetItem *item)
{
    QString name = item->text();
    bool exist = false;
    QTreeWidgetItemIterator it(treeWidget);

    while (*it){
        if ((*it)->text(0) == name){
            exist = true;
            break;
        }
        ++it;
    }

    if(!exist){
        changePresent = true;
        QTreeWidgetItemIterator it2(treeWidget);
        while (*it2){
            if ((*it2)->text(0) == graphicsScene->getSelected()->getName()){
                (*it2)->setText(0,name);
            }
            ++it2;
        }
        graphicsScene->getSelected()->setName(name);

    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, tr("Precaucion!"),"Ya existe una region con ese nombre",QMessageBox::Ok);
    }
}


/*!
 *\brief called when the left (x) value of a Region is changed. Set de x value in GrapchisRecItem
 *\param int x
 *\return void
 */
void MainWindow::setXValue(int x)
{
    qreal y;
    QString percent;
    int value;
    GraphicsRectItem *rectItem;

    changePresent = true;
    if(graphicsScene->getSelected()->getYRecNCL().contains("%") && graphicsScene->getSelected()->parentItem() == 0){
        percent = graphicsScene->getSelected()->getYRecNCL().remove("%");
        value = (percent.toInt()*screenSizeY)/100;
        y = (qreal) value;

    }else if(graphicsScene->getSelected()->getYRecNCL().contains("%")){
        percent = graphicsScene->getSelected()->getYRecNCL().remove("%");
        rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());

        value = (percent.toInt()*rectItem->getHeightRec())/100;
        y = (qreal) value;

    }else{
        y = (qreal) spinY->value();
    }

    if(comboX->currentText() == "%"){
        if(graphicsScene->getSelected()->parentItem() == 0){
            value = (x*screenSizeX)/100;
            graphicsScene->getSelected()->setXNCL(QString::number(x)+"%");
            graphicsScene->getSelected()->setPosistionXY((qreal)value,y);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (x*rectItem->getWidthRec())/100;
            graphicsScene->getSelected()->setXNCL(QString::number(x)+"%");
            graphicsScene->getSelected()->setPosistionXY((qreal)value,y);
        }
    }else{
        graphicsScene->getSelected()->setXNCL(QString::number(x));
        graphicsScene->getSelected()->setPosistionXY((qreal)x,y);
    }

}


/*qreal MainWindow::getWidth(QString widthNCL, int widhtParent)
{
    QString percent = widthNCL.remove("%");
    int value = (percent.toInt()*widhtParent)/100;
    changePresent = true;
    return (qreal) value;
}*/


/*!
 *\brief called when the top (y) value of a Region is changed. Set de y value in GrapchisRecItem
 *\param int y
 *\return void
 */
void MainWindow::setYValue(int y)
{
    qreal x;
    QString percent;
    int value;
    GraphicsRectItem *rectItem;
    changePresent = true;

    if(graphicsScene->getSelected()->getXRecNCL().contains("%") && graphicsScene->getSelected()->parentItem() == 0){
        percent = graphicsScene->getSelected()->getXRecNCL().remove("%");
        value = (percent.toInt()*screenSizeX)/100;
        x = (qreal) value;

    }else if(graphicsScene->getSelected()->getXRecNCL().contains("%")){
        percent = graphicsScene->getSelected()->getXRecNCL().remove("%");
        rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());

        value = (percent.toInt()*rectItem->getWidthRec())/100;
        x = (qreal) value;

    }else{
        x = (qreal) spinX->value();
    }

    if(comboY->currentText() == "%"){
        if(graphicsScene->getSelected()->parentItem() == 0){
            value = (y*screenSizeY)/100;
            graphicsScene->getSelected()->setYNCL(QString::number(y)+"%");
            graphicsScene->getSelected()->setPosistionXY(x,(qreal)value);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (y*rectItem->getHeightRec())/100;
            graphicsScene->getSelected()->setYNCL(QString::number(y)+"%");
            graphicsScene->getSelected()->setPosistionXY(x,(qreal)value);
        }
    }else{
        graphicsScene->getSelected()->setYNCL(QString::number(y));
        graphicsScene->getSelected()->setPosistionXY(x,(qreal)y);
    }
}


/*!
 *\brief called when the width value of a Region is changed. Set de width value in GrapchisRecItem
 *\param int w
 *\return void
 */
void MainWindow::setWValue(int w)
{
    int value;
    GraphicsRectItem *rectItem;
    changePresent = true;
    if(comboW->currentText() == "%"){
        if(graphicsScene->getSelected()->parentItem() == 0){
            value = (w*screenSizeX)/100;
            graphicsScene->getSelected()->setWidthNCL(QString::number(w)+"%");
            graphicsScene->getSelected()->setWidth(value);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (w*rectItem->getWidthRec())/100;
            graphicsScene->getSelected()->setWidthNCL(QString::number(w)+"%");
            graphicsScene->getSelected()->setWidth(value);
        }
    }else{
        graphicsScene->getSelected()->setWidthNCL(QString::number(w));
        graphicsScene->getSelected()->setWidth(w);
    }
}


/*!
 *\brief called when the height value of a Region is changed. Set de height value in GrapchisRecItem
 *\param int h
 *\return void
 */
void MainWindow::setHValue(int h)
{
    int value;
    GraphicsRectItem *rectItem;
    changePresent = true;
    if(comboH->currentText() == "%"){
        if(graphicsScene->getSelected()->parentItem() == 0){
            value = (h*screenSizeY)/100;
            graphicsScene->getSelected()->setHeighNCL(QString::number(h)+"%");
            graphicsScene->getSelected()->setHeight(value);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (h*rectItem->getHeightRec())/100;
            graphicsScene->getSelected()->setHeighNCL(QString::number(h)+"%");
            graphicsScene->getSelected()->setHeight(value);
        }
    }else{
        graphicsScene->getSelected()->setHeighNCL(QString::number(h));
        graphicsScene->getSelected()->setHeight(h);
    }
}


/*!
 *\brief called when the zIndex value of a Region is changed. Set de zIndex value in GrapchisRecItem
 *\param int z
 *\return void
 */
void MainWindow::setZValue(int z)
{
    changePresent = true;
    graphicsScene->getSelected()->setZValue(z);
}


/*!
 *\brief called when the type of value of the x value is changed to percet or pixel.
 *\return void
 */
void MainWindow::setXValueCombo()
{
    changePresent = true;
    this->setXValue(spinX->value());
}


/*!
 *\brief called when the type of value of the y value is changed to percet or pixel.
 *\return void
 */
void MainWindow::setYValueCombo()
{
    changePresent = true;
    this->setYValue(spinY->value());
}


/*!
 *\brief called when the type of value of the height value is changed to percet or pixel.
 *\return void
 */
void MainWindow::setHValueCombo()
{
    changePresent = true;
    this->setHValue(spinH->value());
}


/*!
 *\brief called when the type of value of the width value is changed to percet or pixel.
 *\return void
 */
void MainWindow::setWValueCombo()
{
    changePresent = true;
    this->setWValue(spinW->value());
}


/*!
 *\brief called when a region (GraphicsRectItem) is selected to display their atributtes and medias.
 *\param GraphicsRectItem *item
 *\return void
 */
void MainWindow::itemSelected(GraphicsRectItem *item)
{
    connect(item, SIGNAL(mouseMoveX(qreal,qreal)),horizontalRule,SLOT(rectChange(qreal,qreal)));
    connect(item, SIGNAL(mouseMoveY(qreal,qreal)),verticalRule,SLOT(rectChange(qreal,qreal)));

    int value;
    GraphicsRectItem *rectItem;

    QTreeWidgetItemIterator it(treeWidget);
    while (*it) {
        if ((*it)->text(0) == item->getName()){
            treeWidget->setCurrentItem((*it));
        }
        ++it;
    }

    propertyRegionTable->setRowCount(6);

    propertyRegionTable->blockSignals(true);
    spinX->blockSignals(true);
    spinY->blockSignals(true);
    spinH->blockSignals(true);
    spinW->blockSignals(true);
    spinZ->blockSignals(true);
    comboX->blockSignals(true);
    comboY->blockSignals(true);

    propertyRegionTable->item(0, 1)->setText(item->getName());

    if(item->getXRecNCL().contains("%")){
        if(item->parentItem()==0){
            int xxxx = round(item->x());
            value = (xxxx*100)/screenSizeX;
            spinX->setValue(value);
            comboX->setCurrentIndex(1);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (item->x()*100)/rectItem->getWidthRec();
            spinX->setValue(value);
            comboX->setCurrentIndex(1);
        }
    }else{
        spinX->setValue(item->x());
        comboX->setCurrentIndex(0);
    }

    if(item->getYRecNCL().contains("%")){
        if(item->parentItem()==0){
            value = (item->y()*100)/screenSizeY;
            spinY->setValue(value);
            comboY->setCurrentIndex(1);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (item->y()*100)/rectItem->getHeightRec();
            spinY->setValue(value);
            comboY->setCurrentIndex(1);
        }
    }else{
        spinY->setValue(item->y());
        comboY->setCurrentIndex(0);
    }

    if(item->getWidthRecNCL().contains("%")){
        if(item->parentItem()==0){
            value = (item->getWidthRec()*100)/screenSizeX;
            spinW->setValue(value);
            comboW->setCurrentIndex(1);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (item->getWidthRec()*100)/rectItem->getWidthRec();
            spinW->setValue(value);
            comboW->setCurrentIndex(1);
        }
    }else{
        spinW->setValue(item->getWidthRec());
        comboW->setCurrentIndex(0);
    }


    if(item->getHeighRecNCL().contains("%")){
        if(item->parentItem()==0){
            value = (item->getHeightRec()*100)/screenSizeY;
            spinH->setValue(value);
            comboH->setCurrentIndex(1);
        }else{
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->getSelected()->parentItem());
            value = (item->getHeightRec()*100)/rectItem->getHeightRec();
            spinH->setValue(value);
            comboH->setCurrentIndex(1);
        }
    }else{
        spinH->setValue(item->getHeightRec());
        comboH->setCurrentIndex(0);
    }

    spinZ->setValue(item->zValue());

    propertyRegionTable->blockSignals(false);
    spinX->blockSignals(false);
    spinY->blockSignals(false);
    spinH->blockSignals(false);
    spinW->blockSignals(false);
    spinZ->blockSignals(false);
    comboX->blockSignals(false);
    comboY->blockSignals(false);

    loadMediasRegion();
}


/*!
 *\brief opens a file chooser to choose a media Video to import and add to the list
 *\return void
 */
void MainWindow::fileChoserVideo()
{
    QStringList filesNames;
    int i;

    QString name;
    QString types;
    bool exist = false;
    QTableWidgetItem *item;

    videoListPos = videoList->rowCount();

    videoFiles.clear();
    videoFiles = QFileDialog::getOpenFileNames(this, tr("Abrir Media"), "/", tr("Archivos Medias Video (*.mp2 *.mpeg *.mpg *.mpe *.mp4 *.mpg4 *.mng *.qt *.mov *.avi)"));

    if (!videoFiles.isEmpty()){
        filesNames.clear();
        for (i=0; i < videoFiles.size(); i++){
           name = videoFiles.at(i);

           filesNames.append(name.remove(0, name.lastIndexOf('/')+1));

           QDir *path = new QDir(videoFiles.at(i));

           QString videoPath = videoFiles.at(i);
           videoPath.replace(QString(" "), QString("\\ "));
           QString videoName = filesNames.at(i);
           videoName.replace(QString(" "), QString("\\ "));
           videoName.append(".jpg");

           for (int j = 0; j < importVideoList.size();j++){
               if (importVideoList.at(j)->absolutePath() == path->absolutePath()){
                   exist = true;               
                   videoFiles.removeAt(i);
                   filesNames.removeAt(i);
                   i--;
               }
           }
           if(exist){
               exist = false;
               QMessageBox::StandardButton reply;
               reply = QMessageBox::information(this, tr("Cargar Archivo"), "El archivo \""+name+"\" ya ha sido importado con anterioridad");
           }else{
               importVideoList.append(path);
               QString cmd = "ffmpeg -i "+videoPath+" -ss 3.001 -t 3.001 -y images/"+videoName;
               int numError = system(cmd.toAscii());
               if (numError!=256){
                   QMessageBox::StandardButton reply;
                   reply = QMessageBox::information(this, tr("Cargar Archivo"), "Necesita instalar ffmpeg en su sitema para poder cargar los videos");
                   exist = false;
                   break;

               }else{

                   QIcon icon(QPixmap(QDir::currentPath()+"/images/"+filesNames.at(i)+".jpg"));

                   item = new QTableWidgetItem();
                   item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                   item->setText(filesNames.at(i));
                   item->setIcon(icon);
                   item->setToolTip(path->absolutePath());

                   videoList->setRowCount(videoList->rowCount()+1);
                   videoList->setItem(videoList->rowCount()-1,0,item);
                   videoList->setIconSize(QSize(50,50));
                   videoList->setRowHeight(videoList->rowCount()-1,50);

                   changePresent = true;
               }
            }
        }
    }
}


/*!
 *\brief opens a file chooser to choose a media Audio to import and add to the list
 *\return void
 */
void MainWindow::fileChoserAudio()
{
    QStringList filesNames;
    int i;
    QString name;
    bool exist = false;
    QTableWidgetItem *item;
    audioListPos = audioList->rowCount();
    audioFiles.clear();
    audioFiles = QFileDialog::getOpenFileNames(this, tr("Abrir Media"), "/", tr("Archivos Medias Audio (*.ua *.wav *.mp1 *.mp2 *.mp3 *.mpg4)"));

    if (!audioFiles.isEmpty()){
        filesNames.clear();
        for (i=0; i < audioFiles.size(); i++){
           name = audioFiles.at(i);
           QDir *path = new QDir(audioFiles.at(i));
           filesNames.append(name.remove(0, name.lastIndexOf('/')+1));
           QString extension = filesNames.at(i);

           for (int j = 0; j < importAudioList.size();j++){
               if (importAudioList.at(j)->absolutePath() == path->absolutePath()){
                   exist = true;
                   audioFiles.removeAt(i);
                   filesNames.removeAt(i);
                   i--;
               }
           }
           if(exist){
               QMessageBox::StandardButton reply;
               reply = QMessageBox::information(this, tr("Cargar Archivo"), "El archivo \""+name+"\" ya ha sido importado con anterioridad");
               exist = false;
           }else{
               importAudioList.append(path);

               QString icon;
               extension = extension.toLower();
               if (extension.endsWith(".ua"))
               {
                    icon = QDir::currentPath()+"/images/audioFiles/UA.png";
               }
               if (extension.endsWith(".wav"))
               {
                    icon = QDir::currentPath()+"/images/audioFiles/wav.png";
               }
               if (extension.endsWith(".mp1"))
               {
                    icon = QDir::currentPath()+"/images/audioFiles/MP1.png";
               }
               if (extension.endsWith(".mp2"))
               {
                    icon = QDir::currentPath()+"/images/audioFiles/MP2.png";
               }
               if (extension.endsWith(".mp3"))
               {
                    icon = QDir::currentPath()+"/images/audioFiles/mp3.png";
               }

               if (extension.endsWith(".mpg4"))
               {
                   icon = QDir::currentPath()+"/images/audioFiles/MPG4.png";
               }

               item = new QTableWidgetItem();
               item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
               item->setText(filesNames.at(i));
               item->setIcon(QIcon(icon));
               item->setToolTip(path->absolutePath());

               audioList->setRowCount(audioList->rowCount()+1);
               audioList->setItem(audioList->rowCount()-1,0,item);
               audioList->setIconSize(QSize(50,50));
               audioList->setRowHeight(audioList->rowCount()-1,50);
               changePresent = true;
            }
        }
    }
}


/*!
 *\brief opens a file chooser to choose a media Image to import and add to the list
 *\return void
 */
void MainWindow::fileChoserImage()
{
    QStringList filesNames;
    QStringList files;
    int i;
    QString name;
    QString types;
    bool exist = false;
    files = QFileDialog::getOpenFileNames(this, tr("Abrir Media"), "/", tr("Archivos Medias Imagen (*.bmp *.png *.gif *.jpg *.jpeg *.jpe)"));

    if (!files.isEmpty()){
        filesNames.clear();
        for (i=0; i < files.size(); i++){
           name = files.at(i);
           filesNames.append(name.remove(0, name.lastIndexOf('/')+1));
           QDir *path = new QDir(files.at(i));
           for (int j = 0; j < importImageList.size();j++){
               if (importImageList.at(j)->absolutePath() == path->absolutePath()){
                   exist = true;

               }
           }
           if(exist){
               QMessageBox::StandardButton reply;
               reply = QMessageBox::information(this, tr("Cargar Archivo"), "El archivo \""+name+"\" ya ha sido importado con anterioridad");
               exist = false;
           }else{
               importImageList.append(path);

               QIcon icon(QPixmap(files.at(i)));
               new QListWidgetItem(icon,filesNames.at(i),imageList);
               imageList->setIconSize(QSize(50,50));
               changePresent = true;
           }
        }
    }
}


/*!
 *\brief opens a file chooser to choose a media Text to import and add to the list
 *\return void
 */
void MainWindow::fileChoserText()
{
    QStringList filesNames;
    QStringList files;
    int i;
    QString name;
    bool exist = false;
    files = QFileDialog::getOpenFileNames(this, tr("Abrir Media"), "/", tr("Archivos Medias Texto (*.htm *.html *.css *.xml *.txt )"));

    if (!files.isEmpty()){
        filesNames.clear();
        for (i=0; i < files.size(); i++){
           name = files.at(i);
           filesNames.append(name.remove(0, name.lastIndexOf('/')+1));
           QString extension = filesNames.at(i);
           QDir *path = new QDir(files.at(i));
           for (int j = 0; j < importTextList.size();j++){
               if (importTextList.at(j)->absolutePath() == path->absolutePath()){
                   exist = true;

               }
           }
           if(exist){
               QMessageBox::StandardButton reply;
               reply = QMessageBox::information(this, tr("Cargar Archivo"), "El archivo \""+name+"\" ya ha sido importado con anterioridad");
               exist = false;
           }else{
               importTextList.append(path);

               extension = extension.toLower();
               if (extension.endsWith(".html"))
               {
                    QIcon icon(QPixmap(QDir::currentPath()+"/images/textFiles/html_file.png"));
                    new QListWidgetItem(icon,filesNames.at(i),textList);
               }
               if (extension.endsWith(".htm"))
               {
                    QIcon icon(QPixmap(QDir::currentPath()+"/images/textFiles/htm_file.png"));
                    new QListWidgetItem(icon,filesNames.at(i),textList);
               }
               if (extension.endsWith(".css"))
               {
                    QIcon icon(QPixmap(QDir::currentPath()+"/images/textFiles/css_file.png"));
                    new QListWidgetItem(icon,filesNames.at(i),textList);
               }
               if (extension.endsWith(".xml"))
               {
                    QIcon icon(QPixmap(QDir::currentPath()+"/images/textFiles/xml_file.png"));
                    new QListWidgetItem(icon,filesNames.at(i),textList);
               }
               if (extension.endsWith(".txt"))
               {
                    QIcon icon(QPixmap(QDir::currentPath()+"/images/textFiles/txt_file.png"));
                    new QListWidgetItem(icon,filesNames.at(i),textList);
               }

               textList->setIconSize(QSize(50,50));
               changePresent = true;

            }
        }
    }
}


/*!
 *\brief opens a file chooser to choose a media Lua to import and add to the list
 *\return void
 */
void MainWindow::fileChoserLua()
{
    QStringList filesNames;
    QStringList files;
    int i;
    QString name;
    bool exist = false;
    files = QFileDialog::getOpenFileNames(this, tr("Abrir Media"), "/", tr("Archivos Medias Lua (*.lua)"));

    if (!files.isEmpty()){
        filesNames.clear();
        for (i=0; i < files.size(); i++){
           name = files.at(i);
           filesNames.append(name.remove(0, name.lastIndexOf('/')+1));
           QDir *path = new QDir(files.at(i));
           for (int j = 0; j < importLuaList.size();j++){
               if (importLuaList.at(j)->absolutePath() == path->absolutePath()){
                   exist = true;
               }
           }
           if(exist){
               QMessageBox::StandardButton reply;
               reply = QMessageBox::information(this, tr("Cargar Archivo"), "El archivo \""+name+"\" ya ha sido importado con anterioridad");
               exist = false;
           }else{
               importLuaList.append(path);

               QIcon icon(QPixmap(QDir::currentPath()+"/images/lua_icon.png"));
               new QListWidgetItem(icon,filesNames.at(i),luaList);
           }
           luaList->setIconSize(QSize(50,50));
           changePresent = true;
        }
    }
}


/*!
 *\brief opens a file chooser to choose a media Url to import and add to the list
 *\return void
 */
void MainWindow::fileChoserUri()
{
    UriConfig u(this);
    if(u.exec()== QDialog::Accepted){
        if(u.getUri() != ""){
            importUriList.append(u.getUri());
            QIcon icon(QPixmap(QDir::currentPath()+"/images/uri_icon.png"));
            new QListWidgetItem(icon,u.getName(),uriList);
            uriList->setIconSize(QSize(50,50));
            changePresent = true;
        }
    }
}


/*!
 *\brief called to open a GUI to specify the project description
 *\return void
 */
void MainWindow::newProject(){
    QDate date ;
    newProject("","",100,100,date);
}


/*!
 *\brief creates a new project
 *\param QString description
 *\param QString selected
 *\param int w
 *\param int h
 *\param QDate date
 *\return void
 */
void MainWindow::newProject(QString description,QString selected,int w,int h, QDate date)
{
    if(changePresent){
        QMessageBox msgBox(QMessageBox::Warning, tr("Cambios Realizados"),
                           "¿Decea guardar cambios realizados?", 0, this);
        msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
        msgBox.addButton(tr("No"), QMessageBox::RejectRole);

        if (msgBox.exec() == QMessageBox::AcceptRole)
            save();

    }
    NewProject p(description,selected,w, h,date,this);
    if(p.exec() == QDialog::Accepted){
        createProject(p.getNameProject(),p.getDescription(),p.getDate(),p.getScreenSelected(),p.getWidth(),p.getHeight());
    }
}


/*!
 *\brief creates a new project with name \a projectName, description \a projectDescription, date \a projectDate, screen size \a screen (or  \a width x \a height)
 *\param QString projectName
 *\param QString projectDescription
 *\param QDate projectDate
 *\param QString screen
 *\param int width
 *\param int height
 *\return void
 */
void MainWindow::createProject(QString projectName,QString projectDescription,QDate projectDate, QString screen, int width, int height)
{
    nameProject = projectName;
    descriptionProject = projectDescription;
    dateProject = projectDate;
    if(nameProject==""){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, tr("Nombre del Proyecto"), "Debe darle un nombre al proyecto");
        newProject(descriptionProject,screen,width,height,dateProject);
    }else{
        setWindowTitle("CreaTVDigital - "+nameProject);
        initEnable(true);
        if( screen == "palN"){
            setSizeScreenPALN();
            ui->actionPALN->setChecked(true);
            ui->actionRegionPALN->setChecked(true);
            setVisibleHDTVi(false);
            setVisibleHDTVp(false);
            setVisiblePALAncho(false);
        }
        if(screen == "palAncho"){
            setSizeScreenPALAncho();
            ui->actionPALAncho->setChecked(true);
            ui->actionRegionPALAncho->setChecked(true);
            setVisiblePALN(false);
            setVisibleHDTVi(false);
            setVisibleHDTVp(false);
        }
        if(screen == "hdtvp"){
            setSizeScreenHDTV720p();
            ui->actionHDTV720->setChecked(true);
            ui->actionRegionHDTV720p->setChecked(true);
            setVisiblePALN(false);
            setVisiblePALAncho(false);
            setVisibleHDTVi(false);
        }
        if(screen == "hdtvi"){
            setSizeScreenHDTV1080i();
            ui->actionHDTV1080->setChecked(true);
            ui->actionRegionHDTV1080i->setChecked(true);
            setVisiblePALN(false);
            setVisiblePALAncho(false);
            setVisibleHDTVp(false);
        }
        if(screen == "noEsp"){
            setSizeScreenPALN();
            ui->actionPALN->setChecked(true);
            ui->actionPALAncho->setChecked(true);
            ui->actionHDTV720->setChecked(true);
            ui->actionHDTV1080->setChecked(true);
            ui->actionRegionPALN->setChecked(true);
        }
        if(screen == "otro"){
            QPen *pen = new QPen(Qt::SolidPattern, 2.0,Qt::DashDotLine , Qt::SquareCap,Qt::MiterJoin);
            pen->setColor(QColor(127,127,243,255));

            screenSizeX = width;
            screenSizeY = height;

            otherAction = new QAction(this);
            otherRegionAction = new QAction(this);

            otherAction->setText("Marca de pantalla otro ("+QString::number(screenSizeX)+"x"+QString::number(screenSizeY)+"px)");
            otherAction->setCheckable(true);
            otherAction->setChecked(true);

            otherRegionAction->setText("Relacion Region/Otro ("+QString::number(screenSizeY)+"x"+QString::number(screenSizeY)+"px)");
            otherRegionAction->setCheckable(true);
            otherRegionAction->setChecked(true);

            groupScreens->addAction(otherRegionAction);

            ui->menuVer->addAction(otherAction);
            ui->menuVer->addAction(otherRegionAction);
            ui->menuVer->addSeparator();

            if(screenSizeOtherX != 0){
                graphicsScene->removeItem(otherScreen);
                graphicsScene->removeItem(otherScreenText1);
                graphicsScene->removeItem(otherScreenText2);
            }

            screenSizeOtherX = screenSizeX;
            screenSizeOtherY = screenSizeY;

            otherScreen = new QGraphicsRectItem();
            otherScreen->setFlag(QGraphicsItem::ItemIsMovable,false);
            otherScreen->setRect(QRectF(0, 0, screenSizeOtherX,screenSizeOtherY));
            otherScreen->setPen(*pen);
            graphicsScene->addItem(otherScreen);

            otherScreenText1 = new QGraphicsTextItem("Otro - "+QString::number(screenSizeOtherX)+"x"+QString::number(screenSizeOtherY)+" px");
            otherScreenText1->setDefaultTextColor(QColor(127,127,243,255));
            otherScreenText1->setPos(screenSizeOtherX+5,0);
            graphicsScene->addItem(otherScreenText1);

            otherScreenText2 = new QGraphicsTextItem("Otro - "+QString::number(screenSizeOtherX)+"x"+QString::number(screenSizeOtherY)+" px");
            otherScreenText2->setDefaultTextColor(QColor(127,127,243,255));
            otherScreenText2->setPos(0,screenSizeOtherY);
            graphicsScene->addItem(otherScreenText2);

            connect(otherAction, SIGNAL(toggled(bool)), this, SLOT(setVisibleOther(bool)));
            connect(otherRegionAction, SIGNAL(triggered()), this, SLOT(setSizeScreenOther()));

            setSizeScreenOther();
            setVisiblePALN(false);
            setVisiblePALAncho(false);
            setVisibleHDTVp(false);
            setVisibleHDTVi(false);
        }
        modifyOtherRegionAction = new QAction(this);
        modifyOtherRegionAction->setText("Seleccionar otro formato de pantalla...");
        connect(modifyOtherRegionAction, SIGNAL(triggered()), this, SLOT(setSizeOther()));
        ui->menuVer->addAction(modifyOtherRegionAction);
    }
}


/*!
 *\brief adds a DescriptorParam to \a descriptorList
 *\return void
 */
void MainWindow::addPropertyToDescriptor()
{
    int lineNumber;
    QString nameMedia;
    QString nameMediaDescriptor;
    Image* currentImage;
    QList<QGraphicsItem *> allItems = graphicsSceneHead->items();
    for(int i = 0; i < allItems.size();i++){
        if(allItems.at(i)->type() == 7){//is Image
            currentImage =  qgraphicsitem_cast<Image *>(allItems.at(i));
            if(currentImage->getMyType() == Image::TypeMedia){
                lineNumber = currentImage->scenePos().y() / LINESIZE;
                nameMedia = graphicsSceneHead->NameMediaInLineNumber(lineNumber);
                for(int j = 0; j < descriptorList.size();j++){
                    nameMediaDescriptor = descriptorList.at(j)->getId();
                    nameMediaDescriptor = nameMediaDescriptor.remove("descriptor-");
                    if (nameMedia == nameMediaDescriptor){
                        for(int k = 0; k < currentImage->getDescriptorParamList().size();k++){
                            descriptorList.at(j)->addDescriptorParam(currentImage->getDescriptorParamList().at(k));
                        }
                    }
                }
            }
        }
    }
}


void MainWindow::createNCL()
{
    QString path = NULL;
    QString pathAux;
    path = QFileDialog::getSaveFileName(this,tr("Crear NCL"),myFileName,tr("*.ncl"));
    nclName = path;
    if(!path.isNull()){
        pathAux = path;
        pathAux.remove(pathAux.lastIndexOf('/')+1,pathAux.count());

        QFile connector(QDir::currentPath()+"/connector/causalConnBase.ncl");
        QFile dir(pathAux+"causalConnBase.ncl");
        if(!connector.copy(pathAux+"causalConnBase.ncl")){
            if(!dir.exists()){
                QMessageBox::StandardButton reply;
                reply = QMessageBox::warning(this, tr("Precaucion!"),"Error al copiar causalConnBase.ncl",QMessageBox::Ok);
            }
        }

        addPropertyToDescriptor();
        NclDocument *nclDocument = new NclDocument();
        cout<<"here" << endl;
        nclDocument->createNCL(graphicsScene,graphicsSceneHead,graphicsSceneTemporal,path,mediaVideoList,mediaAudioList,mediaImageList,mediaTextList,mediaLuaList,mediaUriList,descriptorList);
        cout<<"here2" << endl;
    }
}


/*!
 *\brief init the widgets to Regions treatments
 *\return void
 */
void MainWindow::initRegionsArea()
{
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    mainLayout->setContentsMargins(0,0,0,0);

    /**Area para dibujar y reglas*/

    QGridLayout *layout = new QGridLayout;
    graphicsView = new QGraphicsView;

    QGroupBox *horizontalGroupBox = new QGroupBox;
    QGroupBox *verticalGroupBox = new QGroupBox;

    horizontalRule = new QUnitMargin(2500,horizontalGroupBox);
    horizontalRule->setGeometry(0,0,2500,30);

    verticalRule = new QUnitMarginVertical(1660,verticalGroupBox);
    verticalRule->setGeometry(0,0,30,1660);

    layout->addWidget(horizontalGroupBox,0,1,1,1);
    layout->addWidget(verticalGroupBox,1,0,1,1);
    layout->addWidget(graphicsView,1,1,1,1);
    mainLayout->addLayout(layout);

    QWidget *widget = new QWidget;
    widget->setLayout(mainLayout);

    QMainWindow *mainRegion = new QMainWindow(this);
    mainRegion->setCentralWidget(widget);

    ui->dockWidget_2->setWidget(mainRegion);
    ui->menuVer->insertAction(ui->actionPALN,ui->dockWidget_2->toggleViewAction());

    connect(graphicsView->horizontalScrollBar(), SIGNAL(valueChanged(int)),this,SLOT(moveHorizontalRule(int)));
    connect(graphicsView->verticalScrollBar(), SIGNAL(valueChanged(int)),this,SLOT(moveVerticalRule(int)));

    /**Tool bar*/

    editToolBar = new QToolBar("Herramientas",mainRegion);
    editToolBar->setIconSize(QSize(35,35));
    mainRegion->addToolBar(Qt::LeftToolBarArea,editToolBar);

    mouseAction = new QAction(mainRegion);
    mouseAction->setIcon(QIcon("icons/mouseIcon.png"));
    mouseAction->setToolTip("Seleccionar");
    mouseAction->setCheckable(true);

    zoomInAction = new QAction(mainRegion);
    zoomInAction->setIcon(QIcon("icons/zoomIn.png"));
    zoomInAction->setToolTip("Acercar");
    connect(zoomInAction, SIGNAL(triggered()),this, SLOT(zoomIn()));

    zoomOutAction = new QAction(mainRegion);
    zoomOutAction->setIcon(QIcon("icons/zoomOut.png"));
    zoomOutAction->setToolTip("Alejar");
    connect(zoomOutAction, SIGNAL(triggered()),this, SLOT(zoomOut()));

    resetZoomAction = new QAction(mainRegion);
    resetZoomAction->setIcon(QIcon("icons/resetZoom.png"));
    resetZoomAction->setToolTip("Restaurar Zoom");
    connect(resetZoomAction, SIGNAL(triggered()),this, SLOT(resetZoom()));

    spinBoxZoom = new QSpinBox(mainRegion);
    spinBoxZoom->setMinimum(20);
    spinBoxZoom->setMaximum(10000);
    spinBoxZoom->setPrefix("%");
    spinBoxZoom->setValue(100);
    connect(spinBoxZoom, SIGNAL(valueChanged(int)),this, SLOT(zoomInOut(int)));

    QActionGroup* actionGroup;
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(ui->actionNewRegion);
    actionGroup->addAction(mouseAction);

    editToolBar->addAction(mouseAction);
    editToolBar->addAction(ui->actionNewRegion);
    editToolBar->addSeparator();
    editToolBar->addAction(zoomInAction);
    editToolBar->addAction(zoomOutAction);
    editToolBar->addAction(resetZoomAction);
    editToolBar->addWidget(spinBoxZoom);
    editToolBar->addSeparator();

    ui->actionNewRegion->setIcon(QIcon("icons/addRegion.png"));
    connect(ui->actionNewRegion, SIGNAL(triggered()),this, SLOT(addRegion()));
    connect(mouseAction, SIGNAL(triggered()),this, SLOT(selectButton()));

    /***/

    graphicsView->setMouseTracking(true);
    graphicsScene  = new GraphicsScene(ui->menuItem);

    graphicsView->setScene(graphicsScene);
    graphicsView->centerOn(0,0);
    graphicsView->setAcceptDrops(true);
    graphicsView->setBaseSize(900, 500);
    graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    originalMatrix = graphicsView->matrix();
}


/*!
 *\brief initializes the docks area of the main window with its elements
 *\return void
 */
void MainWindow::initDockTools()
{
    QBoxLayout *treeTableLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    /**Arbol de Regiones*/
    treeWidget = new QTreeWidget(/*mainRegion*/);
    treeWidget->setHeaderLabel("Arbol");
    treeTableLayout->addWidget(treeWidget);

    /**Tabla de atributos de las regiones*/

    QStringList columns = QStringList();
    columns.append("Atributo");
    columns.append("Valor");
    columns.append("");
    propertyRegionTable = new QTableWidget(6,3);
    propertyRegionTable->setColumnWidth(0,70);
    propertyRegionTable->setColumnWidth(1,70);
    propertyRegionTable->setColumnWidth(2,40);
    propertyRegionTable->setMaximumHeight(220);
    treeTableLayout->addWidget(propertyRegionTable);
    propertyRegionTable->setHorizontalHeaderLabels(columns);

    QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);
    propertyRegionTable->setGridStyle(pen.style());

    spinX = new QSpinBox();
    spinY = new QSpinBox();
    spinW = new QSpinBox();
    spinH = new QSpinBox();
    spinZ = new QSpinBox();

    spinX->setMaximum(2500);
    spinX->setMinimum(-2500);

    spinY->setMaximum(2000);
    spinY->setMinimum(-2000);

    spinW->setMaximum(2500);
    spinW->setMinimum(0);

    spinH->setMaximum(2000);
    spinH->setMinimum(0);

    spinZ->setMaximum(255);
    spinZ->setMinimum(0);

    comboX = new QComboBox();
    comboY = new QComboBox();
    comboH = new QComboBox();
    comboW = new QComboBox();

    comboX->insertItem(0,"px");
    comboX->insertItem(1,"%");
    comboY->insertItem(0,"px");
    comboY->insertItem(1,"%");
    comboH->insertItem(0,"px");
    comboH->insertItem(1,"%");
    comboW->insertItem(0,"px");
    comboW->insertItem(1,"%");


    QTableWidgetItem *newItem = new QTableWidgetItem();

    newItem = new QTableWidgetItem("Nombre");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(0, 0, newItem);
    newItem = new QTableWidgetItem("");
    propertyRegionTable->setItem(0, 1, newItem);
    newItem = new QTableWidgetItem("");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(0, 2, newItem);

    newItem = new QTableWidgetItem("Eje X");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(1, 0, newItem);
    propertyRegionTable->setCellWidget(1,1,spinX);
    propertyRegionTable->setCellWidget(1,2,comboX);

    newItem = new QTableWidgetItem("Eje Y");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(2, 0, newItem);
    propertyRegionTable->setCellWidget(2,1,spinY);
    propertyRegionTable->setCellWidget(2,2,comboY);

    newItem = new QTableWidgetItem("Ancho");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(3, 0, newItem);
    propertyRegionTable->setCellWidget(3,1,spinW);
    propertyRegionTable->setCellWidget(3,2,comboW);

    newItem = new QTableWidgetItem("Alto");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(4, 0, newItem);
    propertyRegionTable->setCellWidget(4,1,spinH);
    propertyRegionTable->setCellWidget(4,2,comboH);

    newItem = new QTableWidgetItem("Indice Z");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(5, 0, newItem);
    propertyRegionTable->setCellWidget(5,1,spinZ);
    newItem = new QTableWidgetItem("");
    newItem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    propertyRegionTable->setItem(5, 2, newItem);

    connect(propertyRegionTable,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(setNameValue(QTableWidgetItem*)));
    connect(spinX,SIGNAL(valueChanged(int)),this,SLOT(setXValue(int)));
    connect(spinY,SIGNAL(valueChanged(int)),this,SLOT(setYValue(int)));
    connect(spinW,SIGNAL(valueChanged(int)),this,SLOT(setWValue(int)));
    connect(spinH,SIGNAL(valueChanged(int)),this,SLOT(setHValue(int)));
    connect(spinZ,SIGNAL(valueChanged(int)),this,SLOT(setZValue(int)));

    connect(comboX,SIGNAL(currentIndexChanged(int)),this,SLOT(setXValueCombo()));
    connect(comboY,SIGNAL(currentIndexChanged(int)),this,SLOT(setYValueCombo()));
    connect(comboW,SIGNAL(currentIndexChanged(int)),this,SLOT(setWValueCombo()));
    connect(comboH,SIGNAL(currentIndexChanged(int)),this,SLOT(setHValueCombo()));

    //QWidget *spin = spinX;
    //connect(spin,SIGNAL(),this,SLOT(setSelectedFalse()));



    /**Tab*/

    tabRegions = new QTabWidget(/*mainRegion*/);
    QWidget *regions = new QWidget();

    tabRegions->setTabPosition(QTabWidget::West);
    tabRegions->addTab(regions,"Regiones");

    regions->setLayout(treeTableLayout);

    /**ToolBox*/
    QBoxLayout *importMediasLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *importOtherLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    QWidget *importMediasWidget = new QWidget;
    QWidget *importOtherWidget = new QWidget;

    importMediasToolBox = new QToolBox();
    importOtherToolBox = new QToolBox();

    importMediasWidget->setLayout(importMediasLayout);
    importOtherWidget->setLayout(importOtherLayout);

    videoList = new QTableWidget();
    audioList = new QTableWidget();
    imageList = new QListWidget();
    textList = new QListWidget();
    luaList = new QListWidget();
    uriList = new QListWidget();

    columns = QStringList();
    columns.append("Media");
    columns.append("Duracion");
    videoList->setColumnCount(2);
    videoList->setHorizontalHeaderLabels(columns);
    videoList->setColumnWidth(0,200);
    audioList->setColumnCount(2);
    audioList->setHorizontalHeaderLabels(columns);
    audioList->setColumnWidth(0,200);

    videoList->setDragEnabled(true);
    audioList->setDragEnabled(true);
    imageList->setDragEnabled(true);
    textList->setDragEnabled(true);
    luaList->setDragEnabled(true);
    uriList->setDragEnabled(true);

    importMediasToolBox->addItem(videoList,"Videos");
    importMediasToolBox->addItem(audioList,"Sonidos");
    importMediasToolBox->addItem(imageList,"Imagenes");
    importMediasToolBox->addItem(textList,"Texto");
    importOtherToolBox->addItem(luaList,"Lua");
    importOtherToolBox->addItem(uriList,"Uri");

    QToolButton *importMediaButton = new QToolButton();
    QPushButton *addMediaButton = new QPushButton();
    QToolButton *importOtherMediaButton = new QToolButton();
    QPushButton *addOtherMediaButton = new QPushButton();
    QPushButton *removeMediaButton = new QPushButton();

    addMediaButton->setIconSize(QSize(40,40));
    addMediaButton->setIcon(QIcon("icons/addMedia1.png"));
    addMediaButton->setFlat(true);
    addMediaButton->setToolTip("Agregar Media a Region");

    removeMediaButton->setIconSize(QSize(20,20));
    removeMediaButton->setIcon(QIcon("icons/DeleteRed.png"));
    removeMediaButton->setFlat(true);
    removeMediaButton->setToolTip("Eliminar media");

    addOtherMediaButton->setIconSize(QSize(40,40));
    addOtherMediaButton->setIcon(QIcon("icons/addMedia1.png"));
    addOtherMediaButton->setFlat(true);
    addOtherMediaButton->setToolTip("Agregar Media a Region");

    importMediaButton->setText("Importar");
    importOtherMediaButton->setText("Importar");

    QBoxLayout *botonesLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *botonesOtherLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    botonesLayout->addWidget(addMediaButton);
    botonesLayout->addWidget(removeMediaButton);
    botonesLayout->addStretch(1);
    botonesLayout->addWidget(importMediaButton);

    botonesOtherLayout->addWidget(addOtherMediaButton);
    botonesOtherLayout->addStretch(0);
    botonesOtherLayout->addWidget(importOtherMediaButton);

    importMediasLayout->addLayout(botonesLayout);
    importMediasLayout->addWidget(importMediasToolBox);

    importOtherLayout->addLayout(botonesOtherLayout);
    importOtherLayout->addWidget(importOtherToolBox);

    tabRegions->addTab(importMediasWidget,"Importar Medias");
    tabRegions->addTab(importOtherWidget,"Importar Otros");

    connect(importMediaButton,SIGNAL(clicked()),this,SLOT(generalFileChooser()));
    connect(addMediaButton,SIGNAL(clicked()),this,SLOT(addMediaToRegion()));
    connect(removeMediaButton,SIGNAL(clicked()),this,SLOT(removeMedia()));

    connect(importOtherMediaButton,SIGNAL(clicked()),this,SLOT(generalFileChooser()));
    connect(addOtherMediaButton,SIGNAL(clicked()),this,SLOT(addMediaToRegion()));

    this->setCorner(Qt::TopLeftCorner,Qt::LeftDockWidgetArea);
    this->setCorner(Qt::TopRightCorner,Qt::RightDockWidgetArea);

    /*----------------------------------------------*/

    /**Tab*/
    tabLists = new QTabWidget(/*mainTemporal*/);
    QWidget *usedMedias = new QWidget();
    QWidget *mediasRegion = new QWidget();

    tabLists->setTabPosition(QTabWidget::South);
    tabLists->addTab(mediasRegion,"Medias Region");
    tabLists->addTab(usedMedias,"Medias Usados");

    /**Botones Agregar Media a Vista Temporal*/
    QBoxLayout *usedMediaLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *mediasRegionLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    usedMediasList = new QTableWidget();
    mediasRegionList = new QTableWidget;

    usedMediasList->setColumnCount(4);
    mediasRegionList->setColumnCount(4);

    usedMediasList->setDragEnabled(true);
    mediasRegionList->setDragEnabled(true);

    QStringList regionComulmns = QStringList();
    regionComulmns.append("Media");
    regionComulmns.append("Usado");
    regionComulmns.append("Duracion");
    regionComulmns.append("Tipo");
    usedMediasList->setHorizontalHeaderLabels(regionComulmns);
    mediasRegionList->setHorizontalHeaderLabels(regionComulmns);

    usedMediasList->setColumnWidth(1,25);
    usedMediasList->setColumnWidth(0,190);
    mediasRegionList->setColumnWidth(1,25);
    mediasRegionList->setColumnWidth(0,190);

    usedMediasList->setIconSize(QSize(40,40));
    mediasRegionList->setIconSize(QSize(40,40));

    usedMediasList->setGridStyle(Qt::PenStyle());
    mediasRegionList->setGridStyle(Qt::PenStyle());

    QToolButton *delUsedMedia = new QToolButton();
    QToolButton *delMediaRegion = new QToolButton();

    delUsedMedia->setIconSize(QSize(20,20));
    delUsedMedia->setIcon(QIcon("icons/DeleteRed.png"));
    delMediaRegion->setIconSize(QSize(20,20));
    delMediaRegion->setIcon(QIcon("icons/DeleteRed.png"));

    QBoxLayout *botonesLayout1 = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout *botonesLayout2 = new QBoxLayout(QBoxLayout::LeftToRight);

    botonesLayout1->addWidget(delUsedMedia);
    botonesLayout1->addStretch(0);

    botonesLayout2->addWidget(delMediaRegion);
    botonesLayout2->addStretch(0);

    usedMediaLayout->addWidget(usedMediasList);
    usedMediaLayout->addLayout(botonesLayout1);

    mediasRegionLayout->addWidget(mediasRegionList);
    mediasRegionLayout->addLayout(botonesLayout2);

    usedMedias->setLayout(usedMediaLayout);
    mediasRegion->setLayout(mediasRegionLayout);

    connect(delUsedMedia,SIGNAL(pressed()),this,SLOT(removeMediasUsados()));
    connect(delMediaRegion,SIGNAL(released()),this,SLOT(removeMediasRegion()));

    connect(usedMediasList, SIGNAL(cellPressed(int,int)),graphicsSceneTemporal,SLOT(setTrueOkItemDrop()));
    connect(mediasRegionList, SIGNAL(cellPressed(int,int)),graphicsSceneTemporal,SLOT(setTrueOkItemDrop()));

    connect(usedMediasList, SIGNAL(cellPressed(int,int)),this,SLOT(setFlaseAllOkItemDrop()));
    connect(mediasRegionList, SIGNAL(cellPressed(int,int)),this,SLOT(setFlaseAllOkItemDrop()));

    /***/

    QDockWidget *dock = new QDockWidget(tr("Regiones"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(tabRegions);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    ui->menuVer->insertAction(ui->actionPALN,dock->toggleViewAction());

    dock = new QDockWidget(tr("Medias Regiones"), this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(tabLists);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    ui->menuVer->insertAction(ui->actionPALN,dock->toggleViewAction());
    ui->menuVer->insertSeparator(ui->actionPALN);

}


/*!
 *\brief called to select a key of remote control
 *\param Image *button
 *\param Image *startItemP
 *\param Image *endItemP
 *\return void
 */
void MainWindow::selectedButton(Image *button,Image* startItemP,Image* endItemP)
{
    QString buttonName = NULL;
    QString dirIcon;
    SelectKeyGUI control(this);
    if(control.exec() == QDialog::Accepted){
        buttonName = control.getButton();
        if(buttonName == NULL){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, tr("Precaucion!"),"Seleccione un boton",QMessageBox::Ok);
            selectedButton(button,startItemP,endItemP);
            return;
        }
        button->setKeyButton(buttonName);
        if(buttonName == "*")
            buttonName = "asterisco";
        else if(buttonName == "#")
            buttonName = "numeral";
        dirIcon = "icons/interactividad/" +buttonName+ ".png";
        QImage image(dirIcon);
        image = image.scaled(20,20 , Qt::IgnoreAspectRatio, Qt::FastTransformation);
        QPixmap pixTmp(QPixmap::fromImage(image));
        button->setPixmap(pixTmp);

    }else{
        graphicsSceneTemporal->removeItem(button);
        graphicsSceneTemporal->removeItem(startItemP->getAssociatedArrow());
        graphicsSceneTemporal->removeItem(startItemP);
        graphicsSceneTemporal->removeItem(endItemP);
    }
    interactivityAction->setChecked(false);
}


/*!
 *\brief called to select a button to the interactivity.
 *\param Image *button
 *\return void
 */
void MainWindow::setButton(Image *button)
{
    QString buttonName = NULL;
    QString dirIcon;
    SelectKeyGUI control(this);
    if(control.exec() == QDialog::Accepted){
        buttonName = control.getButton();
        if(buttonName == NULL){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, tr("Precaucion!"),"Seleccione un boton",QMessageBox::Ok);
            setButton(button);
            return;
        }
        button->setKeyButton(buttonName);
        if(buttonName == "*")
            buttonName = "asterisco";
        else if(buttonName == "#")
            buttonName = "numeral";
        dirIcon = "icons/interactividad/" +buttonName+ ".png";
        QImage image(dirIcon);
        image = image.scaled(20,20 , Qt::IgnoreAspectRatio, Qt::FastTransformation);
        QPixmap pixTmp(QPixmap::fromImage(image));
        button->setPixmap(pixTmp);
    }
    interactivityAction->setChecked(false);
}


/*!
 *\brief init the widgets to time line treatments (media iteractivity, media time life, etc.)
 *\return void
 */
void MainWindow::initTemporalArea()
{
    QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    mainLayout->setContentsMargins(0,0,0,0);

    /***/
    QMainWindow *mainTemporal = new QMainWindow;

    setCentralWidget(mainTemporal);

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(0,0,0,0);

    graphicsViewTemporalMedias = new QGraphicsView();
    graphicsViewTemporal = new QGraphicsView();

    graphicsSceneTemporal = new DiagramScene();
    graphicsSceneTemporal->setSceneRect(QRectF(0, 0, 775, 378));

    QGroupBox *timeGroupBox = new QGroupBox;

    timeRule = new QUnitMarginTime(graphicsSceneTemporal->width(),timeGroupBox);
    timeRule->setGeometry(0,0,graphicsSceneTemporal->width(),30);

    layout->addWidget(timeGroupBox,0,1,1,1);
    layout->addWidget(graphicsViewTemporal,1,1,1,1);
    layout->addWidget(graphicsViewTemporalMedias,1,0,1,1);

    QWidget *widget = new QWidget();
    widget->setLayout(layout);

    mainTemporal->setCentralWidget(widget);

    graphicsViewTemporalMedias->centerOn(0,0);
    graphicsViewTemporalMedias->setMaximumWidth(200);
    graphicsViewTemporalMedias->setMinimumWidth(200);
    graphicsViewTemporal->setAcceptDrops(true);

    graphicsViewTemporal->setScene(graphicsSceneTemporal);
    graphicsViewTemporal->setBaseSize(600, 378);
    graphicsViewTemporal->setAlignment(Qt::AlignTop);
    graphicsViewTemporal->centerOn(0,0);

    graphicsSceneHead = new DiagramSceneHead();

    graphicsSceneHead->setSceneRect(QRectF(0, 0, graphicsViewTemporalMedias->width()-15, graphicsSceneTemporal->height()));

    graphicsViewTemporalMedias->setScene(graphicsSceneHead);
    graphicsViewTemporalMedias->setAlignment(Qt::AlignTop);

    graphicsViewTemporal->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    graphicsSceneTemporal->update();
    graphicsSceneHead->update();
    graphicsViewTemporalMedias->update();
    graphicsViewTemporal->update();

    connect(graphicsSceneHead, SIGNAL(showWindowPropertiesMedia(QString,Image*)),this, SLOT(showWindowPropertiesMediaSlot(QString,Image*)));
    connect(graphicsSceneTemporal, SIGNAL(showEventsButton2(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)),this, SLOT(showEventsButtonSlot(QPointF,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList)));
    connect(graphicsSceneTemporal, SIGNAL(closeEventsButton2()),this, SLOT(closeEventsButtonSlot()));
    connect(graphicsSceneTemporal, SIGNAL(showWindows2(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)),this, SLOT(showWindowsSlot(Image*,QStringList,QStringList,QStringList,QStringList,QStringList,QStringList,QTableWidget*)));
    connect(graphicsSceneTemporal, SIGNAL(insertDescription(int,QImage,QString,bool)),graphicsSceneHead, SLOT(insertDescriptionMedia(int,QImage,QString,bool)));
    connect(graphicsSceneTemporal, SIGNAL(diagramSceneDrop(qreal)),this, SLOT(diagramSceneDrop(qreal)));    
    connect(graphicsSceneTemporal, SIGNAL(removeLineBetween(int ,int)),this, SLOT(removeLineBetweenSlot(int,int)));
    connect(graphicsSceneTemporal, SIGNAL(selectedBoton(Image*,Image*,Image*)),this, SLOT(selectedButton(Image*,Image*,Image*)));
    connect(graphicsSceneTemporal, SIGNAL(setButton(Image*)),this, SLOT(setButton(Image*)));
    connect(graphicsViewTemporal->verticalScrollBar(), SIGNAL(valueChanged(int)),this,SLOT(changeVerticalBar2(int)));
    connect(graphicsViewTemporalMedias->verticalScrollBar(), SIGNAL(valueChanged(int)),this,SLOT(changeVerticalBar(int)));
    connect(graphicsViewTemporal->horizontalScrollBar(), SIGNAL(valueChanged(int)),this,SLOT(moveHorizontalRuleTime(int)));
    connect(graphicsSceneTemporal, SIGNAL(mouseMove(QPointF)),timeRule,SLOT(mouseMove(QPointF)));

    /**ToolBar*/

    toolBar = new QToolBar("tool",mainTemporal);
    toolBar->setIconSize(QSize(35,35));
    mainTemporal->addToolBar(Qt::LeftToolBarArea,toolBar);

    deleteLineAction = new QAction(mainTemporal);
    deleteLineAction->setIcon(QIcon("icons/deleteLine.png"));
    deleteLineAction->setToolTip("Eliminar Linea de Tiempo");
    deleteLineAction->setCheckable(true);

    deleteInteractivityAction = new QAction(mainTemporal);
    deleteInteractivityAction->setIcon(QIcon("icons/hideRange.png"));
    deleteInteractivityAction->setToolTip("Eliminar Interactividad");
    deleteInteractivityAction->setCheckable(true);

    interactivityAction = new QAction(mainTemporal);
    interactivityAction->setIcon(QIcon("icons/interactividad.png"));
    interactivityAction->setToolTip("Insertar interactividad");
    interactivityAction->setCheckable(true);

    toolBar->addAction(deleteLineAction);
    toolBar->addAction(deleteInteractivityAction);
    toolBar->addSeparator();
    toolBar->addAction(interactivityAction);
    toolBar->addAction(ui->actionNavegacion_de_Teclas);
    ui->actionNavegacion_de_Teclas->setIcon(QIcon("icons/remote_controller.png"));

    QActionGroup* actionGroup;
    actionGroup = new QActionGroup(this);
    actionGroup->addAction(deleteLineAction);
    actionGroup->addAction(interactivityAction);

    connect(deleteLineAction,SIGNAL(triggered()),this,SLOT(deleteLine()));
    connect(interactivityAction,SIGNAL(triggered()),this,SLOT(addInteractivity()));
    connect(deleteInteractivityAction,SIGNAL(toggled(bool)),this,SLOT(hideInteractivity(bool)));
}


/*!
 *\brief shows the properties of an Image
 *\param QPointF posWindow
 *\param QStringList playList
 *\param QStringList stopList
 *\param QStringList pauseList
 *\param QStringList resumeList
 *\param QStringList abortList
 *\param QStringList setList
 *\return void
 */
void MainWindow::showEventsButtonSlot(QPointF posWindow,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList)
{
     QListWidget *listWidget = new QListWidget(widgetPropieties);
     listWidget->setObjectName(QString::fromUtf8("listWidget"));
     QListWidgetItem *item;

     for(int i=0; i<playList.size();i++){
         if(listWidget->count() < 11){
             item = new QListWidgetItem();
             item->setText(playList.at(i));
             item->setIcon(QIcon(QIcon("icons/start.png")));
             listWidget->addItem(item);
         }else
             break;
     }

     for(int i=0; i<stopList.size();i++){
         if(listWidget->count() < 11){
             item = new QListWidgetItem();
             item->setText(stopList.at(i));
             item->setIcon( QIcon(QIcon("icons/stop.png")));
             listWidget->addItem(item);
         }else
             break;
     }

     for(int i=0; i<pauseList.size();i++){
         if(listWidget->count() < 11){
             item = new QListWidgetItem();
             item->setText(pauseList.at(i));
             item->setIcon( QIcon(QIcon("icons/pause.png")));
             listWidget->addItem(item);
         }else
             break;
     }

     for(int i=0; i<resumeList.size();i++){
         if(listWidget->count() < 11){
             item = new QListWidgetItem();
             item->setText(resumeList.at(i));
             item->setIcon( QIcon(QIcon("icons/resume.png")));
             listWidget->addItem(item);
         }else
             break;
     }

     for(int i=0; i<abortList.size();i++){
         if(listWidget->count() < 11){
             item = new QListWidgetItem();
             item->setText(abortList.at(i));
             item->setIcon( QIcon(QIcon("icons/abort.png")));
             listWidget->addItem(item);
         }else
             break;
     }

     for(int i=0; i<setList.size();i++){
         if(listWidget->count() < 11){
             item = new QListWidgetItem();
             item->setText(setList.at(i));
             item->setIcon( QIcon(QIcon("icons/set.png")));
             listWidget->addItem(item);
         }else
             break;
     }

     if(listWidget->count() == 11){
         item = new QListWidgetItem();
         item->setText("");
         item->setIcon( QIcon(QIcon("images/puntosSuspensivos2.png")));
         listWidget->addItem(item);
     }

    widgetPropieties->setGeometry(QRect(posWindow.x(),posWindow.y(), 180, listWidget->count() *26));
    listWidget->setGeometry(0,0,250,(listWidget->count() *26)+5);

    if(listWidget->count()!=0){
        widgetPropieties->show();
        clear=true;
    }else{
        clear=false;
    }   
}


/*void MainWindow::showMediasRegion(QPointF posWindow, QList<Media*> medias)
{
    QListWidget *listWidget = new QListWidget(widgetPropieties);
    QListWidgetItem *item;
    QString mediaName;

    listWidget->clear();
    listWidget->setIconSize(QSize(50,50));
    if(medias.size()!=0){
        for(int i=0; i<medias.size();i++){
            item = new QListWidgetItem();
            item->setText(medias.at(i)->getId());
            for(int j =0 ; j<usedMediasList->rowCount();j++){
                 mediaName = usedMediasList->item(j,0)->text();
                 if(medias.at(i)->getId() == mediaName){
                     item->setIcon(usedMediasList->item(j,0)->icon());
                     break;
                 }
            }
            listWidget->addItem(item);
        }
        listWidget->setGeometry(0,0,300, listWidget->count() *50);
        widgetPropieties->setGeometry(QRect(posWindow.x(),posWindow.y(), 300, listWidget->count() *50));
        widgetPropieties->show();
    }
}*/


/*!
 *\brief close the windows the properties of an Image
 *\return void
 */
void MainWindow::closeEventsButtonSlot()
{
    if(clear)
        widgetPropieties->close();
}


/*void MainWindow::closeMediasRegion()
{
    widgetPropieties->close();
}*/


/*!
 *\brief called to assign actions to \a button
 *\param Image* buttonP
 *\param QStringList playList
 *\param QStringList stopList
 *\param QStringList pauseList
 *\param QStringList resumeList
 *\param QStringList abortList
 *\param QStringList setList
 *\param QTableWidget* setTable
 *\return void
 */
void MainWindow::showWindowsSlot(Image* buttonP,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList,QTableWidget* setTable)
{
    bool aceptedButton =false;
    SelectRole r(this);
    SetAttributesGUI s(this);
    r.setRolesList(playList,stopList,pauseList,resumeList,abortList,setList);
    r.setMediaList(usedMediasList,graphicsSceneHead->getNameMedias());
    if(r.exec() == QDialog::Accepted){
        if(r.getSetList().size() != 0){
            s.setList(usedMediasList,r.getSetList());
            s.setAttributtesList(setTable);
            if (s.exec() == QDialog::Accepted){
                aceptedButton = true;
            }else
                aceptedButton =false;
        }
        if(aceptedButton)
            buttonP->setRoleList(r.getPlayList(),r.getStopList(),r.getPauseList(),r.getResumeList(),r.getAbortList(),r.getSetList(),s.getAttributes());
        else
            buttonP->setRoleList(r.getPlayList(),r.getStopList(),r.getPauseList(),r.getResumeList(),r.getAbortList(),r.getSetList(),setTable);

        addImage(buttonP,r.getPlayList(),r.getStopList(),r.getPauseList(),r.getResumeList(),r.getAbortList(),r.getSetList());
    }
}


/*!
 *\brief adds the role image to an item Image of the Arrow
 *\param Image* buttonP
 *\param QStringList playList
 *\param QStringList stopList
 *\param QStringList pauseList
 *\param QStringList resumeList
 *\param QStringList abortList
 *\param QStringList setList
 *\return void
 */
void MainWindow::addImage(Image* buttonP, QStringList playList,QStringList stopList,QStringList pauseList , QStringList resumeList, QStringList abortList,QStringList setList)
{

    if(playList.count() > 0){
        if(buttonP->getMyType() == Image::BotonInteract)
            imageLocation("/icons/start.png",buttonP,buttonP->boundingRect().width(), -2,1);
        else if(buttonP->getMyType() == Image::EndTermination || buttonP->getMyType() == Image::InitTermination)
            imageLocation("/icons/start.png",buttonP,buttonP->boundingRect().width(), -2,1);
        else
            imageLocation("/icons/start.png",buttonP,(buttonP->boundingRect().width()/2)-6,-12,1);
    }else{
        checkImage(buttonP,1);
    }
    if(stopList.count() > 0){
        if(buttonP->getMyType() == Image::BotonInteract)
            imageLocation("/icons/stop.png",buttonP,buttonP->boundingRect().width(), buttonP->boundingRect().height() -10,2);
        else if(buttonP->getMyType() == Image::EndTermination || buttonP->getMyType() == Image::InitTermination)
            imageLocation("/icons/stop.png",buttonP,buttonP->boundingRect().width(), 11,2);
        else
            imageLocation("/icons/stop.png",buttonP,(buttonP->boundingRect().width()/2)-18 ,-12,2);

    }else{
        checkImage(buttonP,2);
    }

    if(pauseList.count() > 0){
        if(buttonP->getMyType() == Image::BotonInteract)
            imageLocation("/icons/pause.png",buttonP,-12, -2,3);
        else if(buttonP->getMyType() == Image::EndTermination || buttonP->getMyType() == Image::InitTermination)
            imageLocation("/icons/pause.png",buttonP,buttonP->boundingRect().width(), buttonP->boundingRect().height() -9,3);
        else
            imageLocation("/icons/pause.png",buttonP,(buttonP->boundingRect().width()/2)-30, -12,3);
    }else{
        checkImage(buttonP,3);
    }

    if(resumeList.count() > 0){
        if(buttonP->getMyType() == Image::BotonInteract)
            imageLocation("/icons/resume.png",buttonP,-12, buttonP->boundingRect().height() - 10,4);
        else if(buttonP->getMyType() == Image::EndTermination || buttonP->getMyType() == Image::InitTermination)
            imageLocation("/icons/resume.png",buttonP,-12, buttonP->boundingRect().height() - 10,4);
        else
            imageLocation("/icons/resume.png",buttonP,(buttonP->boundingRect().width()/2)-42,-12,4);

    }else{
        checkImage(buttonP,4);
    }

    if(abortList.count() > 0){
        if(buttonP->getMyType() == Image::BotonInteract)
            imageLocation("/icons/abort.png",buttonP,buttonP->boundingRect().width() - 10 , -12,5);
        else if(buttonP->getMyType() == Image::EndTermination || buttonP->getMyType() == Image::InitTermination)
            imageLocation("/icons/abort.png",buttonP,-12 , -2,5);
        else
            imageLocation("/icons/abort.png",buttonP,(buttonP->boundingRect().width()/2)+ 6 , -12,5);

    }else{
        checkImage(buttonP,5);
    }

    if(setList.count() > 0){        
        if(buttonP->getMyType() == Image::BotonInteract)
            imageLocation("/icons/set.png",buttonP,-2, -12,6);
        else if(buttonP->getMyType() == Image::EndTermination || buttonP->getMyType() == Image::InitTermination)
            imageLocation("/icons/set.png",buttonP,-4, buttonP->boundingRect().height(),6);
        else
            imageLocation("/icons/set.png",buttonP,(buttonP->boundingRect().width()/2) +18 , -12,6);
    }else{        
        checkImage(buttonP,6);
    }

}


/*!
 *\brief adds the role image to an item Image of the Arrow
 *\param Image* buttonP
 *\param int typeImage
 *\return void
 */
void MainWindow::checkImage(Image* buttonP, int typeImage)
{
    QList<QGraphicsItem *> AllChildrems = buttonP->childItems();
    if(AllChildrems.size()>=1){
        for(int i = 0; i < AllChildrems.size();i++){
            if(AllChildrems.at(i)->zValue()== typeImage){
                graphicsSceneTemporal->removeItem(AllChildrems.at(i));
                break;
            }
        }
    }
}


/*!
 *\brief sets the type of the image and location of images added with \a addImage
 *\param QString path
 *\param Image *buttonP
 *\param qreal posX
 *\param qreal posY
 *\param qreal zvalue
 *\return void
 */
void MainWindow::imageLocation(QString path, Image *buttonP,qreal posX, qreal posY,qreal zvalue)
{

    Image* playImage;
    QImage image(QDir::currentPath()+path);
    image = image.scaled(12,12);
    QPixmap pixTmp(QPixmap::fromImage(image));
    playImage = new Image(pixTmp);
    graphicsSceneTemporal->addItem(playImage);
    playImage->setParentItem(buttonP);
    playImage->setPos(posX, posY);
    playImage->setZValue(zvalue);


}


/*!
 *\brief called to assign properties to \a imageMedia  when a media is selected in DiagramSceneHead
 *\param QString windowTitle
 *\param Image* imageMedia
 *\return void
 */
void MainWindow::showWindowPropertiesMediaSlot(QString windowTitle, Image* imageMedia)
{
    QString typeMedia = searchTypeMedia(windowTitle);
    DescriptorParam *descriptorParam;
    if(!windowTitle.isEmpty()){
        if(typeMedia == "Imagen"){
            ImageDescriptorAttr i(this);
            i.setValues(imageMedia->getDescriptorParamList());
            i.setWindowTitle("Propiedades del media "+windowTitle);
            if(i.exec()){
                imageMedia->clearDescriptorParamList();
                if(i.getTop() != "0%"){
                    descriptorParam = new DescriptorParam("top",i.getTop());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getBottom() != "0%"){
                    descriptorParam = new DescriptorParam("bottom",i.getBottom());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getHeight() != "100%"){
                    descriptorParam = new DescriptorParam("height",i.getHeight());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getLeft() != "0%"){
                    descriptorParam = new DescriptorParam("left",i.getLeft());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getRight() != "0%"){
                    descriptorParam = new DescriptorParam("right",i.getRight());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getWidth() != "100%"){
                    descriptorParam = new DescriptorParam("width",i.getWidth());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getVisible() != "true"){
                    descriptorParam = new DescriptorParam("visible",i.getVisible());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getZIndex() != "255"){
                    descriptorParam = new DescriptorParam("zIndex",i.getZIndex());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getBackground() != ""){
                    descriptorParam = new DescriptorParam("background",i.getBackground());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getTransparency() != "0%"){
                    descriptorParam = new DescriptorParam("transparency",i.getTransparency());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(i.getFit() != "fill"){
                    descriptorParam = new DescriptorParam("fit",i.getFit());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

            }
        }else if(typeMedia == "Video"){
            VideoDescriptorAttr v(this);
            v.setValues(imageMedia->getDescriptorParamList());
            v.setWindowTitle("Propiedades del media "+windowTitle);
            if(v.exec()){
                imageMedia->clearDescriptorParamList();
                if(v.getVolume() != "100%"){
                    descriptorParam = new DescriptorParam("soundLevel",v.getVolume());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getBalance() != "50%"){
                    descriptorParam = new DescriptorParam("balanceLevel",v.getBalance());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getTreble() != "50%"){
                    descriptorParam = new DescriptorParam("trebleLevel",v.getTreble());
                    imageMedia->addtDescriptorParamToList(descriptorParam);

                }

                if(v.getBass() != "50%"){
                    descriptorParam = new DescriptorParam("bassLevel",v.getBass());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getTop() != "0%"){
                    descriptorParam = new DescriptorParam("top",v.getTop());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getBottom() != "0%"){
                    descriptorParam = new DescriptorParam("bottom",v.getBottom());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getHeight() != "100%"){
                    descriptorParam = new DescriptorParam("height",v.getHeight());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }


                if(v.getLeft() != "0%"){
                    descriptorParam = new DescriptorParam("left",v.getLeft());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getRight() != "0%"){
                    descriptorParam = new DescriptorParam("right",v.getRight());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getWidth() != "100%"){
                    descriptorParam = new DescriptorParam("width",v.getWidth());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getVisible() != "true"){
                    descriptorParam = new DescriptorParam("visible",v.getVisible());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getZIndex() != "255"){
                    descriptorParam = new DescriptorParam("zIndex",v.getZIndex());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getBackground() != ""){
                    descriptorParam = new DescriptorParam("background",v.getBackground());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getTransparency() != "0%"){
                    descriptorParam = new DescriptorParam("transparency",v.getTransparency());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(v.getFit() != "fill"){
                    descriptorParam = new DescriptorParam("fit",v.getFit());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }
            }
        }else if(typeMedia == "Audio"){
            AudioDescriptorAtrr a(this);
            a.setValues(imageMedia->getDescriptorParamList());
            a.setWindowTitle("Propiedades del media "+windowTitle);
            if (a.exec()){
                imageMedia->clearDescriptorParamList();
                if(a.getVolume() != "100%"){           
                    descriptorParam = new DescriptorParam("soundLevel",a.getVolume());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(a.getBalance() != "50%"){
                    descriptorParam = new DescriptorParam("balanceLevel",a.getBalance());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(a.getTreble() != "50%"){
                    descriptorParam = new DescriptorParam("trebleLevel",a.getTreble());
                    imageMedia->addtDescriptorParamToList(descriptorParam);

                }

                if(a.getBass() != "50%"){
                    descriptorParam = new DescriptorParam("bassLevel",a.getBass());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }
            }

        }else if(typeMedia == "Texto"){
            TextDescriptorAtrr t(this);
            t.setValues(imageMedia->getDescriptorParamList());
            t.setWindowTitle("Propiedades del media "+windowTitle);
            if (t.exec()){
                imageMedia->clearDescriptorParamList();
                if(t.getFontFamily() != "Ubuntu"){
                    descriptorParam = new DescriptorParam("fontFamily",t.getFontFamily());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(t.getFontStyle() != "normal"){
                    descriptorParam = new DescriptorParam("fontStyle",t.getFontStyle());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(t.getFontWeight() != "normal"){
                    descriptorParam = new DescriptorParam("fontWeight",t.getFontWeight());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(t.getFontVariant() != "normal"){
                    descriptorParam = new DescriptorParam("fontVariant",t.getFontVariant());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(t.getFontSize() != "12"){
                    descriptorParam = new DescriptorParam("fontSize",t.getFontSize());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(t.getFontColor() != "black"){
                    descriptorParam = new DescriptorParam("fontColor",t.getFontColor());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }

                if(t.getScroll() != "ninguno"){
                    descriptorParam = new DescriptorParam("scroll",t.getScroll());
                    imageMedia->addtDescriptorParamToList(descriptorParam);
                }
            }
        }
    }
}


/*!
 *\brief returns the type of the media with name \a mediaName
 *\param QString media
 *\return QString
 */
QString MainWindow::searchTypeMedia(QString media)
{
    QString nameMedia;
    QString typeMedia;
    for(int i = 0; i < usedMediasList->rowCount();i++){
        nameMedia = usedMediasList->item(i,0)->text();
        if(media == nameMedia){
            typeMedia = usedMediasList->item(i,3)->text();
            break;
        }
    }
    return typeMedia;
}


/*!
 *\brief called to move the horizontal rule when the horizontal scrool bar is moved
 *\param int ejeX
 *\return void
 */
void MainWindow::moveHorizontalRule(int ejeX)
{
   horizontalRule->setGeometry(QRect(-ejeX,0,2500,70));
}


/*!
 *\brief called to move the vertical rule when the horizontal scrool bar is moved
 *\param int ejeY
 *\return void
 */
void MainWindow::moveVerticalRule(int ejeY)
{
    verticalRule->setGeometry(QRect(0,-ejeY,31,1660));
}

/*!
 *\brief called to move the horizontal rule when the horizontal scrool bar in the seccion timeLine is moved
 *\param int ejeX
 *\return void
 */
void MainWindow::moveHorizontalRuleTime(int ejeX)
{
   timeRule->setGeometry(QRect(-ejeX,0,graphicsSceneTemporal->width(),70));
}


/*!
 *\brief called to add a media from an import list to a region using button
 *\return void
 */
void MainWindow::addMediaToRegion()
{
    if(graphicsScene->selectedItems().count() == 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Region donde insertara el Media");
    }else{
        changePresent = true;
        if(tabRegions->currentIndex() == 1){
            if(importMediasToolBox->currentIndex()==0){
                if(videoList->rowCount() != 0){
                    if(videoList->selectedItems().size() !=0){
                        addMediaVideoToRegion();
                    }else{
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Media");
                    }
                }

            }else if (importMediasToolBox->currentIndex()==1){
                if(audioList->rowCount() != 0){
                    if(audioList->selectedItems().size() !=0){
                        addMediaAudioToRegion();
                    }else{
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Media");
                    }
                }

            }else if (importMediasToolBox->currentIndex()==2 ){
                if(imageList->count() != 0){
                    if(imageList->selectedItems().size() !=0 ){
                        addMediaImageToRegion();
                    }else{
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Media");
                    }
                }

            }else if (importMediasToolBox->currentIndex()==3){
                if(textList->count() != 0){
                    if(textList->selectedItems().size() !=0 ){
                        addMediaTextToRegion();
                    }else{
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Media");
                    }
                }
           }

        }else{
            if(tabRegions->currentIndex() == 2){
                if(importOtherToolBox->currentIndex()==0){
                    if(luaList->count() != 0){
                        if(luaList->selectedItems().size() !=0){
                            addMediaLuaToRegion();
                        }else{
                            QMessageBox::StandardButton reply;
                            reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Media");
                        }
                    }

                }else if (importOtherToolBox->currentIndex()==1){
                    if(uriList->count() != 0){
                        if(uriList->selectedItems().size() !=0){
                            addMediaUriToRegion();
                        }else{
                            QMessageBox::StandardButton reply;
                            reply = QMessageBox::information(this, tr("Seleccionar Media"), "Seleccione Media");
                        }
                    }
                }
            }
        }
    }
}


/*!
 *\brief creates a media image, create the descriptor to the media, adds this media to a region, adds this media to
 *\ used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
 *\return void
 */
void MainWindow::addMediaImageToRegion()
{
    if (fileExist(importImageList.at(imageList->currentRow())->absolutePath())){
        QString nombre = imageList->currentItem()->text();
        QString mediaName = getMediaName(nombre);

        if(mediaName != NULL)
            if (!idExist(mediaName)){
                Media *media = new Media(mediaName,"-1");
                media->setSrc(importImageList.at(imageList->currentRow())->absolutePath());
                //media->setType(getType(importImageList.at(imageList->currentRow())));

                Descriptor *imageDescriptor = new Descriptor("descriptor-"+media->getId());
                media->setDescriptor(imageDescriptor->getId());

                imageDescriptor->setRegion(graphicsScene->getSelected()->getName());
                descriptorList.append(imageDescriptor);

                mediaImageList.append(media);
                graphicsScene->getSelected()->addMedia(media->getId());

                int posUsados = usedMediasList->rowCount();
                int posRegion = graphicsScene->getSelected()->getMedias().size();

                usedMediasList->setRowCount(posUsados + 1 );
                mediasRegionList->setRowCount(posRegion);

                QTableWidgetItem *newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(imageList->currentItem()->icon());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                usedMediasList->setItem(posUsados, 0, newItem);
                newItem = new QTableWidgetItem();
                newItem->setCheckState(Qt::Unchecked);
                usedMediasList->setItem(posUsados, 1, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Imagen");
                newItem->setTextAlignment(Qt::AlignCenter);
                usedMediasList->setItem(posUsados, 3, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(mediaName);
                newItem->setIcon(imageList->currentItem()->icon());
                mediasRegionList->setItem(posRegion-1, 0, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                newItem = new QTableWidgetItem();
                mediasRegionList->setItem(posRegion-1, 1, newItem);
                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Imagen");
                newItem->setTextAlignment(Qt::AlignCenter);
                mediasRegionList->setItem(posRegion-1, 3, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            }
    }
}


/*!
 *\brief creates a media audio, create the descriptor to the media, adds this media to a region, adds this media to
 *\ used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
 *\return void
 */
void MainWindow::addMediaAudioToRegion()
{
    if (fileExist(importAudioList.at(audioList->currentRow())->absolutePath())){
        QString nombre = audioList->item(audioList->currentRow(),0)->text();
        QString duracion = audioList->item(audioList->currentRow(),1)->text();
        QString mediaName = getMediaName(nombre);

        if(mediaName != NULL)
            if (!idExist(mediaName)){
                Media *media = new Media(mediaName,duracion);
                media->setSrc(importAudioList.at(audioList->currentRow())->absolutePath());
                //media->setType(getType(importAudioList.at(audioList->currentRow())));

                Descriptor *audioDescriptor = new Descriptor("descriptor-"+media->getId());
                media->setDescriptor(audioDescriptor->getId());

                audioDescriptor->setRegion(graphicsScene->getSelected()->getName());
                descriptorList.append(audioDescriptor);

                mediaAudioList.append(media);
                graphicsScene->getSelected()->addMedia(media->getId());

                int posUsados = usedMediasList->rowCount();
                int posRegion = graphicsScene->getSelected()->getMedias().size();

                usedMediasList->setRowCount(posUsados + 1 );
                mediasRegionList->setRowCount(posRegion);

                QTableWidgetItem *newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(audioList->currentItem()->icon());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                usedMediasList->setItem(posUsados, 0, newItem);
                newItem = new QTableWidgetItem();
                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 1, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText(duracion);
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 2, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText("Audio");
                newItem->setTextAlignment(Qt::AlignCenter);
                usedMediasList->setItem(posUsados, 3, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem(mediaName);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(audioList->currentItem()->icon());
                mediasRegionList->setItem(posRegion-1, 0, newItem);
                newItem = new QTableWidgetItem();
                mediasRegionList->setItem(posRegion-1, 1, newItem);

                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText(duracion);
                newItem->setTextAlignment(Qt::AlignCenter);
                mediasRegionList->setItem(posRegion-1, 2, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Audio");
                newItem->setTextAlignment(Qt::AlignCenter);
                mediasRegionList->setItem(posRegion-1, 3, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            }
    }
}


/*!
 *\brief creates a media text, create the descriptor to the media, adds this media to a region, adds this media to
 *\ used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
 *\return void
 */
void MainWindow::addMediaTextToRegion()
{
    if (fileExist(importTextList.at(textList->currentRow())->absolutePath())){
        QString nombre = textList->currentItem()->text();
        QString mediaName = getMediaName(nombre);

        if(mediaName != NULL)
            if (!idExist(mediaName)){
                Media *media = new Media(mediaName,"-1");
                media->setSrc(importTextList.at(textList->currentRow())->absolutePath());
                //media->setType(getType(importTextList.at(textList->currentRow())));

                Descriptor *textDescriptor = new Descriptor("descriptor-"+media->getId());
                media->setDescriptor(textDescriptor->getId());

                textDescriptor->setRegion(graphicsScene->getSelected()->getName());
                descriptorList.append(textDescriptor);

                mediaTextList.append(media);
                graphicsScene->getSelected()->addMedia(media->getId());

                int posUsados = usedMediasList->rowCount();
                int posRegion = graphicsScene->getSelected()->getMedias().size();

                usedMediasList->setRowCount(posUsados + 1 );
                mediasRegionList->setRowCount(posRegion);

                QTableWidgetItem *newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(textList->currentItem()->icon());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                usedMediasList->setItem(posUsados, 0, newItem);
                newItem = new QTableWidgetItem();

                newItem->setCheckState(Qt::Unchecked);
                usedMediasList->setItem(posUsados, 1, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Texto");
                newItem->setTextAlignment(Qt::AlignCenter);
                usedMediasList->setItem(posUsados, 3, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(textList->currentItem()->icon());
                mediasRegionList->setItem(posRegion-1, 0, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                newItem = new QTableWidgetItem();
                mediasRegionList->setItem(posRegion-1, 1, newItem);

                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Texto");
                newItem->setTextAlignment(Qt::AlignCenter);
                mediasRegionList->setItem(posRegion-1, 3, newItem);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            }
    }
}


/*!
 *\brief creates a media video, create the descriptor to the media, adds this media to a region, adds this media to
 *\ used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
 *\return void
 */
void MainWindow::addMediaVideoToRegion()
{
    if (fileExist(importVideoList.at(videoList->currentRow())->absolutePath())){
        QString nombre = videoList->item(videoList->currentRow(),0)->text();
        QString duracion = videoList->item(videoList->currentRow(),1)->text();
        QString mediaName = getMediaName(nombre);

        if(mediaName != NULL)
            if (!idExist(mediaName)){
                Media *media = new Media(mediaName,duracion);
                media->setSrc(importVideoList.at(videoList->currentRow())->absolutePath());
                //media->setType(getType(importVideoList.at(videoList->currentRow())));

                Descriptor *videoDescriptor = new Descriptor("descriptor-"+media->getId());
                media->setDescriptor(videoDescriptor->getId());

                videoDescriptor->setRegion(graphicsScene->getSelected()->getName());
                descriptorList.append(videoDescriptor);

                mediaVideoList.append(media);
                graphicsScene->getSelected()->addMedia(media->getId());

                int posUsados = usedMediasList->rowCount();
                int posRegion = graphicsScene->getSelected()->getMedias().size();

                usedMediasList->setRowCount(posUsados + 1 );
                mediasRegionList->setRowCount(posRegion);

                QTableWidgetItem *newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(videoList->item(videoList->currentRow(),0)->icon());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                usedMediasList->setItem(posUsados, 0, newItem);
                newItem = new QTableWidgetItem();

                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 1, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText(duracion);
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 2, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText("Video");
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 3, newItem);

                newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(videoList->item(videoList->currentRow(),0)->icon());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(posRegion-1, 0, newItem);
                newItem = new QTableWidgetItem();
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(posRegion-1, 1, newItem);

                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText(duracion);
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(posRegion-1, 2, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText("Video");
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(posRegion-1, 3, newItem);

            }
    }
}


/*!
 *\brief creates a media lua, create the descriptor to the media, adds this media to a region, adds this media to
 *\ used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
 *\return void
 */
void MainWindow::addMediaLuaToRegion()
{
    if (fileExist(importLuaList.at(luaList->currentRow())->absolutePath())){
        QString nombre = luaList->currentItem()->text();
        QString mediaName = getMediaName(nombre);

        if(mediaName != NULL)
            if (!idExist(mediaName)){
                Media *media = new Media(mediaName,"-1");
                media->setSrc(importLuaList.at(luaList->currentRow())->absolutePath());
                //media->setType(getType(importImageList.at(imageList->currentRow())));

                Descriptor *luaDescriptor = new Descriptor("descriptor-"+media->getId());
                media->setDescriptor(luaDescriptor->getId());

                luaDescriptor->setRegion(graphicsScene->getSelected()->getName());
                descriptorList.append(luaDescriptor);

                mediaLuaList.append(media);
                graphicsScene->getSelected()->addMedia(media->getId());

                int posUsados = usedMediasList->rowCount();
                int posRegion = graphicsScene->getSelected()->getMedias().size();

                usedMediasList->setRowCount(posUsados + 1 );
                mediasRegionList->setRowCount(posRegion);

                QTableWidgetItem *newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(luaList->currentItem()->icon());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                usedMediasList->setItem(posUsados, 0, newItem);
                newItem = new QTableWidgetItem();

                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 1, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText("Lua");
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 3, newItem);

                newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(luaList->currentItem()->icon());
                mediasRegionList->setItem(posRegion-1, 0, newItem);
                newItem = new QTableWidgetItem();
                mediasRegionList->setItem(posRegion-1, 1, newItem);
                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Lua");
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(posRegion-1, 3, newItem);
            }
    }
}


/*!
 *\brief creates a media url, create the descriptor to the media, adds this media to a region, adds this media to
 *\ used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
 *\return void
 */
void MainWindow::addMediaUriToRegion()
{
    if (fileExist(importUriList.at(uriList->currentRow()))){
        QString nombre = uriList->currentItem()->text();
        QString mediaName = getMediaName(nombre);
        if(mediaName != NULL)
            if (!idExist(mediaName)){
                Media *media = new Media(mediaName,"-1");
                media->setSrc(importUriList.at(uriList->currentRow()));

                Descriptor *uriDescriptor = new Descriptor("descriptor-"+media->getId());
                media->setDescriptor(uriDescriptor->getId());

                uriDescriptor->setRegion(graphicsScene->getSelected()->getName());
                descriptorList.append(uriDescriptor);

                mediaUriList.append(media);
                graphicsScene->getSelected()->addMedia(media->getId());

                int posUsados = usedMediasList->rowCount();
                int posRegion = graphicsScene->getSelected()->getMedias().size();

                usedMediasList->setRowCount(posUsados + 1 );
                mediasRegionList->setRowCount(posRegion);
                QTableWidgetItem *newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(uriList->currentItem()->icon());

                usedMediasList->setItem(posUsados, 0, newItem);
                newItem = new QTableWidgetItem();
                mediasRegionList->setItem(posRegion-1, 1, newItem);
                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

                newItem = new QTableWidgetItem();
                newItem->setText("Uri");
                newItem->setTextAlignment(Qt::AlignCenter);
                usedMediasList->setItem(posUsados, 3, newItem);

                newItem = new QTableWidgetItem();
                newItem->setCheckState(Qt::Unchecked);
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                usedMediasList->setItem(posUsados, 1, newItem);

                newItem = new QTableWidgetItem(mediaName);
                newItem->setToolTip(media->getSrc());
                newItem->setIcon(uriList->currentItem()->icon());
                mediasRegionList->setItem(posRegion-1, 0, newItem);

                newItem = new QTableWidgetItem();
                newItem->setText("Uri");
                newItem->setTextAlignment(Qt::AlignCenter);
                mediasRegionList->setItem(posRegion-1, 3, newItem);
            }
    }
}


/*!
 *\brief creates a Region an adds it to a region list (\a regionList)
 *\return void
 */
void MainWindow::addRegionNCL()
{
    itemSelected(graphicsScene->getSelected());

    qreal alto = propertyRegionTable->item(3,1)->text().toDouble(0);
    qreal ancho = propertyRegionTable->item(4,1)->text().toDouble(0);
    qreal zValue = propertyRegionTable->item(5,1)->text().toDouble(0);

    Regionn *region = new Regionn(QString::number(regionNumber));

    region->setHeight(QString::number(alto));
    region->setWidth(QString::number(ancho));
    region->setZIndex(QString::number(zValue));

    regionList.append(region);
    regionNumber++;
}


/*!
 *\brief called to enable or disable the create a new region
 *\return void
 */
void MainWindow::addRegion()
{

    if(ui->actionNewRegion->isChecked()){
        setPropItems(false);
        buttonRectAct=true;
        setButtonPressed(true);
        putXCursor(Qt::CrossCursor,false);
    }else{
        setPropItems(false);
        buttonRectAct=false;
        setButtonPressed(false);
        graphicsView->setCursor(Qt::ArrowCursor);
    }
}


/*!
 *\brief returns the media name of the media with path \a dir
 *\param QString dir
 *\return QString
 */
QString MainWindow::getMediaName(QString dir)
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Apodo"), tr("Ingrese el apodo del media"), QLineEdit::Normal, dir, &ok);
    QString name = NULL;
    if (ok && !text.isEmpty())
        name = text;
    return name;
}


/*!
 *\brief changes the type of cursor for \a xCursor
 *\param QCursor xCursor
 *\param bool prop
 *\return void
 */
void MainWindow::putXCursor(QCursor xCursor,bool prop)
{
    QList<QGraphicsItem *> allRec = graphicsScene->items();
       for(int i = 0; i < allRec.size();i++) {
           if(allRec.at(i)->type() == 5){ //is a graphiscsrectitem
               allRec.at(i)->setAcceptsHoverEvents(prop);
               allRec.at(i)->setCursor(xCursor);
           }
       }
}


/*!
 *\brief called to change the type of cursor and prepare to move regions
 *\return void
 */
void MainWindow::selectButton()
{
    setPropItems(true);
    buttonRectAct=false;
    graphicsView->setCursor(Qt::ArrowCursor);
    setButtonPressed(false);
    putXCursor(Qt::SizeAllCursor,true);
}


/*!
 *\brief called when a region inside of a regios is created
 *\param QList<Regionn*> lista
 *\param GraphicsRectItem *item
 *\param Regionn *region
 *\return void
 */
void MainWindow::addSubRegion(QList<Regionn*> lista, GraphicsRectItem *item, Regionn *region)
{
    for(int i=0; i < lista.size(); i++){
        if(lista.at(i)->getId().compare(item->getName())==0){
            lista.at(i)->addRegion(region);
            regionNumber++;
        }else{
            if(!lista.at(i)->getList().isEmpty()){
                addSubRegion(lista.at(i)->getList(), item, region);
            }
        }
    }
}


/*!
 *\brief called when a region on the tree is selected to select a region in the scene.
 *\param QTreeWidgetItem* item
 *\return void
 */
void MainWindow::selectRegion(QTreeWidgetItem* item)
{
    QList<QGraphicsItem *> lista = graphicsScene->items();
    for(int i = 0; i < lista.size();i++){
        if(lista.at(i)->type() == 5){ //is a graphiscsrectitem
            GraphicsRectItem *rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
            lista.at(i)->setSelected(false);
            if(rectItem->getName() == item->text(0)){
                rectItem->setSelected(true);
                emit itemSelected(rectItem);
            }
        }
    }
}


/*!
 *\brief called to hide or show a region when the checkBox in the tree is toggled.
 *\param QTreeWidgetItem* item
 *\return void
 */
void MainWindow::setShowRegion(QTreeWidgetItem* item)
{
    propertyRegionTable->blockSignals(true);
    if(propertyRegionTable->item(0,1)->text() == item->text(0))
    {
        QList<QGraphicsItem *> lista = graphicsScene->items();
        for(int i = 0; i < lista.size();i++)
        {
            if(lista.at(i)->type() == 5)
            {
                GraphicsRectItem *rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
                lista.at(i)->setSelected(false);
                if(rectItem->getName() == item->text(0))
                {
                    rectItem->setVisible(item->checkState(0));
                }
            }
        }
    }else{
        graphicsScene->getSelected()->setVisible(item->checkState(0));
        graphicsScene->getSelected()->setName(item->text(0));
        propertyRegionTable->item(0,1)->setText(item->text(0));
    }
    propertyRegionTable->blockSignals(false);
}


/*!
 *\brief called when a region is removed to remove the region name in the tree.
 *\return void
 */
void MainWindow::removeTreeRegion()
{
    treeWidget->selectedItems().at(0)->~QTreeWidgetItem();
}


/*!
 *\brief called to add a item in the tree on the top level.
 *\param QString regionNumber
 *\return void
 */
void MainWindow::addRootTreeItem(QString regionNumber)
{   
    QTreeWidgetItem *currItem = new QTreeWidgetItem();
    currItem->setText(0,regionNumber);
    currItem->setCheckState(0,Qt::Checked);
    currItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
    treeWidget->addTopLevelItem(currItem);

}


/*!
 *\brief called to add a child item in the tree.
 *\param QString regionNumber
 *\param QString parentName
 *\return void
 */
void MainWindow::addChildTreeItem(QString regionNumber, QString parentName)
{
    QTreeWidgetItemIterator it(treeWidget);
    while (*it) {
        if ((*it)->text(0) == parentName){
            QTreeWidgetItem *currItem = new QTreeWidgetItem(Qt::ItemIsEditable);
            currItem->setText(0,regionNumber);
            currItem->setCheckState(0,Qt::Checked);
            currItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
            (*it)->addChild(currItem);
        }
        ++it;
    }
}


/*!
 *\brief called when the zoom in button is pressed, sets the spinBox value of the zoom
 *\return void
 */
void MainWindow::zoomIn()
{
    spinBoxZoom->setValue(spinBoxZoom->value()+20);
}


/*!
 *\brief called when the zoom out button is pressed, sets the spinBox value of the zoom
 *\return void
 */
void MainWindow::zoomOut()
{
    spinBoxZoom->setValue(spinBoxZoom->value()-20);
}


/*!
 *\brief called when the reset zoom button is pressed, sets the spinBox value of the zoom
 *\return void
 */
void MainWindow::resetZoom()
{
     graphicsView->resetMatrix();
     graphicsView->centerOn(0,0);
     spinBoxZoom->setValue(100);
}


/*!
 *\brief calculates the zoom value to the matrix
 *\param int value
 *\return void
 */
void MainWindow::zoomInOut(int value)
{
    qreal factor = value / 100.0;
    zoom(factor);
}


/*!
 *\brief generates zoom in or zoom out in the drawing area of regions
 *\param const qreal factor
 *\return void
 */
void MainWindow::zoom(const qreal factor)
{
    QPointF topLeft     = graphicsView->mapToScene( 0,0 );
    QPointF bottomRight = graphicsView->mapToScene( graphicsView->viewport()->width() - 1, graphicsView->viewport()->height() - 1 );
    qreal width=bottomRight.x()-topLeft.x();
    qreal height=bottomRight.y()-topLeft.y();
    if((width/factor<=50000)&&(height/factor<=50000)){
        qreal newScale=originalMatrix.m11()*factor;
        graphicsView->resetMatrix();
        graphicsView->translate(originalMatrix.dx(), originalMatrix.dy());
        graphicsView->scale(newScale, newScale);
        originalMatrix.translate( graphicsView->matrix().dx(),graphicsView->matrix().dy());
    }
}


/*!
 *\brief called to save the project
 *\return void
 */
void MainWindow::save()
{
    if (myFileName.isEmpty() || saveAsBool){
        if(saveAsBool){
            QFileDialog::Options options;
            options = 0;
            QString selectedFilter;
            QString fileName = QFileDialog::getSaveFileName(this,
                            tr("Guardar Como ..."),
                            myFileName+".ctv",
                            tr("CTVProject (*.ctv)"),
                            &selectedFilter,
                            options);
            myFileName = fileName;
        }else{
            QFileDialog::Options options;
            options = 0;
            QString selectedFilter;
            QString fileName = QFileDialog::getSaveFileName(this,
                            tr("Guardar..."),
                            nameProject+".ctv",
                            tr("CTVProject (*.ctv)"),
                            &selectedFilter,
                            options);
            myFileName = fileName;
        }
    }

    if (!myFileName.isEmpty()){
        SaveProject *save = new SaveProject(myFileName);

        save->saveProjectDescription(nameProject,dateProject,descriptionProject,graphicsScene->getRegionName());

        if(ui->actionRegionPALN->isChecked())
            save->saveScreenFormat("palN",QString::number(screenSizeX),QString::number(screenSizeY));
        if(ui->actionRegionPALAncho->isChecked())
           save->saveScreenFormat("palAncho",QString::number(screenSizeX),QString::number(screenSizeY));
        if(ui->actionRegionHDTV720p->isChecked())
            save->saveScreenFormat("HDTVP",QString::number(screenSizeX),QString::number(screenSizeY));
        if(ui->actionRegionHDTV1080i->isChecked())
            save->saveScreenFormat("HDTVI",QString::number(screenSizeX),QString::number(screenSizeY));

        if(otherRegionAction->isChecked())
            if(otherAction->isChecked()){
                save->saveScreenFormat("Other",QString::number(screenSizeOtherX),QString::number(screenSizeOtherY));
            }
        save->saveImports(videoList,audioList,imageList,textList,luaList,uriList,importVideoList,importAudioList,importImageList,importTextList,importLuaList,importUriList);
        save->saveMedias(mediaVideoList,mediaAudioList,mediaImageList,mediaTextList,mediaLuaList,mediaUriList,usedMediasList);
        save->saveDescriptiors(descriptorList);
        save->saveRectangles(graphicsScene->items());
        save->saveTimeLines(graphicsSceneTemporal,graphicsSceneHead);
        save->saveDescriptorsParam(graphicsSceneHead);
        save->endSaveFile();
        changePresent = false;
    }
}


/*!
 *\brief called to save the project with another name
 *\return void
 */
void MainWindow::saveAs()
{
    saveAsBool = true;
    save();
}


/*!
 *\brief called to open a project
 *\return void
 */
void MainWindow::open()
{
    QFileDialog::Options options;
    options = 0;
    QString selectedFilter;
    GraphicsRectItem *item;

    if(changePresent){
        QMessageBox msgBox(QMessageBox::Warning, tr("Cambios Realizados"),
                           "Desea guardar cambios realizados?", 0, this);
        msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
        msgBox.addButton(tr("No"), QMessageBox::RejectRole);

        if (msgBox.exec() == QMessageBox::AcceptRole)
            save();

    }

    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir ..."),
                    ".ctv",
                    tr("CTVProject (*.ctv)"),
                    &selectedFilter,
                    options);

    if (!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this,tr("Error al abrir el archivo"),file.errorString());
        }else{

            clearAll();
            QString format;
            SaveProject *open = new SaveProject(fileName);
            connect(open,SIGNAL(fileNotFound(QString, QString,QString,QString)),this,SLOT(fileNotFound(QString, QString,QString,QString)));

            open->openFile();
            open->openDescriptionProject(nameProject,descriptionProject,dateProject,regionNumber);
            graphicsScene->setRegionName(regionNumber);

            open->openScreenFormat(format,screenSizeX,screenSizeY);
            if(format == "Other"){
                screenSizeOtherX = screenSizeX;
                screenSizeOtherY = screenSizeY;
            }

            createProject(nameProject,descriptionProject,dateProject,format,screenSizeX,screenSizeY);            
            open->openImports(*videoList,importVideoList,*audioList,importAudioList, *imageList,importImageList,*textList,importTextList, *luaList, importLuaList, *uriList, importUriList);
            open->openMedias(mediaVideoList,mediaAudioList,mediaImageList,mediaTextList,mediaLuaList,mediaUriList,*usedMediasList);
            open->openDescriptiors(descriptorList);
            open->openRectangles(*graphicsScene,screenSizeX,screenSizeY);
            loadImages();
            open->openTimeLines(graphicsSceneTemporal,usedMediasList); 
            open->openDescriptorsParam(graphicsSceneHead); 
            changePresent = false;

            if(graphicsScene->items().size() > 0){
                graphicsScene->clearSelection();
                for(int i = 0; i < graphicsScene->items().size();i++){
                    if(graphicsScene->items().at(i)->type() == 5){
                        item = qgraphicsitem_cast<GraphicsRectItem *>(graphicsScene->items().at(i));
                        graphicsScene->items().at(i)->setSelected(true);
                        itemSelected(item);
                        break;
                    }
                }
            }
        }
    }
}


/*!
 *\brief  called to choose a new path to a media to return this
 *\param QString name
 *\param QString src
 *\param QString type
 *\param QString duration
 *\return QString
 */
QString MainWindow::fileNotFound(QString name, QString src,QString type,QString duration)
{
    QMessageBox::StandardButton reply;
    QString title = "Nueva ubicacion de "+name;
    if(type == "Video" || type == "Audio"){
        reply = QMessageBox::information(this, tr("Nueva ubicacion"), "Archivo no encontrado seleccione ubicacion \nUbicacion anterior: "+src+"\nTipo: "+type+"\nDuracion: "+duration);
    }else{
        reply = QMessageBox::information(this, tr("Nueva ubicacion"), "Archivo no encontrado seleccione ubicacion \nUbicacion anterior: "+src+"\nTipo: "+type);
    }

    changePresent = true;

    QString dirFile;

    if(type == "Video")
        dirFile = QFileDialog::getOpenFileName(this, title, "/", tr("Archivos Medias Video (*.mp2 *.mpeg *.mpg *.mpe *.mp4 *.mpg4 *.mng *.qt *.mov *.avi)"));
    if(type == "Audio")
        dirFile = QFileDialog::getOpenFileName(this, title, "/", tr("Archivos Medias Audio (*.ua *.wav *.mp1 *.mp2 *.mp3 *.mpg4)"));
    if(type == "Imagen")
        dirFile = QFileDialog::getOpenFileName(this, title, "/", tr("Archivos Medias Imagen (*.bmp *.png *.gif *.jpg *.jpeg *.jpe)"));
    if(type == "Texto")
        dirFile = QFileDialog::getOpenFileName(this, title, "/", tr("Archivos Medias Texto (*.htm *.html *.css *.xml *.txt )"));
    if(type == "Lua")
        dirFile = QFileDialog::getOpenFileName(this, title, "/", tr("Archivos Medias Lua (*.lua)"));

    return dirFile;

}

/*!
 *\brief called to open a file chooser to choose a file to add to a import list
 *\return void
 */
void MainWindow::generalFileChooser()
{
    if(tabRegions->currentIndex() == 1){
        if(importMediasToolBox->currentIndex()==0){
            fileChoserVideo();
            updateMediaTimes();
        }else if (importMediasToolBox->currentIndex()==1){
            fileChoserAudio();
            updateMediaTimes();
        }else if (importMediasToolBox->currentIndex()==2){
            fileChoserImage();
        }else if (importMediasToolBox->currentIndex()==3){
            fileChoserText();
        }
    }else{
        if(importOtherToolBox->currentIndex()==0){
            fileChoserLua();
        }else if (importOtherToolBox->currentIndex()==1){
            fileChoserUri();
        }
    }
}


/*!
 *\brief loads the medias assigned to the region in the rmedia egions table (\a mediasRegionList)
 *\return void
 */
void MainWindow::loadMediasRegion()
{
    QString mediaName;
    QTableWidgetItem *newItem;
    QStringList medias;
    medias.clear();
    medias = graphicsScene->getSelected()->getMedias();
    mediasRegionList->setRowCount(medias.size());

    for(int i = 0; i < medias.size(); i++){
        for(int j = 0 ; j<usedMediasList->rowCount();j++){
            mediaName =usedMediasList->item(j,0)->text();
            if(medias.at(i) == mediaName){
                newItem = new QTableWidgetItem();
                newItem->setText(usedMediasList->item(j,0)->text());
                newItem->setIcon(usedMediasList->item(j,0)->icon());
                newItem->setToolTip(medias.at(i));
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(i, 0, newItem);
                newItem = new QTableWidgetItem();
                newItem->setCheckState(usedMediasList->item(j,1)->checkState());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(i, 1, newItem);
                newItem = new QTableWidgetItem();
                newItem->setText(usedMediasList->item(j,3)->text());
                newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                mediasRegionList->setItem(i, 3, newItem);

                if(usedMediasList->item(j,3)->text() == "Video" || usedMediasList->item(j,3)->text() == "Audio"){
                    newItem = new QTableWidgetItem();
                    newItem->setText(usedMediasList->item(j,2)->text());
                    newItem->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
                    mediasRegionList->setItem(i, 2, newItem);
                }
            }
        }
    }
}


/*!
 *\brief enables the create a new Interactivity arrow
 *\return void
 */
void MainWindow::addInteractivity()
{
    graphicsSceneTemporal->setButtonInteractividad(true);
}


/*!
 *\brief sets \a value value to view or not the diamond
 *\param bool value
 *\return void
 */
void MainWindow::hideInteractivity(bool value)
{
    graphicsSceneTemporal->ViewDiamonds(!value);
}


/*!
 *\brief enables or disables delete a line
 *\return void
 */
void MainWindow::deleteLine()
{
    if(graphicsSceneTemporal->getButtonDeleteLine()){
        graphicsSceneTemporal->deleteLine(false);
    }else{
        graphicsSceneTemporal->deleteLine(true);
    }
}


/*!
 *\brief sets position of \a verticalScrollBar whit \a cant
 *\param int cant
 *\return void
 */
void MainWindow::changeVerticalBar(int cant)
{
    graphicsViewTemporal->verticalScrollBar()->setSliderPosition(cant);
}


/*!
 *\brief sets position of \a verticalScrollBar whit \a cant
 *\param int cant
 *\return void
 */
void MainWindow::changeVerticalBar2(int cant)
{
    graphicsViewTemporalMedias->verticalScrollBar()->setSliderPosition(cant);
}


/*!
 *\brief returns true if the media id \a id is in use
 *\param QString idP
 *\return bool
 */
bool MainWindow::idExist(QString idP)
{
    bool existe = false;
    int pagina;

    if(tabRegions->currentIndex()==1){
        pagina = importMediasToolBox->currentIndex();
    }else{
        pagina = importOtherToolBox->currentIndex();
    }

    for (int i = 0; i < usedMediasList->rowCount();i++){
        if(pagina==0 && tabRegions->currentIndex()==1){
            if(mediaVideoList.size() > 0  && i < mediaVideoList.size()){
                if (mediaVideoList.at(i)->getId() == idP ){
                    existe = true;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Apodo en uso"), "El apodo del media ya existe!");
                    break;
                }
            }
        }else if (pagina==1 && tabRegions->currentIndex()==1 ){
            if(mediaAudioList.size() > 0  && i < mediaAudioList.size()){
                if (mediaAudioList.at(i)->getId() == idP ){
                    existe = true;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Apodo en uso"), "El apodo del media ya existe!");
                    break;
                }
            }
        }else if (pagina==2){
            if(mediaImageList.size() > 0  && i < mediaImageList.size()){
                if (mediaImageList.at(i)->getId() == idP ){
                    existe = true;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Apodo en uso"), "El apodo del media ya existe!");
                    break;
                }
            }
        }else if (pagina==3){
            if(mediaTextList.size() > 0  && i < mediaTextList.size()){
                if (mediaTextList.at(i)->getId() == idP ){
                    existe = true;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Apodo en uso"), "El apodo del media ya existe!");
                    break;
                }
            }
        }else if (pagina==0){
            if(mediaLuaList.size() > 0 && i < mediaLuaList.size()){
                if (mediaLuaList.at(i)->getId() == idP ){
                    existe = true;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Apodo en uso"), "El apodo del media ya existe!");
                    break;
                }
            }
        }else if (pagina==1){
            if(mediaUriList.size() > 0 && i < mediaUriList.size()){
                if (mediaUriList.at(i)->getId() == idP ){
                    existe = true;
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::information(this, tr("Apodo en uso"), "El apodo del media ya existe!");
                    break;
                }
            }
        }
    }
    return existe;
}


/*!
 *\brief returns true if the media file \a dir is in use
 *\param QString dir
 *\return bool
 */
bool MainWindow::fileExist(QString dir)
{
    bool continuar = true;
    int pagina;
    if(tabRegions->currentIndex()==1){
        pagina = importMediasToolBox->currentIndex();
    }else{
        pagina = importOtherToolBox->currentIndex();
    }

    for (int i = 0; i < usedMediasList->rowCount();i++){
        if(pagina ==0 && tabRegions->currentIndex()==1){
            if(mediaVideoList.size() > 0 && i < mediaVideoList.size()){
                if (mediaVideoList.at(i)->getSrc() == dir ){
                    QMessageBox msgBox(QMessageBox::Warning, tr("Precaucion"),
                                       "El Archivo ya esta en uso, ¿desea utilizarlo de todas formas?", 0, this);
                    msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
                    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
                    if (msgBox.exec() == QMessageBox::AcceptRole)
                        continuar = true;
                    else
                        continuar = false;
                    break;
                }
            }
        }else if (pagina==1 && tabRegions->currentIndex()==1) {
            if(mediaAudioList.size() > 0 && i < mediaAudioList.size()){
                if (mediaAudioList.at(i)->getSrc() == dir ){
                    QMessageBox msgBox(QMessageBox::Warning, tr("Precaucion"),
                                       "El Archivo ya esta en uso, ¿desea utilizarlo de todas formas?", 0, this);
                    msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
                    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
                    if (msgBox.exec() == QMessageBox::AcceptRole)
                        continuar = true;
                    else
                        continuar = false;
                    break;
                }
            }
        }else if (pagina==2){
            if(mediaImageList.size() > 0 && i < mediaImageList.size()){

                if (mediaImageList.at(i)->getSrc() == dir ){
                    QMessageBox msgBox(QMessageBox::Warning, tr("Precaucion"),
                                       "El Archivo ya esta en uso, ¿desea utilizarlo de todas formas?", 0, this);
                    msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
                    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
                    if (msgBox.exec() == QMessageBox::AcceptRole)
                        continuar = true;
                    else
                        continuar = false;
                    break;
                }
            }
        }else if (pagina==3){
            if(mediaTextList.size() > 0 && i < mediaTextList.size()){
                if (mediaTextList.at(i)->getSrc() == dir ){
                    QMessageBox msgBox(QMessageBox::Warning, tr("Precaucion"),
                                       "El Archivo ya esta en uso, ¿desea utilizarlo de todas formas?", 0, this);
                    msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
                    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
                    if (msgBox.exec() == QMessageBox::AcceptRole)
                        continuar = true;
                    else
                        continuar = false;
                    break;
                }
            }

        }else if (pagina==0){
            if(mediaLuaList.size() > 0 && i < mediaLuaList.size()){
                if (mediaLuaList.at(i)->getSrc() == dir ){
                    QMessageBox msgBox(QMessageBox::Warning, tr("Precaucion"),
                                       "El Archivo ya esta en uso, ¿desea utilizarlo de todas formas?", 0, this);
                    msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
                    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
                    if (msgBox.exec() == QMessageBox::AcceptRole)
                        continuar = true;
                    else
                        continuar = false;
                    break;
                }
            }
        }else if (pagina==1){
            if(mediaUriList.size() > 0 && i < mediaUriList.size()){
                if (mediaUriList.at(i)->getSrc() == dir ){
                    QMessageBox msgBox(QMessageBox::Warning, tr("Precaucion"),
                                       "El Archivo ya esta en uso, ¿desea utilizarlo de todas formas?", 0, this);
                    msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
                    msgBox.addButton(tr("No"), QMessageBox::RejectRole);
                    if (msgBox.exec() == QMessageBox::AcceptRole)
                        continuar = true;
                    else
                        continuar = false;
                    break;
                }
            }
        }

    }
    return continuar;
}


/*!
 *\brief called to update the media video and media audio times
 *\return void
 */
void MainWindow::updateMediaTimes()
{
    filePos = 0;

    updateMediaTime();
}


/*!
 *\brief called to update the time of a media video or a media audio
 *\return void
 */
void MainWindow::updateMediaTime()
{
    if(importMediasToolBox->currentIndex()==0){
        if( 0 <= filePos && filePos <= videoFiles.size()-1){
            Phonon::MediaObject* metaInformationResolver = new Phonon::MediaObject(this);
            Phonon::MediaSource source(videoFiles.at(filePos));
            metaInformationResolver->setCurrentSource(source);

            connect(metaInformationResolver,SIGNAL(totalTimeChanged(qint64)),this,SLOT(editTime(qint64)));
        }
    }else if (importMediasToolBox->currentIndex()==1){
        if( 0 <= filePos && filePos <= audioFiles.size()-1){
            Phonon::MediaObject* metaInformationResolver = new Phonon::MediaObject(this);
            Phonon::MediaSource source(audioFiles.at(filePos));
            metaInformationResolver->setCurrentSource(source);

            connect(metaInformationResolver,SIGNAL(totalTimeChanged(qint64)),this,SLOT(editTime(qint64)));
        }
    }
}


/*!
 *\brief change time of a media in millisecs to "hour:minits:secons.millisecons" an put this in the import list
 *\param qint64 newTime
 *\return void
 */
void MainWindow::editTime(qint64 newTime)
{
    QTime timeaux(0,0,0);
    time = timeaux.addMSecs(newTime);
    QTableWidgetItem *item = new QTableWidgetItem();

    if(importMediasToolBox->currentIndex()==0){
        item->setText(time.toString("hh:mm:ss:zzz"));
        item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        videoList->setItem(videoListPos,1,item);
        videoListPos++;
    }else if (importMediasToolBox->currentIndex()==1){
        item->setText(time.toString("hh:mm:ss:zzz"));
        item->setFlags(Qt::ItemIsDragEnabled|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        audioList->setItem(audioListPos,1,item);
        audioListPos++;
    }
    filePos++;

    emit updateMediaTime();
}


/*!
 *\brief returns the type of the media with path \a dir
 *\param QDir *dir
 *\return QString
 */
QString MainWindow::getType(QDir *dir)
{
    QString extension = dir->absolutePath().remove(0,dir->absolutePath().lastIndexOf("."));
    extension = extension.toLower();
    if(extension == ".htm" || extension == ".html" || extension == ".xhtm"){
        extension = "text/html";

    }else if(extension == ".css") {
        extension = "text/css";

    }else if(extension == ".xml") {
        extension = "text/xml";

    }else if(extension == ".txt") {
        extension = "text/txt";

    }else if(extension == ".bmp") {
        extension = "image/bmp";

    }else if(extension == ".png") {
        extension = "image/png";

    }else if(extension == ".gif") {
        extension = "image/gif";

    }else if(extension == ".jpg") {
        extension = "image/jpeg";

    }else if(extension == ".jpeg") {
        extension = "image/jpeg";

    }else if(extension == ".jpe") {
        extension = "image/jpeg";

    }else if(extension == ".ua") {
        extension = "audio/basic";

    }else if(extension == ".wav") {
        extension = "audio/x-wav";

    }else if(extension == ".mp1" || extension == ".mp2" || extension == ".mp3") {
        extension = "audio/mpeg";

    }else if(extension == ".mp2" || extension == ".mpeg" || extension == ".mpg" || extension == ".mpe") {
        extension = "video/mpeg";

    }else if(extension == ".mp4" || extension == ".mpg4") {
        extension = "video/mp4";

    }else if(extension == ".mng" ) {
        extension = "video/x-mng";

    }else if(extension == ".qt" || extension == ".mov") {
        extension = "video/quicktime";

    }else if(extension == ".avi") {
        extension = "video/x-msvideo";

    }else{

        QMessageBox::StandardButton reply;
        reply = QMessageBox::critical(this, tr("ERROR!"),
                                        "Error en la extension del archivo",
                                        QMessageBox::Ok);
    }
    return extension;
}


/*!
 *\brief called to show the navigation GUI. Set focus property of medias
 *\return void
 */
void MainWindow::navigation()
{
    if(usedMediasList->rowCount() !=0 ){
        NavegationGui n(this);
        n.setMedias(usedMediasList);
        n.setMoves(descriptorList);

        if(n.exec()){
            for(int i = 0; i < descriptorList.count(); i++)
                descriptorList.at(i)->clearAllFocus();
            for(int i = 0; i < n.getNavigation()->rowCount(); i++){
                for(int j = 0 ; j < descriptorList.count();j++){
                    if(descriptorList.at(j)->getId() == ("descriptor-"+n.getNavigation()->item(i,0)->text())){
                        if(n.getNavigation()->item(i,1)->text() != "")
                            descriptorList.at(j)->setFocusIndex(n.getNavigation()->item(i,1)->text());

                        if(n.getNavigation()->item(i,2) != NULL)
                            if(n.getNavigation()->item(i,2)->text() != "")
                                descriptorList.at(j)->setMoveUp(n.getNavigation()->item(i,2)->text());

                        if(n.getNavigation()->item(i,3) != NULL)
                            if(n.getNavigation()->item(i,3)->text() != "")
                                descriptorList.at(j)->setMoveDown(n.getNavigation()->item(i,3)->text());

                        if(n.getNavigation()->item(i,4) != NULL)
                            if(n.getNavigation()->item(i,4)->text() != "")
                                descriptorList.at(j)->setMoveLeft(n.getNavigation()->item(i,4)->text());

                        if(n.getNavigation()->item(i,5) != NULL)
                            if(n.getNavigation()->item(i,5)->text() != "")
                                descriptorList.at(j)->setMoveRight(n.getNavigation()->item(i,5)->text());

                        if(n.getNavigation()->item(i,6) != NULL)
                            if(n.getNavigation()->item(i,6)->text() != "")
                                descriptorList.at(j)->setFocusBorderColor(n.getNavigation()->item(i,6)->text());

                        if(n.getNavigation()->item(i,7) != NULL)
                            if(n.getNavigation()->item(i,7)->text() != "")
                                descriptorList.at(j)->setSelBorderColor(n.getNavigation()->item(i,7)->text());

                        if(n.getNavigation()->item(i,8) != NULL)
                            if(n.getNavigation()->item(i,8)->text() != "")
                                descriptorList.at(j)->setFocusBorderWidth(n.getNavigation()->item(i,8)->text());

                        if(n.getNavigation()->item(i,9) != NULL)
                            if(n.getNavigation()->item(i,9)->text() != "")
                                descriptorList.at(j)->setFocusBorderTransparency(n.getNavigation()->item(i,9)->text());

                        if(n.getNavigation()->item(i,10) != NULL)
                            if(n.getNavigation()->item(i,10)->text() != "")
                                descriptorList.at(j)->setFocusSrc(n.getNavigation()->item(i,10)->text());

                        if(n.getNavigation()->item(i,11) != NULL)
                            if(n.getNavigation()->item(i,11)->text() != "")
                                descriptorList.at(j)->setFocusSelSrc(n.getNavigation()->item(i,11)->text());
                        break;
                    }
                }
            }
        }
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, tr("Informacion"),
                                        "No hay medias en uso en este momento",
                                        QMessageBox::Ok);
    }
}


/*!
 *\brief returns if the media \a mediaName is used in timeLine
 *\param QString mediaName
 *\return void
 */
bool MainWindow::usedMediaInTimeLine(QString mediaName)
{
    bool used = false;
    QStringList listName = graphicsSceneHead->getNameMedias();
    for(int i = 0; i< listName.count(); i++){
        if(listName.at(i) == mediaName){
            used=true;
            break;
        }
    }
    return used;
}


/*!
 *\brief called to remove a media in the medias usados table (\a QTableWidget \a *usedMediasList).
 *\return void
 */
void MainWindow::removeMediasUsados()
{
    QString mediaName = "";
    if(usedMediasList->currentRow()!=-1){
        if(!usedMediaInTimeLine(usedMediasList->item(usedMediasList->currentRow(),0)->text())){
            for(int i = 0; i< graphicsScene->getSelected()->getMedias().size(); i++){
                mediaName = usedMediasList->item(usedMediasList->currentRow(),0)->text();
                removeIndexMedia(mediaName);
                if(graphicsScene->getSelected()->getMedias().at(i) == mediaName){
                    graphicsScene->getSelected()->removeMedia(i);
                }
            }
            for(int i = 0;i<mediasRegionList->rowCount();i++){
                if(usedMediasList->item(usedMediasList->currentRow(),0)->text() == mediasRegionList->item(i,0)->text()){
                    mediasRegionList->removeRow(i);
                }
            }
            removeMedia(mediaName,usedMediasList->item(usedMediasList->currentRow(),3)->text());
            usedMediasList->removeRow(usedMediasList->currentRow());
            changePresent = true;
        }else{
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, tr("Precaucion!"),"NO se puede eliminar un media que esta siendo usado en la linea de tiempo",QMessageBox::Ok);
        }
    }
}


/*!
 *\brief called to remove a media in the medias region table (\a QTableWidget \a *mediasRegionList).
 *\return void
 */
void MainWindow::removeMediasRegion()
{
    QString mediaName = "";
    if(mediasRegionList->currentRow()!=-1){
        if(!usedMediaInTimeLine(mediasRegionList->item(mediasRegionList->currentRow(),0)->text())){
            for(int i = 0; i< graphicsScene->getSelected()->getMedias().size(); i++){
                mediaName = mediasRegionList->item(mediasRegionList->currentRow(),0)->text();
                removeIndexMedia(mediaName);
                if(graphicsScene->getSelected()->getMedias().at(i) == mediaName){
                    graphicsScene->getSelected()->removeMedia(i);
                }
            }
            for(int i = 0;i<usedMediasList->rowCount();i++){
                if(mediasRegionList->item(mediasRegionList->currentRow(),0)->text() == usedMediasList->item(i,0)->text()){
                    usedMediasList->removeRow(i);
                }
            }
            removeMedia(mediaName,mediasRegionList->item(mediasRegionList->currentRow(),3)->text());
            mediasRegionList->removeRow(mediasRegionList->currentRow());
            changePresent = true;
        }else{
            QMessageBox::StandardButton reply;
            reply = QMessageBox::warning(this, tr("Precaucion!"),"NO se puede eliminar un media que esta siendo usado en la linea de tiempo",QMessageBox::Ok);
        }
    }
}
/*!
 *\brief called to remove a media in some import list with name \a name in list of type \a type.
 *\param QString media
 *\param QString type
 *\return void
 */
void MainWindow::removeMedia(QString media, QString type)
{
    if(type == "Video"){
        for(int i = 0; i < mediaVideoList.count();i++){
            if(media == mediaVideoList.at(i)->getId()){
                mediaVideoList.removeAt(i);
                break;
            }
        }
    }
    if(type == "Audio"){
        for(int i = 0; i < mediaAudioList.count();i++){
            if(media == mediaAudioList.at(i)->getId()){
                mediaAudioList.removeAt(i);
                break;
            }
        }
    }

    if(type == "Texto"){
        for(int i = 0; i < mediaTextList.count();i++){
            if(media == mediaTextList.at(i)->getId()){
                mediaTextList.removeAt(i);
                break;
            }
        }
    }

    if(type == "Imagen"){
        for(int i = 0; i < mediaImageList.count();i++){
            if(media == mediaImageList.at(i)->getId()){
                mediaImageList.removeAt(i);
                break;
            }
        }
    }

    if(type == "Lua"){
        for(int i = 0; i < mediaLuaList.count();i++){
            if(media == mediaLuaList.at(i)->getId()){
                mediaLuaList.removeAt(i);
                break;
            }
        }
    }

    if(type == "Uri"){
        for(int i = 0; i < mediaUriList.count();i++){
            if(media == mediaUriList.at(i)->getId()){
                mediaUriList.removeAt(i);;
                break;
            }
        }
    }
}


/*!
 *\brief called when a media is removed, then removes focus index of media \a media in another descriptors
 *\param QString media
 *\return void
 */
void MainWindow::removeIndexMedia(QString media)
{
    QString descriptorName = "";
    QString index = "";
    for(int i = 0; i < descriptorList.count();i++){
        descriptorName = descriptorList.at(i)->getId();
        descriptorName = descriptorName.remove("descriptor-");
        if(descriptorName == media){
            index = descriptorList.at(i)->getFocusIndex();
        }
        descriptorList.removeAt(i);
    }

    for(int i = 0 ; i < descriptorList.count(); i++){
        if(descriptorList.at(i)->getMoveUp() == index){
            descriptorList.at(i)->removeMoveUp();
        }

        if(descriptorList.at(i)->getMoveDown() == index){
            descriptorList.at(i)->removeMoveDown();
        }

        if(descriptorList.at(i)->getMoveLeft() == index){
            descriptorList.at(i)->removeMoveLeft();
        }

        if(descriptorList.at(i)->getMoveRight() == index){
            descriptorList.at(i)->removeMoveRight();
        }
    }
}


/*!
 *\brief called when the \a actionPALN is toggled to show or hide (\a visible value) the grid Pal-N
 *\param bool visible
 *\return void
 */
void MainWindow::setVisiblePALN(bool visible)
{
    palN->setVisible(visible);
    palNText1->setVisible(visible);
    palNText2->setVisible(visible);
    changePresent = true;
}


/*!
 *\brief called when the \a actionPALAncho is toggled to show or hide (\a visible value) the grid Pal-Weigth
 *\param bool visible
 *\return void
 */
void MainWindow::setVisiblePALAncho(bool visible)
{
    palWeigth->setVisible(visible);
    palWeigthText1->setVisible(visible);
    palWeigthText2->setVisible(visible);
    changePresent = true;
}


/*!
 *\brief called when the \a actionHDTVp is toggled to show or hide (\a visible value) the grid HDTV
 *\param bool visible
 *\return void
 */
void MainWindow::setVisibleHDTVp(bool visible)
{
    hdtv->setVisible(visible);
    hdtvText1->setVisible(visible);
    hdtvText2->setVisible(visible);
    changePresent = true;
}


/*!
 *\brief called when the \a actionHDTVp is toggled to show or hide (\a visible value) the grid HDTV HD
 *\param bool visible
 *\return void
 */
void MainWindow::setVisibleHDTVi(bool visible)
{
    hdtvHD->setVisible(visible);
    hdtvHDText1->setVisible(visible);
    hdtvHDText2->setVisible(visible);
    changePresent = true;
}


/*!
 *\brief called when the \a actionHDTVp is toggled to show or hide (\a visible value) the grid specific
 *\param bool visible
 *\return void
 */
void MainWindow::setVisibleOther(bool visible)
{
    otherScreen->setVisible(visible);
    otherScreenText1->setVisible(visible);
    otherScreenText2->setVisible(visible);
    changePresent = true;
}


/*!
 *\brief called to adapt a region to the PALN screen when have this percent values
 *\return void
 */
void MainWindow::setSizeScreenPALN()
{
    screenSizeX = 720;
    screenSizeY = 576;
    uploadRegions();
    changePresent = true;
}


/*!
 *\brief called to adapt a region to the PALA screen when have this percent values
 *\return void
 */
void MainWindow::setSizeScreenPALAncho()
{
    screenSizeX = 1024;
    screenSizeY = 576;
    uploadRegions();
    changePresent = true;
}


/*!
 *\brief called to adapt a region to the HDTVp  screen when this have percent values
 *\return void
 */
void MainWindow::setSizeScreenHDTV720p()
{
    screenSizeX = 1280;
    screenSizeY = 720;
    uploadRegions();
    changePresent = true;
}


/*!
 *\brief called to adapt a region to the HDTVi screen when this have percent values
 *\return void
 */
void MainWindow::setSizeScreenHDTV1080i()
{
    screenSizeX = 1920;
    screenSizeY = 1080;
    uploadRegions();
    changePresent = true;
}


/*!
 *\brief called to adapt a region to the NEW screen when this have percent values
 *\return void
 */
void MainWindow::setSizeScreenOther()
{
    screenSizeX =  screenSizeOtherX;
    screenSizeY =  screenSizeOtherY;
    uploadRegions();
    changePresent = true;
}


/*!
 *\brief called to show a GUI to modify a new screen size
 *\return void
 */
void MainWindow::setSizeOther()
{
    ModifySize modify(this);
    modify.setWidth(screenSizeOtherX);
    modify.setHeight(screenSizeOtherY);
    if(modify.exec()==QDialog::Accepted){
        QPen *pen = new QPen(Qt::SolidPattern, 2.0,Qt::DashDotLine , Qt::SquareCap,Qt::MiterJoin);
        pen->setColor(QColor(127,127,243,255));

        if(screenSizeOtherX != 0){
            graphicsScene->removeItem(otherScreen);
            graphicsScene->removeItem(otherScreenText1);
            graphicsScene->removeItem(otherScreenText2);

            otherAction->setText("Marca de pantalla otro ("+QString::number(modify.getWidth())+"x"+QString::number(modify.getHeight())+" px)");
            otherRegionAction->setText("Relacion Region/Otro ("+QString::number(modify.getWidth())+"x"+QString::number(modify.getHeight())+" px)");
        }else{
            otherAction->setText("Marca de pantalla otro ("+QString::number(modify.getWidth())+"x"+QString::number(modify.getHeight())+" px)");
            otherAction->setCheckable(true);
            otherAction->setChecked(true);

            otherRegionAction->setText("Relacion Region/Otro ("+QString::number(modify.getWidth())+"x"+QString::number(modify.getHeight())+" px)");
            otherRegionAction->setCheckable(true);
            otherRegionAction->setChecked(true);

            groupScreens->addAction(otherRegionAction);

            ui->menuVer->insertAction(modifyOtherRegionAction,otherAction);
            ui->menuVer->insertAction(modifyOtherRegionAction,otherRegionAction);
            ui->menuVer->insertSeparator(otherRegionAction);

            connect(otherAction, SIGNAL(toggled(bool)), this, SLOT(setVisibleOther(bool)));
            connect(otherRegionAction, SIGNAL(triggered()), this, SLOT(setSizeScreenOther()));

            ui->actionPALN->setChecked(false);
            ui->actionPALAncho->setChecked(false);
            ui->actionHDTV720->setChecked(false);
            ui->actionHDTV1080->setChecked(false);
        }

        screenSizeOtherX = modify.getWidth();
        screenSizeOtherY = modify.getHeight();

        otherScreen = new QGraphicsRectItem();
        otherScreen->setFlag(QGraphicsItem::ItemIsMovable,false);
        otherScreen->setRect(QRectF(0, 0, screenSizeOtherX,screenSizeOtherY));
        otherScreen->setPen(*pen);
        graphicsScene->addItem(otherScreen);

        otherScreenText1 = new QGraphicsTextItem("Otro - "+QString::number(screenSizeOtherX)+"x"+QString::number(screenSizeOtherY)+" px");
        otherScreenText1->setDefaultTextColor(QColor(127,127,243,255));
        otherScreenText1->setPos(screenSizeOtherX+5,0);
        graphicsScene->addItem(otherScreenText1);

        otherScreenText2 = new QGraphicsTextItem("Otro - "+QString::number(screenSizeOtherX)+"x"+QString::number(screenSizeOtherY)+" px");
        otherScreenText2->setDefaultTextColor(QColor(127,127,243,255));
        otherScreenText2->setPos(0,screenSizeOtherY);
        graphicsScene->addItem(otherScreenText2);

        setSizeScreenOther();
        changePresent = true;
    }
}


/*!
 *\brief resizes and relocates the regions if the size or the loacation is in percentaje
 *\return void
 */
void MainWindow::uploadRegions()
{
    QList<QGraphicsItem *> lista = graphicsScene->items();
    GraphicsRectItem *rectItem;
    QString percent;
    int value;
    GraphicsRectItem *rectItemAux;

    for(int i = lista.size()-1; i >= 0 ;i--){   
        if(lista.at(i)->type() == 5){        
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));  
            if(rectItem->getXRecNCL().contains("%") && rectItem->parentItem() == 0){   
                percent = rectItem->getXRecNCL().remove("%");    
                value = (percent.toInt()*screenSizeX)/100;
                rectItem->setPosistionXY((qreal)value,rectItem->y());  
            }else if(rectItem->getXRecNCL().contains("%") ){     
                rectItemAux =  qgraphicsitem_cast<GraphicsRectItem *>(rectItem->parentItem());           
                percent = rectItem->getXRecNCL().remove("%");     
                value = (percent.toInt()*rectItemAux->getWidthRec())/100;       
                rectItem->setPosistionXY((qreal)value,rectItem->y());         
            }     
            if(rectItem->getYRecNCL().contains("%") && rectItem->parentItem() == 0){
                percent = rectItem->getYRecNCL().remove("%");
                value = (percent.toInt()*screenSizeY)/100;
                rectItem->setPosistionXY(rectItem->x(),(qreal)value);
            }else if(rectItem->getYRecNCL().contains("%")){
                rectItemAux =  qgraphicsitem_cast<GraphicsRectItem *>(rectItem->parentItem());
                percent = rectItem->getYRecNCL().remove("%");
                value = (percent.toInt()*rectItemAux->getHeightRec())/100;
                rectItem->setPosistionXY(rectItem->x(),(qreal)value);
            }
            if(rectItem->getWidthRecNCL().contains("%") && rectItem->parentItem() == 0){
                percent = rectItem->getWidthRecNCL().remove("%");
                value = (percent.toInt()*screenSizeX)/100;
                rectItem->setWidth(value);
            }else if(rectItem->getWidthRecNCL().contains("%")){
                rectItemAux =  qgraphicsitem_cast<GraphicsRectItem *>(rectItem->parentItem());
                percent = rectItem->getWidthRecNCL().remove("%");
                value = (percent.toInt()*rectItemAux->getWidthRec())/100;
                rectItem->setWidth(value);
            } 
            if(rectItem->getHeighRecNCL().contains("%") && rectItem->parentItem() == 0){
                percent = rectItem->getHeighRecNCL().remove("%");
                value = (percent.toInt()*screenSizeY)/100;
                rectItem->setHeight(value);
            }else if(rectItem->getHeighRecNCL().contains("%")){
                rectItemAux =  qgraphicsitem_cast<GraphicsRectItem *>(rectItem->parentItem());
                percent = rectItem->getHeighRecNCL().remove("%");
                value = (percent.toInt()*rectItemAux->getHeightRec())/100;
                rectItem->setHeight(value);
            }
        }
    }
}


/*!
 *\brief called to run the project on ginga
 *\return void
 */
void MainWindow::runNcl()
{
    QProcess *ginga = new QProcess(this);
    QStringList arguments;
    if(!nclName.isEmpty() && !nclName.contains(".ncl")){
        nclName.append(".ncl");
    }
    arguments << "--ncl"<< nclName;
    connect(ginga,SIGNAL(error(QProcess::ProcessError)),this,SLOT(gingaError(QProcess::ProcessError)));
    if(nclName.isEmpty()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, tr("Precaucion!"),"Debe generar el archivo NCL antes de ejecutarlo",QMessageBox::Ok);
    }else{
         ginga->start("ginga", arguments);
         QByteArray result = ginga->readAll();
    }
}


/*!
 *\brief called if an error is ocurred when ginga is ran
 *\return void
 */
void MainWindow::gingaError(QProcess::ProcessError error)
{
    if(error == QProcess::FailedToStart){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, tr("Error"),
                                         "Para poder visualizar los resultados, debera instalar Ginga en su equipo",
                                        QMessageBox::Ok);
    }else if(error !=1){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::information(this, tr("Error"),"Error al intentar ejecutar Ginga",QMessageBox::Ok);
    }
}


/*!
 *\brief returns the millisecons from the seconds \a sec
 *\param int sec
 *\return void
 */
int MainWindow::secToMSec(int sec)
{
    int ret;
    ret = sec*1000;
    return ret;
}


/*!
 *\brief returns the millisecons from the minutes \a min
 *\param int min
 *\return void
 */
int MainWindow::minToMSec(int min)
{
    int ret;
    ret = min*60000;
    return ret;
}


/*!
 *\brief returns the millisecons from the hours \a hour
 *\param int hour
 *\return void
 */
int MainWindow::hourToMSec(int hour)
{
    int ret;
    ret = hour*3600000;
    return ret;
}


/*!
 *\brief called to remove a media selected in some import list.
 *\return void
 */
void MainWindow::removeMedia()
{
    if(tabRegions->currentIndex() == 1){
        if (videoList->isVisible()){
            if(videoList->currentRow() != -1){
                importVideoList.removeAt(videoList->currentRow());
                videoList->removeRow(videoList->currentRow());
                changePresent = true;
            }
         }else if (audioList->isVisible()){
             if(audioList->currentRow() != -1){
                importAudioList.removeAt(audioList->currentRow());
                audioList->removeRow(audioList->currentRow());
                changePresent = true;
             }
         }else if (imageList->isVisible()){
             if(imageList->currentRow() != -1){
                importImageList.removeAt(imageList->currentRow());
                delete imageList->takeItem(imageList->currentRow());
                changePresent = true;
             }
         }else if (textList->isVisible()){
             if(textList->currentRow() != -1){
                importTextList.removeAt(textList->currentRow());
                delete textList->takeItem(textList->currentRow());
                changePresent = true;
             }
         }
     }else{
          if(luaList->isVisible()){
             if(luaList->currentRow() != -1){
                importLuaList.removeAt(luaList->currentRow());
                delete luaList->takeItem(luaList->currentRow());
                changePresent = true;
            }
          }else if (uriList->isVisible()){
              if(uriList->currentRow() != -1){
                importUriList.removeAt(uriList->currentRow());
                delete uriList->takeItem(uriList->currentRow());
                changePresent = true;
              }
          }
     }
}


/*!
 *\brief clear all list, tables and diagrams scene.
 *\return void
 */
void MainWindow::clearAll()
{
    graphicsScene->clear();
    graphicsSceneHead->clear();
    graphicsSceneTemporal->clear();

    mediaVideoList.clear();
    mediaAudioList.clear();
    mediaImageList.clear();
    mediaTextList.clear();
    mediaLuaList.clear();
    mediaUriList.clear();

    for(int i = videoList->rowCount();i>=0;i--){
        videoList->removeRow(i);
    }

    for(int i = audioList->rowCount();i>=0;i--){
        audioList->removeRow(i);
    }

    imageList->clear();
    textList->clear();
    luaList->clear();
    uriList->clear();

    for(int i = usedMediasList->rowCount();i>=0;i--){
        usedMediasList->removeRow(i);
    }
    for(int i = mediasRegionList->rowCount();i>=0;i--){
        mediasRegionList->removeRow(i);
    }

    treeWidget->clear();
}


/*!
 *\brief called to show a GUI to edit the project description
 *\return void
 */
void MainWindow::editProjectDescription()
{
    EditProjectDescription edit(nameProject,descriptionProject,dateProject,this);
    if(edit.exec()== QDialog::Accepted){
        nameProject = edit.getName();
        descriptionProject = edit.getDescription();
        dateProject = edit.getDate();
        setWindowTitle("CreaTVDigital - "+nameProject);
        changePresent = true;
    }
}


/*!
 *\brief load images in all tables and lists of the main window when a file is opened
 *\return void
 */
void MainWindow::loadImages()
{
    QString icon;
    QString extension;
    QString videoName;
    QFile file;    
    for(int i = 0; i<videoList->rowCount();i++){
        extension = videoList->item(i,0)->toolTip();
        videoName = videoList->item(i,0)->toolTip().remove(0, videoList->item(i,0)->toolTip().lastIndexOf('/')+1);
        videoName.append(".jpg");
        QString cmd = "ffmpeg -i "+extension+" -ss 3.001 -t 3.001 -y images/"+videoName;

        int numError = system(cmd.toAscii());

        if(numError != 256 ){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::information(this, tr("Cargar Videos"), "Los Archivos de video no se pueden cargar dado a que no posee ffmpeg en su sistema operativo");
            break;
        }

        QIcon icon(QPixmap(QDir::currentPath()+"/images/"+videoName));
        videoList->setIconSize(QSize(50,50));
        videoList->item(i,0)->setIcon(QIcon(icon));
        videoList->setRowHeight(i,50);
    }
    for(int i = 0; i<imageList->count();i++){
        extension = imageList->item(i)->toolTip();
        icon = extension;
        imageList->setIconSize(QSize(50,50));
        imageList->item(i)->setIcon(QIcon(icon));
    }
    for(int i = 0; i<audioList->rowCount();i++){
        extension = audioList->item(i,0)->toolTip();
        if (extension.endsWith(".ua"))
            icon = QDir::currentPath()+"/images/audioFiles/UA.png";
        if (extension.endsWith(".wav"))
             icon = QDir::currentPath()+"/images/audioFiles/wav.png";
        if (extension.endsWith(".mp1"))
             icon = QDir::currentPath()+"/images/audioFiles/MP1.png";
        if (extension.endsWith(".mp2"))
             icon = QDir::currentPath()+"/images/audioFiles/MP2.png";
        if (extension.endsWith(".mp3"))
             icon = QDir::currentPath()+"/images/audioFiles/mp3.png";
        if (extension.endsWith(".mpg4"))
             icon = QDir::currentPath()+"/images/audioFiles/MPG4.png";
        audioList->setIconSize(QSize(50,50));
        audioList->setRowHeight(i,50);
        audioList->item(i,0)->setIcon(QIcon(icon));
    }
    for(int i = 0; i<textList->count();i++){
        extension = textList->item(i)->toolTip();
        if (extension.endsWith(".html"))
            icon =  QDir::currentPath()+"/images/textFiles/html_file.png";
        if (extension.endsWith(".htm"))
            icon =  QDir::currentPath()+"/images/textFiles/htm_file.png";
        if (extension.endsWith(".css"))
            icon =  QDir::currentPath()+"/images/textFiles/css_file.png";
        if (extension.endsWith(".xml"))
            icon =  QDir::currentPath()+"/images/textFiles/xml_file.png";
        if (extension.endsWith(".txt"))
            icon =  QDir::currentPath()+"/images/textFiles/txt_file.png";
        textList->setIconSize(QSize(50,50));
        textList->item(i)->setIcon(QIcon(icon));
    }
    for(int i = 0; i<luaList->count();i++){
        icon =  QDir::currentPath()+"/images/lua_icon.png";
        luaList->setIconSize(QSize(50,50));
        luaList->item(i)->setIcon(QIcon(icon));
    }
    for(int i = 0; i<uriList->count();i++){
        icon =  QDir::currentPath()+"/images/uri_icon.png";
        uriList->setIconSize(QSize(50,50));
        uriList->item(i)->setIcon(QIcon(icon));
    }
    usedMediasList->setIconSize(QSize(40,40));
    for(int i = 0; i<usedMediasList->rowCount();i++){     
        extension = usedMediasList->item(i,0)->toolTip();
        if(usedMediasList->item(i,3)->text() == "Video"){
            videoName = usedMediasList->item(i,0)->toolTip().remove(0,usedMediasList->item(i,0)->toolTip().lastIndexOf('/')+1);
            QIcon icon(QPixmap(QDir::currentPath()+"/images/"+videoName+".jpg"));
            usedMediasList->item(i,0)->setIcon(QIcon(icon));
        }
        if(usedMediasList->item(i,3)->text() == "Audio"){
            if (extension.endsWith(".ua"))
                icon = QDir::currentPath()+"/images/audioFiles/UA.png";
            if (extension.endsWith(".wav"))
                 icon = QDir::currentPath()+"/images/audioFiles/wav.png";
            if (extension.endsWith(".mp1"))
                 icon = QDir::currentPath()+"/images/audioFiles/MP1.png";
            if (extension.endsWith(".mp2"))
                 icon = QDir::currentPath()+"/images/audioFiles/MP2.png";
            if (extension.endsWith(".mp3"))
                 icon = QDir::currentPath()+"/images/audioFiles/mp3.png";
            if (extension.endsWith(".mpg4"))
                 icon = QDir::currentPath()+"/images/audioFiles/MPG4.png";
            usedMediasList->item(i,0)->setIcon(QIcon(icon));;
        }
        if(usedMediasList->item(i,3)->text() == "Imagen"){
            icon = extension;
            usedMediasList->item(i,0)->setIcon(QIcon(icon));
        }      
        if(usedMediasList->item(i,3)->text() == "Texto"){
            if (extension.endsWith(".html"))
                icon =  QDir::currentPath()+"/images/textFiles/html_file.png";
            if (extension.endsWith(".htm"))
                icon =  QDir::currentPath()+"/images/textFiles/htm_file.png";
            if (extension.endsWith(".css"))
                icon =  QDir::currentPath()+"/images/textFiles/css_file.png";
            if (extension.endsWith(".xml"))
                icon =  QDir::currentPath()+"/images/textFiles/xml_file.png";
            if (extension.endsWith(".txt"))
                icon =  QDir::currentPath()+"/images/textFiles/txt_file.png";
            usedMediasList->item(i,0)->setIcon(QIcon(icon));
        }
        if(usedMediasList->item(i,3)->text() == "Lua"){
            icon =  QDir::currentPath()+"/images/lua_icon.png";
            usedMediasList->item(i,0)->setIcon(QIcon(icon));
        }
        if(usedMediasList->item(i,3)->text() == "Uri"){
            icon =  QDir::currentPath()+"/images/uri_icon.png";
            usedMediasList->item(i,0)->setIcon(QIcon(icon));
        }
    }
}


/*!
 *\brief reimplemented method of QMainWindow to verify if you want to save changes
 *\param QCloseEvent *event
 *\return void
 */
void MainWindow::closeEvent(QCloseEvent *event)
 {
    if(changePresent){
        QMessageBox msgBox(QMessageBox::Warning,tr("Cambios Realizados"),"Desea guardar cambios realizados?", 0, this);
        msgBox.addButton(tr("Si"), QMessageBox::AcceptRole);
        msgBox.addButton(tr("No"), QMessageBox::RejectRole);
        msgBox.setStandardButtons(QMessageBox::Cancel);

        int ret = msgBox.exec();

        if (ret == QMessageBox::AcceptRole)
            save();
        if(ret == QMessageBox::Cancel)
            event->ignore();
    }
 }


void MainWindow::setDataNcl()
{
    /*setXValue(spinX->value());
    setYValue(spinY->value());
    setWValue(spinW->value());
    setHValue(spinH->value());*/
}


/*!
 *\brief called to show a warning message whe a bad element is dropped in a GrapchicsScene
 *\return void
 */
void MainWindow::outElement()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Precaucion!"),"El elemento debe ser de la lista \"Medias Region\" o \"Medias Usados\"",QMessageBox::Ok);
    return;
}


/*!
 *\brief called to show a warning message whe a bad element is dropped in a RectItem
 *\return void
 */
void MainWindow::outElementRegion()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, tr("Precaucion!"),"El elemento debe ser de alguna de las listas de medias importados ",QMessageBox::Ok);
    return;
}


/*!
 *\brief called to set false the drop item in all rectangles
 *\return void
 */
void MainWindow::setFlaseAllOkItemDrop()
{
    QList<QGraphicsItem *> lista = graphicsScene->items();
    GraphicsRectItem *rectItem;
    for(int i = 0; i < lista.size();i++){
        if(lista.at(i)->type() == 5){ //is a graphiscsrectitem
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
            rectItem->setFlaseOkItemDrop();
        }
    }
}


/*!
 *\brief called to set true the drop item in all rectangles
 *\return void
 */
void MainWindow::setTrueAllOkItemDrop()
{
    QList<QGraphicsItem *> lista = graphicsScene->items();
    GraphicsRectItem *rectItem;
    for(int i = 0; i < lista.size();i++){
        if(lista.at(i)->type() == 5){ //is a graphiscsrectitem
            rectItem =  qgraphicsitem_cast<GraphicsRectItem *>(lista.at(i));
            rectItem->setTrueOkItemDrop();
        }
    }
}

