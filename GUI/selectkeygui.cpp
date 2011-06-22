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
*\file GUI/selectkeygui.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to set the button of an interactivity.
*/

#include "selectkeygui.h"
#include "ui_selectkeygui.h"


/*!
 *\brief creates the GUI, initialize values and create connectors
 *\param QWidget *parent
 */
SelectKeyGUI::SelectKeyGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectKeyGUI)
{
    ui->setupUi(this);

    QSize *iconSize = new QSize(30,30);

    ui->a->setIconSize(*iconSize);
    ui->a->setIcon(QIcon("icons/interactividad/A.png"));
    ui->a->setAutoRaise(true);
    ui->a->setCheckable(true);

    ui->b->setIconSize(*iconSize);
    ui->b->setIcon(QIcon("icons/interactividad/B.png"));
    ui->b->setAutoRaise(true);
    ui->b->setCheckable(true);

    ui->c->setIconSize(*iconSize);
    ui->c->setIcon(QIcon("icons/interactividad/C.png"));
    ui->c->setAutoRaise(true);
    ui->c->setCheckable(true);

    ui->d->setIconSize(*iconSize);
    ui->d->setIcon(QIcon("icons/interactividad/D.png"));
    ui->d->setAutoRaise(true);
    ui->d->setCheckable(true);

    ui->e->setIconSize(*iconSize);
    ui->e->setIcon(QIcon("icons/interactividad/E.png"));
    ui->e->setAutoRaise(true);
    ui->e->setCheckable(true);

    ui->f->setIconSize(*iconSize);
    ui->f->setIcon(QIcon("icons/interactividad/F.png"));
    ui->f->setAutoRaise(true);
    ui->f->setCheckable(true);

    ui->g->setIconSize(*iconSize);
    ui->g->setIcon(QIcon("icons/interactividad/G.png"));
    ui->g->setAutoRaise(true);
    ui->g->setCheckable(true);

    ui->h->setIconSize(*iconSize);
    ui->h->setIcon(QIcon("icons/interactividad/H.png"));
    ui->h->setAutoRaise(true);
    ui->h->setCheckable(true);

    ui->i->setIconSize(*iconSize);
    ui->i->setIcon(QIcon("icons/interactividad/I.png"));
    ui->i->setAutoRaise(true);
    ui->i->setCheckable(true);

    ui->j->setIconSize(*iconSize);
    ui->j->setIcon(QIcon("icons/interactividad/J.png"));
    ui->j->setAutoRaise(true);
    ui->j->setCheckable(true);

    ui->k->setIconSize(*iconSize);
    ui->k->setIcon(QIcon("icons/interactividad/K.png"));
    ui->k->setAutoRaise(true);
    ui->k->setCheckable(true);

    ui->l->setIconSize(*iconSize);
    ui->l->setIcon(QIcon("icons/interactividad/L.png"));
    ui->l->setAutoRaise(true);
    ui->l->setCheckable(true);

    ui->m->setIconSize(*iconSize);
    ui->m->setIcon(QIcon("icons/interactividad/M.png"));
    ui->m->setAutoRaise(true);
    ui->m->setCheckable(true);

    ui->n->setIconSize(*iconSize);
    ui->n->setIcon(QIcon("icons/interactividad/N.png"));
    ui->n->setAutoRaise(true);
    ui->n->setCheckable(true);

    ui->o->setIconSize(*iconSize);
    ui->o->setIcon(QIcon("icons/interactividad/O.png"));
    ui->o->setAutoRaise(true);
    ui->o->setCheckable(true);

    ui->p->setIconSize(*iconSize);
    ui->p->setIcon(QIcon("icons/interactividad/P.png"));
    ui->p->setAutoRaise(true);
    ui->p->setCheckable(true);

    ui->q->setIconSize(*iconSize);
    ui->q->setIcon(QIcon("icons/interactividad/Q.png"));
    ui->q->setAutoRaise(true);
    ui->q->setCheckable(true);

    ui->r->setIconSize(*iconSize);
    ui->r->setIcon(QIcon("icons/interactividad/R.png"));
    ui->r->setAutoRaise(true);
    ui->r->setCheckable(true);

    ui->s->setIconSize(*iconSize);
    ui->s->setIcon(QIcon("icons/interactividad/S.png"));
    ui->s->setAutoRaise(true);
    ui->s->setCheckable(true);

    ui->t->setIconSize(*iconSize);
    ui->t->setIcon(QIcon("icons/interactividad/T.png"));
    ui->t->setAutoRaise(true);
    ui->t->setCheckable(true);

    ui->u->setIconSize(*iconSize);
    ui->u->setIcon(QIcon("icons/interactividad/U.png"));
    ui->u->setAutoRaise(true);
    ui->u->setCheckable(true);

    ui->v->setIconSize(*iconSize);
    ui->v->setIcon(QIcon("icons/interactividad/V.png"));
    ui->v->setAutoRaise(true);
    ui->v->setCheckable(true);

    ui->w->setIconSize(*iconSize);
    ui->w->setIcon(QIcon("icons/interactividad/W.png"));
    ui->w->setAutoRaise(true);
    ui->w->setCheckable(true);

    ui->x->setIconSize(*iconSize);
    ui->x->setIcon(QIcon("icons/interactividad/X.png"));
    ui->x->setAutoRaise(true);
    ui->x->setCheckable(true);

    ui->y->setIconSize(*iconSize);
    ui->y->setIcon(QIcon("icons/interactividad/Y.png"));
    ui->y->setAutoRaise(true);
    ui->y->setCheckable(true);

    ui->z->setIconSize(*iconSize);
    ui->z->setIcon(QIcon("icons/interactividad/Z.png"));
    ui->z->setAutoRaise(true);
    ui->z->setCheckable(true);

    ui->asterisco->setIconSize(*iconSize);
    ui->asterisco->setIcon(QIcon("icons/interactividad/asterisco.png"));
    ui->asterisco->setAutoRaise(true);
    ui->asterisco->setCheckable(true);

    ui->numeral->setIconSize(*iconSize);
    ui->numeral->setIcon(QIcon("icons/interactividad/numeral.png"));
    ui->numeral->setAutoRaise(true);
    ui->numeral->setCheckable(true);

    ui->cero->setIconSize(*iconSize);
    ui->cero->setIcon(QIcon("icons/interactividad/0.png"));
    ui->cero->setAutoRaise(true);
    ui->cero->setCheckable(true);

    ui->uno->setIconSize(*iconSize);
    ui->uno->setIcon(QIcon("icons/interactividad/1.png"));
    ui->uno->setAutoRaise(true);
    ui->uno->setCheckable(true);

    ui->dos->setIconSize(*iconSize);
    ui->dos->setIcon(QIcon("icons/interactividad/2.png"));
    ui->dos->setAutoRaise(true);
    ui->dos->setCheckable(true);

    ui->tres->setIconSize(*iconSize);
    ui->tres->setIcon(QIcon("icons/interactividad/3.png"));
    ui->tres->setAutoRaise(true);
    ui->tres->setCheckable(true);

    ui->cuatro->setIconSize(*iconSize);
    ui->cuatro->setIcon(QIcon("icons/interactividad/4.png"));
    ui->cuatro->setAutoRaise(true);
    ui->cuatro->setCheckable(true);

    ui->cinco->setIconSize(*iconSize);
    ui->cinco->setIcon(QIcon("icons/interactividad/5.png"));
    ui->cinco->setAutoRaise(true);
    ui->cinco->setCheckable(true);

    ui->seis->setIconSize(*iconSize);
    ui->seis->setIcon(QIcon("icons/interactividad/6.png"));
    ui->seis->setAutoRaise(true);
    ui->seis->setCheckable(true);

    ui->siete->setIconSize(*iconSize);
    ui->siete->setIcon(QIcon("icons/interactividad/7.png"));
    ui->siete->setAutoRaise(true);
    ui->siete->setCheckable(true);

    ui->ocho->setIconSize(*iconSize);
    ui->ocho->setIcon(QIcon("icons/interactividad/8.png"));
    ui->ocho->setAutoRaise(true);
    ui->ocho->setCheckable(true);

    ui->nueve->setIconSize(*iconSize);
    ui->nueve->setIcon(QIcon("icons/interactividad/9.png"));
    ui->nueve->setAutoRaise(true);
    ui->nueve->setCheckable(true);

    ui->down->setIconSize(*iconSize);
    ui->down->setIcon(QIcon("icons/interactividad/CURSOR_DOWN.png"));
    ui->down->setAutoRaise(true);
    ui->down->setToolTip("Abajo");
    ui->down->setCheckable(true);

    ui->up->setIconSize(*iconSize);
    ui->up->setIcon(QIcon("icons/interactividad/CURSOR_UP.png"));
    ui->up->setAutoRaise(true);
    ui->up->setToolTip("Arriba");
    ui->up->setCheckable(true);

    ui->left->setIconSize(*iconSize);
    ui->left->setIcon(QIcon("icons/interactividad/CURSOR_LEFT.png"));
    ui->left->setAutoRaise(true);
    ui->left->setToolTip("Izquierda");
    ui->left->setCheckable(true);

    ui->right->setIconSize(*iconSize);
    ui->right->setIcon(QIcon("icons/interactividad/CURSOR_RIGHT.png"));
    ui->right->setAutoRaise(true);
    ui->right->setToolTip("Derecha");
    ui->right->setCheckable(true);

    ui->enter->setIconSize(*iconSize);
    ui->enter->setIcon(QIcon("icons/interactividad/ENTER.png"));
    ui->enter->setAutoRaise(true);
    ui->enter->setToolTip("Enter");
    ui->enter->setCheckable(true);

    ui->chUp->setIconSize(*iconSize);
    ui->chUp->setIcon(QIcon("icons/interactividad/CHANNEL_UP.png"));
    ui->chUp->setAutoRaise(true);
    ui->chUp->setToolTip("Subir Canal");
    ui->chUp->setCheckable(true);

    ui->chDown->setIconSize(*iconSize);
    ui->chDown->setIcon(QIcon("icons/interactividad/CHANNEL_DOWN.png"));
    ui->chDown->setAutoRaise(true);
    ui->chDown->setToolTip("Bajar Canal");
    ui->chDown->setCheckable(true);

    ui->volUp->setIconSize(*iconSize);
    ui->volUp->setIcon(QIcon("icons/interactividad/VOLUME_UP.png"));
    ui->volUp->setAutoRaise(true);
    ui->volUp->setToolTip("Subir Volumen");
    ui->volUp->setCheckable(true);

    ui->volDown->setIconSize(*iconSize);
    ui->volDown->setIcon(QIcon("icons/interactividad/VOLUME_DOWN.png"));
    ui->volDown->setAutoRaise(true);
    ui->volDown->setToolTip("Bajar Volumen");
    ui->volDown->setCheckable(true);

    ui->menu->setIconSize(*iconSize);
    ui->menu->setIcon(QIcon("icons/interactividad/MENU.png"));
    ui->menu->setAutoRaise(true);
    ui->menu->setToolTip("Menu");
    ui->menu->setCheckable(true);

    ui->guide->setIconSize(*iconSize);
    ui->guide->setIcon(QIcon("icons/interactividad/GUIDE.png"));
    ui->guide->setAutoRaise(true);
    ui->guide->setToolTip("Guia");
    ui->guide->setCheckable(true);

    ui->info->setIconSize(*iconSize);
    ui->info->setIcon(QIcon("icons/interactividad/INFO.png"));
    ui->info->setAutoRaise(true);
    ui->info->setToolTip("Informacion");
    ui->info->setCheckable(true);

    ui->back->setIconSize(*iconSize);
    ui->back->setIcon(QIcon("icons/interactividad/BACK.png"));
    ui->back->setAutoRaise(true);
    ui->back->setToolTip("Volver");
    ui->back->setCheckable(true);

    ui->exit->setIconSize(*iconSize);
    ui->exit->setIcon(QIcon("icons/interactividad/EXIT.png"));
    ui->exit->setAutoRaise(true);
    ui->exit->setToolTip("Salir");
    ui->exit->setCheckable(true);

    ui->power->setIconSize(*iconSize);
    ui->power->setIcon(QIcon("icons/interactividad/POWER.png"));
    ui->power->setAutoRaise(true);
    ui->power->setToolTip("Encendido/Apagado");
    ui->power->setCheckable(true);

    ui->play->setIconSize(*iconSize);
    ui->play->setIcon(QIcon("icons/interactividad/PLAY.png"));
    ui->play->setAutoRaise(true);
    ui->play->setToolTip("Comenzar");
    ui->play->setCheckable(true);

    ui->stop->setIconSize(*iconSize);
    ui->stop->setIcon(QIcon("icons/interactividad/STOP.png"));
    ui->stop->setAutoRaise(true);
    ui->stop->setToolTip("Parar");
    ui->stop->setCheckable(true);

    ui->pause->setIconSize(*iconSize);
    ui->pause->setIcon(QIcon("icons/interactividad/PAUSE.png"));
    ui->pause->setAutoRaise(true);
    ui->pause->setToolTip("Pausa");
    ui->pause->setCheckable(true);

    ui->rewind->setIconSize(*iconSize);
    ui->rewind->setIcon(QIcon("icons/interactividad/REWIND.png"));
    ui->rewind->setAutoRaise(true);
    ui->rewind->setToolTip("Rebobinar");
    ui->rewind->setCheckable(true);

    ui->eject->setIconSize(*iconSize);
    ui->eject->setIcon(QIcon("icons/interactividad/EJECT.png"));
    ui->eject->setAutoRaise(true);
    ui->eject->setToolTip("Expulsar");
    ui->eject->setCheckable(true);

    ui->record->setIconSize(*iconSize);
    ui->record->setIcon(QIcon("icons/interactividad/RECORD.png"));
    ui->record->setAutoRaise(true);
    ui->record->setToolTip("Grabar");
    ui->record->setCheckable(true);

    ui->red->setIconSize(*iconSize);
    ui->red->setIcon(QIcon("icons/interactividad/RED.png"));
    ui->red->setAutoRaise(true);
    ui->red->setCheckable(true);

    ui->green->setIconSize(*iconSize);
    ui->green->setIcon(QIcon("icons/interactividad/GREEN.png"));
    ui->green->setAutoRaise(true);
    ui->green->setCheckable(true);

    ui->yellow->setIconSize(*iconSize);
    ui->yellow->setIcon(QIcon("icons/interactividad/YELLOW.png"));
    ui->yellow->setAutoRaise(true);
    ui->yellow->setCheckable(true);

    ui->blue->setIconSize(*iconSize);
    ui->blue->setIcon(QIcon("icons/interactividad/BLUE.png"));
    ui->blue->setAutoRaise(true);
    ui->blue->setCheckable(true);

    QButtonGroup *group = new QButtonGroup(this);
    group->addButton(ui->a);
    group->addButton(ui->b);
    group->addButton(ui->c);
    group->addButton(ui->d);
    group->addButton(ui->e);
    group->addButton(ui->f);
    group->addButton(ui->g);
    group->addButton(ui->h);
    group->addButton(ui->i);
    group->addButton(ui->j);
    group->addButton(ui->k);
    group->addButton(ui->l);
    group->addButton(ui->m);
    group->addButton(ui->n);
    group->addButton(ui->o);
    group->addButton(ui->p);
    group->addButton(ui->q);
    group->addButton(ui->r);
    group->addButton(ui->s);
    group->addButton(ui->t);
    group->addButton(ui->u);
    group->addButton(ui->v);
    group->addButton(ui->w);
    group->addButton(ui->x);
    group->addButton(ui->y);
    group->addButton(ui->z);
    group->addButton(ui->eject);
    group->addButton(ui->power);
    group->addButton(ui->red);
    group->addButton(ui->green);
    group->addButton(ui->yellow);
    group->addButton(ui->blue);
    group->addButton(ui->guide);
    group->addButton(ui->info);
    group->addButton(ui->menu);
    group->addButton(ui->back);
    group->addButton(ui->exit);
    group->addButton(ui->up);
    group->addButton(ui->left);
    group->addButton(ui->right);
    group->addButton(ui->down);
    group->addButton(ui->enter);
    group->addButton(ui->uno);
    group->addButton(ui->dos);
    group->addButton(ui->tres);
    group->addButton(ui->cuatro);
    group->addButton(ui->cinco);
    group->addButton(ui->seis);
    group->addButton(ui->siete);
    group->addButton(ui->ocho);
    group->addButton(ui->nueve);
    group->addButton(ui->cero);
    group->addButton(ui->asterisco);
    group->addButton(ui->numeral);
    group->addButton(ui->play);
    group->addButton(ui->pause);
    group->addButton(ui->stop);
    group->addButton(ui->rewind);
    group->addButton(ui->record);
    group->addButton(ui->volUp);
    group->addButton(ui->volDown);
    group->addButton(ui->chDown);
    group->addButton(ui->chUp);
}


