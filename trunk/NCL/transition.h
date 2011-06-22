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
*\file NCL/transition.h
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods declaration to create a transition entity.
*/

#ifndef TRANSITION_H
#define TRANSITION_H

#include <QString>

/*!
* \class Transition
* \brief class to create a transition entity.
*/

class Transition
{
private:
    QString transition;
    QString id;
    QString type;
    QString subType;
    QString dur;
    QString startProgress;
    QString endProgress;
    QString direction;
    QString fadeColor;
    QString horRepeat;
    QString vertRepeat;
    QString borderWidth;
    QString borderColor;

public:
    Transition(QString id, QString type);
    void setSubType(QString subType);
    void setDur(QString dur);
    void setStartProgress(QString startProgress);
    void setEndProgress(QString endProgress);
    void setDirection(QString direction);
    void setFadeColor(QString fadeColor);
    void setHorRepeat(QString horRepeat);
    void setVertRepeat(QString vertRepeat);
    void setBorderWidth(QString borderWidth);
    void setBorderColor(QString borderColor);
    QString getTransition();
};

#endif // TRANSITION_H
