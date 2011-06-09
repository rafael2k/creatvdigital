/*!
*\file NCL/rule.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a regionBase entity.
*/

#ifndef RULE_H
#define RULE_H

#include <QString>

/*!
* \class Rule
* \brief class to create a regionBase entity.
*/

class Rule
{
private:
    QString rule;
    QString id;
    QString var;
    QString comparator;
    QString value;

public:
    Rule(QString id, QString var, QString comparator, QString value);
    QString getRule();
};

#endif // RULE_H