/*!
 *\brief destructor of de UI.
 */
SelectKeyGUI::~SelectKeyGUI()
{
    delete ui;
}


/*!
 *\brief returns the selected button of the GUI
 *\return QString
 */
QString SelectKeyGUI::getButton()
{
    QString ret = "";
    if(ui->a->isChecked()){
        ret = "A";
    }

    if(ui->c->isChecked()){
        ret = "B";
    }

    if(ui->c->isChecked()){
        ret = "C";
    }

    if(ui->d->isChecked()){
        ret = "D";
    }

    if(ui->e->isChecked()){
        ret = "E";
    }

    if(ui->f->isChecked()){
        ret = "F";
    }

    if(ui->g->isChecked()){
        ret = "G";
    }

    if(ui->h->isChecked()){
        ret = "H";
    }

    if(ui->i->isChecked()){
        ret = "I";
    }

    if(ui->j->isChecked()){
        ret = "J";
    }

    if(ui->k->isChecked()){
        ret = "K";
    }

    if(ui->l->isChecked()){
        ret = "L";
    }

    if(ui->m->isChecked()){
        ret = "M";
    }

    if(ui->n->isChecked()){
        ret = "N";
    }

    if(ui->o->isChecked()){
        ret = "O";
    }

    if(ui->p->isChecked()){
        ret = "P";
    }

    if(ui->q->isChecked()){
        ret = "Q";
    }

    if(ui->r->isChecked()){
        ret = "R";
    }

    if(ui->s->isChecked()){
        ret = "S";
    }

    if(ui->t->isChecked()){
        ret = "T";
    }

    if(ui->u->isChecked()){
        ret = "U";
    }

    if(ui->b->isChecked()){
        ret = "V";
    }

    if(ui->w->isChecked()){
        ret = "W";
    }

    if(ui->x->isChecked()){
        ret = "X";
    }

    if(ui->y->isChecked()){
        ret = "Y";
    }

    if(ui->z->isChecked()){
        ret = "Z";
    }

    if(ui->eject->isChecked()){
        ret = "EJECT";
    }

    if(ui->power->isChecked()){
        ret = "POWER";
    }

    if(ui->red->isChecked()){
        ret = "RED";
    }

    if(ui->green->isChecked()){
        ret = "GREEN";
    }

    if(ui->yellow->isChecked()){
        ret = "YELLOW";
    }

    if(ui->blue->isChecked()){
        ret = "BLUE";
    }

    if(ui->guide->isChecked()){
        ret = "GUIDE";
    }

    if(ui->info->isChecked()){
        ret = "INFO";
    }

    if(ui->menu->isChecked()){
        ret = "MENU";
    }

    if(ui->back->isChecked()){
        ret = "BACK";
    }

    if(ui->exit->isChecked()){
        ret = "EXIT";
    }

    if(ui->up->isChecked()){
        ret = "CURSOR_UP";
    }

    if(ui->left->isChecked()){
        ret = "CURSOR_LEFT";
    }

    if(ui->right->isChecked()){
        ret = "CURSOR_RIGHT";
    }

    if(ui->down->isChecked()){
        ret = "CURSOR_DOWN";
    }

    if(ui->enter->isChecked()){
        ret = "ENTER";
    }

    if(ui->uno->isChecked()){
        ret = "1";
    }

    if(ui->dos->isChecked()){
        ret = "2";
    }

    if(ui->tres->isChecked()){
        ret = "3";
    }

    if(ui->cuatro->isChecked()){
        ret = "4";
    }

    if(ui->cinco->isChecked()){
        ret = "5";
    }

    if(ui->seis->isChecked()){
        ret = "6";
    }

    if(ui->siete->isChecked()){
        ret = "7";
    }

    if(ui->ocho->isChecked()){
        ret = "8";
    }

    if(ui->nueve->isChecked()){
        ret = "9";
    }

    if(ui->cero->isChecked()){
        ret = "0";
    }

    if(ui->asterisco->isChecked()){
        ret = "*";
    }

    if(ui->numeral->isChecked()){
        ret = "#";
    }

    if(ui->play->isChecked()){
        ret = "PLAY";
    }

    if(ui->pause->isChecked()){
        ret = "PAUSE";
    }

    if(ui->stop->isChecked()){
        ret = "STOP";
    }

    if(ui->rewind->isChecked()){
        ret = "REWIND";
    }

    if(ui->record->isChecked()){
        ret = "RECORD";
    }

    if(ui->volUp->isChecked()){
        ret = "VOLUME_UP";
    }

    if(ui->volDown->isChecked()){
        ret = "VOLUME_DOWN";
    }

    if(ui->chDown->isChecked()){
        ret = "CHANNEL_DOWN";
    }

    if(ui->chUp->isChecked()){
        ret = "CHANNEL_UP";
    }

    return ret;
}
