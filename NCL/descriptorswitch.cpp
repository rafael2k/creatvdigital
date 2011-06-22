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
*\file NCL/descriptorswitch.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an descriptorSwitch entity.
*/

#include "descriptorswitch.h"

DescriptorSwitch::DescriptorSwitch(QString idParam, DefaultDescriptor defaultDescriptorParam)
{
    id = idParam;
    defaultDescriptor = defaultDescriptorParam.getDefaultDescriptor();
    bindRule = "";
    descriptor = "";
}

DescriptorSwitch::DescriptorSwitch(QString idParam, BindRule bindRuleParam)
{
    id = idParam;
    defaultDescriptor = "";
    bindRule = bindRuleParam.getBindRule();
    descriptor = "";
}

DescriptorSwitch::DescriptorSwitch(QString idParam, Descriptor descriptorParam)
{
    id = idParam;
    defaultDescriptor = "";
    bindRule = "";
    descriptor = descriptorParam.getDescriptor();
}

void DescriptorSwitch::setDefaultDescriptor(DefaultDescriptor defaultDescriptorParam)
{
    defaultDescriptor = defaultDescriptorParam.getDefaultDescriptor();
}


void DescriptorSwitch::addDescriptor(Descriptor descriptorParam)
{
    descriptor.append(descriptorParam.getDescriptor());
}

void DescriptorSwitch::addBindRule(BindRule bindRuleParam)
{
    bindRule.append(bindRuleParam.getBindRule());
}

QString DescriptorSwitch::getDescriptorSwitch()
{
    descriptorSwitch = "\t\t\t<descriptorSwitch id=\""+id+">\n";
    descriptorSwitch.append(defaultDescriptor);
    descriptorSwitch.append(bindRule);
    descriptorSwitch.append(descriptor);
    descriptorSwitch.append("\t\t\t<descriptorSwitch />\n");
    return descriptorSwitch;
}
