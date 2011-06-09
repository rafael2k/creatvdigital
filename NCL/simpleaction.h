/*!
*\file NCL/simpleaction.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a simpleAction entity.
*/

#ifndef SIMPLEACTION_H
#define SIMPLEACTION_H

#include <QString>

/*!
* \class SimpleAction
* \brief class to create a simpleAction entity.
*/

class SimpleAction
{
private:
    QString simpleAction;
    QString role;
    QString delay;
    QString eventType;
    QString value;
    QString min;
    QString max;
    QString qualifier;
    QString repeat;
    QString repeatDelay;

public:
    SimpleAction(QString role);
    QString getSimpleAction();
    void setDelay(QString delay);
    void setEventType(QString eventType);
    void setValue(QString value);
    void setMin(QString min);
    void setMax(QString max);
    void setQualifier(QString qualifier);
    void setRepeat(QString repeat);
    void setRepeatDelay(QString repeatDelay);
};

#endif // SIMPLEACTION_H
