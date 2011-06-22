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
*\file GUI/modifysize.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the media size Attributes of the screen configuration.
*/

#ifndef MODIFYSIZE_H
#define MODIFYSIZE_H

#include <QDialog>

/*!
* \class ModifySize
* \brief class to set the media size Attributes of the screen configuration.
*/

namespace Ui {
    class ModifySize;
}

class ModifySize : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI and initialize values
    explicit ModifySize(QWidget *parent = 0);
    ~ModifySize();

    /// returns the Width value selected to the screen
    int getWidth();
    /// returns the Height value selected to the screen
    int getHeight();
    /// initializes the Width value with the current value
    void setWidth(int w);
    /// initializes the Height value with the current value
    void setHeight(int h);

private:
    Ui::ModifySize *ui;
};

#endif // MODIFYSIZE_H
