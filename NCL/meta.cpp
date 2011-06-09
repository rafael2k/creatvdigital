/*!
*\file NCL/meta.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an meta entity.
*/

#include "meta.h"

Meta::Meta(QString nameParam, QString contentParam)
{
    name = nameParam;
    content = contentParam;
}

QString Meta::getMeta()
{
    meta = "\t\t<meta name=\""+name+" content=\""+content+"/>\n";
    return meta;
}
