/*!
*\file NCL/context.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a context entity.
*/

#ifndef CONTEXT_H
#define CONTEXT_H

#include "switch.h"
#include "port.h"
#include "link.h"
#include "media.h"
#include "property.h"

/*!
* \class Context
* \brief class to create a context entity.
*/

class Context
{
private:
    QString context;
    QString id;
    QString refer;
    QString port;
    QString property;
    QString media;
    QString subContext;
    QString link;
    QString switchS;

public:
    Context(QString id);
    Context(QString id, Port port);
    Context(QString id, Property property);
    Context(QString id, Media media);
    Context(QString id, Context context);
    Context(QString id, Link link);
    Context(QString id, Switch switchS);
    QString getContext();
    void setRefer(QString refer);
    void addPort(Port port);
    void addProperty(Property property);
    void addMedia(Media media);
    void addContext(Context context);
    void addLink(Link link);
    void addSwitch(Switch switchS);
};

#endif // CONTEXT_H
