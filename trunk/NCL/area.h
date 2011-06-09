/*!
*\file NCL/area.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create an area entity.
*/

#ifndef AREA_H
#define AREA_H

#include <QString>

/*!
* \class Area
* \brief class to create an area entity.
*/

class Area
{

private:
    QString area;
    QString id;
    QString coords;
    QString begin;
    QString end;
    QString text;
    QString position;
    QString first;
    QString last;
    QString label;

public:
    Area(QString id);
    QString getArea();
    void setCoords(QString coords);
    void setBegin(QString begin);
    void setEnd(QString end);
    void setText(QString text);
    void setPosition(QString position);
    void setFirst(QString first);
    void setLast(QString last);
    void setLabel(QString label);
};

#endif // AREA_H
