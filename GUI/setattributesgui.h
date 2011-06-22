/***************************************************************************
 *   CreaTV Digital - Herramienta para la creación de aplicaciones NCL para
 *   el middleware GINGA de Televisión Digital Terrestre
 *
 *  Copyright © 2010, 2011
 *        -Cardozo, Sergio A. (yojajo@gmail.com)
 *        -Schwartz, Sebastian M. (seba.schwartz.7@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/

/*!
*\file GUI/setattributesgui.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the media Attributes when an event ocurrs.
*/

#ifndef SETATTRIBUTESGUI_H
#define SETATTRIBUTESGUI_H

#include <QDialog>
#include <QTableWidget>
#include <QListWidgetItem>

/*!
* \class SetAttributesGUI
* \brief class to set the media Attributes when an event ocurrs.
*/

namespace Ui {
    class SetAttributesGUI;
}

class SetAttributesGUI : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values and create connectors
    explicit SetAttributesGUI(QWidget *parent = 0);
    ~SetAttributesGUI();

    /// adds the list of medias given in \a \allMedias. \allMedias is used to obtain the media type
    void setList(QTableWidget* mediaList, QStringList allMedias);

    /// returns the volume value selected to the media
    QString getVolume();
    /// returns the balance value selected to the media
    QString getBalance();
    /// returns the treble value selected to the media
    QString getTreble();
    /// returns the bass value selected to the media
    QString getBass();
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
    /// returns the Scroll value selected to the media
    QString getScroll();
    //QString getStyle();
    /// returns the Font Style value selected to the media
    QString getFontStyle();
    /// returns the Font Color value selected to the media
    QString getFontColor();
    /// returns the Font Family value selected to the media
    QString getFontFamily();
    /// returns the Font Size value selected to the media
    QString getFontSize();
    /// returns the Font Varianr value selected to the media
    QString getFontVariant();
    /// returns the Font Weight value selected to the media
    QString getFontWeight();

    QTableWidget *attributes;

    /// returns the table with the media name (colum = 0), the attribute name (colum = 1) and the value (column = 2)
    QTableWidget* getAttributes();
    /// initializes the attributtes table with the values of \a table
    void setAttributtesList(QTableWidget *table);

private:
    Ui::SetAttributesGUI *ui;

    QTableWidget *mediasList;
    QTableWidgetItem *item;

    /// returns the type of the media \a mediaName
    QString getMediaType(QString mediaName);
    /// returns the Background name color selected to the media
    QString getBackgroundColorName(int index);
    /// returns the Font color selected to the media
    QString getFontColorName(int index);
    /// returns the Scroll name selected to the media
    QString getScrollName(int index);
     /// returns the index in the comboBox of a background \a color
    int getBackgroundColorIndex(QString color);
     /// returns the index in the comboBox of a font \a color
    int getFontColorIndex(QString color);
     /// returns the index in the comboBox of a \a scroll
    int getScrollIndex(QString scroll);
    /// returns the index in the comboBox of a \a fit
    int getFitIndex(QString fit);

    /// add the media \a with the attributte \a attribute and the value \a value to de list of attributes
    void addAttribute(QString media,QString attribute, QString value);
    /// removes the attribute \a attribute of the media \a media to the list of attributes
    void removeAttribute(QString media,QString attribute);
    /// saves the previos media selected (\a previous) configuration of attributes
    void savePrevious(QListWidgetItem* previous);
    /// load the configuration of attributes of the current media
    void loadCurrent(QListWidgetItem* current);

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

    /// called to save the media attributes when the current item is changed
    void saveChanges(QListWidgetItem* current,QListWidgetItem* previous);
    /// initializes the radio buttons disables
    void initRadioButtons();

    /// sets the top values enabled or not (\a b)
    void setTopEnable(bool b);
    /// sets the left values enabled or not (\a b)
    void setLeftEnable(bool b);
    /// sets the Bottom values enabled or not (\a b)
    void setBottomtEnable(bool b);
    /// sets the Right values enabled or not (\a b)
    void setRightEnable(bool b);
    /// sets the Height values enabled or not (\a b)
    void setHeightEnable(bool b);
    /// sets the Width values enabled or not (\a b)
    void setWidthEnable(bool b);
    /// sets the Visible value enabled or not (\a b)
    void setVisibleEnable(bool b);
    /// sets the zIndex value enabled or not (\a b)
    void setZIndexEnable(bool b);
    /// sets the Background value enabled or not (\a b)
    void setBackgroundEnable(bool b);
    /// sets the Transparency value enabled or not (\a b)
    void setTransparencyEnable(bool b);
    /// sets the Fit value enabled or not (\a b)
    void setFitEnable(bool b);

    /// sets the Volume values enabled or not (\a b)
    void setVolumeEnable(bool b);
    /// sets the Bass values enabled or not (\a b)
    void setBassEnable(bool b);
    /// sets the Treble value senabled or not (\a b)
    void setTrebleEnable(bool b);
    /// sets the Balance values enabled or not (\a b)
    void setBalanceEnable(bool b);

    /// sets the Font values enabled or not (\a b)
    void setFontEnable(bool b);
    /// sets the Style Font values enabled or not (\a b)
    void setStyleFontEnable(bool b);
    /// sets the Size value enabled or not (\a b)
    void setSizeEnable(bool b);
    /// sets the Color Font value enabled or not (\a b)
    void setColorFontEnable(bool b);
    /// sets the Scroll value enabled or not (\a b)
    void setScrollEnable(bool b);

    /// called to save the current media attributes when the window is closed
    void saveCurrentMedia();
};

#endif // SETATTRIBUTESGUI_H
