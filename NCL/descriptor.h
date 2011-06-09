/*!
*\file NCL/descriptor.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a descriptor entity.
*/

#ifndef DESCRIPTOR_H
#define DESCRIPTOR_H

#include <QString>
#include "descriptorparam.h"

/*!
* \class Descriptor
* \brief class to create a descriptor entity.
*/

class Descriptor
{
private:
    QString descriptor;
    QString id;
    QString player;
    QString explicitDur;
    QString region;
    QString freeze;
    QString moveLeft;
    QString moveRight;
    QString moveUp;
    QString moveDown;
    QString focusIndex;
    QString focusBorderColor;
    QString focusBorderWidth;
    QString focusBorderTransparency;
    QString focusSrc;
    QString focusSelSrc;
    QString selBorderColor;
    QString transIn;
    QString transOut;
    QString descriptorParam;

public:
    Descriptor(QString id);
    QString getDescriptor();
    void addDescriptorParam(DescriptorParam *descriptorParam);
    void setPlayer(QString player);
    void setExplicitDur(QString explicitDur);
    void setRegion(QString region);
    void setFreeze(QString freeze);
    void setMoveLeft(QString moveLeft);
    void setMoveRight(QString moveRight);
    void setMoveUp(QString moveUp);
    void setMoveDown(QString moveDown);
    void setFocusIndex(QString focusIndex);
    void setFocusBorderColor(QString focusBorderColor);
    void setFocusBorderWidth(QString focusBorderWidth);
    void setFocusBorderTransparency(QString focusBorderTransparency);
    void setFocusSrc(QString focusSrc);
    void setFocusSelSrc(QString focusSelSrc);
    void setSelBorderColor(QString selBorderColor);
    void setTransIn(QString transIn);
    void setTransOut(QString transOut);
    void setDescriptorParam(QString descriptorParam);
    void removeMoveLeft();
    void removeMoveRight();
    void removeMoveUp();
    void removeMoveDown();
    QString getExplicitDur();
    QString getRegion();
    QString getMoveLeft();
    QString getMoveRight();
    QString getMoveUp();
    QString getMoveDown();
    QString getFocusIndex();
    QString getFocusBorderColor();
    QString getFocusBorderWidth();
    QString getFocusBorderTransparency();
    QString getFocusSrc();
    QString getFocusSelSrc();
    QString getSelBorderColor();
    QString getDescriptorParam();
    void clearAllFocus();
    void clearAllDescriptorParam();


    void deleteExplicitDur();
    QString getId();

};

#endif // DESCRIPTOR_H
