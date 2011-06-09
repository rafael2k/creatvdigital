/*!
*\file NCL/rule.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an rule entity.
*/


#include "rule.h"

Rule::Rule(QString idParam, QString varParam, QString comparatorParam, QString valueParam)
{
    id = idParam;
    varParam = varParam;
    comparator = comparatorParam;
    value = valueParam;
}

QString Rule::getRule()
{
    rule = "\t\t\t<rule id=\""+id+"\" var=\""+var+"\" value=\""+value+"\" comparator=\""+comparator+"\" />\n";
    return rule;
}
