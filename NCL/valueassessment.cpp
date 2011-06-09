/*!
*\file NCL/valueassessment.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an valueAssessment entity.
*/

#include "valueassessment.h"

ValueAssessment::ValueAssessment(QString valueParam)
{
    value = valueParam;
}

QString ValueAssessment::getValueAssessment()
{
    valueAssessment = "\t\t\t\t\t\t<valueAssesment value=\""+value+"\"/>\n";
    return valueAssessment;
}
