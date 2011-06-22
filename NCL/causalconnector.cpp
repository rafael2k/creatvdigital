/***************************************************************************
 *   CreaTV Digital - Herramienta para la creación de aplicaciones NCL para
 *   el middleware GINGA de Televisión Digital Terrestre
 *
 *  Copyright © 2010, 2011
 *        -Cardozo, Sergio A. (yojajo@gmail.com)
 *        -Schwartz, Sebastian M. (seba.schwartz.7@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

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


