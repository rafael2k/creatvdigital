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
*\file GUI/newproject.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the new project Attributes.
*/

#ifndef NEWPROJECT_H
#define NEWPROJECT_H

#include <QtGui/QDialog>
#include <QDate>

/*!
* \class NewProject
* \brief class to set the new project Attributes.
*/

namespace Ui {
    class NewProject;
}

class NewProject : public QDialog {
    Q_OBJECT
public:
    /// creates the GUI, initialize values with the params (\a description,\a w,\a h,\a date) and create connectors
    NewProject(QString description,QString selected, int w, int h,QDate date,QWidget *parent = 0);
    ~NewProject();

    /// returns the name value selected to the project
    QString getNameProject();
    /// returns the description value selected to the project
    QString getDescription();
    /// returns the screen value selected to the project
    QString getScreenSelected();
    /// returns the date value selected to the project
    QDate getDate();
    /// returns the width value selected to the project
    int getWidth();
    /// returns the height value selected to the project
    int getHeight();
    /// sets the descirption value of the GUI
    void setDescription(QString description);
    /// sets the screen selected value of the GUI
    void setScreenSelected(QString selected);
    /// sets the width value of the GUI
    void setWidth(int w);
    /// sets the height value of the GUI
    void setHeight(int h);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NewProject *m_ui;

private slots:
    /// sets enable or not the widht and height \a SipnBoxes (\a enable)
    void setLineButtonEnable(bool enable);

};

#endif // NEWPROJECT_H
