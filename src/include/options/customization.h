/*
 * customization.h
 * This file is part of Open-Typer
 *
 * Copyright (C) 2021-2022 - adazem009
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

#ifndef CUSTOMIZATION_H
#define CUSTOMIZATION_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QPropertyAnimation>
#include "options/optionswindow.h"
#include "simplecolordialog.h"
#include "core/utils.h"

namespace Ui {
	class customizationOptions;
}

/*!
 * \brief The customizationOptions class is the customization category in the options.
 * \image html customizationOptions.png
 * \n
 * \image html customizationOptions2.png
 * \see optionsWindow
 */
class customizationOptions : public QWidget
{
	Q_OBJECT
	public:
		explicit customizationOptions(QWidget *parent = nullptr);
		~customizationOptions();
		void init(void);

	private:
		Ui::customizationOptions *ui;
		QVector<QVariantMap> themes;
		QListWidgetItem *lastItem = nullptr;
		bool blockThemeSignal;
		int levelTextRedColor, levelTextGreenColor, levelTextBlueColor;
		int inputTextRedColor, inputTextGreenColor, inputTextBlueColor;
		int bgRedColor, bgGreenColor, bgBlueColor;
		int paperRedColor, paperGreenColor, paperBlueColor;
		int panelRedColor, panelGreenColor, panelBlueColor;
		bool customLevelTextColor, customInputTextColor, customBgColor, customPaperColor, customPanelColor;
		void selectCurrentFullTheme(void);
		void setFont(QString fontFamily, int fontSize, bool fontBold, bool fontItalic, bool fontUnderline);
		void saveColorSettings(void);
		void setColors();
		void updateTheme();

	signals:
		/*! A signal, which is emitted when the theme changes. */
		void themeChanged();

	private slots:
		void changeFullTheme(QListWidgetItem* item);
		void goBack(void);
		void changeFont(QFont font);
		void changeFontSize(int size);
		void setBoldText(void);
		void setItalicText(void);
		void setUnderlineText(void);
		void changeLevelTextColor(void);
		void changeInputTextColor(void);
		void resetTextColors(void);
		void changeBgColor(void);
		void changePaperColor(void);
		void changePanelColor(void);
		void resetBgPaperColors(void);
		void changeTheme(int index);
};

#endif // CUSTOMIZATION_H
