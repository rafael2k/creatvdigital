/*!
*\file NCL/transition.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a transition entity.
*/

#ifndef TRANSITION_H
#define TRANSITION_H

#include <QString>

/*!
* \class Transition
* \brief class to create a transition entity.
*/

class Transition
{
private:
    QString transition;
    QString id;
    QString type;
    QString subType;
    QString dur;
    QString startProgress;
    QString endProgress;
    QString direction;
    QString fadeColor;
    QString horRepeat;
    QString vertRepeat;
    QString borderWidth;
    QString borderColor;

public:
    Transition(QString id, QString type);
    void setSubType(QString subType);
    void setDur(QString dur);
    void setStartProgress(QString startProgress);
    void setEndProgress(QString endProgress);
    void setDirection(QString direction);
    void setFadeColor(QString fadeColor);
    void setHorRepeat(QString horRepeat);
    void setVertRepeat(QString vertRepeat);
    void setBorderWidth(QString borderWidth);
    void setBorderColor(QString borderColor);
    QString getTransition();
};

#endif // TRANSITION_H
