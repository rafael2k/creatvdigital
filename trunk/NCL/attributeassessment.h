/*!
*\file NCL/attributeassessment.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create an attributeAssessment entity.
*/

#ifndef ATTRIBUTEASSESSMENT_H
#define ATTRIBUTEASSESSMENT_H

#include <QString>

/*!
* \class AttributeAssessment
* \brief class to create an attributeAssessment entity.
*/

class AttributeAssessment
{
private:
    QString attributeAssessment;
    QString role;
    QString eventType;
    QString key;
    QString attributeType;
    QString offset;

public:
    AttributeAssessment(QString role, QString eventType);
    void setKey(QString key);
    void setAttributeType(QString attributeType);
    void setOffset(QString offset);
    QString getAttributeAssessment();
};

#endif // ATTIBUTEASSESSMENT_H
