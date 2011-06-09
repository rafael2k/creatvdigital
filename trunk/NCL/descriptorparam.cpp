/*!
*\file NCL/descriptorparam.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an descriptorParam entity.
*/

#include "descriptorparam.h"

DescriptorParam::DescriptorParam(QString nameParam, QString valueParam)
{
    name = nameParam;
    value = valueParam;
}

QString DescriptorParam::getDescriptorParam()
{
    descriptorParam = "\t\t\t<descriptorParam name=\""+name+"\" value=\""+value+"\"/>\n";
    return descriptorParam;
}

QString DescriptorParam::getName(){
    return name;
}

QString DescriptorParam::getValue(){
    return value;
}
