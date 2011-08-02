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
*\file GUI/selectrole.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to add an action when a event ocurrs.
*/

#include "selectrole.h"
#include "ui_selectrole.h"

#include <iostream>

using namespace std;


/*!
 *\brief creates the GUI, initialize values and create connectors
 *\param QWidget *parent
 */
SelectRole::SelectRole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectRole)
{
    ui->setupUi(this);

    this->setWindowTitle("Acciones");
    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->startCheckBox);
    group->addButton(ui->stopCheckBox);
    group->addButton(ui->abortCheckBox);
    group->addButton(ui->pauseCheckBox);
    group->addButton(ui->resumeCheckBox);
    group->addButton(ui->setCheckBox);

    ui->startCheckBox->setChecked(true);

    mediasList = new QTableWidget();
    mediasList->setColumnCount(2);

    ui->addMedia->setIconSize(QSize(30,30));
    ui->addMedia->setToolTip("Agregar Media");
    ui->addMedia->setIcon(QIcon("icons/addMedia2.png"));

    ui->removeMedia->setIconSize(QSize(30,30));
    ui->removeMedia->setToolTip("Eliminar Media");
    ui->removeMedia->setIcon(QIcon("icons/deleteMedia.png"));

    ui->startCheckBox->setIcon(QIcon("icons/start.png"));
    ui->stopCheckBox->setIcon(QIcon("icons/stop.png"));
    ui->abortCheckBox->setIcon(QIcon("icons/abort.png"));
    ui->pauseCheckBox->setIcon(QIcon("icons/pause.png"));
    ui->resumeCheckBox->setIcon(QIcon("icons/resume.png"));
    ui->setCheckBox->setIcon(QIcon("icons/set.png"));

    connect(ui->addMedia,SIGNAL(clicked()),this,SLOT(addMedia()));
    connect(ui->removeMedia,SIGNAL(clicked()),this,SLOT(removeMedia()));

    connect(ui->startCheckBox,SIGNAL(clicked()),this,SLOT(changeToPlay()));
    connect(ui->stopCheckBox,SIGNAL(clicked()),this,SLOT(changeToStop()));
    connect(ui->pauseCheckBox,SIGNAL(clicked()),this,SLOT(changeToPause()));
    connect(ui->resumeCheckBox,SIGNAL(clicked()),this,SLOT(changeToResume()));
    connect(ui->abortCheckBox,SIGNAL(clicked()),this,SLOT(changeToAbort()));
    connect(ui->setCheckBox,SIGNAL(clicked()),this,SLOT(changeToSet()));
    connect(this,SIGNAL(changeRoleListSiganl(QStringList)),this,SLOT(changeRoleList(QStringList)));
}



/*!
 *\brief destructor of de UI.
 */
SelectRole::~SelectRole()
{
    delete ui;
}


/*!
 *\brief add the medias in \a mediaListP in to the table. \a is used to see the media type of a media un \a mediaListP
 *\param QTableWidget* list
 *\param QStringList mediaListP
 *\return void
 */
void SelectRole::setMediaList(QTableWidget* list, QStringList mediaListP)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    QString mediaName;
    int k= 0;
    mediasList->setRowCount(mediaListP.size());
    for(int i = 0; i < list->rowCount(); i++){
        for(int j = 0; j < mediaListP.size(); j++){
            mediaName = list->item(i,0)->text();

            if(mediaName==mediaListP.at(j)){
                item = new QTableWidgetItem();
                item->setText(mediaListP.at(j));

                mediasList->setItem(k,0,item);
                item = new QTableWidgetItem();
                item->setText(list->item(i,3)->text());
                mediasList->setItem(k,1,item);
                k++;
            }
        }
    }
    changeToPlay();
}


/*!
 *\brief adds a media to a list
 *\return void
 */
