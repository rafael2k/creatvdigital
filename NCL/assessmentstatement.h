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
