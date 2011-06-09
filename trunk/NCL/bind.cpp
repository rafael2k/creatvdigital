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

