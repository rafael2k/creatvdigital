/*!
*\file NCL/regionbase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a regionBase entity.
*/

#ifndef REGIONBASE_H
#define REGIONBASE_H

#include <QString>
#include "regionn.h"

/*!
* \class RegionBase
* \brief class to create a regionBase entity.
*/

class RegionBase
{
private:
    QString regionBase;
    QString id;
    QString device;
    QString region;

public:
    RegionBase(Regionn region);
    RegionBase(QString id, Regionn region);
    QString getRegionBase();
    void addRegion(Regionn region);
    void setDevice(QString device);
};

#endif // REGIONBASE_H
