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
*\file GUI/textdescriptoratrr.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the text Attributes of a media text.
*/

#ifndef TEXTDESCRIPTORATRR_H
#define TEXTDESCRIPTORATRR_H

#include <QDialog>
#include "NCL/descriptorparam.h"


/*!
* \class TextDescriptorAtrr
* \brief class to set the text Attributes of a media text.
*/

namespace Ui {
    class TextDescriptorAtrr;
}

class TextDescriptorAtrr : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values and create connectors
    explicit TextDescriptorAtrr(QWidget *parent = 0);
    ~TextDescriptorAtrr();

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
    /// returns the Font Variant value selected to the media
    QString getFontVariant();
    /// returns the Font Weight value selected to the media
    QString getFontWeight();

    /// returns the index of the comboBox of the \a color given
    int getFontColorIndex(QString color);
    /// returns the index of the comboBox of the \a scroll given
    int getScrollIndex(QString scroll);

    /// sets the values given in the \a list in to the GUI of a media selected
    void setValues(QList<DescriptorParam*> list);

private:
    Ui::TextDescriptorAtrr *ui;

};

#endif // TEXTDESCRIPTORATRR_H
