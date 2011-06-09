/*!
*\file GUI/textdescriptoratrr.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the text Attributes of a media text.
*/

#include "textdescriptoratrr.h"
#include "ui_textdescriptoratrr.h"

#include <iostream>

using namespace std;


/*!
 *\brief creates the GUI, initialize values and create connectors
 *\param QWidget* parent
 */
TextDescriptorAtrr::TextDescriptorAtrr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TextDescriptorAtrr)
{
    ui->setupUi(this);

    ui->italicToolButton->setCheckable(true);
    ui->weigthToolButton->setCheckable(true);
    ui->variantToolButton->setCheckable(true);

    ui->italicToolButton->setToolTip("Italica");
    ui->weigthToolButton->setToolTip("Negrita");
    ui->variantToolButton->setToolTip("Mayusculas pequeñas");

    ui->sizeSpinBox->setValue(12);

    QColor color("white");
    ui->colorComboBox->insertItem(0,"blanco");
    ui->colorComboBox->setItemData(0, color, Qt::DecorationRole);

    ui->colorComboBox->insertItem(1,"negro");
    QColor color1("black");
    ui->colorComboBox->setItemData(1, color1, Qt::DecorationRole);

    ui->colorComboBox->insertItem(2,"plateado");
    QColor color2("silver");
    ui->colorComboBox->setItemData(2, color2, Qt::DecorationRole);

    ui->colorComboBox->insertItem(3,"gris");
    QColor color3("gray");
    ui->colorComboBox->setItemData(3, color3, Qt::DecorationRole);

    ui->colorComboBox->insertItem(4,"rojo");
    QColor color4("red");
    ui->colorComboBox->setItemData(4, color4, Qt::DecorationRole);

    ui->colorComboBox->insertItem(5,"granate");
    QColor color5("maroon");
    ui->colorComboBox->setItemData(5, color5, Qt::DecorationRole);

    ui->colorComboBox->insertItem(6,"fucsia");
    QColor color6("fuchsia");
    ui->colorComboBox->setItemData(6, color6, Qt::DecorationRole);

    ui->colorComboBox->insertItem(7,"purpura");
    QColor color7("purple");
    ui->colorComboBox->setItemData(7, color7, Qt::DecorationRole);

    ui->colorComboBox->insertItem(8,"lima");
    QColor color8("lime");
    ui->colorComboBox->setItemData(8, color8, Qt::DecorationRole);

    ui->colorComboBox->insertItem(9,"verde");
    QColor color9("green");
    ui->colorComboBox->setItemData(9, color9, Qt::DecorationRole);

    ui->colorComboBox->insertItem(10,"amarillo");
    QColor color10("yellow");
    ui->colorComboBox->setItemData(10, color10, Qt::DecorationRole);

    ui->colorComboBox->insertItem(11,"oliva");
    QColor color11("olive");
    ui->colorComboBox->setItemData(11, color11, Qt::DecorationRole);

    ui->colorComboBox->insertItem(12,"azul");
    QColor color12("blue");
    ui->colorComboBox->setItemData(12, color12, Qt::DecorationRole);

    ui->colorComboBox->insertItem(13,"azul marino");
    QColor color13("navy");
    ui->colorComboBox->setItemData(13, color13, Qt::DecorationRole);

    ui->colorComboBox->insertItem(14,"agua");
    QColor color14("aqua");
    ui->colorComboBox->setItemData(14, color14, Qt::DecorationRole);

    ui->colorComboBox->insertItem(15,"verde azulado");
    QColor color15("teal");
    ui->colorComboBox->setItemData(15, color15, Qt::DecorationRole);

    ui->scrollComboBox->insertItem(0,"ninguno");
    ui->scrollComboBox->insertItem(1,"horizontal");
    ui->scrollComboBox->insertItem(2,"vertical");
    ui->scrollComboBox->insertItem(3,"ambos");
    ui->scrollComboBox->insertItem(4,"automatico");

    ui->colorComboBox->setCurrentIndex(1);
}

/*!
 *\brief destructor of de UI.
 */
TextDescriptorAtrr::~TextDescriptorAtrr()
{
    delete ui;
}


