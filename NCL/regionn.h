/*!
*\file NCL/regionn.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a region entity.
*/

#ifndef REGION_H
#define REGION_H

#include <QString>
#include <QList>

/*!
* \class Regionn
* \brief class to create a region entity.
*/

class Regionn
{

private:
    QString region;
    QString id;
    QString title;
    QString left;
    QString right;
    QString top;
    QString bottom;
    QString height;
    QString width;
    QString zIndex;
    QString subRegion;
    QList<Regionn*> subRegiones;



public:
    Regionn(QString idRegion);
    QString getRegion();
    void addRegion(Regionn *region);
    void setId(QString id);
    void setTitle(QString title);
    void setLeft(QString left);
    void setRight(QString right);
    void setTop(QString top);
    void setBottom(QString bottom);
    void setHeight(QString height);
    void setWidth(QString width);
    void setZIndex(QString zIndex);
    QString getSubRegiones(QList<Regionn*> lista, QString tabs);
    QList<Regionn*> getList();
    QString getId();

    QString getTitle();
    QString getLeft();
    QString getRight();
    QString getTop();
    QString getBottom();
    QString getHeight();
    QString getWidth();
    QString getZIndex();


};

#endif // REGION_H
