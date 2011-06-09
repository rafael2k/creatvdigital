/*!
*\file NCL/attributeassessment.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an attributeAssessment entity.
*/

#include "attributeassessment.h"

AttributeAssessment::AttributeAssessment(QString roleParam, QString eventTypeParam)
{
    role = roleParam;
    eventType = eventTypeParam;
    key = "";
    attributeType = "";
    offset = "";
}

QString AttributeAssessment::getAttributeAssessment()
{
    attributeAssessment = "\t\t\t\t\t\t<attributeAssessment role=\""+role+"\" eventType=\""+eventType+"\""+attributeType+offset+"/>\n";
    return attributeAssessment;
}

void AttributeAssessment::setKey(QString keyParam)
{
    key = " keyParam=\""+keyParam+"\"";
}

void AttributeAssessment::setAttributeType(QString attributeTyperParam)
{
    attributeType = " attributeType=\""+attributeTyperParam+"\"";
}

void AttributeAssessment::setOffset(QString offsetParam)
{
    offset = " offset=\""+offsetParam+"\"";
}