/*!
 *\brief returns the Scroll value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getScroll()
{
    QString ret =  "ninguno";
    if(ui->scrollComboBox->currentText() == "horizontal"){
        ret = "horizontal";
    }

    if(ui->scrollComboBox->currentText() == "vertical"){
        ret = "vertical";
    }

    if(ui->scrollComboBox->currentText() == "ambos"){
        ret = "both";
    }

    if(ui->scrollComboBox->currentText() == "automatico"){
        ret = "automatic";
    }

    return ui->scrollComboBox->currentText();
}


/*!
 *\brief returns the Font style value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getFontStyle()
{
    QString ret = "normal";
    if(ui->italicToolButton->isChecked())
        ret = "italic";
    return ret;
}


/*!
 *\brief returns the Font color value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getFontColor()
{
    QString ret = "";
    if(ui->colorComboBox->currentText() == "blanco"){
        ret = "white";
    }

    if(ui->colorComboBox->currentText() == "negro"){
        ret = "black";
    }

    if(ui->colorComboBox->currentText() == "plateado"){
        ret = "silver";
    }

    if(ui->colorComboBox->currentText() == "gris"){
        ret = "gray";
    }

    if(ui->colorComboBox->currentText() == "rojo"){
        ret = "red";
    }

    if(ui->colorComboBox->currentText() == "granate"){
        ret = "maroon";
    }

    if(ui->colorComboBox->currentText() == "fucsia"){
        ret = "fuchsia";
    }

    if(ui->colorComboBox->currentText() == "purpura"){
        ret = "purpura";
    }

    if(ui->colorComboBox->currentText() == "lima"){
        ret = "lime";
    }

    if(ui->colorComboBox->currentText() == "verde"){
        ret = "green";
    }

    if(ui->colorComboBox->currentText() == "amarillo"){
        ret = "yellow";
    }

    if(ui->colorComboBox->currentText() == "oliva"){
        ret = "olive";
    }

    if(ui->colorComboBox->currentText() == "azul"){
        ret = "blue";
    }

    if(ui->colorComboBox->currentText() == "azul marino"){
        ret = "navy";
    }

    if(ui->colorComboBox->currentText() == "agua"){
        ret = "aqua";
    }

    if(ui->colorComboBox->currentText() == "verde azulado"){
        ret = "teal";
    }

    return ret;
}


/*!
 *\brief returns the Font family value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getFontFamily()
{
    QStringList values;
    QString ret;
    values = ui->fontComboBox->currentFont().toString().split(",");
    ret = values.at(0);
    return values.at(0);
}


/*!
 *\brief returns the Font size value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getFontSize()
{
    return QString::number(ui->sizeSpinBox->value());
}


/*!
 *\brief returns the Font variant value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getFontVariant()
{
    QString ret = "normal";
    if(ui->variantToolButton->isChecked())
        ret = "small-caps";
    return ret;
}


/*!
 *\brief returns the Font weigth value selected to the media
 *\return QString
 */
QString TextDescriptorAtrr::getFontWeight()
{
    QString ret = "normal";
    if(ui->weigthToolButton->isChecked())
        ret = "bold";
    return ret;
}


/*!
 *\brief sets the values given in the \a list in to the GUI of a media selected
 *\param QList<DescriptorParam*> list
 *\return QString
 */
void TextDescriptorAtrr::setValues(QList<DescriptorParam*> list)
{
    for(int i = 0; i < list.count();i++){
        if(list.at(i)->getName() == "fontFamily"){
            ui->fontComboBox->setCurrentFont(QFont(list.at(i)->getValue()));
        }

        if(list.at(i)->getName() == "fontVariant"){
            ui->variantToolButton->setChecked((list.at(i)->getValue() == "normal") ? false: true);
        }

        if(list.at(i)->getName() == "fontWeight"){
            ui->weigthToolButton->setChecked((list.at(i)->getValue() == "normal") ? false: true);
        }

        if(list.at(i)->getName() == "fontStyle"){
            ui->italicToolButton->setChecked((list.at(i)->getValue() == "normal") ? false: true);
        }

        if(list.at(i)->getName() == "fontSize"){
            ui->sizeSpinBox->setValue(list.at(i)->getValue().toInt());
        }

        if(list.at(i)->getName() == "fontColor"){
            ui->colorComboBox->setCurrentIndex(getFontColorIndex(list.at(i)->getValue()));
        }

        if(list.at(i)->getName() == "scroll"){
             ui->scrollComboBox->setCurrentIndex(getScrollIndex(list.at(i)->getValue()));
        }
    }
}


/*!
 *\brief returns the index of the comboBox of the \a color given
 *\param QString color
 *\return int
 */
int TextDescriptorAtrr::getFontColorIndex(QString color)
{
    int index = -1;
    if (color == "white")
        index = 0;

    if (color == "black")
        index = 1;

    if (color == "silver")
        index = 2;

    if (color == "gray")
        index = 3;

    if (color == "red")
        index = 4;

    if (color == "maroon")
        index = 5;

    if (color == "fuchsia")
        index = 6;

    if (color == "purple")
        index = 7;

    if (color == "lime")
        index = 8;

    if (color == "green")
        index = 9;

    if (color == "yellow")
        index = 10;

    if (color == "olive")
        index = 11;

    if (color == "blue")
        index = 12;

    if (color == "navy")
        index = 13;

    if (color == "aqua")
        index = 14;

    if (color == "teal")
        index = 15;

    return index;
}


/*!
 *\brief returns the index of the comboBox of the \a scroll given
 *\param QString scroll
 *\return int
 */
int TextDescriptorAtrr::getScrollIndex(QString scroll)
{
    int index = -1;

    if(scroll == "none")
        index = 0;

    if(scroll == "horizontal")
        index = 1;

    if(scroll == "vertical")
        index = 2;

    if(scroll == "both")
        index = 3;

    if(scroll == "automatic")
        index = 4;

    return index;
}
