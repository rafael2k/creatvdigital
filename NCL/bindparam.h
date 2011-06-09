/*!
*\file NCL/bindparam.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a bindParam entity.
*/

#ifndef BINDPARAM_H
#define BINDPARAM_H

#include <QString>


/*!
* \class BindParam
* \brief class to create a bindParam entity.
*/

class BindParam
{
private:
    QString bindParam;
    QString name;
    QString value;

public:
    BindParam(QString name, QString value);
    QString getBindParam();
};

#endif // BINDPARAM_H
