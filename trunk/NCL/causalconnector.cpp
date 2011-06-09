/*!
*\file NCL/causalconnector.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an causalConnector entity.
*/

#include "causalconnector.h"

CausalConnector::CausalConnector(QString idParam, SimpleCondition simpleConditionParam, SimpleAction simpleActionParam)
{
    id = idParam;
    simpleCondition = simpleConditionParam.getSimpleCondition();
    simpleAction = simpleActionParam.getSimpleAction();
    compoundCondition = "";
    compoundAction = "";
}


CausalConnector::CausalConnector(QString idParam, SimpleCondition simpleConditionParam, CompoundAction compoundActionParam)
{
    id = idParam;
    simpleCondition = simpleConditionParam.getSimpleCondition();
    simpleAction = "";
    compoundCondition = "";
    compoundAction = compoundActionParam.getCompoundAction();
}

CausalConnector::CausalConnector(QString idParam, CompoundCondition compoundConditionParam, SimpleAction simpleActionParam)
{
    id = idParam;
    simpleCondition = "";
    simpleAction = simpleActionParam.getSimpleAction();
    compoundCondition = compoundConditionParam.getCompoundCondition();
    compoundAction = "";
}

CausalConnector::CausalConnector(QString idParam, CompoundCondition compoundConditionParam, CompoundAction compoundActionParam)
{
    id = idParam;
    simpleCondition = "";
    simpleAction = "";
    compoundCondition = compoundConditionParam.getCompoundCondition();
    compoundAction = compoundActionParam.getCompoundAction();
}

QString CausalConnector::getCausalConector()
{
    causalConnector = "\t\t\t<causalConnector id=\""+id+">\n";
    causalConnector.append(connectorParam);
    causalConnector.append(simpleCondition);
    causalConnector.append(compoundCondition);
    causalConnector.append(simpleAction);
    causalConnector.append(compoundAction);
    causalConnector.append("\t\t\t</causalConnector>\n");
    return causalConnector;
}

void CausalConnector::addConnectorParam(ConnectorParam connectorParamParam)
{
    connectorParam.append(connectorParamParam.getConnectorParam());
}


