/*!
*\file GUI/imagedescriptorattr.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the image Attributes of a media image.
*/

#include "imagedescriptorattr.h"
#include "ui_imagedescriptorattr.h"

/*!
 *\brief creates the GUI
 *\param QWidget* parent
 */
ImageDescriptorAttr::ImageDescriptorAttr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDescriptorAttr)
{
    ui->setupUi(this);
    initialize();
}


/*!
 *\brief destructor of de UI.
 */
ImageDescriptorAttr::~ImageDescriptorAttr()
{
    delete ui;
}


/*!
 *\brief initializes values and create connectors
 *\return void
 */
void ImageDescriptorAttr::initialize()
{
    QButtonGroup *topGroup = new QButtonGroup();
    QButtonGroup *leftGroup = new QButtonGroup();
    QButtonGroup *bottomGroup = new QButtonGroup();
    QButtonGroup *rightGroup = new QButtonGroup();
    QButtonGroup *heightGroup = new QButtonGroup();
    QButtonGroup *widthGroup = new QButtonGroup();

    topGroup->addButton(ui->pxTop);
    topGroup->addButton(ui->percentTop);
    leftGroup->addButton(ui->pxLeft);
    leftGroup->addButton(ui->percentLeft);
    bottomGroup->addButton(ui->pxBottom);
    bottomGroup->addButton(ui->percentBottom);
    rightGroup->addButton(ui->pxRight);
    rightGroup->addButton(ui->percentRight);
    heightGroup->addButton(ui->pxHeight);
    heightGroup->addButton(ui->percentHeight);
    widthGroup->addButton(ui->pxWidth);
    widthGroup->addButton(ui->percentWidth);

    ui->percentTop->setChecked(true);
    ui->percentLeft->setChecked(true);
    ui->percentBottom->setChecked(true);
    ui->percentRight->setChecked(true);
    ui->percentHeight->setChecked(true);
    ui->percentWidth->setChecked(true);

    ui->topSB->setSuffix("%");
    ui->leftSP->setSuffix("%");
    ui->bottomSB->setSuffix("%");
    ui->rightSP->setSuffix("%");
    ui->widthSB->setSuffix("%");
    ui->heightSB->setSuffix("%");

    ui->visibleCB->setChecked(true);

    QColor color0("transparent");
    ui->backgroundCB->insertItem(0,"Sin fondo");
    ui->backgroundCB->setItemData(0, color0, Qt::DecorationRole);

    QColor color("white");
    ui->backgroundCB->insertItem(1,"blanco");
    ui->backgroundCB->setItemData(1, color, Qt::DecorationRole);

    ui->backgroundCB->insertItem(2,"negro");
    QColor color1("black");
    ui->backgroundCB->setItemData(2, color1, Qt::DecorationRole);

    ui->backgroundCB->insertItem(3,"plateado");
    QColor color2("silver");
    ui->backgroundCB->setItemData(3, color2, Qt::DecorationRole);

    ui->backgroundCB->insertItem(4,"gris");
    QColor color3("gray");
    ui->backgroundCB->setItemData(4, color3, Qt::DecorationRole);

    ui->backgroundCB->insertItem(5,"rojo");
    QColor color4("red");
    ui->backgroundCB->setItemData(5, color4, Qt::DecorationRole);

    ui->backgroundCB->insertItem(6,"granate");
    QColor color5("maroon");
    ui->backgroundCB->setItemData(6, color5, Qt::DecorationRole);

    ui->backgroundCB->insertItem(7,"fucsia");
    QColor color6("fuchsia");
    ui->backgroundCB->setItemData(7, color6, Qt::DecorationRole);

    ui->backgroundCB->insertItem(8,"purpura");
    QColor color7("purple");
    ui->backgroundCB->setItemData(8, color7, Qt::DecorationRole);

    ui->backgroundCB->insertItem(9,"lima");
    QColor color8("lime");
    ui->backgroundCB->setItemData(9, color8, Qt::DecorationRole);

    ui->backgroundCB->insertItem(10,"verde");
    QColor color9("green");
    ui->backgroundCB->setItemData(10, color9, Qt::DecorationRole);

    ui->backgroundCB->insertItem(11,"amarillo");
    QColor color10("yellow");
    ui->backgroundCB->setItemData(11, color10, Qt::DecorationRole);

    ui->backgroundCB->insertItem(12,"oliva");
    QColor color11("olive");
    ui->backgroundCB->setItemData(12, color11, Qt::DecorationRole);

    ui->backgroundCB->insertItem(13,"azul");
    QColor color12("blue");
    ui->backgroundCB->setItemData(13, color12, Qt::DecorationRole);

    ui->backgroundCB->insertItem(14,"azul marino");
    QColor color13("navy");
    ui->backgroundCB->setItemData(14, color13, Qt::DecorationRole);

    ui->backgroundCB->insertItem(15,"agua");
    QColor color14("aqua");
    ui->backgroundCB->setItemData(15, color14, Qt::DecorationRole);

    ui->backgroundCB->insertItem(16,"verde azulado");
    QColor color15("teal");
    ui->backgroundCB->setItemData(16, color15, Qt::DecorationRole);

    ui->zIndexSB->setMinimum(0);
    ui->zIndexSB->setMaximum(255);
    ui->zIndexSB->setValue(255);
    ui->transparencySB->setSuffix("%");

    ui->fitCB->addItem("Fill");
    ui->fitCB->addItem("Hidden");
    ui->fitCB->addItem("Meet");
    ui->fitCB->addItem("MeetBest");
    ui->fitCB->addItem("Slice");

    ui->topSB->setMaximum(100);
    ui->leftSP->setMaximum(100);
    ui->bottomSB->setMaximum(100);
    ui->rightSP->setMaximum(100);
    ui->widthSB->setMaximum(100);
    ui->heightSB->setMaximum(100);

    ui->heightSB->setValue(100);
    ui->widthSB->setValue(100);

    connect(ui->pxTop,SIGNAL(clicked()),this,SLOT(changeTopToPx()));
    connect(ui->pxLeft,SIGNAL(clicked()),this,SLOT(changeLeftToPx()));
    connect(ui->pxBottom,SIGNAL(clicked()),this,SLOT(changeBottomToPx()));
    connect(ui->pxRight,SIGNAL(clicked()),this,SLOT(changeRightToPx()));
    connect(ui->pxHeight,SIGNAL(clicked()),this,SLOT(changeHeightToPx()));
    connect(ui->pxWidth,SIGNAL(clicked()),this,SLOT(changeWidthToPx()));

    connect(ui->percentTop,SIGNAL(clicked()),this,SLOT(changeTopToPercentaje()));
    connect(ui->percentLeft,SIGNAL(clicked()),this,SLOT(changeLeftToPercentaje()));
    connect(ui->percentBottom,SIGNAL(clicked()),this,SLOT(changeBottomToPercentaje()));
    connect(ui->percentRight,SIGNAL(clicked()),this,SLOT(changeRightToPercentaje()));
    connect(ui->percentHeight,SIGNAL(clicked()),this,SLOT(changeHeightToPercentaje()));
    connect(ui->percentWidth,SIGNAL(clicked()),this,SLOT(changeWidthToPercentaje()));
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Top
 *\return void
 */
void ImageDescriptorAttr::changeTopToPx()
{
    ui->topSB->setSuffix("Px");
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Left
 *\return void
 */
void ImageDescriptorAttr::changeLeftToPx()
{
    ui->leftSP->setSuffix("Px");
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Bottom
 *\return void
 */
void ImageDescriptorAttr::changeBottomToPx()
{
    ui->bottomSB->setSuffix("Px");
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Right
 *\return void
 */
void ImageDescriptorAttr::changeRightToPx()
{
    ui->rightSP->setSuffix("Px");
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Height
 *\return void
 */
void ImageDescriptorAttr::changeHeightToPx(){

    ui->heightSB->setSuffix("Px");
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Width
 *\return void
 */
void ImageDescriptorAttr::changeWidthToPx()
{
    ui->widthSB->setSuffix("Px");
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Top
 *\return void
 */
void ImageDescriptorAttr::changeTopToPercentaje()
{
    ui->topSB->setSuffix("%");
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Left
 *\return void
 */
void ImageDescriptorAttr::changeLeftToPercentaje()
{
    ui->leftSP->setSuffix("%");
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Bottom
 *\return void
 */
void ImageDescriptorAttr::changeBottomToPercentaje()
{
    ui->bottomSB->setSuffix("%");
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Right
 *\return void
 */
void ImageDescriptorAttr::changeRightToPercentaje()
{
    ui->rightSP->setSuffix("%");
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Height
 *\return void
 */
void ImageDescriptorAttr::changeHeightToPercentaje()
{
    ui->heightSB->setSuffix("%");
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Width
 *\return void
 */
void ImageDescriptorAttr::changeWidthToPercentaje()
{
    ui->widthSB->setSuffix("%");
}


/*!
 *\brief returns the Top value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getTop()
{
    int value = ui->topSB->value();
    QString ret = QString::number(value)+ui->topSB->suffix();
    return ret;
}


/*!
 *\brief returns the Left value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getLeft()
{
    int value = ui->leftSP->value();
    QString ret = QString::number(value)+ui->leftSP->suffix();
    return ret;
}


/*!
 *\brief returns the Bottom value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getBottom()
{
    int value = ui->bottomSB->value();
    QString ret = QString::number(value)+ui->bottomSB->suffix();
    return ret;
}


/*!
 *\brief returns the Right value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getRight()
{
    int value = ui->rightSP->value();
    QString ret = QString::number(value)+ui->rightSP->suffix();
    return ret;
}


/*!
 *\brief returns the Top value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getHeight()
{
    int value = ui->heightSB->value();
    QString ret = QString::number(value)+ui->heightSB->suffix();
    return ret;
}


/*!
 *\brief returns the Width value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getWidth()
{
    int value = ui->widthSB->value();
    QString ret = QString::number(value)+ui->widthSB->suffix();
    return ret;
}


/*!
 *\brief returns the Visible value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getVisible()
{
    QString ret = "true";
    if (ui->visibleCB->isChecked())
        ret = "true";
    else
        ret = "false";
    return ret;
}


/*!
 *\brief returns the zIndex value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getZIndex()
{
    int value = ui->zIndexSB->value();
    QString ret = QString::number(value);
    return ret;
}


/*!
 *\brief returns the Background color value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getBackground()
{
    QString ret = "";
    if(ui->backgroundCB->currentText() == "blanco"){
        ret = "white";
    }

    if(ui->backgroundCB->currentText() == "negro"){
        ret = "black";
    }

    if(ui->backgroundCB->currentText() == "plateado"){
        ret = "silver";
    }

    if(ui->backgroundCB->currentText() == "gris"){
        ret = "gray";
    }

    if(ui->backgroundCB->currentText() == "rojo"){
        ret = "red";
    }

    if(ui->backgroundCB->currentText() == "granate"){
        ret = "maroon";
    }

    if(ui->backgroundCB->currentText() == "fucsia"){
        ret = "fuchsia";
    }

    if(ui->backgroundCB->currentText() == "purpura"){
        ret = "purpura";
    }


    if(ui->backgroundCB->currentText() == "lima"){
        ret = "lime";
    }

    if(ui->backgroundCB->currentText() == "verde"){
        ret = "green";
    }

    if(ui->backgroundCB->currentText() == "amarillo"){
        ret = "yellow";
    }


    if(ui->backgroundCB->currentText() == "oliva"){
        ret = "olive";
    }

    if(ui->backgroundCB->currentText() == "azul"){
        ret = "blue";
    }

    if(ui->backgroundCB->currentText() == "azul marino"){
        ret = "navy";
    }

    if(ui->backgroundCB->currentText() == "agua"){
        ret = "aqua";
    }

    if(ui->backgroundCB->currentText() == "verde azulado"){
        ret = "teal";
    }

    return ret;
}


/*!
 *\brief returns the Transparency value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getTransparency()
{
    int value = ui->transparencySB->value();
    QString ret = QString::number(value)+ui->transparencySB->suffix();
    return ret;
}


/*!
 *\brief returns the Fit value selected to the media
 *\return QString
 */
QString ImageDescriptorAttr::getFit()
{
    QString ret = "Fill";
    if(ui->fitCB->currentText()== "Fill"){
        ret = "fill";
    }

    if(ui->fitCB->currentText()== "Hidden"){
        ret = "hidden";
    }

    if(ui->fitCB->currentText()== "Meet"){
        ret = "meet";
    }

    if(ui->fitCB->currentText()== "MeetBest"){
        ret = "meetBest";
    }

    if(ui->fitCB->currentText()== "Slice"){
        ret = "slice";
    }

    return ret;
}


/*!
 *\brief sets the values given in the \a list in to the GUI of a media selected
 *\param QList<DescriptorParam*> list
 *\return void
 */
void ImageDescriptorAttr::setValues(QList<DescriptorParam*> list)
{
    QString value;
    for(int i = 0; i < list.count();i++){
        if(list.at(i)->getName() == "top"){
            if(list.at(i)->getValue().contains("%")){
                value= list.at(i)->getValue().remove("%");
                ui->percentTop->setChecked(true);
                ui->topSB->setSuffix("%");
            }else{
                value= list.at(i)->getValue().remove("px");
                ui->pxTop->setChecked(true);
                ui->topSB->setSuffix("Px");
            }
            ui->topSB->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "bottom"){
            if(list.at(i)->getValue().contains("%")){
                value= list.at(i)->getValue().remove("%");
                ui->percentBottom->setChecked(true);
                ui->bottomSB->setSuffix("%");
            }else{
                value= list.at(i)->getValue().remove("px");
                ui->pxBottom->setChecked(true);
                ui->bottomSB->setSuffix("Px");
            }
            ui->bottomSB->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "height"){
            if(list.at(i)->getValue().contains("%")){
                value= list.at(i)->getValue().remove("%");
                ui->percentHeight->setChecked(true);
                ui->heightSB->setSuffix("%");
            }else{
                value= list.at(i)->getValue().remove("px");
                ui->pxHeight->setChecked(true);
                ui->heightSB->setSuffix("Px");
            }
            ui->heightSB->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "right"){
            if(list.at(i)->getValue().contains("%")){
                value= list.at(i)->getValue().remove("%");
                ui->percentRight->setChecked(true);
                ui->rightSP->setSuffix("%");
            }else{
                value= list.at(i)->getValue().remove("px");
                ui->pxRight->setChecked(true);
                ui->rightSP->setSuffix("Px");
            }
            ui->rightSP->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "left"){
            if(list.at(i)->getValue().contains("%")){
                value= list.at(i)->getValue().remove("%");
                ui->percentLeft->setChecked(true);
                ui->leftSP->setSuffix("%");
            }else{
                value= list.at(i)->getValue().remove("px");
                ui->pxLeft->setChecked(true);
                ui->leftSP->setSuffix("Px");
            }
            ui->leftSP->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "width"){
            if(list.at(i)->getValue().contains("%")){
                value= list.at(i)->getValue().remove("%");
                ui->percentWidth->setChecked(true);
                ui->widthSB->setSuffix("%");
            }else{
                value= list.at(i)->getValue().remove("px");
                ui->pxWidth->setChecked(true);
                ui->widthSB->setSuffix("Px");
            }
            ui->widthSB->setValue(value.toInt());
        }

        if(list.at(i)->getName() == "visible"){
            ui->visibleCB->setChecked(list.at(i)->getValue() == "true");
        }

        if(list.at(i)->getName() == "zIndex"){
            ui->zIndexSB->setValue(list.at(i)->getValue().toInt());
        }
        if(list.at(i)->getName() == "background"){
            ui->backgroundCB->setCurrentIndex(getBackgroundColorIndex(list.at(i)->getValue()));;
        }

        if(list.at(i)->getName() == "transparency"){

            ui->transparencySB->setValue(list.at(i)->getValue().remove("%").toInt());
        }

        if(list.at(i)->getName() == "fit"){
            ui->fitCB->setCurrentIndex(getFitIndex(list.at(i)->getValue()));
        }
    }
}


/*!
 *\brief returns the index in the comboBox of a \a color
 *\param QString color
 *\return int
 */
int ImageDescriptorAttr::getBackgroundColorIndex(QString color)
{
    int index = -1;
    if (color == "transparent")
        index = 0;

    if (color == "white")
        index = 1;

    if (color == "black")
        index = 2;

    if (color == "silver")
        index = 3;

    if (color == "grey")
        index = 4;

    if (color == "red")
        index = 5;

    if (color == "maroon")
        index = 6;

    if (color == "fuchsia")
        index = 7;

    if (color == "purple")
        index = 8;

    if (color == "lime")
        index = 9;

    if (color == "green")
        index = 10;

    if (color == "yellow")
        index = 11;

    if (color == "olive")
        index = 12;

    if (color == "blue")
        index = 13;

    if (color == "navy")
        index = 14;

    if (color == "aqua")
        index = 15;

    if (color == "teal")
        index = 16;

    return index;
}


/*!
 *\brief returns the index in the comboBox of a \a fit
 *\param QString fit
 *\return int
 */
int ImageDescriptorAttr::getFitIndex(QString fit)
{
    int index = -1;

    if(fit == "fill")
        index = 0;

    if(fit == "hidden")
        index = 1;

    if(fit == "meet")
        index = 2;

    if(fit == "meetBest")
        index = 3;

    if(fit == "slice")
        index = 4;

    return index;
}
