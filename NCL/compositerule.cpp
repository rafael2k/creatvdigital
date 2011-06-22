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



