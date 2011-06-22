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
