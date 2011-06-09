/*!
 *\file mainwindow.h
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods declaration to manipulates activities in main window.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QStringList>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QActionGroup>
#include <QMouseEvent>
#include <QTreeWidgetItem>
#include "graphicsscene.h"
#include "graphicsrectitem.h"
#include "ncldocument.h"
#include <Phonon/MediaObject>
#include <QTime>

#include "NCL/media.h"
#include "NCL/descriptor.h"

#include "QUnitMargin.h"
#include "QUnitMarginVertical.h"
#include "QUnitMarginTime.h"

#include "diagramscene.h"
#include "diagramscenehead.h"

#include "GUI/newproject.h"
#include "GUI/selectrole.h"
#include "GUI/imagedescriptorattr.h"
#include "GUI/audiodescriptoratrr.h"
#include "GUI/textdescriptoratrr.h"
#include "GUI/videodescriptorattr.h"
#include "GUI/setattributesgui.h"
#include "GUI/navegationgui.h"
#include "GUI/selectkeygui.h"
#include "GUI/uriconfig.h"
#include "GUI/modifysize.h"
#include "saveproject.h"
#include "GUI/editprojectdescription.h"

#include <QList>


/*!
* \class MainWindow
* \brief class to manipulates activities in main window.
*/


namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// initializes main window, creates connectors.
    MainWindow(QWidget *parent = 0);
    /// destructor of de UI.
    ~MainWindow();
    //QGridLayout *gridLayout;

public slots:
    /// called to open a file chooser to choose a file to add to a import list
    void generalFileChooser();
    /// called to open a GUI to specify the project description
    void newProject();
    /// called to to create the NCL file
    void createNCL();
    /// called to add a media from an import list to a region using button
    void addMediaToRegion();
    /// called when a region (GraphicsRectItem) is selected to display their atributtes and medias.
    void itemSelected(GraphicsRectItem *item);

    /// called to add a media from an import list to a region using mouse
    void dropItem(GraphicsRectItem *item);
    /// called to enable or disable the create a new region
    void addRegion();
    /// called to change the type of cursor and prepare to move regions
    void selectButton();
    /// called when a region inside of a regios is created
    void addSubRegion(QList<Regionn*> lista, GraphicsRectItem *item, Regionn *region);
    /// called when a region on the tree is selected to select a region in the scene.
    void selectRegion(QTreeWidgetItem* item);
    /// called to hide or show a region when the checkBox in the tree is toggled.
    void setShowRegion(QTreeWidgetItem* item);
    /// called when a region is removed to remove the region name in the tree
    void removeTreeRegion();
    /// called to remove a region of the scene.
    void deleteItem();
    /// called to add a item in the tree on the top level
    void addRootTreeItem(QString regionNumber);
    /// called to add a child item in the tree
    void addChildTreeItem(QString regionNumber,QString parentName);
    /// called to move the horizontal rule when the horizontal scrool bar is moved
    void moveHorizontalRule(int ejeX);
    /// called to move the vertical rule when the vertical scrool bar is moved
    void moveVerticalRule(int ejeY);
    /// called to move the horizontal rule when the horizontal scrool bar in the seccion timeLine is moved
    void moveHorizontalRuleTime(int ejeX);

    /// called to save the project
    void save();
    /// called to save the project with another name
    void saveAs();
    /// called to open a project
    void open();
    /// called to update the time of a media video or a media audio
    void updateMediaTime();
    /// called to update the media video and media audio times
    void updateMediaTimes();
    /// change time of a media in millisecs to "hour:minits:secons.millisecons" an put this in the import list
    void editTime(qint64 newTime);
    /// called when a media is dropped into "timeLine"
    void diagramSceneDrop(qreal posX);
    /// called to select a key of remote control
    void selectedButton(Image *button,Image* startItemP,Image* endItemP);
    /// called to show a warning message whe a bad element is dropped in a GrapchicsScene
    void outElement();
    /// called to show a warning message whe a bad element is dropped in a RectItem
    void outElementRegion();

signals:
    /// this signal is emitted when we select create a new region
    void setButtonPressed(bool press);

