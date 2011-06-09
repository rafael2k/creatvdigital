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

