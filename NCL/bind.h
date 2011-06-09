/*!
*\file NCL/bind.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a bind entity.
*/

#ifndef BIND_H
#define BIND_H

#include "bindparam.h"


/*!
* \class Bind
* \brief class to create a bind entity.
*/

class Bind
{
private:
    QString bind;
    QString role;
    QString component;
    QString interface;
    QString descriptor;
    QString bindParam;

public:
    Bind(QString role, QString component);
    Bind(QString role, QString component, BindParam *bindParam);
    void setInterface(QString interface);
    void setDescriptor(QString descriptor);
    void addBindParam(BindParam bindParam);
    QString getBind();

};

#endif // BIND_H
