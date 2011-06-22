/***************************************************************************
 *   CreaTV Digital - Herramienta para la creación de aplicaciones NCL para
 *   el middleware GINGA de Televisión Digital Terrestre
 *
 *  Copyright © 2010, 2011
 *        -Cardozo, Sergio A. (yojajo@gmail.com)
 *        -Schwartz, Sebastian M. (seba.schwartz.7@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

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


