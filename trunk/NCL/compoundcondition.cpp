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
*\file NCL/compoundcondition.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an compoundCondition entity.
*/

#include "compoundcondition.h"

CompoundCondition::CompoundCondition(QString operatorCParam, SimpleCondition simpleConditionParam)
{
    operatorC = operatorCParam;
    simpleCondition = simpleConditionParam.getSimpleCondition();
    subCompoundCondition = "";
    delay = "";
    assessmentStatement = "";
    compoundStatement = "";
}

CompoundCondition::CompoundCondition(QString operatorCParam, CompoundCondition compoundConditionParam)
{
    operatorC = operatorCParam;
    simpleCondition = "";
    subCompoundCondition = compoundConditionParam.getCompoundCondition();
    delay = "";
    assessmentStatement = "";
    compoundStatement = "";
}


CompoundCondition::CompoundCondition(QString operatorCParam, SimpleCondition simpleConditionParam, AssessmentStatement assessmentStatementParam)
{
    operatorC = operatorCParam;
    simpleCondition = simpleConditionParam.getSimpleCondition();
    subCompoundCondition = "";
    delay = "";
    assessmentStatement = assessmentStatementParam.getAssessmentStatement();
    compoundStatement = "";
}

CompoundCondition::CompoundCondition(QString operatorCParam, SimpleCondition simpleConditionParam, CompoundStatement compoundStatementParam)
{
    operatorC = operatorCParam;
    simpleCondition = simpleConditionParam.getSimpleCondition();
    subCompoundCondition = "";
    delay = "";
    assessmentStatement = "";
    compoundStatement = compoundStatementParam.getCompoundStatement();
}

CompoundCondition::CompoundCondition(QString operatorCParam, CompoundCondition compoundConditionParam, AssessmentStatement assessmentStatementParam)
{
    operatorC = operatorCParam;
    simpleCondition = "";
    subCompoundCondition = compoundConditionParam.getCompoundCondition();
    delay = "";
    assessmentStatement = assessmentStatementParam.getAssessmentStatement();
    compoundStatement = "";
}

CompoundCondition::CompoundCondition(QString operatorCParam, CompoundCondition compoundConditionParam, CompoundStatement compoundStatementParam)
{
    operatorC = operatorCParam;
    simpleCondition = "";
    subCompoundCondition = compoundConditionParam.getCompoundCondition();
    delay = "";
    assessmentStatement = "";
    compoundStatement = compoundStatementParam.getCompoundStatement();
}


QString CompoundCondition::getCompoundCondition()
{
    compoundCondition = "\t\t\t\t\t<compoundSCondition operator=\""+operatorC+"\""+delay+">\n";
    compoundCondition.append(simpleCondition);
    compoundCondition.append(subCompoundCondition);
    compoundCondition.append(assessmentStatement);
    compoundCondition.append(compoundStatement);
    compoundCondition.append("\t\t\t\t\t</compoundSCondition>\n");
    return compoundCondition;
}

void CompoundCondition::addSimpleCondition(SimpleCondition simpleConditionParam)
{
    simpleCondition.append(simpleConditionParam.getSimpleCondition());
}

void CompoundCondition::addCompoundCondition(CompoundCondition compoundConditionParam)
{
    subCompoundCondition.append("\t"+compoundConditionParam.getCompoundCondition());
}

void CompoundCondition::addCompoundStatement(CompoundStatement compoundnStatementParam)
{
    compoundStatement.append("\t"+compoundnStatementParam.getCompoundStatement());
}

void CompoundCondition::addAssessmentStatement(AssessmentStatement assessmentStatementParam)
{
    assessmentStatement.append("\t"+assessmentStatementParam.getAssessmentStatement());
}

void CompoundCondition::setDelay(QString delayParam)
{
    delay = delayParam;
}