void SelectRole::addMedia()
{
    bool add = true;
    if(ui->mediasList->currentRow() != -1){
        if(ui->startCheckBox->isChecked()){
            playList.append(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
        }else if(ui->stopCheckBox->isChecked()){
            stopList.append(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
        }else if(ui->pauseCheckBox->isChecked()){
            pauseList.append(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
        }else if(ui->resumeCheckBox->isChecked()){
            resumeList.append(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
        }else if(ui->abortCheckBox->isChecked()){
            abortList.append(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
        }else if(ui->setCheckBox->isChecked()){
            if(ui->mediasList->item(ui->mediasList->currentRow(),1)->text() != "Lua" && ui->mediasList->item(ui->mediasList->currentRow(),1)->text() != "Uri"){
                setList.append(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
            }else{
                QMessageBox::StandardButton reply;
                reply = QMessageBox::information(this, tr("Agregar Media"), "a los Medias de tipo \"Lua\" o del tipo \"Uri\" no se le puede setear los atributos");
                add = false;
            }
        }

        if(add){
            ui->selectedMediasList->addItem(ui->mediasList->item(ui->mediasList->currentRow(),0)->text());
            ui->mediasList->removeRow(ui->mediasList->currentRow());
        }
    }
}


/*!
 *\brief removes a media to a list
 *\return void
 */
void SelectRole::removeMedia()
{
    if(ui->selectedMediasList->selectedItems().size() != 0){
        QTableWidgetItem *item = new QTableWidgetItem();
        item = new QTableWidgetItem();

        ui->mediasList->insertRow(ui->mediasList->rowCount());
        item->setText( ui->selectedMediasList->currentItem()->text());
        ui->mediasList->setItem(ui->mediasList->rowCount()-1,0,item);
        item = new QTableWidgetItem();
        item->setText(getMediaType(ui->selectedMediasList->currentItem()->text()));
        ui->mediasList->setItem(ui->mediasList->rowCount()-1,1,item);

        if(ui->startCheckBox->isChecked()){
            playList.removeAt(playList.indexOf(ui->selectedMediasList->currentItem()->text()));
        }else if(ui->stopCheckBox->isChecked()){
            stopList.removeAt(stopList.indexOf(ui->selectedMediasList->currentItem()->text()));
        }else if(ui->pauseCheckBox->isChecked()){
            pauseList.removeAt(pauseList.indexOf(ui->selectedMediasList->currentItem()->text()));
        }else if(ui->resumeCheckBox->isChecked()){
            resumeList.removeAt(resumeList.indexOf(ui->selectedMediasList->currentItem()->text()));
        }else if(ui->abortCheckBox->isChecked()){
            abortList.removeAt(abortList.indexOf(ui->selectedMediasList->currentItem()->text()));
        }else if(ui->setCheckBox->isChecked()){
            setList.removeAt(setList.indexOf(ui->selectedMediasList->currentItem()->text()));
        }

        delete ui->selectedMediasList->takeItem(ui->selectedMediasList->currentRow());
    }
}


/*!
 *\brief called when a list checkBox is selected, loadig the list \a list
 *\param QStringList list
 *\return void
 */
void SelectRole::changeRoleList(QStringList list)
{
    ui->selectedMediasList->clear();
    ui->mediasList->clear();
    bool equals= false;
    QTableWidgetItem *item;
    QListWidgetItem *item2;

    if(list.size() != 0){
        ui->mediasList->setRowCount(mediasList->rowCount()-list.size());
        item = new QTableWidgetItem();
        item2 = new QListWidgetItem();
        int k = 0;
        for (int i=0; i<mediasList->rowCount();i++){
            for(int j=0; j < list.size();j++){
                if(mediasList->item(i,0)->text() == list.at(j)){
                    item2 = new QListWidgetItem();
                    item2->setText(list.at(j));
                    ui->selectedMediasList->addItem(item2);
                    equals = true;
                    break;
                }
            }
            if(!equals){
                item = new QTableWidgetItem();
                item->setText(mediasList->item(i,0)->text());
                ui->mediasList->setItem(k,0,item);
                item = new QTableWidgetItem();
                item->setText(getMediaType(mediasList->item(i,0)->text()));
                ui->mediasList->setItem(k,1,item);
                k++;
            }
            equals = false;
        }

    }else{
        ui->mediasList->setRowCount(mediasList->rowCount());
        for(int i = 0; i < mediasList->rowCount(); i++){
            item = new QTableWidgetItem();
            item->setText(mediasList->item(i,0)->text());
            ui->mediasList->setItem(i,0,item);

            item = new QTableWidgetItem();
            item->setText(mediasList->item(i,1)->text());
            ui->mediasList->setItem(i,1,item);
        }
    }
}


/**
 *\brief called when a stop list checkBox is selected, loadig the list \a list
 *\return void
 */
void SelectRole::changeToStop()
{
    emit changeRoleListSiganl(stopList);
}


/**
 *\brief called when a pause list checkBox is selected, loadig the list \a list
 *\return void
 */
void SelectRole::changeToPause()
{
    emit changeRoleListSiganl(pauseList);
}


/**
 *\brief called when a resume list checkBox is selected, loadig the list \a list
 *\return void
 */
void SelectRole::changeToResume()
{
    emit changeRoleListSiganl(resumeList);
}


/**
 *\brief called when a abort list checkBox is selected, loadig the list \a list
 *\return void
 */
void SelectRole::changeToAbort()
{
    emit changeRoleListSiganl(abortList);
}


/**
 *\brief called when a set list checkBox is selected, loadig the list \a list
 *\return void
 */
void SelectRole::changeToSet()
{
    emit changeRoleListSiganl(setList);
}


/**
 *\brief called when a play list checkBox is selected, loadig the list \a list
 *\return void
 */
void SelectRole::changeToPlay()
{
   emit changeRoleListSiganl(playList);
}


/**
 *\brief sets the start list, stop list pause list, resume list, abort list, set list with the params \a startListP, \a stopListP, \a pauseListP, \a resumeListP, \a abortListP, \a setListP respectively
 *\param QStringList startListP
 *\param QStringList stopListP
 *\param QStringList pauseListP
 *\param QStringList resumeListP
 *\param QStringList abortListP
 *\param QStringList setListP
 *\return void
 */
void SelectRole::setRolesList(QStringList startListP, QStringList stopListP, QStringList pauseListP, QStringList resumeListP, QStringList abortListP, QStringList setListP){
    playList.clear();
    stopList.clear();
    pauseList.clear();
    resumeList.clear();
    abortList.clear();
    setList.clear();
    playList.append(startListP);
    stopList.append(stopListP);
    pauseList.append(pauseListP);
    resumeList.append(resumeListP);
    abortList.append(abortListP);
    setList.append(setListP);
}


/**
 *\brief returns the media in the play list selected
 *\return void
 */
QStringList SelectRole::getPlayList()
{
    return playList;
}


/**
 *\brief returns the media in the stop list selected
 *\return void
 */
QStringList SelectRole::getStopList()
{
    return stopList;
}


/**
 *\brief returns the media in the pause list selected
 *\return void
 */
QStringList SelectRole::getPauseList()
{
    return pauseList;
}


/**
 *\brief returns the media in the resume list selected
 *\return void
 */
QStringList SelectRole::getResumeList()
{
    return resumeList;
}


/**
 *\brief returns the media in the abort list selected
 *\return void
 */
QStringList SelectRole::getAbortList(){
    return abortList;
}


/**
 *\brief returns the media in the set list selected
 *\return void
 */
QStringList SelectRole::getSetList()
{
    return setList;
}


/**
 *\brief returns the media in the play list selected
 *\param QString mediaName
 *\return void
 */
QString SelectRole::getMediaType(QString mediaName)
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
