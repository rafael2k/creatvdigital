/*!
*\file NCL/assessmentstatement.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create an assessmentStatement entity.
*/

#ifndef ASSESSMENTSTATEMENT_H
#define ASSESSMENTSTATEMENT_H

#include <QString>
#include "attributeassessment.h"
#include "valueassessment.h"

/*!
* \class AssessmentStatement
* \brief class to create an assessmentStatement entity.
*/

class AssessmentStatement
{
private:
    QString assessmentStatement;
    QString comparator;
    QString attributeAssessment1;
    QString attributeAssessment2;
    QString valueAssessment;

public:
    AssessmentStatement(QString comparator, AttributeAssessment attributeAssessment1, AttributeAssessment attributeAssessment2);
    AssessmentStatement(QString comparator, AttributeAssessment attributeAssessment, ValueAssessment valueAssessment);
    QString getAssessmentStatement();
};

#endif // ASSESSMENTSTATEMENT_H
