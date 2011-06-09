/*!
*\file NCL/simplecondition.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a simpleCondition entity.
*/

#ifndef SIMPLECONDITION_H
#define SIMPLECONDITION_H

#include <QString>

/*!
* \class SimpleCondition
* \brief class to create a simpleCondition entity.
*/

class SimpleCondition
{
private:
    QString simpleCondition;
    QString role;
    QString delay;
    QString eventType;
    QString key;
    QString transition;
    QString min;
    QString max;
    QString qualifier;

public:
    SimpleCondition(QString role);
    QString getSimpleCondition();
    void setDelay(QString delay);
    void setEventType(QString eventType);
    void setKey(QString key);
    void setTransition(QString transition);
    void setMin(QString min);
    void setMax(QString max);
    void setQualifier(QString qualifier);
};

#endif // SIMPLECONDITION_H
