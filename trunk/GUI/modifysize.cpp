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
*\file GUI/modifysize.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the media size Attributes of the screen configuration.
*/

#include "modifysize.h"
#include "ui_modifysize.h"


/*!
 *\brief creates the GUI and initialize values
 *\param QWidget* parent
 */
ModifySize::ModifySize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifySize)
{
    ui->setupUi(this);

    ui->width->setMaximum(2500);
    ui->height->setMaximum(2000);
}


/*!
 *\brief destructor of de UI.
 */
ModifySize::~ModifySize()
{
    delete ui;
}


/*!
 *\brief returns the Width value selected to the media
 *\return int
 */
int ModifySize::getWidth()
{
    return ui->width->value();
}


/*!
 *\brief returns the Height value selected to the media
 *\return int
 */
int ModifySize::getHeight()
{
    return ui->height->value();
}


/*!
 *\brief returns the Width value selected to the media
 *\return int
 */
void ModifySize::setWidth(int w)
{
    ui->width->setValue(w);
}


/*!
 *\brief returns the Height value selected to the media
 *\return int
 */
void ModifySize::setHeight(int h)
{
    ui->height->setValue(h);
}

