/*!
*\file NCL/rulebase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an ruleBase entity.
*/

#include "rulebase.h"

#include <QString>

RuleBase::RuleBase(ImportBase importBaseParam)
{
    id = "";
    importBase = importBaseParam.getImportBase();
    rule = "";
    compositeRule = "";
}

RuleBase::RuleBase(Rule ruleParam)
{
    id = "";
    importBase = "";
    rule = ruleParam.getRule();
    compositeRule = "";
}

RuleBase::RuleBase(CompositeRule compositeRuleParam)
{
    id = "";
    importBase = "";
    rule = "";
    compositeRule = compositeRuleParam.getCompositeRule();
}

RuleBase::RuleBase(QString idParam, ImportBase importBaseParam)
{
    id = "id=\""+idParam+"\"";
    importBase = importBaseParam.getImportBase();
    rule = "";
    compositeRule = "";
}

RuleBase::RuleBase(QString idParam, Rule ruleParam)
{
    id = "id=\""+idParam+"\"";
    importBase = "";
    rule = ruleParam.getRule();
    compositeRule = "";
}

RuleBase::RuleBase(QString idParam, CompositeRule compositeRuleParam)
{
    id = "id=\""+idParam+"\"";
    importBase = "";
    rule = "";
    compositeRule = compositeRuleParam.getCompositeRule();
}

QString RuleBase::getRuleBase()
{
    ruleBase = "\t\t<ruleBase "+id+ ">\n";
    ruleBase.append(importBase);
    ruleBase.append(rule);
    ruleBase.append(compositeRule);
    ruleBase.append("\t\t<ruleBase/>\n");
    return ruleBase;
}

void RuleBase::addImporBase(ImportBase importBaseParam)
{
    importBase.append("\t\t\t"+importBaseParam.getImportBase()+"\n");
}

void RuleBase::addRule(Rule ruleParam)
{
    rule.append("\t\t\t"+ruleParam.getRule()+"\n");
}

void RuleBase::addCompositeRule(CompositeRule compositeRuleParam)
{
    compositeRule.append("\t\t\t"+compositeRuleParam.getCompositeRule()+"\n");
}


