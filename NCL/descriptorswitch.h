/*!
*\file NCL/descriptorswitch.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a descriptorSwitch entity.
*/

#ifndef DESCRIPTORSWITCH_H
#define DESCRIPTORSWITCH_H

#include <QString>
#include "defaultdescriptor.h"
#include "bindrule.h"
#include "descriptor.h"

/*!
* \class DescriptorSwitch
* \brief class to create a descriptorSwitch entity.
*/

class DescriptorSwitch
{
private:
    QString descriptorSwitch;
    QString id;
    QString defaultDescriptor;
    QString descriptor;
    QString bindRule;

public:
    DescriptorSwitch(QString id, DefaultDescriptor defaultDescriptor);
    DescriptorSwitch(QString id, BindRule bindRule);
    DescriptorSwitch(QString id, Descriptor descriptor);
    void setDefaultDescriptor(DefaultDescriptor defaultDescriptor);
    void addDescriptor(Descriptor descriptor);
    void addBindRule(BindRule bindRule);
    QString getDescriptorSwitch();

};

#endif // DESCRIPTORSWITCH_H
