/*!
 *\file GUI/audiodescriptoratrr.cpp
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods implementation to set the audio Attributes of a media audio.
 */

#include "audiodescriptoratrr.h"
#include "ui_audiodescriptoratrr.h"


/*!
 *\brief creates the GUI, initialize values and create connectors
 *\param QWidget* parent
 */
AudioDescriptorAtrr::AudioDescriptorAtrr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AudioDescriptorAtrr)
{
    ui->setupUi(this);

    ui->volumeDial->setMinimum(0);
    ui->volumeDial->setMaximum(100);
    ui->balanceSlider->setMinimum(0);
    ui->balanceSlider->setMaximum(100);
    ui->trebleDial->setMinimum(0);
    ui->trebleDial->setMaximum(100);
    ui->bassDial->setMinimum(0);
    ui->bassDial->setMaximum(100);

    ui->volumeSpinBox->setMaximum(100);
    ui->balanceSpinBox->setMaximum(100);
    ui->trebleSpinBox->setMaximum(100);
    ui->bassSpinBox->setMaximum(100);

    ui->volumeDial->setValue(100);
    ui->volumeSpinBox->setValue(100);
    ui->balanceSlider->setValue(50);
    ui->balanceSpinBox->setValue(50);
    ui->trebleDial->setValue(50);
    ui->trebleSpinBox->setValue(50);
    ui->bassDial->setValue(50);
    ui->bassSpinBox->setValue(50);

    connect(ui->volumeDial,SIGNAL(valueChanged(int)),ui->volumeSpinBox,SLOT(setValue(int)));
    connect(ui->volumeSpinBox,SIGNAL(valueChanged(int)),ui->volumeDial,SLOT(setValue(int)));
    connect(ui->balanceSlider,SIGNAL(valueChanged(int)),ui->balanceSpinBox,SLOT(setValue(int)));
    connect(ui->balanceSpinBox,SIGNAL(valueChanged(int)),ui->balanceSlider,SLOT(setValue(int)));
    connect(ui->trebleDial,SIGNAL(valueChanged(int)),ui->trebleSpinBox,SLOT(setValue(int)));
    connect(ui->trebleSpinBox,SIGNAL(valueChanged(int)),ui->trebleDial,SLOT(setValue(int)));
    connect(ui->bassDial,SIGNAL(valueChanged(int)),ui->bassSpinBox,SLOT(setValue(int)));
    connect(ui->bassSpinBox,SIGNAL(valueChanged(int)),ui->bassDial,SLOT(setValue(int)));
}


/*!
 *\brief destructor of de UI.
 */
AudioDescriptorAtrr::~AudioDescriptorAtrr()
{
    delete ui;
}


/*!
 *\brief returns the volume value selected to the media
 *\return QString
 */
QString AudioDescriptorAtrr::getVolume()
{
    return QString::number(ui->volumeDial->value())+"%";
}


/*!
 *\brief returns the balance value selected to the media
 *\return QString
 */
QString AudioDescriptorAtrr::getBalance()
{
    return QString::number(ui->balanceSlider->value())+"%";
}


/*!
 *\brief returns the treble value selected to the media
 *\return QString
 */
QString AudioDescriptorAtrr::getTreble()
{
    return QString::number(ui->trebleDial->value())+"%";
}


/*!
 *\brief returns the bass value selected to the media
 *\return QString
 */
QString AudioDescriptorAtrr::getBass()
{
    return QString::number(ui->bassDial->value())+"%";
}


/*!
 *\brief sets the values given in the \a list in to the GUI of a media selected
 *\param QList<DescriptorParam*> list
 *\return void
 */
void AudioDescriptorAtrr::setValues(QList<DescriptorParam*> list){
    QString value = "";
    for(int i = 0; i < list.count();i++){
        if(list.at(i)->getName() == "soundLevel"){
            value = list.at(i)->getValue();
            value = value.remove("%");
            ui->volumeDial->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "bassLevel"){
            value = list.at(i)->getValue();
            value = value.remove("%");
            ui->bassDial->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "trebleLevel"){
            value = list.at(i)->getValue();
            value = value.remove("%");
            ui->trebleDial->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "balanceLevel"){
            value = list.at(i)->getValue();
            value = value.remove("%");
            ui->balanceSlider->setValue(value.toInt());
        }
    }
}
