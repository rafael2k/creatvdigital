/*!
*\file NCL/transitionbase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an transitionBase entity.
*/

#include "transitionbase.h"

TransitionBase::TransitionBase(Transition transitionParam)
{
    id = "";
    transition = transitionParam.getTransition();
}

TransitionBase::TransitionBase(QString idParam, Transition transitionParam)
{
    id = " id=\""+idParam+"\"";
    transition = transitionParam.getTransition();
}

QString TransitionBase::getTransitionBase()
{
    transitionBase = "\t\t<transition"+id+">\n";
    transition.append(transition);
    transitionBase.append("\t\t<transition/>\n");
    return transitionBase;
}
