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
*\file GUI/uriconfig.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to config an url.
*/

#include "uriconfig.h"
#include "ui_uriconfig.h"


/*!
 *\brief initializes values and creates connectors
 *\param QWidget* parent
 */
UriConfig::UriConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UriConfig)
{
    ui->setupUi(this);

    this->setWindowTitle("Uri");
    QButtonGroup *group = new QButtonGroup();
    group->addButton(ui->videoRB);
    group->addButton(ui->audioRB);
    group->addButton(ui->imagenRB);
    group->addButton(ui->textoRB);
    group->addButton(ui->luaRB);

    ui->videoRB->setChecked(true);
}


/*!
 *\brief destructor of de UI.
 */
UriConfig::~UriConfig()
{
    delete ui;
}


/*!
 *\brief returns the url value selected
 *\return QString
 */
QString UriConfig::getUri()
{
    return ui->uri->text();
}


/*!
 *\brief returns the Type of the media of the url
 *\return QString
 */
QString UriConfig::getType()
{
    QString ret;
    if(ui->videoRB->isChecked())
        ret = "Video";
    if(ui->audioRB->isChecked())
        ret = "Audio";
    if(ui->imagenRB->isChecked())
        ret = "Imagen";
    if(ui->textoRB->isChecked())
        ret = "Texto";
    if(ui->luaRB->isChecked())
        ret = "Lua";

    return ret;
}


/*!
 *\brief returns the media name value selected to the media
 *\return QString
 */
QString UriConfig::getName()
{
    QString ret = ui->name->text();
    return ret;
}
