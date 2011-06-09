/*!
*\file NCL/compositerule.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a compositeRule entity.
*/

#ifndef COMPOSITERULE_H
#define COMPOSITERULE_H

#include <QString>
#include "rule.h"
#include "compositerule.h"

/*!
* \class CompositeRule
* \brief class to create a compositeRule entity.
*/

class CompositeRule
{
private:
    QString compositeRule;
    QString id;
    QString operatorC;
    QString rule;
    QString subCompositeRule;

public:
    CompositeRule(QString id, QString operatorC, Rule rule);
    CompositeRule(QString id, QString operatorC, CompositeRule compositeRule);
    void addRule(Rule rule);
    void addCompositeRule(CompositeRule compositeRule);
    QString getCompositeRule();
};

#endif // COMPOSITERULE_H
