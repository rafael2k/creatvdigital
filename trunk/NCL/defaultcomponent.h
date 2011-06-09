/*!
*\file NCL/defaultcomponent.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a defaultComponent entity.
*/

#ifndef DEFAULTCOMPONENT_H
#define DEFAULTCOMPONENT_H

#include <QString>

/*!
* \class DefaultComponent
* \brief class to create a defaultComponent entity.
*/

class DefaultComponent
{
private:
    QString defaultComponent;
    QString component;

public:
    DefaultComponent(QString component);
    QString getDefaultComponent();
};

#endif // DEFAULTCOMPONENT_H
