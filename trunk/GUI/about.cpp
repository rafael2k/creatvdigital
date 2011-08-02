#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);

    setWindowTitle("Acerca de CreaTV Digital");
    ui->toolButton->setIcon(QIcon("images/CreaTV.png"));
    ui->toolButton->setToolTip("http://code.google.com/p/creatvdigital/");
    connect(ui->toolButton,SIGNAL(clicked()),this,SLOT(goUrl()));

}

About::~About()
{
    delete ui;
}

void About::goUrl(){
    QDesktopServices::openUrl(QUrl("http://code.google.com/p/creatvdigital/"));
}
