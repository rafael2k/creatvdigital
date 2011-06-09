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
