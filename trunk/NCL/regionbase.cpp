/*!
*\file NCL/regionbase.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an regionBase entity.
*/

#include "regionbase.h"


RegionBase::RegionBase(Regionn regionParam)
{
    regionBase="";
    id="";
    device="";
    region = regionParam.getRegion();
}

RegionBase::RegionBase(QString idRegionBase, Regionn regionParam)
{
    regionBase = "";
    id = " id=\""+idRegionBase+"\"";
    device = "";
    region = regionParam.getRegion();
}

QString RegionBase::getRegionBase()
{
    regionBase="\t\t<regionBase"+id+device+">\n";
    regionBase.append(region);
    regionBase.append("\t\t</regionBase>\n");
    return regionBase;
}

void RegionBase::addRegion(Regionn regionR)
{
    region.append(regionR.getRegion());
}

void RegionBase::setDevice(QString deviceParam)
{
    device = " device=\""+deviceParam+"\"";
}


