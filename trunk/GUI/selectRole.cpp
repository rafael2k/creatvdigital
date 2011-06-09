#include "selectRole.h"
#include "ui_se

NewProject::NewProject(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::NewProject)
{
    m_ui->setupUi(this);
}

NewProject::~NewProject()
{
    delete m_ui;
}

void NewProject::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

QString NewProject::getNameProject()
{
    return m_ui->lineEdit->text();
}

