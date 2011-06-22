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
*\file NCL/switch.cpp
*\author Sergio A. Cardozo (yojajo@gmail.com)
*\author Sebastian M. Schwatrz (seba.schwartz.7@gmail.com)
*\date May 2011
*\version 0.1
*\note A file containing the methods implementation to create an switch entity.
*/

#include "switch.h"

Switch::Switch(QString idParam, DefaultComponent defaultComponentParam)
{
    id = idParam;
    defaultComponent = defaultComponentParam.getDefaultComponent();
    refer = "";
    switchPort = "";
    bindRule = "";
    media = "";
    context = "";
    subSwitch = "";
}

Switch::Switch(QString idParam, SwitchPort switchPortParam)
{
    id = idParam;
    defaultComponent = "";
    refer = "";
    switchPort = switchPortParam.getSwitchPort();
    bindRule = "";
    media = "";
    context = "";
    subSwitch = "";
}


Switch::Switch(QString idParam, BindRule bindRuleParam)
{
    id = idParam;
    defaultComponent = "";
    refer = "";
    switchPort = "";
    bindRule = bindRuleParam.getBindRule();
    media = "";
    context = "";
    subSwitch = "";
}

Switch::Switch(QString idParam, Media mediaParam)
{
    id = idParam;
    defaultComponent = "";
    refer = "";
    switchPort = "";
    bindRule = "";
    media = mediaParam.getMedia();
    context = "";
    subSwitch = "";
}

Switch::Switch(QString idParam, QString contextParam)
{
    id = idParam;
    defaultComponent = "";
    refer = "";
    switchPort = "";
    bindRule = "";
    media = "";
    context = contextParam;
    subSwitch = "";
}

Switch::Switch(QString idParam, Switch switchParam)
{
    id = idParam;
    defaultComponent = "";
    refer = "";
    switchPort = "";
    bindRule = "";
    media = "";
    context = "";
    subSwitch = switchParam.getSwitch();
}

QString Switch::getSwitch()
{
    switchS = "\t\t<switch id=\""+id+">\n";
    switchS.append(defaultComponent);
    switchS.append(switchPort);
    switchS.append(bindRule);
    switchS.append(media);
    switchS.append(context);
    switchS.append(subSwitch);
    switchS.append("\t\t</switch>");
    return switchS;
}

void Switch::setRefer(QString referParam)
{
    refer = referParam;
}

void Switch::setDefaultComponent(DefaultComponent defaultComponentParam)
{
    defaultComponent = defaultComponentParam.getDefaultComponent();
}

void Switch::addSwitchPort(SwitchPort switchPortParam)
{
    switchPort.append(switchPortParam.getSwitchPort());
}

void Switch::addBindRulet(BindRule bindRuleParam)
{
    bindRule.append(bindRuleParam.getBindRule());
}

void Switch::addMedia(Media mediaParam)
{
    media.append(mediaParam.getMedia());
}

void Switch::addContext(QString contextParam)
{
    context.append(contextParam);
}

void Switch::addSwitch(Switch subSwitchParam)
{
    subSwitch.append(subSwitchParam.getSwitch());
}
