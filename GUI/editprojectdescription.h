/*!
*\file GUI/editprojectdescription.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the project Attributes.
*/

#ifndef EDITPROJECTDESCRIPTION_H
#define EDITPROJECTDESCRIPTION_H

#include <QDialog>
#include <QDate>

/*!
* \class EditProjectDescription
* \brief class to set the project Attributes.
*/

namespace Ui {
    class EditProjectDescription;
}

class EditProjectDescription : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values with the params (\a projectName,\a projectName,\a projectDate) and create connectors
    explicit EditProjectDescription(QString projectName,QString projectDescription,QDate projectDate,QWidget *parent = 0);
    ~EditProjectDescription();

    /// returns the Name value selected to the project
    QString getName();
    /// returns the Description value selected to the project
    QString getDescription();
    /// returns the Date value selected to the project
    QDate getDate();

private:
    Ui::EditProjectDescription *ui;
};

#endif // EDITPROJECTDESCRIPTION_H
