/*!
*\file NCL/defaultdescriptor.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an defaultDescriptor entity.
*/

#include "defaultdescriptor.h"

DefaultDescriptor::DefaultDescriptor(QString descriptorParam)
{
    descriptor = descriptorParam;
}

QString DefaultDescriptor::getDefaultDescriptor()
{
    defaultDescriptor = "\t\t\t\t<defaultDescriptor descriptor=\""+descriptor+"\"/>\n";
    return defaultDescriptor;
}
