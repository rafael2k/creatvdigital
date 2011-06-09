/*!
 *\file QUnitMarginTime.cpp
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods implementations to creates a horizontal rule in hour:minutes:secons.
 * Source code obtained of an example of Qt web page with some own changes.
 */

#include "QUnitMarginTime.h"

#include <iostream>
#include <QtDebug>

using namespace std;

QUnitMarginTime::QUnitMarginTime(const int MaximumCollisionPermission , QWidget *parent)
  :QWidget(parent),units("px"),dimfontsize(8),Cursor_1_X(15),Cursor_Rect_1(-1),Cursor_Rect_2(-1),actual_x(15)
{
    ColText = Qt::black;
    MaximumCollisionAllowed = MaximumCollisionPermission;
    setMaximumHeight (20);
}


void QUnitMarginTime::paintEvent(QPaintEvent *)
{
    paintScale();
    paintCursor();
    paintRectCursor();
}

void QUnitMarginTime::mouseMove(  QPointF point )
{
     qreal Pointer_X = point.x();
     Cursor_1_X = Pointer_X;
     update();
}


void QUnitMarginTime::rectChange(  qreal point1, qreal point2)
{

    Cursor_Rect_1 = qBound(1.,point1,3000.);
    Cursor_Rect_2 = qBound(1.,point2,3000.);
    update();
}

void QUnitMarginTime::paintCursor()
{
    QPainter painter(this);
    const int large = width();
    painter.setWindow(0, 0,large,22);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::red,1));
    painter.drawLine(Cursor_1_X, 1,Cursor_1_X, 21);

}

void QUnitMarginTime::paintRectCursor()
{
    QPainter painter(this);
    const int large = width();
    painter.setWindow(0, 0,large,22);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::blue,1.5));
    painter.drawLine(Cursor_Rect_1, 1,Cursor_Rect_1, 21);
    painter.drawLine(Cursor_Rect_2, 1,Cursor_Rect_2, 21);
}




void QUnitMarginTime::paintScale()
{
    const int large = width();
    const qreal lineseparator_0 = FopInttt(QString("10%1").arg(units));
    const qreal lineseparator_1 = lineseparator_0 / 10;
    QPainter painter(this);
    painter.setWindow(0, 0,large,22);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::darkGray,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    const uint linessumme_0 = large / lineseparator_0;
    const uint linessumme_1 = large / lineseparator_1;
    int PressUnit = -1;
    painter.setPen(QPen(ColText,0.8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i<=linessumme_1; i++)
    {
        PressUnit++;
        
        QString strnu = QString("%1").arg(i);
        const int LeftPointer1 = i * lineseparator_1 - 0.4;
        if (i > 0 && (i % 10 == 0)) {
            painter.drawLine(LeftPointer1,19,LeftPointer1,22);
        }
        
        if (PressUnit == 9) {
          PressUnit = -1;
        }
    }
    painter.setPen(QPen(ColText,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    QFont valFont("Arial", dimfontsize, QFont::Normal);
    painter.setFont(valFont);
    for (int i = 0; i<=linessumme_0; i++)
    {

        int magicNumber = i*10*100;

        QTime timeaux(0,0,0);
        QTime time;
        time = timeaux.addMSecs(magicNumber);

        QString hour = QString::number(time.hour());
        QString minutes = QString::number(time.minute());
        QString secs = QString::number(time.second());
        QString msecs = QString::number(time.msec());


        if (i >= 0 && (i % 5 == 0 )) {
            const int LeftPointer0 = i * lineseparator_0 - 0.5;
            painter.drawLine(LeftPointer0,14,LeftPointer0,22);

            QString val = hour+":"+minutes+":"+secs;

            QRectF valR(LeftPointer0-25,4,50,10);
            painter.drawText(valR, Qt::AlignCenter , val);
        }
    }
    
    painter.setPen(QPen(Qt::darkGray,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(0,21,large,21);
    
    painter.end();
}


QSize QUnitMarginTime::minimumSizeHint() const
{
    return QSize(100,45);
}

QSize QUnitMarginTime::sizeHint() const
{
    return QSize(700,45);
}


