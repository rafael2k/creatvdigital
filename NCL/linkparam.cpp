/*!
*\file NCL/linkparam.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an linkParam entity.
*/

#include "linkparam.h"

LinkParam::LinkParam(QString nameParam, QString valueParam)
{
    name = nameParam;
    value = valueParam;
}

QString LinkParam::getLinkParam()
{
    linkParam = "\t\t\t<linkParam name=\""+name+" value=\""+value+"/>\n";
    return linkParam;
}
