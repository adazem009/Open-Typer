/*
 * AddonApi.h
 * This file is part of Open-Typer
 *
 * Copyright (C) 2022 - adazem009
 *
 * Open-Typer is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Open-Typer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Open-Typer. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADDONAPI_H
#define ADDONAPI_H

#include <QObject>
#include <QIcon>
#include <QMessageBox>
#include <QVariantMap>
#include <QMenu>
#include <QPushButton>
#include "IAddon.h"

#if defined CORE_SHARED_LIB
#define CORE_LIB_EXPORT Q_DECL_EXPORT
#else
#define CORE_LIB_EXPORT Q_DECL_IMPORT
#endif

/*! \brief The AddonApi class provides an API for addons. */
class CORE_LIB_EXPORT AddonApi
{
	public:
		enum TopBarSection
		{
			TopBarSection_Home = 0,
			TopBarSection_Navigation = 1,
			TopBarSection_ExOptions = 2,
			TopBarSection_State = 3,
			TopBarSection_Time = 4
		};
		static bool addSettingsCategory(QString categoryName, QIcon icon, QString className);
		static QList<QVariantMap> settingsCategories(void);
		static void clearSettingsCategories(void);
		static void initSettingsCategories(bool clear = false);
		static void sendEvent(IAddon::Event type);
		static void deleteMenus(void);
		static void addMenu(QString name);
		static void registerMenu(QMenu *menu);
		static QMap<QString, QMenu *> menus(void);
		static QMenu *menu(QString name);
		static void deleteButtons(void);
		static void addButton(QString id, QIcon icon, QString toolTip, TopBarSection section);
		static void registerButton(QString id, QPushButton *button);
		static QMap<QString, QPair<QPair<QIcon, QString>, QPair<TopBarSection, QPushButton *>>> buttons(void);
		static QPushButton *button(QString id);

	private:
		static QList<QVariantMap> m_settingsCategories;
		static QMap<QString, QMenu *> m_menus;
		static QMap<QString, QPair<QPair<QIcon, QString>, QPair<TopBarSection, QPushButton *>>> m_buttons;
};

#endif // ADDONAPI_H
