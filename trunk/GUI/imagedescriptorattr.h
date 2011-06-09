/*!
*\file GUI/imagedescriptorattr.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the image Attributes of a media image.
*/

#ifndef IMAGEDESCRIPTORATTR_H
#define IMAGEDESCRIPTORATTR_H

#include <QDialog>
#include "NCL/descriptorparam.h"


/*!
* \class ImageDescriptorAttr
* \brief class to set the image Attributes of a media image.
*/

namespace Ui {
    class ImageDescriptorAttr;
}

class ImageDescriptorAttr : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI
    explicit ImageDescriptorAttr(QWidget *parent = 0);
    ~ImageDescriptorAttr();

    /// returns the Top value selected to the media
    QString getTop();
    /// returns the Left value selected to the media
    QString getLeft();
    /// returns the Bottom value selected to the media
    QString getBottom();
    /// returns the Right value selected to the media
    QString getRight();
    /// returns the Height value selected to the media
    QString getHeight();
    /// returns the Name value selected to the media
    QString getWidth();
    /// returns the Width value selected to the media
    QString getVisible();
    /// returns the zIndex value selected to the media
    QString getZIndex();
    /// returns the Background value selected to the media
    QString getBackground();
    /// returns the Transparency value selected to the media
    QString getTransparency();
    /// returns the Fit value selected to the media
    QString getFit();
    /// sets the values given in the \a list in to the GUI of a media selected
    void setValues(QList<DescriptorParam*> list);


private:
    Ui::ImageDescriptorAttr *ui;

    /// initializes values and create connectors
    void initialize();
    /// returns the index in the comboBox of a \a color
    int getBackgroundColorIndex(QString color);
    /// returns the index in the comboBox of a \a fit
    int getFitIndex(QString fit);

private slots:
    /// changes the suffix "%" to "Px" in the comboBox Top
    void changeTopToPx();
    /// changes the suffix "%" to "Px" in the comboBox Left
    void changeLeftToPx();
    /// changes the suffix "%" to "Px" in the comboBox Bottom
    void changeBottomToPx();
    /// changes the suffix "%" to "Px" in the comboBox Right
    void changeRightToPx();
    /// changes the suffix "%" to "Px" in the comboBox Height
    void changeHeightToPx();
    /// changes the suffix "%" to "Px" in the comboBox Width
    void changeWidthToPx();
    /// changes the suffix "Px" to "%" in the comboBox Top
    void changeTopToPercentaje();
    /// changes the suffix "Px" to "%" in the comboBox Left
    void changeLeftToPercentaje();
    /// changes the suffix "Px" to "%" in the comboBox Bottom
    void changeBottomToPercentaje();
    /// changes the suffix "Px" to "%" in the comboBox Right
    void changeRightToPercentaje();
    /// changes the suffix "Px" to "%" in the comboBox Height
    void changeHeightToPercentaje();
    /// changes the suffix "Px" to "%" in the comboBox Width
    void changeWidthToPercentaje();
};


#endif // IMAGEDESCRIPTORATTR_H
