/*!
*\file NCL/valueassessment.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a valueAssessment entity.
*/

#ifndef VALUEASSESSMENT_H
#define VALUEASSESSMENT_H

#include <QString>

/*!
* \class ValueAssessment
* \brief class to create a valueAssessment entity.
*/

class ValueAssessment
{
private:
    QString valueAssessment;
    QString value;

public:
    ValueAssessment(QString value);
    QString getValueAssessment();
};

#endif // VALUEASSESSMENT_H
