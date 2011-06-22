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
*\file NCL/head.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a head entity.
*/

#ifndef HEAD_H
#define HEAD_H

#include <QString>
#include "importeddocumentbase.h"

/*!
* \class Head
* \brief class to create a head entity.
*/

class Head
{
private:
    QString head;
    QString importedDocumentBase;
    QString ruleBase;
    QString transitionBase;
    QString regionBase;
    QString descriptorBase;
    QString connectorBase;
    QString meta;
    QString metaData;

public:
    Head();
    QString getHead();
    void setImpotedDocumentBase(QString importedDocumentBase);
    void setRuleBase(QString ruleBase);
    void setTransitionBase(QString transitionBase);
    void addRegionBase(QString transitionBase);
    void addDescriptorBase(QString transitionBase);
    void setConnectorBase(QString connectorBase);
    void addMeta(QString meta);
    void addMetaData(QString metaData);
};

#endif // HEAD_H
