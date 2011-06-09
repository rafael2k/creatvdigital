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
