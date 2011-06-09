/*!
*\file NCL/ncl.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an ncl entity.
*/

#include "ncl.h"
Ncl::Ncl(Head headParam, Body bodyParam)
{
    ncl = "";
    id = "";
    title = "";
    xmlns = "";
    head = headParam.getHead();
    body = bodyParam.getBody();
    versionEncodig = "";
}

Ncl::~Ncl()
{

}

QString Ncl::getNCL()
{
    ncl = versionEncodig;
    ncl.append("<ncl"+id+""+ xmlns+">\n");
    ncl.append(head);
    ncl.append("\n");
    ncl.append(body);
    ncl.append("</ncl>\n");
    return ncl;
}
void Ncl::setXmlns(QString xmls)
{
    xmlns = " xmlns=\""+xmls+"\"";
}

void Ncl::setId(QString idP)
{
    id = " id=\""+idP+"\"";
}

void Ncl::setVersionEncoding(QString version, QString encoding)
{
    versionEncodig = "<?xml version=\""+version+"\" encoding=\""+encoding+"\"?>\n";
}
