/*!
*\file NCL/bindrule.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a bindRule entity.
*/

#ifndef BINDRULE_H
#define BINDRULE_H

#include <QString>

/*!
* \class BindRule
* \brief class to create a bindRule entity.
*/

class BindRule
{
private:
    QString bindRule;
    QString constituent;
    QString rule;

public:
    BindRule(QString constituent, QString rule);
    QString getBindRule();
};

#endif // BINDRULE_H
