/*!
*\file NCL/importbase.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a importBase entity.
*/

#ifndef IMPORTBASE_H
#define IMPORTBASE_H

#include <QString>

/*!
* \class ImportBase
* \brief class to create a importBase entity.
*/

class ImportBase
{
private:    
    QString importBase;
    QString documentURI;
    QString alias;

public:
    ImportBase(QString documentURI, QString alias);
    QString getImportBase();
};

#endif // IMPORTBASE_H
