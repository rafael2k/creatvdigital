/*!
*\file NCL/importbase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an importBase entity.
*/

#include "importbase.h"

ImportBase::ImportBase(QString documentURIParam, QString aliasParam)
{
    documentURI = documentURIParam;
    alias = aliasParam;
}

QString ImportBase::getImportBase()
{
    importBase = "\t\t\t<importBase documentURI=\""+documentURI+"\" alias=\""+alias+"\"/>\n";
    return importBase;
}
