/*!
*\file NCL/defaultdescriptor.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a defaultDescriptor entity.
*/

#ifndef DEFAULTDESCRIPTOR_H
#define DEFAULTDESCRIPTOR_H

#include <QString>

/*!
* \class DefaultDescriptor
* \brief class to create a defaultDescriptor entity.
*/

class DefaultDescriptor
{
private:
    QString defaultDescriptor;
    QString descriptor;

public:
    DefaultDescriptor(QString descriptor);
    QString getDefaultDescriptor();
};

#endif // DEFAULTDESCRIPTOR_H
