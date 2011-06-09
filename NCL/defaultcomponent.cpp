/*!
*\file NCL/defaultcomponent.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an defaultComponent entity.
*/

#include "defaultcomponent.h"

DefaultComponent::DefaultComponent(QString componentParam)
{
    component = componentParam;
}

QString DefaultComponent::getDefaultComponent()
{
    defaultComponent = "\t\t\t\t<defaultComponent component=\""+component+"\"/>\n";
    return defaultComponent;
}
