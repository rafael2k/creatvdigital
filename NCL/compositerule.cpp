/*!
*\file NCL/compositerule.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an compositeRule entity.
*/

#include "compositerule.h"

CompositeRule::CompositeRule(QString idParam, QString operatorCParam, Rule ruleParam)
{
    id = idParam;
    operatorC = operatorCParam;
    rule = ruleParam.getRule();
    subCompositeRule = "";
}

CompositeRule::CompositeRule(QString idParam, QString operatorCParam, CompositeRule compositeRule)
{
    id = idParam;
    operatorC = operatorCParam;
    rule = "";
    subCompositeRule = "\t"+compositeRule.getCompositeRule();
}

QString CompositeRule::getCompositeRule()
{
    compositeRule = "\t\t\t<compositeRule id=\""+id+"\" operator=\""+operatorC+"\" >\n";
    compositeRule.append(rule);
    compositeRule.append("\t\t\t<compositeRule/>\n");
    return compositeRule;
}

void CompositeRule::addRule(Rule ruleParam)
{
    rule.append(ruleParam.getRule());
}

void CompositeRule::addCompositeRule(CompositeRule compositeRuleParam)
{
    subCompositeRule.append(compositeRuleParam.getCompositeRule());
}



