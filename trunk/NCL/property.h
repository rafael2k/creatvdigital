/*!
*\file NCL/property.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a property entity.
*/

#ifndef PROPERTY_H
#define PROPERTY_H

#include <QString>

/*!
* \class Property
* \brief class to create a property entity.
*/

class Property
{
private:
    QString property;
    QString name;
    QString value;

public:
    Property(QString name);
    Property(QString name, QString value);
    void setValue(QString value);
    QString getProperty();
};

#endif // PROPERTY_H
