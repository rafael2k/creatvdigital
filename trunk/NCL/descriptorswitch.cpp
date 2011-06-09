/*!
*\file NCL/descriptorswitch.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an descriptorSwitch entity.
*/

#include "descriptorswitch.h"

DescriptorSwitch::DescriptorSwitch(QString idParam, DefaultDescriptor defaultDescriptorParam)
{
    id = idParam;
    defaultDescriptor = defaultDescriptorParam.getDefaultDescriptor();
    bindRule = "";
    descriptor = "";
}

DescriptorSwitch::DescriptorSwitch(QString idParam, BindRule bindRuleParam)
{
    id = idParam;
    defaultDescriptor = "";
    bindRule = bindRuleParam.getBindRule();
    descriptor = "";
}

DescriptorSwitch::DescriptorSwitch(QString idParam, Descriptor descriptorParam)
{
    id = idParam;
    defaultDescriptor = "";
    bindRule = "";
    descriptor = descriptorParam.getDescriptor();
}

void DescriptorSwitch::setDefaultDescriptor(DefaultDescriptor defaultDescriptorParam)
{
    defaultDescriptor = defaultDescriptorParam.getDefaultDescriptor();
}


void DescriptorSwitch::addDescriptor(Descriptor descriptorParam)
{
    descriptor.append(descriptorParam.getDescriptor());
}

void DescriptorSwitch::addBindRule(BindRule bindRuleParam)
{
    bindRule.append(bindRuleParam.getBindRule());
}

QString DescriptorSwitch::getDescriptorSwitch()
{
    descriptorSwitch = "\t\t\t<descriptorSwitch id=\""+id+">\n";
    descriptorSwitch.append(defaultDescriptor);
    descriptorSwitch.append(bindRule);
    descriptorSwitch.append(descriptor);
    descriptorSwitch.append("\t\t\t<descriptorSwitch />\n");
    return descriptorSwitch;
}
