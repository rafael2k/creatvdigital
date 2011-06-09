/*!
*\file NCL/bindrule.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an bindRule entity.
*/

#include "bindrule.h"

BindRule::BindRule(QString constituentParam, QString ruleParam)
{
    constituent = constituentParam;
    rule = ruleParam;
}

QString BindRule::getBindRule()
{
    bindRule = "\t\t\t\t<bindRule constituent=\""+constituent+"\" rule=\""+rule+"\"/>";
    return bindRule;
}
