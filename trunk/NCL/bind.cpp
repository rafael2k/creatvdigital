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
*\file NCL/bind.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an bind entity.
*/

#include "bind.h"

#include <iostream>

using namespace std;

Bind::Bind(QString roleParam, QString componentParam)
{
    role = roleParam;
    component = componentParam;
    interface = "";
    descriptor = "";
    bindParam = "";
}

Bind::Bind(QString roleParam, QString componentParam, BindParam *bindParamParam)
{
    role = roleParam;
    component = componentParam;
    interface = "";
    descriptor = "";
    bindParam = bindParamParam->getBindParam();
}

QString Bind::getBind()
{
    bind = "\t\t\t<bind role=\""+role+"\" component=\""+component+"\""+interface+">\n";
    bind.append(bindParam);
    bind.append("\t\t\t</bind>\n");
    return bind;
}

void Bind::setInterface(QString interfaceParam)
{
    interface = " interface=\""+interfaceParam+"\"";
}

void Bind::setDescriptor(QString descriptorParam)
{
    descriptor = " descriptor=\""+descriptorParam+"\"";
}

void Bind::addBindParam(BindParam bindParamParam)
{
    bindParam.append("\t"+bindParamParam.getBindParam());
}

