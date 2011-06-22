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
*\file GUI/navegationgui.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implemention to set the focus and navigation key of a media.
*/

#include "navegationgui.h"
#include "ui_navegationgui.h"


/*!
 *\brief creates the GUI, initialize values and create connectors
 *\param QWidget* parent
 */
NavegationGui::NavegationGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NavegationGui)
{
    ui->setupUi(this);

    index = 0;

    ui->selectButton->hide();
    ui->cancelButton->hide();

    ui->upButton->setIconSize(QSize(40,40));
    ui->upButton->setToolTip("Agregar Media");
    ui->upButton->setIcon(QIcon("icons/navegation grey/arrow-up.png"));

    ui->downButton->setIconSize(QSize(40,40));
    ui->downButton->setToolTip("Agregar Media");
    ui->downButton->setIcon(QIcon("icons/navegation grey/arrow-down.png"));

    ui->leftButton->setIconSize(QSize(40,40));
    ui->leftButton->setToolTip("Agregar Media");
    ui->leftButton->setIcon(QIcon("icons/navegation grey/arrow-left.png"));

    ui->rightButton->setIconSize(QSize(40,40));
    ui->rightButton->setToolTip("Agregar Media");
    ui->rightButton->setIcon(QIcon("icons/navegation grey/arrow-right.png"));

    ui->delUpButton->setIconSize(QSize(25,25));
    ui->delUpButton->setToolTip("Eliminar");
    ui->delUpButton->setIcon(QIcon("icons/DeleteRed.png"));

    ui->delDownButton->setIconSize(QSize(25,25));
    ui->delDownButton->setToolTip("Eliminar");
    ui->delDownButton->setIcon(QIcon("icons/DeleteRed.png"));

    ui->delLefButton->setIconSize(QSize(25,25));
    ui->delLefButton->setToolTip("Eliminar");
    ui->delLefButton->setIcon(QIcon("icons/DeleteRed.png"));

    ui->delRightButton->setIconSize(QSize(25,25));
    ui->delRightButton->setToolTip("Eliminar");
    ui->delRightButton->setIcon(QIcon("icons/DeleteRed.png"));

    ui->mediaButton->setIconSize(QSize(90,90));

    ui->upButton->setAutoRaise(true);
    ui->downButton->setAutoRaise(true);
    ui->leftButton->setAutoRaise(true);
    ui->rightButton->setAutoRaise(true);

    ui->delUpButton->setAutoRaise(true);
    ui->delDownButton->setAutoRaise(true);
    ui->delLefButton->setAutoRaise(true);
    ui->delRightButton->setAutoRaise(true);

    ui->delUpButton->setEnabled(false);
    ui->delDownButton->setEnabled(false);
    ui->delLefButton->setEnabled(false);
    ui->delRightButton->setEnabled(false);

    ui->mediaButton->setAutoRaise(true);
    ui->mediaLayout->setAlignment(Qt::AlignCenter);

    ui->mediaTable->setColumnCount(2);

    movesTable = new QTableWidget();
    movesTable->setColumnCount(12);

    mediaTableAux = new QTableWidget();
    mediaTableAux->setColumnCount(3);

    QStringList columnas = QStringList();
    columnas.append("Media");
    columnas.append("Tipo");
    ui->mediaTable->setHorizontalHeaderLabels(columnas);

    ui->upLabel->setPixmap(QPixmap("icons/noMedia.png"));
    ui->upLabel->setScaledContents(true);
    ui->downlLabel->setPixmap(QPixmap("icons/noMedia.png"));
    ui->downlLabel->setScaledContents(true);
    ui->leftLabel->setPixmap(QPixmap("icons/noMedia.png"));
    ui->leftLabel->setScaledContents(true);
    ui->rightLabel->setPixmap(QPixmap("icons/noMedia.png"));
    ui->rightLabel->setScaledContents(true);

    QColor color("white");
    ui->focusBorderColor->insertItem(0,"blanco");
    ui->focusBorderColor->setItemData(0, color, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(1,"negro");
    QColor color1("black");
    ui->focusBorderColor->setItemData(1, color1, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(2,"plateado");
    QColor color2("silver");
    ui->focusBorderColor->setItemData(2, color2, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(3,"gris");
    QColor color3("gray");
    ui->focusBorderColor->setItemData(3, color3, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(4,"rojo");
    QColor color4("red");
    ui->focusBorderColor->setItemData(4, color4, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(5,"granate");
    QColor color5("maroon");
    ui->focusBorderColor->setItemData(5, color5, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(6,"fucsia");
    QColor color6("fuchsia");
    ui->focusBorderColor->setItemData(6, color6, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(7,"purpura");
    QColor color7("purple");
    ui->focusBorderColor->setItemData(7, color7, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(8,"lima");
    QColor color8("lime");
    ui->focusBorderColor->setItemData(8, color8, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(9,"verde");
    QColor color9("green");
    ui->focusBorderColor->setItemData(9, color9, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(10,"amarillo");
    QColor color10("yellow");
    ui->focusBorderColor->setItemData(10, color10, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(11,"oliva");
    QColor color11("olive");
    ui->focusBorderColor->setItemData(11, color11, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(12,"azul");
    QColor color12("blue");
    ui->focusBorderColor->setItemData(12, color12, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(13,"azul marino");
    QColor color13("navy");
    ui->focusBorderColor->setItemData(13, color13, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(14,"agua");
    QColor color14("aqua");
    ui->focusBorderColor->setItemData(14, color14, Qt::DecorationRole);

    ui->focusBorderColor->insertItem(15,"verde azulado");
    QColor color15("teal");
    ui->focusBorderColor->setItemData(15, color15, Qt::DecorationRole);

    ui->selBorderColor->insertItem(0,"blanco");
    ui->selBorderColor->setItemData(0, color, Qt::DecorationRole);

    ui->selBorderColor->insertItem(1,"negro");
    ui->selBorderColor->setItemData(1, color1, Qt::DecorationRole);

    ui->selBorderColor->insertItem(2,"plateado");
    ui->selBorderColor->setItemData(2, color2, Qt::DecorationRole);

    ui->selBorderColor->insertItem(3,"gris");
    ui->selBorderColor->setItemData(3, color3, Qt::DecorationRole);

    ui->selBorderColor->insertItem(4,"rojo");
    ui->selBorderColor->setItemData(4, color4, Qt::DecorationRole);

    ui->selBorderColor->insertItem(5,"granate");
    ui->selBorderColor->setItemData(5, color5, Qt::DecorationRole);

    ui->selBorderColor->insertItem(6,"fucsia");
    ui->selBorderColor->setItemData(6, color6, Qt::DecorationRole);

    ui->selBorderColor->insertItem(7,"purpura");
    ui->selBorderColor->setItemData(7, color7, Qt::DecorationRole);

    ui->selBorderColor->insertItem(8,"lima");
    ui->selBorderColor->setItemData(8, color8, Qt::DecorationRole);

    ui->selBorderColor->insertItem(9,"verde");
    ui->selBorderColor->setItemData(9, color9, Qt::DecorationRole);

    ui->selBorderColor->insertItem(10,"amarillo");
    ui->selBorderColor->setItemData(10, color10, Qt::DecorationRole);

    ui->selBorderColor->insertItem(11,"oliva");
    ui->selBorderColor->setItemData(11, color11, Qt::DecorationRole);

    ui->selBorderColor->insertItem(12,"azul");
    ui->selBorderColor->setItemData(12, color12, Qt::DecorationRole);

    ui->selBorderColor->insertItem(13,"azul marino");
    ui->selBorderColor->setItemData(13, color13, Qt::DecorationRole);

    ui->selBorderColor->insertItem(14,"agua");
    ui->selBorderColor->setItemData(14, color14, Qt::DecorationRole);

    ui->selBorderColor->insertItem(15,"verde azulado");
    ui->selBorderColor->setItemData(15, color15, Qt::DecorationRole);

    ui->focusBorderWidth->setSuffix("Px");
    ui->focusBorderWidth->setMinimum(-100);
    ui->focusBorderWidth->setMaximum(100);
    ui->focusBorderWidth->setValue(2);
    ui->focusBorderTransparency->setSuffix("%");
    ui->focusBorderTransparency->setMinimum(0);
    ui->focusBorderTransparency->setMaximum(100);

    ui->focusSrc->setReadOnly(true);
    ui->focusSelSrc->setReadOnly(true);

    ui->checkBox->setEnabled(false);

    this->setFocusEnable(false);

    reply = new QErrorMessage(this);

    connect(ui->upButton,SIGNAL(clicked()),this,SLOT(changeToUp()));
    connect(ui->downButton,SIGNAL(clicked()),this,SLOT(changeToDown()));
    connect(ui->leftButton,SIGNAL(clicked()),this,SLOT(changeToLeft()));
    connect(ui->rightButton,SIGNAL(clicked()),this,SLOT(changeToRight()));
    connect(ui->delUpButton,SIGNAL(clicked()),this,SLOT(delUp()));
    connect(ui->delDownButton,SIGNAL(clicked()),this,SLOT(delDown()));
    connect(ui->delLefButton,SIGNAL(clicked()),this,SLOT(delLeft()));
    connect(ui->delRightButton,SIGNAL(clicked()),this,SLOT(delRight()));
    connect(ui->selectButton,SIGNAL(clicked()),this,SLOT(selectMedia()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(cancelMedia()));
    connect(ui->focusSrcButton,SIGNAL(clicked()),this,SLOT(focusSrc()));
    connect(ui->focusSelSrcButton,SIGNAL(clicked()),this,SLOT(focusSelSrc()));
    connect(ui->mediaTable,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(currentMediaChange(int,int,int,int)));
    connect(ui->checkBox,SIGNAL(toggled(bool)),this,SLOT(setFocusEnable(bool)));
    connect(this,SIGNAL(accepted()),this,SLOT(saveCurrent()));
}


/*!
 *\brief destructor of de UI.
 */
NavegationGui::~NavegationGui()
{
    delete ui;
}


/*!
 *\brief sets the list of medias given in the \a mediaList in to the GUI
 *\param QTableWidget *mediaList
 *\return void
 */
void NavegationGui::setMedias(QTableWidget *mediaList)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    QString mediaName;
    ui->mediaTable->setRowCount(mediaList->rowCount());
    mediaTableAux->setRowCount(mediaList->rowCount());

    for(int i = 0; i < ui->mediaTable->rowCount(); i++){
        mediaName = mediaList->item(i,0)->text();

        item = new QTableWidgetItem();
        item->setText(mediaName);
        item->setIcon(mediaList->item(i,0)->icon());
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ui->mediaTable->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setText(mediaList->item(i,3)->text());
        ui->mediaTable->setItem(i,1,item);

        item = new QTableWidgetItem();
        item->setText(mediaName);
        item->setIcon(mediaList->item(i,0)->icon());
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        mediaTableAux->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        item->setText(mediaList->item(i,3)->text());
        mediaTableAux->setItem(i,2,item);
    }

    if(ui->mediaTable->rowCount()>= 1){
        ui->mediaTable->setCurrentCell(0,0);
    }
}


/*!
 *\brief reloads the medias table
 *\return void
 */
void NavegationGui::reloadTable()
{
    QString mediaName;
    QTableWidgetItem* item = new QTableWidgetItem();
    ui->mediaTable->setRowCount(mediaTableAux->rowCount());
    for(int i = 0; i < ui->mediaTable->rowCount(); i++){
        mediaName = mediaTableAux->item(i,0)->text();

        item = new QTableWidgetItem();
        item->setText(mediaName);
        item->setIcon(mediaTableAux->item(i,0)->icon());
        ui->mediaTable->setItem(i,0,item);

        item = new QTableWidgetItem();
        item->setText(mediaTableAux->item(i,2)->text());
        ui->mediaTable->setItem(i,1,item);
    }

    for (int i = 0; i < ui->mediaTable->rowCount(); i++){
        if(ui->mediaTable->item(i,0)->text() == ui->mediaButton->text()){
            ui->mediaTable->setCurrentCell(i,0);
        }
    }
}


/*!
 *\brief asigns a media to the arrow selected \a move (if have not a assigned media) or change the current media \a move (if have a assigned media)
 *\param QString move
 *\return void
 */
void NavegationGui::changeToMove(QString move)
{
    QString mediaName;
    bool indexFound = false;
    int column;
    media = ui->mediaButton->text();

    if(move=="up"){
        button = "up";
        column = 2;
    }
    if(move=="down"){
        button = "down";
        column = 3;
    }
    if(move=="left"){
        button = "left";
        column = 4;
    }
    if(move=="right"){
        button = "right";
        column = 5;
    }

    if(ui->mediaTable->currentRow()!=-1){
        for(int i = 0; i < movesTable->rowCount();i++){
            if(movesTable->item(i,0)->text() == ui->mediaTable->item(ui->mediaTable->currentRow(),0)->text()){
                if(movesTable->item(i,column) != NULL){
                    if(movesTable->item(i,column)->text() != ""){
                        for(int j=0;j<ui->mediaTable->rowCount();j++){
                            if(ui->mediaTable->item(j,0)->text()==getMedia(movesTable->item(i,column)->text())){
                                ui->mediaTable->setCurrentCell(j,0);
                                currentMediaChange(j,0,ui->mediaTable->currentRow(),0);
                                indexFound = true;
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }

        if(!indexFound){
            if(ui->mediaTable->rowCount() != 1){
                reply->showMessage(tr("Seleccione un Media en la tabla para asignar al boton"));
                ui->selectButton->show();
                ui->cancelButton->show();
                setEnableButtons(column,false);
                ui->mediaTable->removeRow(ui->mediaTable->currentRow());
                QColor color = QColor(11,2,0,28);
                for(int i = 0; i < ui->mediaTable->rowCount();i++){
                    ui->mediaTable->item(i,0)->setBackgroundColor(color);
                    ui->mediaTable->item(i,1)->setBackgroundColor(color);
                }
            }else{
                QMessageBox::StandardButton reply;
                reply = QMessageBox::information(this, tr("Seleccionar Media"), "Debe haber mas de un media para poder asignar proximo foco");
            }
        }
    }
}


/*!
 *\brief sets the buttons left, right, up and down enable or disable depending of the \a enable value and \a column value
 *\param int column
 *\param bool enable
 *\return void
 */
void NavegationGui::setEnableButtons(int column,bool enable)
{
    ui->checkBox->setEnabled(enable);
    if(ui->checkBox->isChecked())
        setFocusEnable(enable);
    if(column == 2){
        ui->downButton->setEnabled(enable);
        ui->leftButton->setEnabled(enable);
        ui->rightButton->setEnabled(enable);
    }

    if(column == 3){
        ui->upButton->setEnabled(enable);
        ui->leftButton->setEnabled(enable);
        ui->rightButton->setEnabled(enable);

    }

    if(column == 4){
        ui->upButton->setEnabled(enable);
        ui->downButton->setEnabled(enable);
        ui->rightButton->setEnabled(enable);
    }

    if(column == 5){
        ui->upButton->setEnabled(enable);
        ui->downButton->setEnabled(enable);
        ui->leftButton->setEnabled(enable);
    }
}


/*!
 *\brief called when the upArrow button is pressed in the GUI
 *\return void
 */
void NavegationGui::changeToUp()
{
    changeToMove("up");
}


/*!
 *\brief called when the downArrow button is pressed in the GUI
 *\return void
 */
void NavegationGui::changeToDown()
{
    changeToMove("down");
}


/*!
 *\brief called when the leftArrow button is pressed in the GUI
 *\return void
 */
void NavegationGui::changeToLeft(){
    changeToMove("left");
}


/*!
 *\brief called when the rightArrow button is pressed in the GUI
 *\return void
 */
void NavegationGui::changeToRight(){
    changeToMove("right");
}


/*!
 *\brief delete the media assigned in the button move \a move
 *\param QString move
 *\return void
 */
void NavegationGui::delMove(QString move)
{
    int column;
    if(move=="up")
        column = 2;
    if(move=="down")
        column = 3;
    if(move=="left")
        column = 4;
    if(move=="right")
        column = 5;

    for(int i = 0; i<movesTable->rowCount();i++){
        if(movesTable->item(i,0)->text() == ui->mediaButton->text()){
            movesTable->item(i,column)->setText("");
            if(column==2){
                ui->delUpButton->setEnabled(false);
                ui->upButton->setIcon(QIcon("icons/navegation grey/arrow-up.png"));
                ui->upButton->setToolTip("Agregar Media");

                ui->upLabel->setPixmap(QPixmap("icons/noMedia.png"));
            }
            if(column==3){
                ui->delDownButton->setEnabled(false);
                ui->downButton->setIcon(QIcon("icons/navegation grey/arrow-down.png"));
                ui->downButton->setToolTip("Agregar Media");

                ui->downlLabel->setPixmap(QPixmap("icons/noMedia.png"));
            }
            if(column==4){
                ui->delLefButton->setEnabled(false);
                ui->leftButton->setIcon(QIcon("icons/navegation grey/arrow-left.png"));
                ui->leftButton->setToolTip("Agregar Media");

                ui->leftLabel->setPixmap(QPixmap("icons/noMedia.png"));
            }
            if(column==5){
                ui->delRightButton->setEnabled(false);
                ui->rightButton->setIcon(QIcon("icons/navegation grey/arrow-right.png"));
                ui->rightButton->setToolTip("Agregar Media");

                ui->rightLabel->setPixmap(QPixmap("icons/noMedia.png"));
            }
            break;
        }
    }
}


/*!
 *\brief called when the button "up delete" is pressed in the GUI
 *\return void
 */
void NavegationGui::delUp()
{
    delMove("up");
}


/*!
 *\brief called when the button "down delete" is pressed in the GUI
 *\return void
 */
void NavegationGui::delDown()
{
    delMove("down");
}


/*!
 *\brief called when the button "left delete" is pressed in the GUI
 *\return void
 */
void NavegationGui::delLeft()
{
    delMove("left");
}


/*!
 *\brief called when the button "right delete" is pressed in the GUI
 *\return void
 */
void NavegationGui::delRight()
{
    delMove("right");
}


/*!
 *\brief called when current media change in the table. Set the current media focus configuration in the GUI
 *\param int currenti
 *\param int currentj
 *\param int previousi
 *\param int previousj
 *\return void
 */
void NavegationGui::currentMediaChange(int currenti,int currentj,int previousi,int previousj)
{
    currentj = 0;
    previousj = 0;
    if(previousi != -1){
        if(previousi != currenti){
            if(ui->selectButton->isHidden()){
                apllyFocus(previousi);
                ui->mediaButton->setIcon(ui->mediaTable->item(currenti,0)->icon());
                ui->mediaButton->setText(ui->mediaTable->item(currenti,0)->text());

                if(getIndex(ui->mediaTable->item(currenti,0)->text()) != -1){
                    ui->checkBox->setChecked(true);
                    for(int i = 0 ; i<movesTable->rowCount();i++){
                        if(ui->mediaTable->item(currenti,0)->text() == movesTable->item(i,0)->text()){
                            if(movesTable->item(i,2)->text() != ""){
                                ui->upButton->setIcon(QIcon("icons/navegation orange/arrow-up.png"));
                                ui->upButton->setToolTip(getMedia(movesTable->item(i,2)->text()));
                                ui->delUpButton->setEnabled(true);

                                ui->upLabel->setPixmap(getPixmap(getMedia(movesTable->item(i,2)->text())));

                            }else{
                                ui->upButton->setIcon(QIcon("icons/navegation grey/arrow-up.png"));
                                ui->upButton->setToolTip("Agregar Media");
                                ui->delUpButton->setEnabled(false);

                                ui->upLabel->setPixmap(QPixmap("icons/noMedia.png"));

                            }

                            if(movesTable->item(i,3)->text() != ""){
                                ui->downButton->setIcon(QIcon("icons/navegation orange/arrow-down.png"));
                                ui->downButton->setToolTip(getMedia(movesTable->item(i,3)->text()));
                                ui->delDownButton->setEnabled(true);

                                ui->downlLabel->setPixmap(getPixmap(getMedia(movesTable->item(i,3)->text())));
                            }else{
                                ui->downButton->setIcon(QIcon("icons/navegation grey/arrow-down.png"));
                                ui->downButton->setToolTip("Agregar Media");
                                ui->delDownButton->setEnabled(false);

                                ui->downlLabel->setPixmap(QPixmap("icons/noMedia.png"));
                            }

                            if(movesTable->item(i,4)->text() != ""){
                                ui->leftButton->setIcon(QIcon("icons/navegation orange/arrow-left.png"));
                                ui->leftButton->setToolTip(getMedia(movesTable->item(i,4)->text()));
                                ui->delLefButton->setEnabled(true);

                                ui->leftLabel->setPixmap(getPixmap(getMedia(movesTable->item(i,4)->text())));
                            }else{
                                ui->leftButton->setIcon(QIcon("icons/navegation grey/arrow-left.png"));
                                ui->leftButton->setToolTip("Agregar Media");
                                ui->delLefButton->setEnabled(false);

                                ui->leftLabel->setPixmap(QPixmap("icons/noMedia.png"));
                            }

                            if(movesTable->item(i,5)->text() != ""){
                                ui->rightButton->setIcon(QIcon("icons/navegation orange/arrow-right.png"));
                                ui->rightButton->setToolTip(getMedia(movesTable->item(i,5)->text()));
                                ui->delRightButton->setEnabled(true);

                                ui->rightLabel->setPixmap(getPixmap(getMedia(movesTable->item(i,5)->text())));
                            }else{
                                ui->rightButton->setIcon(QIcon("icons/navegation grey/arrow-right.png"));
                                ui->rightButton->setToolTip("Agregar Media");
                                ui->delRightButton->setEnabled(false);

                                ui->rightLabel->setPixmap(QPixmap("icons/noMedia.png"));
                            }

                            if(movesTable->item(i,6)->text() != ""){
                                ui->focusBorderColor->setCurrentIndex(getColorIndex(movesTable->item(i,6)->text()));
                                ui->selBorderColor->setCurrentIndex(getColorIndex(movesTable->item(i,7)->text()));
                                ui->focusBorderWidth->setValue(movesTable->item(i,8)->text().toInt());
                                ui->focusBorderTransparency->setValue(movesTable->item(i,9)->text().toInt());
                                ui->focusSrc->setText(movesTable->item(i,10)->text());
                                ui->focusSelSrc->setText(movesTable->item(i,11)->text());
                            }
                        }
                    }

                }else{
                    ui->upButton->setIcon(QIcon("icons/navegation grey/arrow-up.png"));
                    ui->downButton->setIcon(QIcon("icons/navegation grey/arrow-down.png"));
                    ui->leftButton->setIcon(QIcon("icons/navegation grey/arrow-left.png"));
                    ui->rightButton->setIcon(QIcon("icons/navegation grey/arrow-right.png"));
                    ui->upButton->setToolTip("Agregar Media");
                    ui->downButton->setToolTip("Agregar Media");
                    ui->leftButton->setToolTip("Agregar Media");
                    ui->rightButton->setToolTip("Agregar Media");

                    ui->delUpButton->setEnabled(false);
                    ui->delDownButton->setEnabled(false);
                    ui->delLefButton->setEnabled(false);
                    ui->delRightButton->setEnabled(false);

                    ui->upLabel->setPixmap(QPixmap("icons/noMedia.png"));
                    ui->downlLabel->setPixmap(QPixmap("icons/noMedia.png"));
                    ui->leftLabel->setPixmap(QPixmap("icons/noMedia.png"));
                    ui->rightLabel->setPixmap(QPixmap("icons/noMedia.png"));

                    ui->checkBox->setChecked(false);
                }
            }else{
                if(ui->upButton->isEnabled()){
                    ui->upLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
                }
                if(ui->downButton->isEnabled()){
                    ui->downlLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
                }
                if(ui->leftButton->isEnabled()){
                    ui->leftLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
                }
                if(ui->rightButton->isEnabled()){
                    ui->rightLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
                }
            }
        }
    }else{
        ui->mediaButton->setIcon(ui->mediaTable->item(currenti,0)->icon());
        ui->mediaButton->setText(ui->mediaTable->item(currenti,0)->text());
        ui->checkBox->setEnabled(true);
    }
}



/*!
 *\brief returns the indexf of the media with name \a media
 *\param QString media
 *\return int
 */
int NavegationGui::getIndex(QString media)
{
    int ret = -1;
    for(int i=0 ; i < movesTable->rowCount();i++){
        if(movesTable->item(i,0)->text() == media){
            ret = movesTable->item(i,1)->text().toInt();
            break;
        }
    }
    return ret;
}


/*!
 *\brief returns the media name with the focus index given in the param \a index
 *\param QString index
 *\return Qstring
 */
QString NavegationGui::getMedia(QString index)
{
    QString ret = "";
    for(int i=0 ; i < movesTable->rowCount();i++){
        if(movesTable->item(i,1)->text() == index){
            ret = movesTable->item(i,0)->text();
            break;
        }
    }
    return ret;
}


/*!
 *\brief called to select a media to an arrow button
 *\return void
 */
void NavegationGui::selectMedia()
{
    int column;
    if(ui->mediaTable->currentRow() != -1){
        if(ui->upButton->isEnabled()){
            ui->upButton->setIcon(QIcon("icons/navegation orange/arrow-up.png"));
            ui->upButton->setToolTip(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->text());
            ui->delUpButton->setEnabled(true);

            ui->upLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
            column = 2;
        }
        if(ui->downButton->isEnabled()){
            ui->downButton->setIcon(QIcon("icons/navegation orange/arrow-down.png"));
            ui->downButton->setToolTip(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->text());
            ui->delDownButton->setEnabled(true);

            ui->downlLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
            column = 3;
        }
        if(ui->leftButton->isEnabled()){
            ui->leftButton->setIcon(QIcon("icons/navegation orange/arrow-left.png"));
            ui->leftButton->setToolTip(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->text());
            ui->delLefButton->setEnabled(true);

            ui->leftLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
            column = 4;
        }
        if(ui->rightButton->isEnabled()){
            ui->rightButton->setIcon(QIcon("icons/navegation orange/arrow-right.png"));
            ui->rightButton->setToolTip(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->text());
            ui->delRightButton->setEnabled(true);

            ui->rightLabel->setPixmap(ui->mediaTable->item(ui->mediaTable->currentRow(),0)->icon().pixmap(70,70,QIcon::Normal));
            column = 5;
        }

        this->setMove(media,ui->mediaTable->item(ui->mediaTable->currentRow(),0)->text(),column);

        setEnableButtons(column,true);
        QColor color = QColor("white");
        for(int i = 0; i < ui->mediaTable->rowCount();i++){
            ui->mediaTable->item(i,0)->setBackgroundColor(color);
            ui->mediaTable->item(i,1)->setBackgroundColor(color);
        }

        ui->mediaTable->blockSignals(true);
        for(int i = 0;i<ui->mediaTable->rowCount();i++){
            if(ui->mediaTable->item(i,0)->text() == media){
                ui->mediaTable->setCurrentCell(i,0);
                break;
            }
        }

        this->reloadTable();

        ui->mediaTable->blockSignals(false);
        ui->selectButton->hide();
        ui->cancelButton->hide();
    }
}


/*!
 *\brief called to cancel the select media to an arrow button
 *\return void
 */
void NavegationGui::cancelMedia()
{
    int column;
    if(ui->upButton->isEnabled()){

        column = 2;
    }
    if(ui->downButton->isEnabled()){

        column = 3;
    }
    if(ui->leftButton->isEnabled()){

        column = 4;
    }
    if(ui->rightButton->isEnabled()){

        column = 5;
    }
    setEnableButtons(column,true);

    ui->selectButton->hide();
    ui->cancelButton->hide();

    this->reloadTable();
}


/*!
 *\brief sets the moves (focus indexes) given in the \a descriptorList in to the GUI
 *\param QString mediaP
 *\param QString mediaToMove
 *\param int column
 *\return void
 */
void NavegationGui::setMove(QString mediaP, QString mediaToMove, int column)
{
    QTableWidgetItem *item = new QTableWidgetItem();
    if(getIndex(mediaP) == -1){
        index++;
        movesTable->setRowCount(movesTable->rowCount()+1);
        item = new QTableWidgetItem();
        item->setText(mediaP);
        movesTable->setItem(movesTable->rowCount()-1,0,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(index));
        movesTable->setItem(movesTable->rowCount()-1,1,item);

        for(int i = 2; i < movesTable->columnCount(); i++){
            item = new QTableWidgetItem();
            item->setText("");
            movesTable->setItem(movesTable->rowCount()-1,i,item);
        }
    }

    if(getIndex(mediaToMove) == -1){
        index++;
        movesTable->setRowCount(movesTable->rowCount()+1);
        item = new QTableWidgetItem();
        item->setText(mediaToMove);
        movesTable->setItem(movesTable->rowCount()-1,0,item);

        item = new QTableWidgetItem();
        item->setText(QString::number(index));
        movesTable->setItem(movesTable->rowCount()-1,1,item);

        for(int i = 2; i < movesTable->columnCount(); i++){
            item = new QTableWidgetItem();
            item->setText("");
            movesTable->setItem(movesTable->rowCount()-1,i,item);
        }
    }

    for(int i=0;i<movesTable->rowCount();i++){

        if(movesTable->item(i,0)->text() == media){
            item = new QTableWidgetItem();
            item->setText(QString::number(getIndex(mediaToMove)));
            movesTable->setItem(i,column,item);
        }
    }
}


/*!
 *\brief returns the image (QPixmap) of the media with name \a mediaName
 *\param QString mediaName
 *\return QPixmap
 */
QPixmap NavegationGui::getPixmap(QString mediaName)
{
    QPixmap ret;
    for(int i = 0 ; i < ui->mediaTable->rowCount();i++){
        if(ui->mediaTable->item(i,0)->text() == mediaName){
            ret =  ui->mediaTable->item(i,0)->icon().pixmap(70,QIcon::Normal);
        }
    }
    return ret;

}

/*!
 *\brief called to select the focusSrc of the media
 *\return void
 */
void NavegationGui::focusSrc()
{
    QString mediaFile = QFileDialog::getOpenFileName(this, tr("Abrir Media"), "/",
                                                     tr("Archivos Medias (*.mp2 *.mpeg *.mpg *.mpe *.mp4 *.mpg4 *.mng *.qt *.mov *.avi *.ua *.wav *.mp1 *.mp2 *.mp3 *.mp4 *.mpg4 *.bmp *.png *.gif *.jpg *.jpeg *.jpe *.htm *.html *.css *.xml *.txt)"));

    if(mediaFile != NULL){
        ui->focusSrc->setText(mediaFile);
    }
}


/*!
 *\brief called to select the focusSelSrc of the media
 *\return void
 */
void NavegationGui::focusSelSrc()
{
    QString mediaFile = QFileDialog::getOpenFileName(this, tr("Abrir Media"), "/",
                                                     tr("Archivos Medias (*.mp2 *.mpeg *.mpg *.mpe *.mp4 *.mpg4 *.mng *.qt *.mov *.avi *.ua *.wav *.mp1 *.mp2 *.mp3 *.mp4 *.mpg4 *.bmp *.png *.gif *.jpg *.jpeg *.jpe *.htm *.html *.css *.xml *.txt)"));

    if(mediaFile != NULL){
        ui->focusSelSrc->setText(mediaFile);
    }
}


/*!
 *\brief called set enable or not the focus configuration of the media
 *\param bool enable
 *\return void
 */
void NavegationGui::setFocusEnable(bool enable)
{
    ui->focusBorderColor->setEnabled(enable);
    ui->selBorderColor->setEnabled(enable);
    ui->focusBorderWidth->setEnabled(enable);
    ui->focusBorderTransparency->setEnabled(enable);
    ui->focusSrc->setEnabled(enable);
    ui->focusSrcButton->setEnabled(enable);
    ui->focusSelSrc->setEnabled(enable);
    ui->focusSelSrcButton->setEnabled(enable);
}


/*!
 *\brief returns the color name with the index in the comboBox given in the param \a index
 *\param int index
 *\return QString
 */
QString NavegationGui::getColorName(int index)
{
    QString color = "";
    switch(index){
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
 *\brief return the index of the color in the comboBox with name \a color
 *\param QString color
 *\return int
 */
int NavegationGui::getColorIndex(QString color)
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
 *\brief called to save the focus when the current item is changed
 *\param int row
 *\return void
 */
void NavegationGui::apllyFocus(int row){
    QTableWidgetItem *item = new QTableWidgetItem();
    if(ui->checkBox->isChecked()){
        for(int i = 0; i < movesTable->rowCount(); i++){
            if(movesTable->item(i,0)->text() == ui->mediaTable->item(row,0)->text()){
                item = new QTableWidgetItem();
                item->setText(getColorName(ui->focusBorderColor->currentIndex()));
                movesTable->setItem(i,6,item);

                item = new QTableWidgetItem();
                item->setText(getColorName(ui->selBorderColor->currentIndex()));
                movesTable->setItem(i,7,item);

                item = new QTableWidgetItem();
                item->setText(QString::number(ui->focusBorderWidth->value()));
                movesTable->setItem(i,8,item);

                item = new QTableWidgetItem();
                item->setText(QString::number(ui->focusBorderTransparency->value()));
                movesTable->setItem(i,9,item);

                item = new QTableWidgetItem();
                item->setText(ui->focusSrc->text());
                movesTable->setItem(i,10,item);

                item = new QTableWidgetItem();
                item->setText(ui->focusSelSrc->text());
                movesTable->setItem(i,11,item);
            }
        }
    }else{
        for(int i = 0; i < movesTable->rowCount(); i++){
            if(movesTable->item(i,0)->text() == ui->mediaTable->item(row,0)->text()){
                item = new QTableWidgetItem();
                item->setText("");
                movesTable->setItem(i,6,item);

                item = new QTableWidgetItem();
                item->setText("");
                movesTable->setItem(i,7,item);

                item = new QTableWidgetItem();
                item->setText("");
                movesTable->setItem(i,8,item);

                item = new QTableWidgetItem();
                item->setText("");
                movesTable->setItem(i,9,item);

                item = new QTableWidgetItem();
                item->setText("");
                movesTable->setItem(i,10,item);

                item = new QTableWidgetItem();
                item->setText("");
                movesTable->setItem(i,11,item);
            }
        }
    }
}


/*!
 *\brief called to save the current media configuration when the windows is closed
 *\return void
 */
void NavegationGui::saveCurrent()
{
    apllyFocus(ui->mediaTable->currentRow());
}


/*!
 *\brief returns \a QTableWidget with the focus attributes and the focus indexes
 *\return QTableWidget*
 */
QTableWidget* NavegationGui::getNavigation()
{
    return movesTable;
}


/*!
 *\brief sets the moves (focus indexes) given in the \a descriptorList in to the GUI
 *\return void
 */
void NavegationGui::setMoves(QList<Descriptor*> descriptorList)
{
    QTableWidgetItem *item;
    QString id;
    for(int i = 0; i < descriptorList.count();i++){
        if(descriptorList.at(i)->getFocusIndex() != ""){
            movesTable->setRowCount(movesTable->rowCount()+1);
            item = new QTableWidgetItem();
            id = descriptorList.at(i)->getId();
            item->setText(id.remove("descriptor-"));
            movesTable->setItem(i,0,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getFocusIndex());
            movesTable->setItem(i,1,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getMoveUp());
            movesTable->setItem(i,2,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getMoveDown());
            movesTable->setItem(i,3,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getMoveLeft());
            movesTable->setItem(i,4,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getMoveRight());
            movesTable->setItem(i,5,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getFocusBorderColor());
            movesTable->setItem(i,6,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getSelBorderColor());
            movesTable->setItem(i,7,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getFocusBorderWidth());
            movesTable->setItem(i,8,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getFocusBorderTransparency());
            movesTable->setItem(i,9,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getFocusSrc());
            movesTable->setItem(i,10,item);

            item = new QTableWidgetItem();
            item->setText(descriptorList.at(i)->getFocusSelSrc());
            movesTable->setItem(i,11,item);
        }
    }
}
