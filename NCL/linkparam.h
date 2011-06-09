/*!
*\file NCL/linkparam.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a linkParam entity.
*/

#ifndef LINKPARAM_H
#define LINKPARAM_H

#include <QString>

/*!
* \class LinkParam
* \brief class to create a linkParam entity.
*/

class LinkParam
{
private:
    QString linkParam;
    QString name;
    QString value;

public:
    LinkParam(QString name, QString value);
    QString getLinkParam();
};

#endif // LINKPARAM_H
