/*!
*\file NCL/head.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a head entity.
*/

#ifndef HEAD_H
#define HEAD_H

#include <QString>
#include "importeddocumentbase.h"

/*!
* \class Head
* \brief class to create a head entity.
*/

class Head
{
private:
    QString head;
    QString importedDocumentBase;
    QString ruleBase;
    QString transitionBase;
    QString regionBase;
    QString descriptorBase;
    QString connectorBase;
    QString meta;
    QString metaData;

public:
    Head();
    QString getHead();
    void setImpotedDocumentBase(QString importedDocumentBase);
    void setRuleBase(QString ruleBase);
    void setTransitionBase(QString transitionBase);
    void addRegionBase(QString transitionBase);
    void addDescriptorBase(QString transitionBase);
    void setConnectorBase(QString connectorBase);
    void addMeta(QString meta);
    void addMetaData(QString metaData);
};

#endif // HEAD_H
