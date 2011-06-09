/*!
*\file saveproject.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to save and open projects.
*/

#ifndef SAVEPROJECT_H
#define SAVEPROJECT_H

#include <QString>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDate>
#include <QListWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDir>
#include <QStringList>
#include "NCL/media.h"
#include "NCL/descriptor.h"
#include "QGraphicsItem"
#include "graphicsrectitem.h"
#include "graphicsscene.h"
#include "image.h"
#include "diagramscene.h"
#include "diagramscenehead.h"


/*!
 * \class SaveProject
 * \brief class to save and open projects.
 */
class SaveProject: public QObject
{
    Q_OBJECT

public:
    /// assigns the name of project to the file
    SaveProject(QString myFileName);
    QXmlStreamWriter xmlWriter;
    QXmlStreamReader xmlReader;
    QFile file;
    /// saves the format of the screen chosen
    void saveScreenFormat(QString format,QString width,QString height);
    /// saves the datas about the project(like date,description,etc)
    void saveProjectDescription(QString projectName,QDate date,QString description,int regionNumber);
    /// saves the list of medias imported
    void saveImports(QTableWidget *videoList,QTableWidget *audioList,QListWidget *imageList,QListWidget *textList,QListWidget *luaList,QListWidget *uriList,QList<QDir*> importVideoList,QList<QDir*> importAudioList,QList<QDir*> importImageList,QList<QDir*> importTextList,QList<QDir*> importLuaList,QStringList importUriList);
    /// saves all medias assigned to a rectangle
    void saveMedias(QList<Media*> mediaVideoList,QList<Media*> mediaAudioList,QList<Media*> mediaImageList,QList<Media*> mediaTextList,QList<Media*> mediaLuaList,QList<Media*> mediaUriList,QTableWidget *mediasUsadosList);
    /// saves all rectangles
    void saveRectangles(QList<QGraphicsItem*> regions);
    /// saves all arrows(and images) and their relations
    void saveTimeLines(DiagramScene *graphicsSceneTemporal,DiagramSceneHead *graphicsSceneHead);
    /// saves the properties of media
    void saveDescriptorsParam(DiagramSceneHead *graphicsSceneHead);
    /// saves the \b descriptor and his attributes
    void saveDescriptiors(QList<Descriptor*> &descriptorList);
    /// writes the final of the document and close the file
    void endSaveFile();

    /// open the file to reading
    void openFile();
    /// opens the \b descriptor with his attributes to assign to a \a descriptorList
    void openDescriptiors(QList<Descriptor*> &descriptorList);
    /// recuperates the datas about the project(like date,description,etc)
    void openDescriptionProject(QString &projectName, QString &projectDescriptio, QDate &projectDate, int &regionNumber);

    /// recuperates the format of the screen chosen
    void openScreenFormat(QString &format,int &width,int &height);
    /// recuperates the list of the imported medias
    void openImports(QTableWidget &videoList, QList<QDir*> &importVideoList,QTableWidget &audioList, QList<QDir*> &importAudioList, QListWidget &imageList, QList<QDir*> &importImageList,QListWidget &textList, QList<QDir*> &importTextList ,QListWidget &luaList,QList<QDir*> &importLuaList, QListWidget &uriList,QStringList &importUriList);
    /// recuperates the medias assigned to a rectangle
    void openMedias(QList<Media*> &mediaVideoList,QList<Media*> &mediaAudioList,QList<Media*> &mediaImageList,QList<Media*> &mediaTextList,QList<Media*> &mediaLuaList,QList<Media*> &mediaUriList,QTableWidget &mediasUsadosList);
    /// recuperates all rectangles
    void openRectangles(GraphicsScene &regions, int screenSizeX,int screenSizeY);
    /// recuperates the arrows(and images) and builds the timeLine view
    void openTimeLines(DiagramScene *graphicsSceneTemporal , QTableWidget *mediasUsadosList);
    /// recuperates the properties of media
    void openDescriptorsParam(DiagramSceneHead *graphicsSceneHead);

private:
    QStringList srcList;
    /// returns the image of media \a nameMedia
    QImage getImage(QTableWidget * mediasUsadosList,QString nameMedia);
    /// saves the \b ncl properties of each image
    void saveButtonProperties(DiagramScene *graphicsSceneTemporal);
    /// recuperates the \b ncl properties of each image and sets
    void openButtonProperties(DiagramScene *graphicsSceneTemporal);
    /// adds images like properties to another images(butons)
    void addImage(Image* boton , QStringList playList,QStringList stopList,QStringList pauseList , QStringList resumeList, QStringList abortList,QStringList setList,DiagramScene *graphicsSceneTemporal);
    /// sets the type of the image and location of images added with \a addImage
    void imageLocation(QString path, Image *boton,qreal posX, qreal posY,qreal zvalue,DiagramScene *graphicsSceneTemporal);

    /// gets the new file path of the previos path \a src
    QString getNewSrc(QString src);
    /// verifys if file path \a srs is present in the file systems. If is not present emit a signal \a fileNotFound to chose a new path
    QString getSrc(QString src, QString name, QString type, QString &correctSrc, QString duration);

signals:
    /// this signal is emitted when a path \a src is not found in file system
    QString fileNotFound(QString name, QString src, QString type, QString duration);


};

#endif // SAVEPROJECT_H
