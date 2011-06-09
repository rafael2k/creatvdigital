/*!
*\file GUI/setattributesgui.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the media Attributes when an event ocurrs.
*/

#include "setattributesgui.h"
#include "ui_setattributesgui.h"
#include "iostream"

using namespace std;


/*!
 *\brief creates the GUI, initialize values and create connectors
 *\param QWidget* parent
 */
SetAttributesGUI::SetAttributesGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetAttributesGUI)
{
    ui->setupUi(this);

    mediasList = new QTableWidget();
    mediasList->setColumnCount(2);

    attributes = new QTableWidget();
    attributes->setColumnCount(3);

    /************************************************/

    ui->volumeDial->setMinimum(0);
    ui->volumeDial->setMaximum(100);
    ui->balanceSlider->setMinimum(0);
    ui->balanceSlider->setMaximum(100);
    ui->trebleDial->setMinimum(0);
    ui->trebleDial->setMaximum(100);
    ui->bassDial->setMinimum(0);
    ui->bassDial->setMaximum(100);

    ui->volumeSpinBox->setMaximum(100);
    ui->balanceSpinBox->setMaximum(100);
    ui->trebleSpinBox->setMaximum(100);
    ui->bassSpinBox->setMaximum(100);

    ui->volumeDial->setValue(100);
    ui->volumeSpinBox->setValue(100);
    ui->balanceSlider->setValue(50);
    ui->balanceSpinBox->setValue(50);
    ui->trebleDial->setValue(50);
    ui->trebleSpinBox->setValue(50);
    ui->bassDial->setValue(50);
    ui->bassSpinBox->setValue(50);

    connect(ui->volumeDial,SIGNAL(valueChanged(int)),ui->volumeSpinBox,SLOT(setValue(int)));
    connect(ui->volumeSpinBox,SIGNAL(valueChanged(int)),ui->volumeDial,SLOT(setValue(int)));

    connect(ui->balanceSlider,SIGNAL(valueChanged(int)),ui->balanceSpinBox,SLOT(setValue(int)));
    connect(ui->balanceSpinBox,SIGNAL(valueChanged(int)),ui->balanceSlider,SLOT(setValue(int)));

    connect(ui->trebleDial,SIGNAL(valueChanged(int)),ui->trebleSpinBox,SLOT(setValue(int)));
    connect(ui->trebleSpinBox,SIGNAL(valueChanged(int)),ui->trebleDial,SLOT(setValue(int)));

    connect(ui->bassDial,SIGNAL(valueChanged(int)),ui->bassSpinBox,SLOT(setValue(int)));
    connect(ui->bassSpinBox,SIGNAL(valueChanged(int)),ui->bassDial,SLOT(setValue(int)));

    /************************************************/

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

    ui->fitCB->addItem("fill");
    ui->fitCB->addItem("hidden");
    ui->fitCB->addItem("meet");
    ui->fitCB->addItem("meetBest");
    ui->fitCB->addItem("slice");

    ui->topSB->setMaximum(500);
    ui->leftSP->setMaximum(500);
    ui->bottomSB->setMaximum(500);
    ui->rightSP->setMaximum(500);
    ui->widthSB->setMaximum(500);
    ui->heightSB->setMaximum(500);

    ui->topSB->setValue(0);
    ui->leftSP->setValue(0);
    ui->bottomSB->setValue(0);
    ui->rightSP->setValue(0);
    ui->widthSB->setValue(100);
    ui->heightSB->setValue(100);

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

    /******************************************/

    ui->italicToolButton_2->setCheckable(true);
    ui->weigthToolButton_2->setCheckable(true);
    ui->variantToolButton_2->setCheckable(true);

    ui->italicToolButton_2->setToolTip("Italica");
    ui->weigthToolButton_2->setToolTip("Negrita");
    ui->variantToolButton_2->setToolTip("Mayusculas pequeñas");

    ui->sizeSpinBox_2->setValue(12);

    ui->colorComboBox_2->insertItem(0,"blanco");
    ui->colorComboBox_2->setItemData(0, color, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(1,"negro");
    ui->colorComboBox_2->setItemData(1, color1, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(2,"plateado");
    ui->colorComboBox_2->setItemData(2, color2, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(3,"gris");
    ui->colorComboBox_2->setItemData(3, color3, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(4,"rojo");
    ui->colorComboBox_2->setItemData(4, color4, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(5,"granate");
    ui->colorComboBox_2->setItemData(5, color5, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(6,"fucsia");
    ui->colorComboBox_2->setItemData(6, color6, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(7,"purpura");
    ui->colorComboBox_2->setItemData(7, color7, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(8,"lima");
    ui->colorComboBox_2->setItemData(8, color8, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(9,"verde");
    ui->colorComboBox_2->setItemData(9, color9, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(10,"amarillo");
    ui->colorComboBox_2->setItemData(10, color10, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(11,"oliva");
    ui->colorComboBox_2->setItemData(11, color11, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(12,"azul");
    ui->colorComboBox_2->setItemData(12, color12, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(13,"azul marino");
    ui->colorComboBox_2->setItemData(13, color13, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(14,"agua");
    ui->colorComboBox_2->setItemData(14, color14, Qt::DecorationRole);
    ui->colorComboBox_2->insertItem(15,"verde azulado");
    ui->colorComboBox_2->setItemData(15, color15, Qt::DecorationRole);
    ui->colorComboBox_2->setCurrentIndex(1);

    ui->scrollComboBox_2->insertItem(0,"ninguno");
    ui->scrollComboBox_2->insertItem(1,"horizontal");
    ui->scrollComboBox_2->insertItem(2,"vertical");
    ui->scrollComboBox_2->insertItem(3,"ambos");
    ui->scrollComboBox_2->insertItem(4,"automatico");

    /*********************************************/

    ui->tabWidget->setTabEnabled(0,false);
    ui->tabWidget->setTabEnabled(1,false);
    ui->tabWidget->setTabEnabled(2,false);

    connect(ui->listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(saveChanges(QListWidgetItem*,QListWidgetItem*)));

    connect(ui->topRadioButton,SIGNAL(toggled(bool)),this,SLOT(setTopEnable(bool)));
    connect(ui->leftRadioButton,SIGNAL(toggled(bool)),this,SLOT(setLeftEnable(bool)));
    connect(ui->bottomRadioButton,SIGNAL(toggled(bool)),this,SLOT(setBottomtEnable(bool)));
    connect(ui->rightRadioButton,SIGNAL(toggled(bool)),this,SLOT(setRightEnable(bool)));
    connect(ui->heightRadioButton,SIGNAL(toggled(bool)),this,SLOT(setHeightEnable(bool)));
    connect(ui->widthRadioButton,SIGNAL(toggled(bool)),this,SLOT(setWidthEnable(bool)));
    connect(ui->visibleRadioButton,SIGNAL(toggled(bool)),this,SLOT(setVisibleEnable(bool)));
    connect(ui->zIndexRadioButton,SIGNAL(toggled(bool)),this,SLOT(setZIndexEnable(bool)));
    connect(ui->backgroundRadioButton,SIGNAL(toggled(bool)),this,SLOT(setBackgroundEnable(bool)));
    connect(ui->trnsparencyRadioButton,SIGNAL(toggled(bool)),this,SLOT(setTransparencyEnable(bool)));
    connect(ui->fitRadioButton,SIGNAL(toggled(bool)),this,SLOT(setFitEnable(bool)));

    connect(ui->volumeRadioButton,SIGNAL(toggled(bool)),this,SLOT(setVolumeEnable(bool)));
    connect(ui->bassRadioButton,SIGNAL(toggled(bool)),this,SLOT(setBassEnable(bool)));
    connect(ui->trebleRadioButton,SIGNAL(toggled(bool)),this,SLOT(setTrebleEnable(bool)));
    connect(ui->balanceRadioButton,SIGNAL(toggled(bool)),this,SLOT(setBalanceEnable(bool)));

    connect(ui->fontRadioButton,SIGNAL(toggled(bool)),this,SLOT(setFontEnable(bool)));
    connect(ui->stylesRadioButton,SIGNAL(toggled(bool)),this,SLOT(setStyleFontEnable(bool)));
    connect(ui->sizeFontRadioButton,SIGNAL(toggled(bool)),this,SLOT(setSizeEnable(bool)));
    connect(ui->colorFontRadioButton,SIGNAL(toggled(bool)),this,SLOT(setColorFontEnable(bool)));
    connect(ui->scrollRadioButton,SIGNAL(toggled(bool)),this,SLOT(setScrollEnable(bool)));

    connect(this,SIGNAL(accepted()),this,SLOT(saveCurrentMedia()));

    initRadioButtons();
}


/*!
 *\brief destructor of de UI.
 */
SetAttributesGUI::~SetAttributesGUI()
{
    delete ui;
}


/*!
 *\brief adds the list of medias given in \a \allMedias. \allMedias is used to obtain the media type
 *\param QTableWidget *list
 *\param QStringList setMediasList
 *\return void
 */
void SetAttributesGUI::setList(QTableWidget *list, QStringList setMediasList)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    QString mediaName;
    int k= 0;
    ui->listWidget->addItems(setMediasList);
    mediasList->setRowCount(setMediasList.size());

    for(int i = 0; i < list->rowCount(); i++){
        for(int j = 0; j < setMediasList.size(); j++){
           mediaName = list->item(i,0)->text();
            if(mediaName==setMediasList.at(j)){
                item = new QTableWidgetItem();
                item->setText(setMediasList.at(j));

                mediasList->setItem(k,0,item);
                item = new QTableWidgetItem();
                item->setText(list->item(i,3)->text());
                mediasList->setItem(k,1,item);
                k++;
            }
        }
    }
    ui->listWidget->setCurrentRow(0);
}


/*!
 *\brief returns the volume value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getVolume()
{
    return QString::number(ui->volumeDial->value());
}


/*!
 *\brief returns the volume balance selected to the media
 *\return QString
 */
QString SetAttributesGUI::getBalance()
{
    return QString::number(ui->balanceSlider->value());
}


/*!
 *\brief returns the treble value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getTreble()
{
    return QString::number(ui->trebleDial->value());
}


/*!
 *\brief returns the bass value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getBass()
{
    return QString::number(ui->bassDial->value());
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Top
 *\return QString
 */
void SetAttributesGUI::changeTopToPx()
{
    ui->topSB->setSuffix("Px");
    ui->topSB->setMaximum(2000);
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Left
 *\return void
 */
void SetAttributesGUI::changeLeftToPx()
{
    ui->leftSP->setSuffix("Px");
    ui->leftSP->setMaximum(2000);
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Bottom
 *\return void
 */
void SetAttributesGUI::changeBottomToPx()
{
    ui->bottomSB->setSuffix("Px");
    ui->bottomSB->setMaximum(2000);
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Right
 *\return void
 */
void SetAttributesGUI::changeRightToPx()
{
    ui->rightSP->setSuffix("Px");
    ui->rightSP->setMaximum(2000);
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Height
 *\return void
 */
void SetAttributesGUI::changeHeightToPx()
{
    ui->heightSB->setSuffix("Px");
    ui->heightSB->setMaximum(1080);
}


/*!
 *\brief changes the suffix "%" to "Px" in the comboBox Width
 *\return void
 */
void SetAttributesGUI::changeWidthToPx()
{
    ui->widthSB->setSuffix("Px");
    ui->widthSB->setMaximum(1920);
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Top
 *\return void
 */
void SetAttributesGUI::changeTopToPercentaje()
{
    ui->topSB->setSuffix("%");
    ui->topSB->setMaximum(100);
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Left
 *\return void
 */
void SetAttributesGUI::changeLeftToPercentaje(){
    ui->leftSP->setSuffix("%");
    ui->leftSP->setMaximum(100);
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Bottom
 *\return void
 */
void SetAttributesGUI::changeBottomToPercentaje()
{
    ui->bottomSB->setSuffix("%");
    ui->bottomSB->setMaximum(100);
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Right
 *\return void
 */
void SetAttributesGUI::changeRightToPercentaje()
{
    ui->rightSP->setSuffix("%");
    ui->rightSP->setMaximum(100);
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Height
 *\return void
 */
void SetAttributesGUI::changeHeightToPercentaje()
{

    ui->heightSB->setSuffix("%");
    ui->heightSB->setMaximum(100);
}


/*!
 *\brief changes the suffix "Px" to "%" in the comboBox Width
 *\return void
 */
void SetAttributesGUI::changeWidthToPercentaje()
{
    ui->widthSB->setSuffix("%");
    ui->widthSB->setMaximum(100);
}


/*!
 *\brief returns the Top value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getTop()
{
    int value = ui->topSB->value();
    QString ret = QString::number(value)+ui->topSB->suffix();
    return ret;
}


/*!
 *\brief returns the Left value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getLeft()
{
    int value = ui->leftSP->value();
    QString ret = QString::number(value)+ui->leftSP->suffix();
    return ret;
}


/*!
 *\brief returns the Bottom value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getBottom()
{
    int value = ui->bottomSB->value();
    QString ret = QString::number(value)+ui->bottomSB->suffix();
    return ret;
}


/*!
 *\brief returns the Right value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getRight()
{
    int value = ui->rightSP->value();
    QString ret = QString::number(value)+ui->rightSP->suffix();
    return ret;
}


/*!
 *\brief returns the Height value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getHeight()
{
    int value = ui->heightSB->value();
    QString ret = QString::number(value)+ui->heightSB->suffix();
    return ret;
}


/*!
 *\brief returns the Width value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getWidth()
{
    int value = ui->widthSB->value();
    QString ret = QString::number(value)+ui->widthSB->suffix();
    return ret;
}


/*!
 *\brief returns the Visible value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getVisible()
{
    QString ret = "true";
    if (ui->visibleCB->isChecked())
        ret = "true";
    else
        ret = "false";
    return ret;
}


/*!
 *\brief returns the Top zIndex selected to the media
 *\return QString
 */
QString SetAttributesGUI::getZIndex()
{
    int value = ui->zIndexSB->value();
    QString ret = QString::number(value);
    return ret;
}


/*!
 *\brief returns the Background value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getBackground()
{
    return ui->backgroundCB->currentText();
}


/*!
 *\brief returns the Transparency value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getTransparency()
{
    int value = ui->transparencySB->value();
    QString ret = QString::number(value)+ui->transparencySB->suffix();
    return ret;
}


/*!
 *\brief returns the Fit value selected to the media
 *\return QString
 */
QString SetAttributesGUI::getFit()
{
    return ui->fitCB->currentText();
}


/*!
 *\brief returns the type of the media \a mediaName
 *\param QString mediaName
 *\return QString
 */
QString SetAttributesGUI::getMediaType(QString mediaName)
{
    QString nameMedia;
    QString typeMedia;
    for(int i = 0; i < mediasList->rowCount();i++){
        nameMedia = mediasList->item(i,0)->text();
        if(mediaName == nameMedia){
            typeMedia = mediasList->item(i,1)->text();
            break;
        }
    }
    return typeMedia;
}


/*!
 *\brief returns the table with the media name (colum = 0), the attribute name (colum = 1) and the value (column = 2)
 *\return QTableWidget
 */
QTableWidget* SetAttributesGUI::getAttributes()
{
    return attributes;
}


/*!
 *\brief called to save the media attributes when the current item is changed
 *\param QListWidgetItem* current
 *\param QListWidgetItem* previous
 *\return void
 */
void SetAttributesGUI::saveChanges(QListWidgetItem* current,QListWidgetItem* previous)
{
    if(getMediaType(ui->listWidget->currentItem()->text()) == "Video"){
        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,false);
    }else if(getMediaType(ui->listWidget->currentItem()->text()) == "Audio"){
        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,false);
    }else if(getMediaType(ui->listWidget->currentItem()->text()) == "Imagen"){
        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,false);
    }else if(getMediaType(ui->listWidget->currentItem()->text()) == "Texto"){
        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,true);
    }

    if(previous != NULL)
        savePrevious(previous);
    loadCurrent(current);
}


/*!
 *\brief load the configuration of attributes of the current media
 *\param QListWidgetItem* current
 *\return void
 */
void SetAttributesGUI::loadCurrent(QListWidgetItem* current)
{
    initRadioButtons();
    QString value;
    for(int i = 0; i < attributes->rowCount();i++){
        if(attributes->item(i,0)->text() == current->text()){
            if(attributes->item(i,1)->text() == "top"){

                if(attributes->item(i,2)->text().contains("%")){
                    value= attributes->item(i,2)->text().remove("%");
                    ui->percentTop->setChecked(true);
                    ui->topSB->setSuffix("%");
                }else{
                    value= attributes->item(i,2)->text().remove("px");
                    ui->pxTop->setChecked(true);
                    ui->topSB->setSuffix("Px");
                }
                ui->topSB->setValue(value.toInt());
                setTopEnable(true);
            }

            if(attributes->item(i,1)->text() == "left"){
                if(attributes->item(i,2)->text().contains("%")){
                    value= attributes->item(i,2)->text().remove("%");
                    ui->percentLeft->setChecked(true);
                    ui->leftSP->setSuffix("%");
                }else{
                    value= attributes->item(i,2)->text().remove("px");
                    ui->pxLeft->setChecked(true);
                    ui->leftSP->setSuffix("Px");
                }
                ui->leftSP->setValue(value.toInt());
                setLeftEnable(true);
            }

            if(attributes->item(i,1)->text() == "bottom"){
                if(attributes->item(i,2)->text().contains("%")){
                    value= attributes->item(i,2)->text().remove("%");
                    ui->percentBottom->setChecked(true);
                    ui->bottomSB->setSuffix("%");
                }else{
                    value= attributes->item(i,2)->text().remove("px");
                    ui->pxBottom->setChecked(true);
                    ui->bottomSB->setSuffix("Px");
                }
                ui->bottomSB->setValue(value.toInt());
                setBottomtEnable(true);
            }
            if(attributes->item(i,1)->text() == "right"){
                if(attributes->item(i,2)->text().contains("%")){
                    value= attributes->item(i,2)->text().remove("%");
                    ui->percentRight->setChecked(true);
                    ui->rightSP->setSuffix("%");
                }else{
                    value= attributes->item(i,2)->text().remove("px");
                    ui->pxRight->setChecked(true);
                    ui->rightSP->setSuffix("Px");
                }
                ui->rightSP->setValue(value.toInt());
                setRightEnable(true);
            }

            if(attributes->item(i,1)->text() == "height"){
                if(attributes->item(i,2)->text().contains("%")){
                    value= attributes->item(i,2)->text().remove("%");
                    ui->percentHeight->setChecked(true);
                    ui->heightSB->setSuffix("%");
                }else{
                    value= attributes->item(i,2)->text().remove("px");
                    ui->pxHeight->setChecked(true);
                    ui->heightSB->setSuffix("Px");
                }
                ui->heightSB->setValue(value.toInt());
                setHeightEnable(true);
            }

            if(attributes->item(i,1)->text() == "width"){
                if(attributes->item(i,2)->text().contains("%")){
                    value= attributes->item(i,2)->text().remove("%");
                    ui->percentWidth->setChecked(true);
                    ui->widthSB->setSuffix("%");
                }else{
                    value= attributes->item(i,2)->text().remove("px");
                    ui->pxWidth->setChecked(true);
                    ui->widthSB->setSuffix("Px");
                }
                ui->widthSB->setValue(value.toInt());
                setWidthEnable(true);
            }

            if(attributes->item(i,1)->text() == "visible"){
                ui->visibleCB->setChecked((attributes->item(i,2)->text() == "true")?true:false);
                setVisibleEnable(true);

            }

            if(attributes->item(i,1)->text() == "background"){
                ui->backgroundCB->setCurrentIndex(getBackgroundColorIndex(attributes->item(i,2)->text()));
                setBackgroundEnable(true);
            }

            if(attributes->item(i,1)->text() == "zIndex"){
                ui->zIndexSB->setValue(attributes->item(i,2)->text().toInt());
                setZIndexEnable(true);
            }

            if(attributes->item(i,1)->text() == "transparency"){
                ui->transparencySB->setValue(attributes->item(i,2)->text().remove("%").toInt());
                setTransparencyEnable(true);
            }

            if(attributes->item(i,1)->text() == "fit"){
                ui->fitCB->setCurrentIndex(getFitIndex(attributes->item(i,2)->text()));
                setFitEnable(true);
            }

            if(attributes->item(i,1)->text() == "soundLevel"){
                ui->volumeSpinBox->setValue(attributes->item(i,2)->text().toFloat()*100);
                setVolumeEnable(true);
            }

            if(attributes->item(i,1)->text() == "bassLevel"){
                ui->bassRadioButton->setChecked(true);
                ui->bassSpinBox->setValue(attributes->item(i,2)->text().toFloat()*100);
                setBassEnable(true);
            }

            if(attributes->item(i,1)->text() == "trebleLevel"){
                ui->trebleSpinBox->setValue(attributes->item(i,2)->text().toFloat()*100);
                setTrebleEnable(true);
            }

            if(attributes->item(i,1)->text() == "balanceLevel"){
                ui->balanceSpinBox->setValue((attributes->item(i,2)->text().toFloat()*100));
                setBalanceEnable(true);
            }
            if(attributes->item(i,1)->text() == "fontFamily"){
                ui->fontComboBox_2->setCurrentFont(QFont(attributes->item(i,2)->text()));
                setFontEnable(true);
            }

            if(attributes->item(i,1)->text() == "fontVariant"){
                ui->stylesRadioButton->setChecked(true);
                ui->variantToolButton_2->setChecked((attributes->item(i,2)->text() == "normal") ? false: true);
                setStyleFontEnable(true);
            }

            if(attributes->item(i,1)->text() == "fontWeight"){
                ui->stylesRadioButton->setChecked(true);
                ui->weigthToolButton_2->setChecked((attributes->item(i,2)->text() == "normal") ? false: true);
                setStyleFontEnable(true);
            }

            if(attributes->item(i,1)->text() == "fontStyle"){
                ui->stylesRadioButton->setChecked(true);
                ui->italicToolButton_2->setChecked((attributes->item(i,2)->text() == "normal") ? false: true);
                setStyleFontEnable(true);
            }

            if(attributes->item(i,1)->text() == "fontSize"){
                ui->sizeFontRadioButton->setChecked(true);
                ui->sizeSpinBox_2->setValue(attributes->item(i,2)->text().toInt());
                setSizeEnable(true);
            }
            if(attributes->item(i,1)->text() == "fontColor"){
                ui->colorComboBox_2->setCurrentIndex(getFontColorIndex(attributes->item(i,2)->text()));
                setColorFontEnable(true);
            }

            if(attributes->item(i,1)->text() == "scroll"){
                ui->scrollComboBox_2->setCurrentIndex(getScrollIndex(attributes->item(i,2)->text()));
                setScrollEnable(true);
            }
        }
    }
}


/*!
 *\brief returns the index in the comboBox of a background \a color
 *\param QString color
 *\return int
 */
int SetAttributesGUI::getBackgroundColorIndex(QString color)
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

    if (color == "gray")
        index = 4;

    if (color == "red")
        index = 5;

    if (color == "maroon")
        index = 6;

    if (color == "fucsia")
        index = 7;

    if (color == "purple")
        index = 8;

    if (color == "lima")
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
 *\brief returns the index in the comboBox of a font \a color
 *\param QString color
 *\return int
 */
int SetAttributesGUI::getFontColorIndex(QString color)
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

    if (color == "fucsia")
        index = 6;

    if (color == "purple")
        index = 7;

    if (color == "lima")
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
 *\brief returns the index in the comboBox of a \a fit
 *\param QString fit
 *\return int
 */
int SetAttributesGUI::getFitIndex(QString fit)
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


/*!
 *\brief returns the index in the comboBox of a \a scroll
 *\param QString scroll
 *\return int
 */
int SetAttributesGUI::getScrollIndex(QString scroll)
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


/*!
 *\brief saves the previos media selected (\a previous) configuration of attributes
 *\param QListWidgetItem* previous
 *\return void
 */
void SetAttributesGUI::savePrevious(QListWidgetItem* previous)
{
        if(ui->topRadioButton->isChecked())
            addAttribute(previous->text(),"top",QString::number(ui->topSB->value())+(ui->pxTop->isChecked()?"px":"%") );
        else
            removeAttribute(previous->text(),"top");

        if(ui->leftRadioButton->isChecked())
            addAttribute(previous->text(),"left",QString::number(ui->leftSP->value())+(ui->pxLeft->isChecked()?"px":"%"));
        else
            removeAttribute(previous->text(),"left");

        if(ui->bottomRadioButton->isChecked())
            addAttribute(previous->text(),"bottom",QString::number(ui->bottomSB->value())+(ui->pxBottom->isChecked()?"px":"%"));
        else
            removeAttribute(previous->text(),"bottom");

        if(ui->rightRadioButton->isChecked())
            addAttribute(previous->text(),"right",QString::number(ui->rightSP->value())+(ui->pxRight->isChecked()?"px":"%"));
        else
            removeAttribute(previous->text(),"right");

        if(ui->widthRadioButton->isChecked())
            addAttribute(previous->text(),"width",QString::number(ui->widthSB->value())+(ui->pxWidth->isChecked()?"px":"%"));
        else
            removeAttribute(previous->text(),"width");

        if(ui->heightRadioButton->isChecked())
            addAttribute(previous->text(),"height",QString::number(ui->heightSB->value())+(ui->pxHeight->isChecked()?"px":"%"));
        else
            removeAttribute(previous->text(),"height");

        if(ui->visibleRadioButton->isChecked())
            addAttribute(previous->text(),"visible",(ui->visibleCB->isChecked())?"true":"false");
        else
            removeAttribute(previous->text(),"visible");

        if(ui->backgroundRadioButton->isChecked())
            addAttribute(previous->text(),"background",getBackgroundColorName(ui->backgroundCB->currentIndex()));
        else
            removeAttribute(previous->text(),"background");

        if(ui->zIndexRadioButton->isChecked())
            addAttribute(previous->text(),"zIndex",QString::number(ui->zIndexSB->value()));
        else
            removeAttribute(previous->text(),"zIndex");

        if(ui->trnsparencyRadioButton->isChecked())
            addAttribute(previous->text(),"transparency",QString::number(ui->transparencySB->value())+"%");
        else
            removeAttribute(previous->text(),"transparency");

        if(ui->fitRadioButton->isChecked())
            addAttribute(previous->text(),"fit",ui->fitCB->currentText());
        else
            removeAttribute(previous->text(),"fit");

        if(ui->volumeRadioButton->isChecked())
            addAttribute(previous->text(),"soundLevel",QString::number(((qreal)ui->volumeSpinBox->value())/100.0));
        else
            removeAttribute(previous->text(),"soundLevel");

        if(ui->bassRadioButton->isChecked())
            addAttribute(previous->text(),"bassLevel",QString::number((qreal)ui->bassSpinBox->value()/100.0));
        else
            removeAttribute(previous->text(),"bassLevel");

        if(ui->trebleRadioButton->isChecked())
            addAttribute(previous->text(),"trebleLevel",QString::number((qreal)ui->trebleSpinBox->value()/100.0));
        else
            removeAttribute(previous->text(),"trebleLevel");

        if(ui->balanceRadioButton->isChecked())
            addAttribute(previous->text(),"balanceLevel",QString::number((qreal)ui->balanceSpinBox->value()/100.0));
        else
            removeAttribute(previous->text(),"balanceLevel");

        if(ui->fontRadioButton->isChecked())
            addAttribute(previous->text(),"fontFamily",ui->fontComboBox_2->currentFont().family());
        else
            removeAttribute(previous->text(),"fontFamily");

        if(ui->stylesRadioButton->isChecked()){
            addAttribute(previous->text(),"fontVariant",(ui->variantToolButton_2->isChecked())?"small-caps":"normal");
            addAttribute(previous->text(),"fontWeight",(ui->weigthToolButton_2->isChecked())?"bold":"normal");
            addAttribute(previous->text(),"fontStyle",(ui->italicToolButton_2->isChecked())?"italic":"normal");
        }else{
            removeAttribute(previous->text(),"fontVariant");
            removeAttribute(previous->text(),"fontWeight");
            removeAttribute(previous->text(),"fontStyle");
        }

        if(ui->sizeFontRadioButton->isChecked())
            addAttribute(previous->text(),"fontSize",QString::number(ui->sizeSpinBox_2->value()));
        else
            removeAttribute(previous->text(),"fontSize");

        if(ui->colorFontRadioButton->isChecked())
            addAttribute(previous->text(),"fontColor",getFontColorName(ui->colorComboBox_2->currentIndex()));
        else
            removeAttribute(previous->text(),"fontColor");

        if(ui->scrollRadioButton->isChecked())
            addAttribute(previous->text(),"scroll",getScrollName(ui->scrollComboBox_2->currentIndex()));
        else
            removeAttribute(previous->text(),"scroll");
}


/*!
 *\brief returns the Background name color selected to the media
 *\param int index
 *\return QString
 */
QString SetAttributesGUI::getBackgroundColorName(int index)
{
    QString color = "";
    switch(index){
        case 0 :
            color = "transparent";
            break;
        case 1 :
            color = "white";
            break;
        case 2 :
            color = "black";
            break;
        case 3 :
            color = "silver";
            break;
        case 4 :
            color = "gray";
            break;
        case 5 :
            color = "red";
            break;
        case 6 :
            color = "maroon";
            break;
        case 7 :
            color = "fucsia";
            break;
        case 8 :
            color = "purple";
            break;
        case 9 :
            color = "lima";
            break;
        case 10 :
            color = "green";
            break;
        case 11 :
            color = "yellow";
            break;
        case 12 :
            color = "olive";
            break;
        case 13 :
            color = "blue";
            break;
        case 14 :
            color = "navy";
            break;
        case 15 :
            color = "aqua";
            break;
        case 16 :
            color = "teal";
            break;
    }

    return color;
}


/*!
 *\brief returns the Font name color selected to the media
 *\param int index
 *\return QString
 */
QString SetAttributesGUI::getFontColorName(int index)
{
    QString color = "";
    switch(index) {
        case 0 :
            color = "white";
            break;
        case 1 :
            color = "black";
            break;
        case 2 :
            color = "silver";
            break;
        case 3 :
            color = "gray";
            break;
        case 4 :
            color = "red";
            break;
        case 5 :
            color = "maroon";
            break;
        case 6 :
            color = "fucsia";
            break;
        case 7 :
            color = "purple";
            break;
        case 8 :
            color = "lima";
            break;
        case 9 :
            color = "green";
            break;
        case 10 :
            color = "yellow";
            break;
        case 11 :
            color = "olive";
            break;
        case 12 :
            color = "blue";
            break;
        case 13 :
            color = "navy";
            break;
        case 14 :
            color = "aqua";
            break;
        case 15 :
            color = "teal";
            break;
    }
    return color;
}


/*!
 *\brief returns the Scroll name selected to the media
 *\param int index
 *\return QString
 */
QString SetAttributesGUI::getScrollName(int index)
{
    QString scroll = "";
    switch(index){
        case 0 :
            scroll = "none";
            break;
        case 1 :
            scroll = "horizontal";
            break;
        case 2 :
            scroll = "vertical";
            break;
        case 3 :
            scroll = "both";
            break;
        case 4 :
            scroll = "automatic";
            break;
    }
    return scroll;
}


/*!
 *\brief add the media \a with the attributte \a attribute and the value \a value to de list of attributes
 *\param QString media
 *\param QString attribute
 *\param QString value
 *\return void
 */
void SetAttributesGUI::addAttribute(QString media,QString attribute, QString value)
{
    bool attrib = false;
    for(int i = 0 ; i < attributes->rowCount(); i++){
        if(media == attributes->item(i,0)->text() && attribute == attributes->item(i,1)->text()){
            attributes->item(i,2)->setText(value);
            attrib = true;
            break;
        }
    }
    if(!attrib){
        attributes->insertRow(0);
        item = new QTableWidgetItem();
        item->setText(media);
        attributes->setItem(0,0,item);

        item = new QTableWidgetItem();
        item->setText(attribute);
        attributes->setItem(0,1,item);

        item = new QTableWidgetItem();
        item->setText(value);
        attributes->setItem(0,2,item);

        attributes->sortByColumn(0);
    }
}


/*!
 *\brief removes the attribute \a attribute of the media \a media to the list of attributes
 *\param QString media
 *\param QString attribute
 *\return void
 */
void SetAttributesGUI::removeAttribute(QString media,QString attribute)
{
    for(int i = 0 ; i < attributes->rowCount(); i++){
        if(media == attributes->item(i,0)->text() && attribute == attributes->item(i,1)->text()){
            attributes->removeRow(i);
            break;
        }
    }
}


/*!
 *\brief initializes the radio buttons disables
 *\return void
 */
void SetAttributesGUI::initRadioButtons()
{
    /** Image **/
    setTopEnable(false);
    setLeftEnable(false);
    setBottomtEnable(false);
    setRightEnable(false);
    setHeightEnable(false);
    setWidthEnable(false);

    setVisibleEnable(false);
    setZIndexEnable(false);
    setBackgroundEnable(false);
    setTransparencyEnable(false);
    setFitEnable(false);

    /** Audio **/
    setVolumeEnable(false);
    setBassEnable(false);
    setTrebleEnable(false);
    setBalanceEnable(false);

    /** Texto **/
    setFontEnable(false);
    setStyleFontEnable(false);
    setSizeEnable(false);
    setColorFontEnable(false);
    setScrollEnable(false);
}


/*!
 *\brief sets the top values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setTopEnable(bool b)
{
    ui->topSB->setEnabled(b);
    ui->pxTop->setEnabled(b);
    ui->percentTop->setEnabled(b);

    ui->topRadioButton->setChecked(b);
}


/*!
 *\brief sets the left values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setLeftEnable(bool b)
{
    ui->leftSP->setEnabled(b);
    ui->pxLeft->setEnabled(b);
    ui->percentLeft->setEnabled(b);

    ui->leftRadioButton->setChecked(b);
}


/*!
 *\brief sets the bottom values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setBottomtEnable(bool b)
{
    ui->bottomSB->setEnabled(b);
    ui->pxBottom->setEnabled(b);
    ui->percentBottom->setEnabled(b);

    ui->bottomRadioButton->setChecked(b);
}


/*!
 *\brief sets the right values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setRightEnable(bool b)
{
    ui->rightSP->setEnabled(b);
    ui->pxRight->setEnabled(b);
    ui->percentRight->setEnabled(b);

    ui->rightRadioButton->setChecked(b);
}


/*!
 *\brief sets the height values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setHeightEnable(bool b)
{
    ui->heightSB->setEnabled(b);
    ui->pxHeight->setEnabled(b);
    ui->percentHeight->setEnabled(b);

    ui->heightRadioButton->setChecked(b);
}


/*!
 *\brief sets the width values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setWidthEnable(bool b)
{
    ui->widthSB->setEnabled(b);
    ui->pxWidth->setEnabled(b);
    ui->percentWidth->setEnabled(b);

    ui->widthRadioButton->setChecked(b);
}


/*!
 *\brief sets the visible value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setVisibleEnable(bool b)
{
    ui->visibleCB->setEnabled(b);
    ui->visibleRadioButton->setChecked(b);
}


/*!
 *\brief sets the zIndex value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setZIndexEnable(bool b)
{
    ui->zIndexSB->setEnabled(b);
    ui->zIndexRadioButton->setChecked(b);
}


/*!
 *\brief sets the background value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setBackgroundEnable(bool b)
{
    ui->backgroundCB->setEnabled(b);
    ui->backgroundRadioButton->setChecked(b);
}


/*!
 *\brief sets the transparency value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setTransparencyEnable(bool b)
{
   ui->transparencySB->setEnabled(b);
   ui->trnsparencyRadioButton->setChecked(b);
}


/*!
 *\brief sets the fit values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setFitEnable(bool b)
{
   ui->fitCB->setEnabled(b);
   ui->fitRadioButton->setChecked(b);
}


/*!
 *\brief sets the volume values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setVolumeEnable(bool b)
{
    ui->volumeDial->setEnabled(b);
    ui->volumeSpinBox->setEnabled(b);
    ui->volumeRadioButton->setChecked(b);
}


/*!
 *\brief sets the bass values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setBassEnable(bool b)
{
    ui->bassDial->setEnabled(b);
    ui->bassSpinBox->setEnabled(b);
    ui->bassRadioButton->setChecked(b);
}


/*!
 *\brief sets the treble values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setTrebleEnable(bool b)
{
    ui->trebleDial->setEnabled(b);
    ui->trebleSpinBox->setEnabled(b);
    ui->trebleRadioButton->setChecked(b);
}


/*!
 *\brief sets the balance values enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setBalanceEnable(bool b)
{
    ui->balanceSlider->setEnabled(b);
    ui->balanceSpinBox->setEnabled(b);
    ui->balanceRadioButton->setChecked(b);
}


/*!
 *\brief sets the font value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setFontEnable(bool b)
{
    ui->fontComboBox_2->setEnabled(b);
    ui->fontRadioButton->setChecked(b);
}


/*!
 *\brief sets the style value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setStyleFontEnable(bool b)
{
    ui->italicToolButton_2->setEnabled(b);
    ui->weigthToolButton_2->setEnabled(b);
    ui->variantToolButton_2->setEnabled(b);
    ui->stylesRadioButton->setChecked(b);
}


/*!
 *\brief sets the size value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setSizeEnable(bool b)
{
    ui->sizeSpinBox_2->setEnabled(b);
    ui->sizeFontRadioButton->setChecked(b);
}


/*!
 *\brief sets the font color value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setColorFontEnable(bool b)
{
   ui->colorComboBox_2->setEnabled(b);
   ui->colorFontRadioButton->setChecked(b);
}


/*!
 *\brief sets the scroll value enabled or not (\a b)
 *\param bool b
 *\return void
 */
void SetAttributesGUI::setScrollEnable(bool b)
{
   ui->scrollComboBox_2->setEnabled(b);
   ui->scrollRadioButton->setChecked(b);
}


/*!
 *\brief called to save the current media attributes when the window is closed
 *\return void
 */
void SetAttributesGUI::saveCurrentMedia()
{
    if(getMediaType(ui->listWidget->currentItem()->text()) == "Video"){
        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,false);
    }else if(getMediaType(ui->listWidget->currentItem()->text()) == "Audio"){
        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,false);
    }else if(getMediaType(ui->listWidget->currentItem()->text()) == "Imagen"){
        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,false);
    }else if(getMediaType(ui->listWidget->currentItem()->text()) == "Texto"){
        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,true);
    }
    savePrevious(ui->listWidget->currentItem());
}


/*!
 *\brief initializes the attributtes table with the values of \a table
 *\param QTableWidget *table
 *\return void
 */
void SetAttributesGUI::setAttributtesList(QTableWidget *table)
{
    QTableWidgetItem *item;
    attributes->setRowCount(table->rowCount());
    for(int i = 0; i<table->rowCount();i++){
        item = new QTableWidgetItem();
        item->setText(table->item(i,0)->text());
        attributes->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setText(table->item(i,1)->text());
        attributes->setItem(i,1,item);

        item = new QTableWidgetItem();
        item->setText(table->item(i,2)->text());
        attributes->setItem(i,2,item);
    }
    loadCurrent(ui->listWidget->item(0));
}
