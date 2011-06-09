/*!
*\file NCL/media.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a media entity.
*/


#ifndef MEDIA_H
#define MEDIA_H

#include "area.h"
#include "property.h"

/*!
* \class Media
* \brief class to create a media entity.
*/

class Media
{
private:
    QString media;
    QString id;
    QString src;
    QString refer;
    QString instance;
    QString type;
    QString descriptor;
    QString property;
    QString area;
    QString originalDuration;

public:
    Media(QString id, QString originalDuration);
    Media(QString id, QString originalDuration, Property property);
    Media(QString id, QString originalDuration, Area area);
    void setId(QString id);
    void setSrc(QString src);
    void setRefer(QString refer);
    void setInstance(QString instance);
    void setType(QString type);
    void setDescriptor(QString descriptor);
    void addProperty(Property *property);
    void addArea(Area *area);
    QString getProperty();
    QString getSrc();
    QString getId();
    QString getMedia();
    QString getType();
    QString getDescriptor();
    QString getOriginalDuration();
    void clearAreas();
    void clearProperty();
};

#endif // MEDIA_H

