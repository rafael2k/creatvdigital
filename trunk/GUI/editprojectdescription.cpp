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
*\file GUI/editprojectdescription.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the project Attributes.
*/

#include "editprojectdescription.h"
#include "ui_editprojectdescription.h"

/*!
 *\brief creates the GUI, initialize values with the params (\a projectName,\a projectName,\a projectDate)
 *\param QWidget* parent
 */
EditProjectDescription::EditProjectDescription(QString projectName,QString projectDescription,QDate projectDate,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProjectDescription)
{
    ui->setupUi(this);

    ui->lineEdit->setText(projectName);
    ui->description->setText(projectDescription);
    ui->dateEdit->setDate(projectDate);
}


/*!
 *\brief destructor of de UI.
 */
EditProjectDescription::~EditProjectDescription()
{
    delete ui;
}

/*!
 *\brief returns the name value selected to the project
 *\return QString
 */
QString EditProjectDescription::getName(){
    return ui->lineEdit->text();
}


/*!
 *\brief returns the description value selected to the project
 *\return QString
 */
QString EditProjectDescription::getDescription(){
    return ui->description->document()->toPlainText();
}


/*!
 *\brief returns the date value selected to the project
 *\return QDate
 */
QDate EditProjectDescription::getDate(){
    return ui->dateEdit->date();
}
