/*!
*\file NCL/connectorparam.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a connectorParam entity.
*/

#ifndef CONNECTORPARAM_H
#define CONNECTORPARAM_H

#include <QString>

/*!
* \class ConnectorParam
* \brief class to create a connectorParam entity.
*/

class ConnectorParam
{
private:
    QString connectorParam;
    QString name;
    QString type;

public:
    ConnectorParam(QString name);
    ConnectorParam(QString name, QString type);
    void setType(QString type);
    QString getConnectorParam();
};

#endif // CONNECTORPARAM_H
