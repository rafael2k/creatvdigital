/*!
*\file NCL/compoundcondition.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a compoundCondition entity.
*/

#ifndef COMPOUNDCONDITION_H
#define COMPOUNDCONDITION_H

#include "simplecondition.h"
#include "compoundstatement.h"

/*!
* \class CompoundCondition
* \brief class to create a compoundCondition entity.
*/

class CompoundCondition
{
private:
    QString compoundCondition;
    QString operatorC;
    QString delay;
    QString simpleCondition;
    QString subCompoundCondition;
    QString assessmentStatement;
    QString compoundStatement;

public:
    CompoundCondition(QString operatorC, SimpleCondition simpleCondition);
    CompoundCondition(QString operatorC, CompoundCondition compoundCondition);

    CompoundCondition(QString operatorC, SimpleCondition simpleCondition, AssessmentStatement assessmentStatement);
    CompoundCondition(QString operatorC, SimpleCondition simpleCondition, CompoundStatement compoundStatement);

    CompoundCondition(QString operatorC, CompoundCondition compoundCondition, AssessmentStatement assessmentStatement);
    CompoundCondition(QString operatorC, CompoundCondition compoundCondition, CompoundStatement compoundStatement);

    void addSimpleCondition(SimpleCondition simpleCondition);
    void addCompoundCondition(CompoundCondition compoundCondition);
    void addAssessmentStatement(AssessmentStatement assessmentStatement);
    void addCompoundStatement(CompoundStatement compoundStatement);
    void setDelay(QString delay);
    QString getCompoundCondition();
};

#endif // COMPOUNDCONDITION_H
