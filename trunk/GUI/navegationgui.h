/*!
*\file GUI/navegationgui.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to set the focus and navigation key of a media.
*/

#ifndef NAVEGATIONGUI_H
#define NAVEGATIONGUI_H

#include <QDialog>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QErrorMessage>
#include "NCL/descriptor.h"


/*!
* \class NavegationGui
* \brief class to set the focus and navigation key of a media.
*/

namespace Ui {
    class NavegationGui;
}

class NavegationGui : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values and create connectors
    explicit NavegationGui(QWidget *parent = 0);
    ~NavegationGui();

    /// returns \a QTableWidget with the focus attributes and the focus indexes
    QTableWidget* getNavigation();

    /// sets the list of medias given in the \a mediaList in to the GUI
    void setMedias(QTableWidget *mediaList);
    /// sets the moves (focus indexes) given in the \a descriptorList in to the GUI
    void setMoves(QList<Descriptor*> descriptorList);

private:
    Ui::NavegationGui *ui;

    QTableWidget *movesTable;
    QTableWidget *mediaTableAux;

    QString button;
    QString media;

    int index;

    QErrorMessage *reply;

    /// returns the media name with the focus index given in the param \a index
    QString getMedia(QString index);
    /// returns the color name with the index in the comboBox given in the param \a index
    QString getColorName(int index);

    /// returns the indexf of the media with name \a media
    int getIndex(QString media);
    /// return the index of the color in the comboBox with name \a color
    int getColorIndex(QString color);

    /// returns the image (QPixmap) of the media with name \a mediaName
    QPixmap getPixmap(QString mediaName);

    /// sets the buttons left, right, up and down enable or disable depending of the \a enable value and \a column value
    void setEnableButtons(int colum,bool enable);

    /// sets focus movement from \a mediaP to \a mediaToMove pressing the button \a column(up=2, down=3, left=4, right=5)
    void setMove(QString mediaP, QString mediaToMove, int column);
    /// reloads the medias table
    void reloadTable();

private slots:
    /// asigns a media to the arrow selected \a move (if have not a assigned media) or change the current media \a move (if have a assigned media)
    void changeToMove(QString move);
    /// called when the upArrow button is pressed in the GUI
    void changeToUp();
    /// called when the downArrow button is pressed in the GUI
    void changeToDown();
    /// called when the leftArrow button is pressed in the GUI
    void changeToLeft();
    /// called when the rightArrow button is pressed in the GUI
    void changeToRight();

    /// delete the media assigned in the button move \a move
    void delMove(QString move);
    /// called when the button "up delete" is pressed in the GUI
    void delUp();
    /// called when the button "down delete" is pressed in the GUI
    void delDown();
    /// called when the button "left delete" is pressed in the GUI
    void delLeft();
    /// called when the button "right delete" is pressed in the GUI
    void delRight();

    /// called when current media change in the table. Set the current media focus configuration in the GUI
    void currentMediaChange(int currenti,int currentj,int previousi,int intpreviousj);

    /// called to select a media to an arrow button
    void selectMedia();
    /// called to cancel the select media to an arrow button
    void cancelMedia();

    /// called to select the focusSrc of the media
    void focusSrc();
    /// called to select the focusSelSrc of the media
    void focusSelSrc();
    /// called set enable or not the focus configuration of the media
    void setFocusEnable(bool enable);
    /// called to save the focus when the current item is changed
    void apllyFocus(int row);
    /// called to save the current media configuration when the windows is closed
    void saveCurrent();

};

#endif // NAVEGATIONGUI_H
