/*!
*\file NCL/metadata.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a metaData entity.
*/


#ifndef METADATA_H
#define METADATA_H

#include <QString>

/*!
* \class MetaData
* \brief class to create a metaData entity.
*/

class MetaData
{
private:
    QString metaData;
    QString rdfTree;

public:
    MetaData(QString rdfTree);
    QString getMetaData();

};

#endif // METADATA_H
