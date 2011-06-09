/*!
*\file NCL/descriptorparam.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a descriptorParam entity.
*/

#ifndef DESCRIPTORPARAM_H
#define DESCRIPTORPARAM_H

#include <QString>

/*!
* \class DescriptorParam
* \brief class to create a descriptorParam entity.
*/

class DescriptorParam
{
private:
    QString descriptorParam;
    QString name;
    QString value;

public:
    DescriptorParam(QString name, QString value);
    QString getDescriptorParam();
    QString getName();
    QString getValue();
};

#endif // DESCRIPTORPARAM_H
