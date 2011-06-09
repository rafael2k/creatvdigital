/*!
*\file NCL/switchport.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a switchPort entity.
*/


#ifndef SWITCHPORT_H
#define SWITCHPORT_H

#include "mapping.h"

/*!
* \class SwitchPort
* \brief class to create a switchPort entity.
*/

class SwitchPort
{
private:
    QString swicthPort;
    QString id;
    QString mapping;

public:
    SwitchPort(QString id, Mapping mapping);
    QString getSwitchPort();
    void addMapping(Mapping mapping);
};

#endif // SWITCHPORT_H
