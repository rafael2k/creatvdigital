/*!
*\file NCL/connectorbase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a connectorBase entity.
*/

#ifndef CONNECTORBASE_H
#define CONNECTORBASE_H

#include "importbase.h"
#include "causalconnector.h"

/*!
* \class ConnectorBase
* \brief class to create a connectorBase entity.
*/

class ConnectorBase
{
private:
    QString connectorBase;
    QString id;
    QString importBase;
    QString causalConnector;


public:
    ConnectorBase();
    ConnectorBase(ImportBase *importBase);
    ConnectorBase(CausalConnector causalConnector);
    void addImporBase(ImportBase importbase);
    void addCausalConnector(CausalConnector causalConnector);
    void setId(QString id);
    QString getConnectorBase();

};

#endif // CONNECTORBASE_H
