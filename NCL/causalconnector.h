/*!
*\file NCL/causalconnector.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a causalConnector entity.
*/

#ifndef CAUSALCONNECTOR_H
#define CAUSALCONNECTOR_H

#include "connectorparam.h"
#include "compoundcondition.h"
#include "compoundaction.h"

/*!
* \class CausalConnector
* \brief class to create a causalConnector entity.
*/

class CausalConnector
{
private:
    QString causalConnector;
    QString id;
    QString connectorParam;
    QString simpleCondition;
    QString compoundCondition;
    QString simpleAction;
    QString compoundAction;

public:
    CausalConnector(QString id, SimpleCondition simpleCondition, SimpleAction simpleAction);
    CausalConnector(QString id, SimpleCondition simpleCondition, CompoundAction compoundAction);

    CausalConnector(QString id, CompoundCondition compoundCondition, SimpleAction simpleAction);
    CausalConnector(QString id, CompoundCondition compoundCondition, CompoundAction compoundAction);

    void addConnectorParam(ConnectorParam connectorParam);

    QString getCausalConector();
};

#endif // CAUSALCONNECTOR_H