private:
    Ui::MainWindow *ui;

    QString nameProject;
    QString descriptionProject;
    QString myFileName;
    QString nclName;

    QDate dateProject;

    int filePos;
    int videoListPos;
    int audioListPos;

    int screenSizeX;
    int screenSizeY;
    int screenSizeOtherX;
    int screenSizeOtherY;

    int sceneTemporalWidth;

    int mediaNumber;
    int regionNumber;

    bool buttonRectAct;
    bool saveAsBool;
    bool changePresent;
    bool clear;

    QStringList videoFiles;
    QStringList audioFiles;

    QList<Media*> mediaVideoList;
    QList<QDir*> importVideoList;

    QList<Media*> mediaAudioList;
    QList<QDir*> importAudioList;

    QList<Media*> mediaImageList;
    QList<QDir*> importImageList;

    QList<Media*> mediaTextList;
    QList<QDir*> importTextList;

    QList<Media*> mediaLuaList;
    QList<QDir*> importLuaList;

    QList<Media*> mediaUriList;
    QStringList importUriList;

    QList<Descriptor*> descriptorList;
    QList<Regionn*> regionList;

    QToolBar *editToolBar;
    QToolBar *toolBar;

    GraphicsScene *graphicsScene;
    DiagramScene *graphicsSceneTemporal;
    DiagramSceneHead *graphicsSceneHead;

    QUnitMargin *horizontalRule;
    QUnitMarginVertical *verticalRule;
    QUnitMarginTime *timeRule;

    QGraphicsView *graphicsView;
    QGraphicsView *graphicsViewTemporal;
    QGraphicsView *graphicsViewTemporalMedias;

    QTreeWidget *treeWidget;

    QTableWidget *propertyRegionTable;
    QTableWidget *videoList;
    QTableWidget *audioList;
    QTableWidget *usedMediasList;
    QTableWidget *mediasRegionList;

    QToolBox *importMediasToolBox;
    QToolBox *importOtherToolBox;

    QTabWidget *tabRegions;
    QTabWidget *tabLists;

    QListWidget *imageList;
    QListWidget *textList;
    QListWidget *luaList;
    QListWidget *uriList;

    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *resetZoomAction;
    QAction *mouseAction;
    QAction *deleteLineAction;
    QAction *deleteInteractivityAction;
    QAction *interactivityAction;
    QAction *otherAction;
    QAction *otherRegionAction;
    QAction *modifyOtherRegionAction;

    QActionGroup *groupScreens;

    QSpinBox *spinBoxZoom;
    QSpinBox *spinX;
    QSpinBox *spinY;
    QSpinBox *spinW;
    QSpinBox *spinH;
    QSpinBox *spinZ;

    QWidget *widgetPropieties;
    QWidget *widgetMediasRegion;

    QGraphicsRectItem * palN;
    QGraphicsRectItem * palWeigth;
    QGraphicsRectItem * hdtv;
    QGraphicsRectItem * hdtvHD;
    QGraphicsRectItem * otherScreen;

    QGraphicsTextItem * palNText1;
    QGraphicsTextItem * palNText2;
    QGraphicsTextItem * palWeigthText1;
    QGraphicsTextItem * palWeigthText2;
    QGraphicsTextItem * hdtvText1;
    QGraphicsTextItem * hdtvText2;
    QGraphicsTextItem * hdtvHDText1;
    QGraphicsTextItem * hdtvHDText2;
    QGraphicsTextItem * otherScreenText1;
    QGraphicsTextItem * otherScreenText2;

    QComboBox *comboX;
    QComboBox *comboY;
    QComboBox *comboH;
    QComboBox *comboW;

    Phonon::MediaObject *mediaObject;

    QMatrix originalMatrix;

    QTime time;

    QGroupBox *timeGroupBox;

    QFileDialog *fileChooser;

    /// returns the type of the media with path \a dir
    QString getType(QDir *dir);
    /// returns the media name of the media with path \a dir
    QString getMediaName(QString dir);
    /// returns the type of the media with name \a mediaName
    QString searchTypeMedia(QString mediaName);

    /// returns the millisecons from the seconds \a sec
    int secToMSec(int sec);
    /// returns the millisecons from the minutes \a min
    int minToMSec(int min);
    /// returns the millisecons from the hours \a hour
    int hourToMSec(int hour);

    /// returns true if the media id \a id is in use
    bool idExist(QString id);
    /// returns true if the media file \a dir is in use
    bool fileExist(QString dir);

    /// initializes the actions of the main window toolbar with icons
    void initToolBarIcons();
    /// initializes the elments main window disable if \a enable value is false (before to create a new project or open ones).
    /// if \enable value is true, does disable the elements in main window (after to create a project or open ones).
    void initEnable(bool enable);
    /// init the widgets to Regions treatments
    void initRegionsArea();
    /// init the widgets to time line treatments (media iteractivity, media time life, etc.)
    void initTemporalArea();
    /// creates a Region an adds it to a region list (\a regionList)
    void addRegionNCL();

    /// sets the movement property and focus property disable when a sub-region is create (\a bool \a prop \a = \a false )
    void setPropItems(bool prop);

    /// creates a media image, create the descriptor to the media, adds this media to a region, adds this media to
    /// used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
    void addMediaImageToRegion();
    /// creates a media text, create the descriptor to the media, adds this media to a region, adds this media to
    /// used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
    void addMediaTextToRegion();
    /// creates a media audio, create the descriptor to the media, adds this media to a region, adds this media to
    /// used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
    void addMediaAudioToRegion();
    /// creates a media video, create the descriptor to the media, adds this media to a region, adds this media to
    /// used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
    void addMediaVideoToRegion();
    /// creates a media lua, create the descriptor to the media, adds this media to a region, adds this media to
    /// used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
    void addMediaLuaToRegion();
    /// creates a media url, create the descriptor to the media, adds this media to a region, adds this media to
    /// used media table (\a usedMediasList) and adds this media to regions media table (\a mediasRegionList)
    void addMediaUriToRegion();

    /// adds the role image to an item Image of the Arrow
    void addImage(Image* button , QStringList playList,QStringList stopList,QStringList pauseList , QStringList resumeList, QStringList abortList,QStringList setList);
    /// sets the type of the image and location of images added with \a addImage
    void imageLocation(QString path, Image *button,qreal posX, qreal posY ,qreal zvalue);
    /// eliminates the image with type \a typeImage
    void checkImage(Image* button, int typeImage);
    /// changes the type of cursor for \a xCursor
    void putXCursor(QCursor xCursor,bool prop);
    /// adds a DescriptorParam to \a descriptorList
    void addPropertyToDescriptor();

    /// opens a file chooser to choose a media Video to import and add to the list
    void fileChoserVideo();
    /// opens a file chooser to choose a media Audio to import and add to the list
    void fileChoserAudio();
    /// opens a file chooser to choose a media Image to import and add to the list
    void fileChoserImage();
    /// opens a file chooser to choose a media Text to import and add to the list
    void fileChoserText();
    /// opens a file chooser to choose a media Lua to import and add to the list
    void fileChoserLua();
    /// opens a file chooser to choose a media Url to import and add to the list
    void fileChoserUri();

    /// sets the checkBox (with value \a ok)of the table \a usedMediasList and \a mediasRegionList if the media \a name is used in the timelime diagram
    void setMediaUsedIconOk(QString name, bool ok);
    /// loads the medias assigned to the region in the rmedia egions table (\a mediasRegionList)
    void loadMediasRegion();
    /// initializes the screen sizes of the drawing area of regions
    void initScreenSize();
    /// initializes the actions of the main window
    void initActions();
    /// initializes the docks area of the main window with its elements
    void initDockTools();
    /// resizes and relocates the regions if the size or the loacation is in percentaje
    void uploadRegions();

    /// creates a new project
    void newProject(QString description,QString selected,int w,int h, QDate date);
    /// clear all list, tables and diagrams scene.
    void clearAll();
    /// creates a new project with name \a projectName, description \a projectDescription, date \a projectDate, screen size \a screen (or  \a width x \a height)
    void createProject(QString projectName,QString projectDescription,QDate projectDate, QString screen, int width, int height);
    /// load images in all tables and lists of the main window when a file is opened
    void loadImages();
    /// returns if the media \a mediaName is used in timeLine
    bool usedMediaInTimeLine(QString mediaName);

