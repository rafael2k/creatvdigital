/*!
*\file NCL/importncl.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a importNCL entity.
*/

#ifndef IMPORTNCL_H
#define IMPORTNCL_H

#include <QString>

/*!
* \class ImportNCL
* \brief class to create a importNCL entity.
*/

class ImportNCL
{
private:
    QString importNCL;
    QString alias;
    QString documentURI;

public:
    ImportNCL(QString alias, QString documentURI);
    QString getImportNCL();
};

#endif // IMPORTNCL_H
