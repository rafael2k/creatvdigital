/*!
*\file NCL/importeddocumentbase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an importedDocumentBase entity.
*/

#include "importeddocumentbase.h"

ImportedDocumentBase::ImportedDocumentBase(QString importNCLParam)
{
    id = "";
    importNCL = importNCLParam;
}

ImportedDocumentBase::ImportedDocumentBase(QString idParam, QString importNCLParam)
{
    id = " id=\""+idParam+"\"";
    importNCL = importNCLParam;
}

QString ImportedDocumentBase::getImportedDocumentBase()
{
    importedDocumentBase = "\t\t<importedDocumentBase"+id+">\n";
    importedDocumentBase.append(importNCL);
    importedDocumentBase.append("\t\t</importedDocumentBase>\n");
    return importedDocumentBase;
}

void ImportedDocumentBase::addImportNCL(QString importNCLParam)
{
    importNCL.append("\t\t\t"+importNCLParam+"\n");
}