private slots:
    /// generates zoom in or zoom out in the drawing area of regions
    void zoom(const qreal factor);
    /// called when the zoom in button is pressed, sets the spinBox value of the zoom
    void zoomIn();
    /// called when the zoom out button is pressed, sets the spinBox value of the zoom
    void zoomOut();
    /// called when the reset zoom button is pressed, sets the spinBox value of the zoom
    void resetZoom();

    /// calculates the zoom value to the matrix
    void zoomInOut(int value);
    /// enables the create a new Interactivity arrow
    void addInteractivity();
    /// sets \a value value to view or not the diamond
    void hideInteractivity(bool value);
    /// enables or disables delete a line
    void deleteLine();
    /// sets position of \a verticalScrollBar whit \a cant
    void changeVerticalBar(int cant);
    /// sets position of \a verticalScrollBar whit \a cant
    void changeVerticalBar2(int cant);    
    /// called to remove Images between \a fromLineNumber and \a toLineNumber and sets unused icon to media
    void removeLineBetweenSlot(int fromLineNumber,int toLineNumber);
    /// called to assign actions to \a button
    void showWindowsSlot(Image *button,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList,QTableWidget* setTable);
    /// called to assign properties to \a imageMedia  when a media is selected in DiagramSceneHead
    void showWindowPropertiesMediaSlot(QString windowTitle,Image* imageMedia);
    /// shows the properties of an Image
    void showEventsButtonSlot(QPointF posWindow,QStringList playList,QStringList stopList,QStringList pauseList,QStringList resumeList,QStringList abortList,QStringList setList);
    /// close the windows the properties of an Image
    void closeEventsButtonSlot();

   /* void showMediasRegion(QPointF point, QList<Media*> medias);
    void closeMediasRegion();*/

    /// called to show the navigation GUI. Set focus property of medias
    void navigation();

    /// called to remove a media in the medias usados table (\a QTableWidget \a *usedMediasList).
    void removeMediasUsados();
    /// called to remove a media in the medias region table (\a QTableWidget \a *mediasRegionList)..
    void removeMediasRegion();
    /// called to remove a media in some import list with name \a name in list of type \a type.
    void removeMedia(QString media, QString type);
    /// called when a media is removed, then removes focus index of media \a media in another descriptors
    void removeIndexMedia(QString media);
    /// called when the \a actionPALN is toggled to show or hide (\a visible value) the grid Pal-N
    void setVisiblePALN(bool visible);
    /// called when the \a actionPALAncho is toggled to show or hide (\a visible value) the grid Pal-Weigth
    void setVisiblePALAncho(bool visible);
    /// called when the \a actionHDTVp is toggled to show or hide (\a visible value) the grid HDTV
    void setVisibleHDTVp(bool visible);
    /// called when the \a actionHDTVp is toggled to show or hide (\a visible value) the grid HDTV HD
    void setVisibleHDTVi(bool visible);
    /// called when the \a actionHDTVp is toggled to show or hide (\a visible value) the grid specific
    void setVisibleOther(bool visible);

    /// called when the Name value of a Region is changed. Set de name value in GrapchisRecItem
    void setNameValue(QTableWidgetItem* item);
    /// called when the left (x) value of a Region is changed. Set de x value in GrapchisRecItem
    void setXValue(int x);
    /// called when the top (y) value of a Region is changed. Set de y value in GrapchisRecItem
    void setYValue(int y);
    /// called when the height value of a Region is changed. Set de height value in GrapchisRecItem
    void setHValue(int h);
    /// called when the width value of a Region is changed. Set de width value in GrapchisRecItem
    void setWValue(int w);
    /// called when the zIndex value of a Region is changed. Set de zIndex value in GrapchisRecItem
    void setZValue(int z);

    /// called when the type of value of the x value is changed to percet or pixel.
    void setXValueCombo();
    /// called when the type of value of the y value is changed to percet or pixel.
    void setYValueCombo();
    /// called when the type of value of the height value is changed to percet or pixel.
    void setHValueCombo();
    /// called when the type of value of the width value is changed to percet or pixel.
    void setWValueCombo();

    /// called to adapt a region to the PALN screen when have this percent values
    void setSizeScreenPALN();
    /// called to adapt a region to the PALA screen when have this percent values
    void setSizeScreenPALAncho();
    /// called to adapt a region to the HDTVp  screen when this have percent values
    void setSizeScreenHDTV720p();
    /// called to adapt a region to the HDTVi screen when this have percent values
    void setSizeScreenHDTV1080i();
    /// called to adapt a region to the NEW screen when this have percent values
    void setSizeScreenOther();

    /// called to show a GUI to modify a new screen size
    void setSizeOther();
    /// called to run the project on ginga
    void runNcl();
    /// called if an error is ocurred when ginga is ran
    void gingaError(QProcess::ProcessError error);
    /// called to remove a media selected in some import list.
    void removeMedia();
    /// called to show a GUI to edit the project description
    void editProjectDescription();


    void setDataNcl();
    /// called to select a button to the interactivity.
    void setButton(Image *button);

    /// called to set true the drop item in all rectangles
    void setFlaseAllOkItemDrop();
    /// called to set false the drop item in all rectangles
    void setTrueAllOkItemDrop();

    /// called to choose a new path to a media to return this
    QString fileNotFound(QString name, QString src,QString type,QString duration);


protected:
    /// reimplemented method of QMainWindow to verify if you want to save changes
    void closeEvent(QCloseEvent * event);;

};

#endif // MAINWINDOW_H
