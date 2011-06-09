/*!
*\file NCL/importeddocumentbase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a importedDocumentBase entity.
*/

#ifndef IMPORTEDDOCUMENTBASE_H
#define IMPORTEDDOCUMENTBASE_H

#include <QString>
#include "importncl.h"

/*!
* \class ImportedDocumentBase
* \brief class to create a importedDocumentBase entity.
*/

class ImportedDocumentBase
{
private:
    QString importedDocumentBase;
    QString id;
    QString importNCL;


public:
    ImportedDocumentBase(QString importNCL);
    ImportedDocumentBase(QString id, QString importNCL);
    QString getImportedDocumentBase();
    void addImportNCL(QString importNCL);
};

#endif // IMPORTEDDOCUMENTBASE_H
