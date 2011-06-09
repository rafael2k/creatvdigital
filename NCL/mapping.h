/*!
*\file NCL/mapping.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a mapping entity.
*/


#ifndef MAPPING_H
#define MAPPING_H

#include <QString>

/*!
* \class Mapping
* \brief class to create a mapping entity.
*/

class Mapping
{
private:
    QString mapping;
    QString component;
    QString interface;

public:
    Mapping(QString component);
    Mapping(QString component, QString interface);
    void setInterface(QString interface);
    QString getMapping();
};

#endif // MAPPING_H
