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
 *\file GUI/audiodescriptoratrr.h
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods declaration to set the audio Attributes of a media audio.
 */

#ifndef AUDIODESCRIPTORATRR_H
#define AUDIODESCRIPTORATRR_H


#include <QDialog>
#include "NCL/descriptorparam.h"

/*!
* \class AudioDescriptorAtrr
* \brief class to set the audio Attributes of a media audio.
*/

namespace Ui {
    class AudioDescriptorAtrr;
}

class AudioDescriptorAtrr : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values and create connectors
    explicit AudioDescriptorAtrr(QWidget *parent = 0);
    ~AudioDescriptorAtrr();

    /// returns the volume value selected to the media
    QString getVolume();
    /// returns the balance value selected to the media
    QString getBalance();
    /// returns the treble value selected to the media
    QString getTreble();
    /// returns the bass value selected to the media
    QString getBass();

    /// sets the values given in the \a list in to the GUI of a media selected
    void setValues(QList<DescriptorParam*> list);

private:
    Ui::AudioDescriptorAtrr *ui;
};

#endif // AUDIODESCRIPTORATRR_H
