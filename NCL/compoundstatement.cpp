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
*\file NCL/compoundstatement.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an compoundStatement entity.
*/

#include "compoundstatement.h"

CompoundStatement::CompoundStatement(QString operatorCParam, AssessmentStatement assessmentStatementParam)
{
    operatorC = operatorCParam;
    assessmentStatement = assessmentStatementParam.getAssessmentStatement();
    subCompundSatement = "";
    isNegated = "";
}

CompoundStatement::CompoundStatement(QString operatorCParam, CompoundStatement compoundStatementtParam)
{
    operatorC = operatorCParam;
    assessmentStatement = "";
    subCompundSatement = compoundStatementtParam.getCompoundStatement();
    isNegated = "";
}

QString CompoundStatement::getCompoundStatement()
{
    compoundStatement = "\t\t\t\t\t<compundSatement operator=\""+operatorC+"\""+isNegated+">\n";
    compoundStatement.append(assessmentStatement);
    compoundStatement.append(subCompundSatement);
    compoundStatement.append("\t\t\t\t\t</compundSatement>\n");
    return compoundStatement;
}

void CompoundStatement::addAssessmentStatement(AssessmentStatement assessmentStatementParam)
{
    assessmentStatement.append(assessmentStatementParam.getAssessmentStatement());
}

void CompoundStatement::addCompoundStatement(CompoundStatement compoundStatementParam)
{
    subCompundSatement.append("\t"+compoundStatementParam.getCompoundStatement());
}


void CompoundStatement::setIsNegated(QString isNegatedParam)
{
    isNegated = isNegatedParam;
}

