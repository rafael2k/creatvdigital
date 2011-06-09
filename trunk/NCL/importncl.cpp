/*!
*\file NCL/importncl.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an importNCL entity.
*/

#include "importncl.h"

ImportNCL::ImportNCL(QString aliasParam, QString documentURIParam)
{
    alias = aliasParam;
    documentURI = documentURIParam;
}

QString ImportNCL::getImportNCL()
{
    importNCL = "\t\t\t<importNCL alias=\""+alias+"\" documentURI=\""+documentURI+"\" />\n";
    return importNCL;
}
