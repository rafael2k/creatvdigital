/*!
*\file NCL/descriptor.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an descriptor entity.
*/

#include "descriptor.h"

Descriptor::Descriptor(QString idDescriptor)
{
    descriptor = "";
    id = "id=\""+idDescriptor+"\"";
    player = "";
    explicitDur = "";
    region = "";
    freeze = "";
    moveLeft = "";
    moveRight = "";
    moveUp = "";
    moveDown = "";
    focusIndex = "";
    focusBorderColor = "";
    focusBorderWidth = "";
    focusBorderTransparency = "";
    focusSrc= "";
    focusSelSrc = "";
    selBorderColor = "";
    transIn = "";
    transOut = "";
    descriptorParam = "";
}

QString Descriptor::getDescriptor()
{
    descriptor = "\t\t\t<descriptor "+id+player+explicitDur+region+freeze+moveLeft+moveRight+moveUp+moveDown+
                 focusIndex+focusBorderColor+focusBorderWidth+focusBorderTransparency+focusSrc+focusSelSrc+
                 selBorderColor+transIn+transOut+">\n";
    descriptor.append(descriptorParam);
    descriptor.append("\t\t\t</descriptor>\n");
    return descriptor;
}

void Descriptor::addDescriptorParam(DescriptorParam *descriptorParamParam)
{
   descriptorParam.append("\t\t\t"+descriptorParamParam->getDescriptorParam());
}

void Descriptor::setPlayer(QString playerParam)
{
    player = " player=\""+playerParam+"\"";
}

void Descriptor::setExplicitDur(QString explicitDurParam)
{
    explicitDur = " explicitDur=\""+explicitDurParam+"s\"";
}

void Descriptor::setRegion(QString regionParam)
{
    region = " region=\""+regionParam+"\"";
}

void Descriptor::setFreeze(QString freezeParam)
{
    freeze = " freeze=\""+freezeParam+"\"";
}

void Descriptor::setMoveLeft(QString moveLeftParam)
{
    moveLeft = " moveLeft=\""+moveLeftParam+"\"";
}

void Descriptor::setMoveRight(QString moveRightParam)
{
    moveRight = " moveRight=\""+moveRightParam+"\"";
}

void Descriptor::setMoveUp(QString moveUpParam)
{
    moveUp = " moveUp=\""+moveUpParam+"\"";
}

void Descriptor::setMoveDown(QString moveDownParam)
{
    moveDown = " moveDown=\""+moveDownParam+"\"";
}

void Descriptor::setFocusIndex(QString focusIndexParam)
{
    focusIndex = " focusIndex=\""+focusIndexParam+"\"";
}

void Descriptor::setFocusBorderColor(QString focusBorderColorParam)
{
    focusBorderColor = " focusBorderColor=\""+focusBorderColorParam+"\"";
}

void Descriptor::setFocusBorderWidth(QString focusBorderWidthParam)
{
    focusBorderWidth = " focusBorderWidth=\""+focusBorderWidthParam+"\"";
}

void Descriptor::setFocusBorderTransparency(QString focusBorderTransparencyParam)
{
    focusBorderTransparency = " focusBorderTransparency=\""+focusBorderTransparencyParam+"\"";
}

void Descriptor::setFocusSrc(QString focusSrcParam)
{
    focusSrc = " focusSrc=\""+focusSrcParam+"\"";
}

void Descriptor::setFocusSelSrc(QString focusSelSrcParam)
{
    focusSelSrc = " focusSelSrc=\""+focusSelSrcParam+"\"";
}

void Descriptor::setSelBorderColor(QString selBorderColorParam)
{
    selBorderColor = " selBorderColor=\""+selBorderColorParam+"\"";
}

void Descriptor::setTransIn(QString transInParam)
{
    transIn = " transIn=\""+transInParam+"\"";
}

void Descriptor::setTransOut(QString transOutParam)
{
    transOut = " transOut=\""+transOutParam+"\"";
}


void Descriptor::removeMoveLeft(){
   moveLeft = "";
}

