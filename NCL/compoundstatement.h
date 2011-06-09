/*!
*\file NCL/compoundstatement.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a compoundStatement entity.
*/


#ifndef COMPOUNDSTATEMENT_H
#define COMPOUNDSTATEMENT_H

#include <QString>
#include "assessmentstatement.h"

/*!
* \class CompoundStatement
* \brief class to create a compoundStatement entity.
*/


class CompoundStatement
{
private:
    QString compoundStatement;
    QString operatorC;
    QString isNegated;
    QString assessmentStatement;
    QString subCompundSatement;

public:
    CompoundStatement(QString operatorC,AssessmentStatement assessmentStatement);
    CompoundStatement(QString operatorC, CompoundStatement compoundStatement);
    void addAssessmentStatement(AssessmentStatement assessmentStatement);
    void addCompoundStatement(CompoundStatement compoundStatement);
    void setIsNegated(QString isNegated);
    QString getCompoundStatement();
};

#endif // COMPOUNDSTATEMENT_H
