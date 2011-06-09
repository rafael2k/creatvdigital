/*!
*\file GUI/selectrole.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to add an action when a event ocurrs.
*/

#ifndef SELECTROLE_H
#define SELECTROLE_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QListWidgetItem>
#include <QMessageBox>

/*!
* \class SelectRole
* \brief class to add an action when a event ocurrs.
*/

namespace Ui {
    class SelectRole;
}

class SelectRole : public QDialog
{
    Q_OBJECT

public:
    /// creates the GUI, initialize values and create connectors
    explicit SelectRole(QWidget *parent = 0);
    ~SelectRole();

    /// add the medias in \a mediaListP in to the table. \a is used to see the media type of a media un \a mediaListP
    void setMediaList(QTableWidget* list, QStringList mediaListP);

    /// returns the media in the play list selected
    QStringList getPlayList();
    /// returns the media in the stop list selected
    QStringList getStopList();
    /// returns the media in the pause list selected
    QStringList getPauseList();
    /// returns the media in the resume list selected
    QStringList getResumeList();
    /// returns the media in the abort list selected
    QStringList getAbortList();
    /// returns the media in the set list selected
    QStringList getSetList();

    /// sets the start list, stop list pause list, resume list, abort list, set list with the params \a startListP, \a stopListP, \a pauseListP, \a resumeListP, \a abortListP, \a setListP respectively
    void setRolesList(QStringList startListP, QStringList stopListP, QStringList pauseListP, QStringList resumeListP, QStringList abortListP, QStringList setListP);

private:
    Ui::SelectRole *ui;

    QTableWidget *mediasList;
    QStringList playList;
    QStringList stopList;
    QStringList pauseList;
    QStringList resumeList;
    QStringList abortList;
    QStringList setList;
    QTableWidget *mediaListTable;

    /// returns the of the media \a mediaName
    QString getMediaType(QString mediaName);


signals:
    /// this signal is emited when a checkBox of list name is selected
    void changeRoleListSiganl(QStringList list);

private slots:
    /// adds a media to a list
    void addMedia();
    /// removes a media to a list
    void removeMedia();
    /// called when the stop list checkBox is selected
    void changeToStop();
    /// called when the pause list checkBox is selected
    void changeToPause();
    /// called when the resume list checkBox is selected
    void changeToResume();
    /// called when the abort list checkBox is selected
    void changeToAbort();
    /// called when the set list checkBox is selected
    void changeToSet();
    /// called when the play list checkBox is selected
    void changeToPlay();
    /// called when the list checkBox is selected, loadig the list \a list
    void changeRoleList(QStringList list);
};

#endif // SELECTROLE_H
