#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
    class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    Ui::About *ui;

private slots:
    void goUrl();
};

#endif // ABOUT_H
