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
*\file GUI/newproject.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the new project Attributes.
*/

#include "newproject.h"
#include "ui_newproject.h"


/*!
 *\brief creates the GUI, initialize values with the params (\a description,\a w,\a h,\a date) and create connectors
 *\param QString description
 *\param QString selected
 *\param int w
 *\param int h
 *\param QDate date
 *\param QWidget *parent
 */
NewProject::NewProject(QString description, QString selected, int w, int h,QDate date, QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::NewProject)
{
    m_ui->setupUi(this);

    QButtonGroup *group = new QButtonGroup();
    group->addButton(m_ui->palN);
    group->addButton(m_ui->palAncho);
    group->addButton(m_ui->hdtvI);
    group->addButton(m_ui->hdtvP);
    group->addButton(m_ui->otro);
    group->addButton(m_ui->noEsp);

    m_ui->palN->setChecked(true);
    m_ui->width->setEnabled(false);
    m_ui->height->setEnabled(false);

    m_ui->width->setMaximum(2500);
    m_ui->height->setMaximum(2000);
    m_ui->width->setMinimum(100);
    m_ui->height->setMinimum(100);

    m_ui->dateEdit->setDisplayFormat("dd/MM/yyyy");
    if(date.isNull())
        m_ui->dateEdit->setDate(QDate::currentDate());
    else
        m_ui->dateEdit->setDate(date);

    connect(m_ui->otro,SIGNAL(toggled(bool)),this,SLOT(setLineButtonEnable(bool)));
    connect(this,SIGNAL(accepted()),this,SLOT(verify()));

    m_ui->description->setPlainText(description);

    if(selected == "palN")
        m_ui->palN->setChecked(true);

    if(selected == "palAncho")
        m_ui->palAncho->setChecked(true);

    if(selected == "hdtvp")
        m_ui->hdtvP->setChecked(true);

    if(selected == "hdtvi")
        m_ui->hdtvI->setChecked(true);

    if(selected == "noEsp")
        m_ui->noEsp->setChecked(true);

    if(selected == "otro")
        m_ui->otro->setChecked(true);

    m_ui->width->setValue(w);
    m_ui->height->setValue(h);

    m_ui->lineEdit->setFocus();
}


/*!
 *\brief destructor of de UI.
 */
NewProject::~NewProject()
{
    delete m_ui;
}

void NewProject::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


/*!
 *\brief returns the name value selected to the project
 *\return QString
 */
QString NewProject::getNameProject()
{
    return m_ui->lineEdit->text();
}


/*!
 *\brief sets enable or not the widht and height \a SipnBoxes (\a enable)
 *\param bool enable
 *\return void
 */
void NewProject::setLineButtonEnable(bool enable)
{
    m_ui->width->setEnabled(enable);
    m_ui->height->setEnabled(enable);
}


/*!
 *\brief returns the screen value selected to the project
 *\return QString
 */
QString NewProject::getScreenSelected()
{
    QString ret;
    if(m_ui->palN->isChecked())
        ret = "palN";
    if(m_ui->palAncho->isChecked())
        ret = "palAncho";
    if(m_ui->hdtvP->isChecked())
        ret = "hdtvp";
    if(m_ui->hdtvI->isChecked())
        ret = "hdtvi";
    if(m_ui->noEsp->isChecked())
        ret = "noEsp";
    if(m_ui->otro->isChecked())
        ret = "otro";
    return ret;
}


/*!
 *\brief returns the description value selected to the project
 *\return QString
 */
QString NewProject::getDescription()
{
   return m_ui->description->document()->toPlainText();
}


/*!
 *\brief returns the Width value selected to the project
 *\return int
 */
int NewProject::getWidth()
{
    return m_ui->width->value();
}


/*!
 *\brief returns the Height value selected to the project
 *\return int
 */
int NewProject::getHeight()
{
    return m_ui->height->value();
}


/*!
 *\brief sets the descirption value of the GUI
 *\param QString description
 *\return void
 */
void NewProject::setDescription(QString description)
{
    m_ui->description->setText(description);
}


/*!
 *\brief returns the date value selected to the project
 *\return QDate
 */
QDate NewProject::getDate()
{
    return m_ui->dateEdit->date();
}
