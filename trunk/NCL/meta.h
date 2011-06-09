/*!
*\file NCL/meta.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a meta entity.
*/


#ifndef META_H
#define META_H

#include <QString>

/*!
* \class Meta
* \brief class to create a meta entity.
*/


class Meta
{
private:
    QString meta;
    QString name;
    QString content;

public:
    Meta(QString name, QString content);
    QString getMeta();
};

#endif // META_H
