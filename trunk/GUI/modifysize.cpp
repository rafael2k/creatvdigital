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

