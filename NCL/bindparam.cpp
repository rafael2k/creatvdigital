/*!
*\file NCL/bindparam.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an bindParam entity.
*/

#include "bindparam.h"

BindParam::BindParam(QString nameParam, QString valueParam)
{
    name = nameParam;
    value = valueParam;
}

QString BindParam::getBindParam()
{
    bindParam = "\t\t\t\t<bindParam name=\""+name+"\" value=\""+value+"\"/>\n";
    return bindParam;
}
