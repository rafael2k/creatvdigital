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
*\file GUI/uriconfig.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to config an url.
*/

#ifndef URICONFIG_H
#define URICONFIG_H

#include <QDialog>

/*!
* \class UriConfig
* \brief class to config an url.
*/

namespace Ui {
    class UriConfig;
}

class UriConfig : public QDialog
{
    Q_OBJECT

public:
    /// initializes values and create connectors
    explicit UriConfig(QWidget *parent = 0);
    ~UriConfig();

    /// returns the url value selected
    QString getUri();
    /// returns the Type of the media of the url
    QString getType();
    /// returns the media name value selected to the media
    QString getName();

private:
    Ui::UriConfig *ui;
};

#endif // URICONFIG_H
