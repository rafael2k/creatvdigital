/*!
*\file NCL/metadata.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an metaData entity.
*/


#include "metadata.h"

MetaData::MetaData(QString rdfTreeParam)
{
    rdfTree = rdfTreeParam;
}

QString MetaData::getMetaData()
{
    metaData = "\t\t<metaData>\n";
    metaData.append(rdfTree);
    metaData.append("\t\t<metaData/>\n");
    return metaData;
}
