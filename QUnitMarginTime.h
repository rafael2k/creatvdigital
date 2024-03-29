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
 *\file QUnitMarginTime.h
 *\author Sergio A. Cardozo (yojajo@gmail.com)
 *\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
 *\date May 2011
 *\version 0.1
 *\note A file containing the methods declarations to creates a horizontal rule in hour:minutes:secons.
 * Source code obtained of an example of Qt web page with some own changes.
 */

#ifndef QMUNITMARGINTIME_H
#define QMUNITMARGINTIME_H

#include <QtGui>


//////static const int MaximumCollisionAllowed = 100; 

#define POINT_TO_CM(cm) ((cm)/28.3465058)  
#define POINT_TO_MM(mm) ((mm)/2.83465058)     ////////  0.352777778
#define POINT_TO_DM(dm) ((dm)/283.465058)
#define POINT_TO_INCH(inch) ((inch)/72.0)
#define POINT_TO_PI(pi) ((pi)/12)
#define POINT_TO_DD(dd) ((dd)/154.08124)
#define POINT_TO_CC(cc) ((cc)/12.840103)

#define MM_TO_POINT(mm) ((mm)*2.83465058)
#define CM_TO_POINT(cm) ((cm)*28.3465058)     ///// 28.346456693
#define DM_TO_POINT(dm) ((dm)*283.465058)
#define INCH_TO_POINT(inch) ((inch)*72.0)
#define PI_TO_POINT(pi) ((pi)*12)
#define DD_TO_POINT(dd) ((dd)*154.08124)
#define CC_TO_POINT(cc) ((cc)*12.840103)


static inline qreal Pointooo( qreal unit , const QString unita )  {
    qreal ri = 0;
    if (unita == "cm") {
    ri = POINT_TO_CM( unit );
    } else if (unita == "pt" || unita == "px" ) {
    ri = unit;
    return ri;
    } else if (unita == "mm") {
    ri = POINT_TO_MM( unit );
    } else if (unita == "dm") {
    ri = POINT_TO_DM( unit );
    } else if (unita == "inch") {
    ri = POINT_TO_INCH( unit );
    } else if (unita == "pi") {
    ri = POINT_TO_PI( unit );
    } else if (unita == "dd") {
    ri = POINT_TO_DD( unit );
    }  else if (unita == "cc") {
    ri = POINT_TO_CC( unit );
    } else {
    ri = 10;
    }
    return ri;
}


static inline qreal FopInttt( const QString datain )
{
  QString ctmp = datain;
  const QString data = ctmp.replace(" ","").trimmed();
  //////////qDebug() << "### request unit data->" << datain << " size->" << datain.size();   
  qreal points = 0;
  if (data.size() < 1) {
  return points;
  }
  if (datain == "0") {
  return points;
  }
  if ( data.endsWith( "pt" ) ||  data.endsWith( "px" ) )  {
    points = data.left( data.length() - 2 ).toDouble();
    return points;
  } else if ( data.endsWith( "cm" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = CM_TO_POINT( value );
  } else if ( data.endsWith( "em" ) ) {
    points = data.left( data.length() - 2 ).toDouble();
  } else if ( data.endsWith( "mm" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = MM_TO_POINT( value );
  } else if ( data.endsWith( "dm" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = DM_TO_POINT( value );
  } else if ( data.endsWith( "in" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = INCH_TO_POINT( value );
  } else if ( data.endsWith( "inch" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = INCH_TO_POINT( value );
  } else if ( data.endsWith( "pi" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = PI_TO_POINT( value );
  } else if ( data.endsWith( "dd" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = DD_TO_POINT( value );
  } else if ( data.endsWith( "cc" ) ) {
    double value = data.left( data.length() - 2 ).toDouble();
    points = CC_TO_POINT( value );
  } else {
    points = 0;
  }
  return points;
}



/*!
 * \class QUnitMarginTime
 * \brief A class containing the methods declarations to creates a horizontal rule in hour:minutes:secons.
 */
class QUnitMarginTime : public QWidget
{
    Q_OBJECT

public:

    QUnitMarginTime(const int MaximumCollisionPermission = 200 , QWidget *parent = 0);
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    qreal Cursor_1_X;
    qreal Cursor_Rect_1;
    qreal Cursor_Rect_2;

signals:
    void CursorMove(qreal);

public slots:
    void mouseMove(  QPointF point );
    void rectChange(  qreal point1, qreal point2);


protected:
    QRectF AreaCursor_1;

    qreal actual_x;
    QString units;
    int MaximumCollisionAllowed;
    int dimfontsize;
    int lastMove;
    void paintEvent(QPaintEvent *);
    void paintRectCursor();

    void paintScale();
    void paintCursor();

private:
    QColor ColText;


};

#endif
