/*!
 *\file QUnitMarginVertical.cpp
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods implementations to creates a vertical rule in pixels.
 *Source code obtained of an example of Qt web page with some own changes.
 */

#include "QUnitMarginVertical.h"

#include <iostream>
#include <QtDebug>

using namespace std;

QUnitMarginVertical::QUnitMarginVertical(const int MaximumCollisionPermission , QWidget *parent)
  :QWidget(parent),units("px"),dimfontsize(8),Cursor_1_Y(15),Cursor_Rect_1(-1),Cursor_Rect_2(-1),actual_x(15)
{
    ColText = Qt::black;
    MaximumCollisionAllowed = MaximumCollisionPermission;
    setMaximumWidth (20);
}


void QUnitMarginVertical::paintEvent(QPaintEvent *)
{
    paintScale();
    paintCursor();
    paintRectCursor();
}

void QUnitMarginVertical::mouseMove(  QPointF point )
{
     qreal Pointer_X = point.y();

     Cursor_1_Y = qBound(1.,Pointer_X,3000.);
     update();
}


void QUnitMarginVertical::paintRectCursor()
{
    QPainter painter(this);
    const int large = height();
    painter.setWindow(0, 0,22,large);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::blue,1));
    painter.drawLine( 1,Cursor_Rect_1, 21,Cursor_Rect_1);
    painter.drawLine(1, Cursor_Rect_2, 21, Cursor_Rect_2);
}

void QUnitMarginVertical::rectChange(  qreal point1, qreal point2)
{
    Cursor_Rect_1 = qBound(point1,1.,3000.);
    Cursor_Rect_2 = qBound(point2,1.,3000.);
    update();
}

void QUnitMarginVertical::paintCursor()
{
    QPainter painter(this);
    const int large = height();
    painter.setWindow(0, 0,22,large);
    painter.setRenderHint(QPainter::Antialiasing);

    QRectF cursor(Cursor_1_Y,12,5,18);
    painter.setPen(QPen(Qt::red,1.5));
    painter.drawLine( 1, Cursor_1_Y, 21,Cursor_1_Y);

    painter.setPen(QPen(Qt::darkRed,1));


}


void QUnitMarginVertical::paintScale()
{
    const int large = height();
    const qreal lineseparator_0 = FopInto(QString("10%1").arg(units));
    const qreal lineseparator_1 = lineseparator_0 / 10;
    QPainter painter(this);
    painter.setWindow(0, 0,22,large);

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::darkGray,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    const uint linessumme_0 = large / lineseparator_0;
    const uint linessumme_1 = large / lineseparator_1;
    int PressUnit = -1;
    painter.setPen(QPen(ColText,0.8, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    for (int i = 0; i<=linessumme_1; i++)
    {
        PressUnit++;
        const int LeftPointer1 = i * lineseparator_1 - 0.4;
        if (i > 0 && (i % 5 == 0)) {
            painter.drawLine(19,LeftPointer1,22,LeftPointer1);
        }

        if (i > 0 && (i % 25 == 0)) {
                 painter.drawLine(15,LeftPointer1,22,LeftPointer1);
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

        if (i >= 0 && (i % 10 == 0 || i % 5 == 0) ) {
            const int LeftPointer0 = i * lineseparator_0 - 0.5;
            painter.drawLine(14,LeftPointer0,22,LeftPointer0);
            QString val = QString("%1").arg(i*10);

            QRectF valR(-5,LeftPointer0-3,30,10);
            if(i != 0)
                painter.drawText(valR, Qt::AlignCenter , val);
        }
    }

    painter.setPen(QPen(Qt::darkGray,1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(21,0,21,large);

    painter.end();
}

QSize QUnitMarginVertical::minimumSizeHint() const
{
    return QSize(100,45);
}

QSize QUnitMarginVertical::sizeHint() const
{
    return QSize(700,45);
}


