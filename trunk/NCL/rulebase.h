/*!
*\file NCL/rulebase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a ruleBase entity.
*/

#ifndef RULEBASE_H
#define RULEBASE_H

#include <QString>
#include "importbase.h"
#include "rule.h"
#include "compositerule.h"

/*!
* \class RuleBase
* \brief class to create a ruleBase entity.
*/

class RuleBase
{
private:
    QString ruleBase;
    QString id;
    QString importBase;
    QString rule;
    QString compositeRule;

public:
    RuleBase(ImportBase importBase);
    RuleBase(Rule rule);
    RuleBase(CompositeRule compositeRule);
    RuleBase(QString id, ImportBase importBase);
    RuleBase(QString id, Rule rule);
    RuleBase(QString id, CompositeRule compositeRule);
    void addImporBase(ImportBase importBase);
    void addRule(Rule rule);
    void addCompositeRule(CompositeRule compositeRule);
    QString getRuleBase();
};

#endif // RULEBASE_H