void Descriptor::removeMoveRight(){
    moveRight = "";
}

void Descriptor::removeMoveUp(){
    moveUp = "";
}

void Descriptor::removeMoveDown(){
    moveDown = "";
}

QString Descriptor::getId()
{
    QString idR = id;
    idR.remove("\"");
    idR.remove("id=");
    return idR;
}

QString Descriptor::getExplicitDur()
{
    QString explicitDurR = explicitDur;
    explicitDurR.remove("\"");
    explicitDurR.remove(" explicitDur=");
    explicitDurR.remove("s");
    return explicitDurR;
}

QString Descriptor::getRegion()
{
    QString regionR = region;
    regionR.remove("\"");
    regionR.remove(" region=");
    return regionR ;
}

QString Descriptor::getMoveLeft()
{
    QString moveLeftR = moveLeft;
    moveLeftR.remove("\"");
    moveLeftR.remove(" moveLeft=");
    return moveLeftR ;
}

QString Descriptor::getMoveRight()
{
    QString moveRightR = moveRight;
    moveRightR.remove("\"");
    moveRightR.remove(" moveRight=");
    return moveRightR ;
}

QString Descriptor::getMoveUp()
{
    QString moveUpR = moveUp;
    moveUpR.remove("\"");
    moveUpR.remove(" moveUp=");
    return moveUpR ;
}

QString Descriptor::getMoveDown()
{
    QString moveDownR = moveDown;
    moveDownR.remove("\"");
    moveDownR.remove(" moveDown=");
    return moveDownR ;
}

QString Descriptor::getFocusIndex()
{
    QString focusIndexR = focusIndex;
    focusIndexR.remove("\"");
    focusIndexR.remove(" focusIndex=");
    return focusIndexR ;
}

QString Descriptor::getFocusBorderColor()
{
    QString focusBorderColorR = focusBorderColor;
    focusBorderColorR.remove("\"");
    focusBorderColorR.remove(" focusBorderColor=");
    return focusBorderColorR ;
}

QString Descriptor::getFocusBorderWidth()
{
    QString focusBorderWidthR = focusBorderWidth;
    focusBorderWidthR.remove("\"");
    focusBorderWidthR.remove(" focusBorderWidth=");
    return focusBorderWidthR ;
}

QString Descriptor::getFocusBorderTransparency()
{
    QString focusBorderTransparencyR = focusBorderTransparency;
    focusBorderTransparencyR.remove("\"");
    focusBorderTransparencyR.remove(" focusBorderTransparency=");
    return focusBorderTransparencyR ;
}

QString Descriptor::getFocusSrc()
{
    QString focusSrcR = focusSrc;
    focusSrcR.remove("\"");
    focusSrcR.remove(" focusSrc=");
    return focusSrcR ;
}

QString Descriptor::getFocusSelSrc()
{
    QString focusSelSrcR = focusSelSrc;
    focusSelSrcR.remove("\"");
    focusSelSrcR.remove(" focusSelSrc=");
    return focusSelSrcR ;
}

QString Descriptor::getSelBorderColor()
{
    QString selBorderColorR = selBorderColor;
    selBorderColorR.remove("\"");
    selBorderColorR.remove(" selBorderColor=");
    return selBorderColorR ;
}

QString Descriptor::getDescriptorParam()
{
    QString descriptorParamR = descriptorParam;
    descriptorParamR.remove("\"");
    descriptorParamR.remove(" descriptorParam=");
    return descriptorParamR ;
}

void Descriptor::deleteExplicitDur()
{
    explicitDur = "";
}

void Descriptor::clearAllFocus()
{
    moveLeft = "";
    moveRight = "";
    moveUp = "";
    moveDown = "";
    focusIndex = "";
    focusBorderColor = "";
    focusBorderWidth = "";
    focusBorderTransparency = "";
    focusSrc= "";
    focusSelSrc = "";
    selBorderColor = "";
}

void Descriptor::clearAllDescriptorParam()
{
    descriptorParam = "";
}
