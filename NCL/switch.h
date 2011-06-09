/*!
*\file NCL/switch.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a switch entity.
*/

#ifndef SWITCH_H
#define SWITCH_H

#include "defaultcomponent.h"
#include "switchport.h"
#include "bindrule.h"
#include "media.h"

/*!
* \class Switch
* \brief class to create a switch entity.
*/

class Switch
{
private:
    QString switchS;
    QString id;
    QString refer;
    QString defaultComponent;
    QString switchPort;
    QString bindRule;
    QString media;
    QString context;
    QString subSwitch;

public:
    Switch(QString id, DefaultComponent defaultComponent);
    Switch(QString id, SwitchPort switchPort);
    Switch(QString id, BindRule bindRule);
    Switch(QString id, Media media);
    Switch(QString id, QString context);
    Switch(QString id, Switch switchS);
    void setRefer(QString refer);
    void setDefaultComponent(DefaultComponent defaultComponent);
    void addSwitchPort(SwitchPort switchPort);
    void addBindRulet(BindRule bindRule);
    void addMedia(Media media);
    void addContext(QString context);
    void addSwitch(Switch subSwitch);
    QString getSwitch();

};

#endif // SWITCH_H
