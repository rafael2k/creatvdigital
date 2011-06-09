/*!
*\file GUI/uriconfig.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to config an url.
*/

#ifndef URICONFIG_H
#define URICONFIG_H

#include <QDialog>

/*!
* \class UriConfig
* \brief class to config an url.
*/

namespace Ui {
    class UriConfig;
}

class UriConfig : public QDialog
{
    Q_OBJECT

public:
    /// initializes values and create connectors
    explicit UriConfig(QWidget *parent = 0);
    ~UriConfig();

    /// returns the url value selected
    QString getUri();
    /// returns the Type of the media of the url
    QString getType();
    /// returns the media name value selected to the media
    QString getName();

private:
    Ui::UriConfig *ui;
};

#endif // URICONFIG_H
