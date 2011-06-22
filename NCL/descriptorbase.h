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
*\file NCL/descriptorbase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a descriptorBase entity.
*/

#ifndef DESCRIPTORBASE_H
#define DESCRIPTORBASE_H

#include <QString>
#include "importbase.h"
#include "descriptorswitch.h"
#include "descriptor.h"

/*!
* \class DescriptorBase
* \brief class to create a descriptorBase entity.
*/


class DescriptorBase
{
private:
    QString descriptorBase;
    QString id;
    QString importBase;
    QString descriptorSwitch;
    QString descriptor;

public:
    DescriptorBase(ImportBase importBase);
    DescriptorBase(DescriptorSwitch descriptorSwitch);
    DescriptorBase(Descriptor descriptor);
    DescriptorBase(QString id, ImportBase importBase);
    DescriptorBase(QString id, DescriptorSwitch descriptorSwitch);
    DescriptorBase(QString id, Descriptor descriptor);
    void addImportBase(ImportBase importBase);
    void addDescriptorSwitch(DescriptorSwitch descriptorSwitch);
    void addDescriptor(Descriptor descriptor);
    void addImportBase(QString id, ImportBase importBase);
    void addDescriptorSwitch(QString id, DescriptorSwitch descriptorSwitch);
    void addDescriptor(QString id, Descriptor descriptor);
    QString getDescriptorBase();
};

#endif // DESCRIPTORBASE_H
