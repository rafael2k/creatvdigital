/*!
*\file GUI/modifysize.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the media size Attributes of the screen configuration.
*/

#ifndef MODIFYSIZE_H
#define MODIFYSIZE_H

#include <QDialog>

/*!
* \class ModifySize
* \brief class to set the media size Attributes of the screen configuration.
*/

namespace Ui {
    class ModifySize;
}

class ModifySize : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI and initialize values
    explicit ModifySize(QWidget *parent = 0);
    ~ModifySize();

    /// returns the Width value selected to the screen
    int getWidth();
    /// returns the Height value selected to the screen
    int getHeight();
    /// initializes the Width value with the current value
    void setWidth(int w);
    /// initializes the Height value with the current value
    void setHeight(int h);

private:
    Ui::ModifySize *ui;
};

#endif // MODIFYSIZE_H
