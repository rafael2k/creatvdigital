/*!
*\file NCL/link.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a link entity.
*/

#ifndef LINK_H
#define LINK_H

#include "linkparam.h"
#include "bind.h"

/*!
* \class Link
* \brief class to create a link entity.
*/

class Link
{
private:
    QString link;
    QString id;
    QString xConnector;
    QString linkParam;
    QString bind;

public:
    Link(QString xConnector, Bind *bind);
    Link(QString xConnector, Bind *bind, LinkParam *linkParam);
    void setId(QString id);
    QString getLink();
    void addBind(Bind *bindParam);
};

#endif // LINK_H
