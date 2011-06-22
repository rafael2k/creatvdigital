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
*\file NCL/assessmentstatement.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an assessmentStatement entity.
*/

#include "assessmentstatement.h"

AssessmentStatement::AssessmentStatement(QString comparatorParam, AttributeAssessment attributeAssessment1Param, AttributeAssessment attributeAssessment2Param)
{
    attributeAssessment1 = attributeAssessment1Param.getAttributeAssessment();
    attributeAssessment2 = attributeAssessment2Param.getAttributeAssessment();
    valueAssessment = "";
    comparator = comparatorParam;
}

AssessmentStatement::AssessmentStatement(QString comparatorParam, AttributeAssessment attributeAssessmentParam, ValueAssessment valueAssessmentParam)
{
    attributeAssessment1 = attributeAssessmentParam.getAttributeAssessment();
    attributeAssessment2 = "";
    valueAssessment = valueAssessmentParam.getValueAssessment();
    comparator = comparatorParam;
}

QString AssessmentStatement::getAssessmentStatement()
{
    assessmentStatement = "\t\t\t\t\t<assessmentStatement coparator=\""+comparator+">\n";
    assessmentStatement.append(attributeAssessment1);
    assessmentStatement.append(attributeAssessment2);
    assessmentStatement.append(valueAssessment);
    assessmentStatement.append("\t\t\t\t\t</assessmentStatement>\n");
    return assessmentStatement;
}


