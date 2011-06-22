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
*\file NCL/descriptorbase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an descriptorBase entity.
*/

#include "descriptorbase.h"

DescriptorBase::DescriptorBase(ImportBase importBaseParam)
{
    id = "";
    importBase = importBaseParam.getImportBase();
    descriptorSwitch = "";
    descriptor = "";
}

DescriptorBase::DescriptorBase(DescriptorSwitch descriptorSwitchParam)
{
    id = "";
    importBase = "";
    descriptorSwitch = descriptorSwitchParam.getDescriptorSwitch();
    descriptor = "";
}

DescriptorBase::DescriptorBase(Descriptor descriptorParam)
{
    id = "";
    importBase = "";
    descriptorSwitch = "";
    descriptor = descriptorParam.getDescriptor();
}

DescriptorBase::DescriptorBase(QString idParam, ImportBase importBaseParam)
{
    id = " id=\""+idParam+"\"";
    importBase = importBaseParam.getImportBase();
    descriptorSwitch = "";
    descriptor = "";
}

DescriptorBase::DescriptorBase(QString idParam, DescriptorSwitch descriptorSwitchParam)
{
    id = " id=\""+idParam+"\"";
    importBase = "";
    descriptorSwitch = descriptorSwitchParam.getDescriptorSwitch();
    descriptor = "";
}

DescriptorBase::DescriptorBase(QString idParam, Descriptor descriptorParam)
{
    id = " id=\""+idParam+"\"";
    importBase = "";
    descriptorSwitch = "";
    descriptor = descriptorParam.getDescriptor();
}

void DescriptorBase::addImportBase(ImportBase importBaseParam)
{
    importBase.append(importBaseParam.getImportBase());
}

void DescriptorBase::addDescriptorSwitch(DescriptorSwitch descriptorSwitchParam)
{
    descriptorSwitch.append(descriptorSwitchParam.getDescriptorSwitch());
}

void DescriptorBase::addDescriptor(Descriptor descriptorParam)
{
    descriptor.append(descriptorParam.getDescriptor());
}

QString DescriptorBase::getDescriptorBase()
{
    descriptorBase = "\t\t<descriptorBase"+id+">\n";
    descriptorBase.append(importBase);
    descriptorBase.append(descriptorSwitch);
    descriptorBase.append(descriptor);
    descriptorBase.append("\t\t</descriptorBase>\n");
    return descriptorBase;
}
