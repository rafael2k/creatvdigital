/*!
*\file NCL/ncl.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a ncl entity.
*/

#ifndef NCL_H
#define NCL_H
#include <QString>
#include "head.h"
#include "body.h"

/*!
* \class Ncl
* \brief class to create a ncl entity.
*/

class Ncl
{
private:
    QString ncl;
    QString id;
    QString title;
    QString xmlns;
    QString head;
    QString body;
    QString versionEncodig;

public:
    Ncl(Head head, Body body);
    ~Ncl();
    QString getNCL();
    QString getId();
    QString getTitle();
    QString getXmls();
    void setId(QString id);
    void setTitle(QString title);
    void setXmlns(QString xmls);
    void setVersionEncoding(QString version, QString encoding);
};
#endif // NCL_H
