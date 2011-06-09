/*!
*\file NCL/port.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a port entity.
*/

#ifndef PORT_H
#define PORT_H

#include <QString>

/*!
* \class Port
* \brief class to create a port entity.
*/

class Port
{
private:
    QString port;
    QString id;
    QString component;
    QString interface;

public:
    Port(QString id, QString component);
    Port(QString id, QString component, QString interface);
    void setInterface(QString interface);
    QString getPort();
};

#endif // PORT_H
