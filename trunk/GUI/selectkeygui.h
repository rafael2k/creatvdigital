/*!
*\file GUI/selectkeygui.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the button of an interactivity.
*/

#ifndef SELECTKEYGUI_H
#define SELECTKEYGUI_H

#include <QDialog>
#include <QTableWidget>

/*!
* \class SelectKeyGUI
* \brief class to set the button of an interactivity.
*/

namespace Ui {
    class SelectKeyGUI;
}

class SelectKeyGUI : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values and create connectors
    explicit SelectKeyGUI(QWidget *parent = 0);
    ~SelectKeyGUI();

    /// returns the selected button of the GUI
    QString getButton();

private:
    Ui::SelectKeyGUI *ui;
};

#endif // SELECTKEYGUI_H
