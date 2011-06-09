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


