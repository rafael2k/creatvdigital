/*!
*\file NCL/transitionbase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a transitionBase entity.
*/

#ifndef TRANSITIONBASE_H
#define TRANSITIONBASE_H

#include <QString>
#include "transition.h"

/*!
* \class TransitionBase
* \brief class to create a transitionBase entity.
*/


class TransitionBase
{
private:
    QString transitionBase;
    QString id;
    QString transition;

public:
    TransitionBase(Transition transition);
    TransitionBase(QString id, Transition transition);
    QString getTransitionBase();
    void addTransition(Transition transition);

};

#endif // TRANSITIONBASE_H
