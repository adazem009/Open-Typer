/*
 * opentyper.h
 * This file is part of Open-Typer
 *
 * Copyright (C) 2021 - adazem009
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

#ifndef OPENTYPER_H
#define OPENTYPER_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QElapsedTimer>
#include <QSettings>
#include "updater/updater.h"
#include "simplecolordialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class OpenTyper; }
QT_END_NAMESPACE

class OpenTyper : public QMainWindow
{
	Q_OBJECT

public:
	OpenTyper(QWidget *parent = nullptr);
	~OpenTyper();
	void loadConfigs(void);
	char *loadConfig(QString configName);
	void startLevel(FILE *cr, int lesson, int sublesson, int level);
	QString level, displayLevel, input, displayInput, publicConfigName;
	int lessonCount, sublessonCount, levelCount, currentLesson, currentSublesson, currentLevel, levelPos, displayPos, levelMistakes, levelLengthExtension;
	int sublessonListStart;
	QElapsedTimer levelTimer;
	bool levelInProgress, mistake, ignoreMistakeLabelAppend;
	int lastTime;
	QString getConfigLoc(void);
	bool isSpecialKey(QKeyEvent *event);
	QString _init_level(QString level);
	int _line_count(QString str);
	Updater *versionHdw;
	void autoUpdate(void);
	void adjustSize(void);
	int labelWidth(QLabel *targetLabel);
	void setFont(QString fontFamily, int fontSize, bool fontBold, bool fontItalic, bool fontUnderline);
	int levelTextRedColor, levelTextGreenColor, levelTextBlueColor;
	int inputTextRedColor, inputTextGreenColor, inputTextBlueColor;
	int bgRedColor, bgGreenColor, bgBlueColor;
	int paperRedColor, paperGreenColor, paperBlueColor;
	bool customLevelTextColor, customInputTextColor, customBgColor, customPaperColor;
	void saveColorSettings(void);
	void setColors(void);
	void updateTheme(void);
	QPalette currentPalette;

protected:
	void keyPressEvent(QKeyEvent *event);

private:
	Ui::OpenTyper *ui;

private slots:
    void packListIndexChanged(int index);
    void repeatLevel(void);
    void nextLevel(void);
    void previousLevel(void);
    void updateCurrentTime(void);
    void lessonSelectionListIndexChanged(int index);
    void sublessonSelectionListIndexChanged(int index);
    void levelSelectionListIndexChanged(int index);
    void randomOrderCheckBoxChanged(bool checked);
    void changeFont(QFont font);
    void changeFontSize(int size);
    void setBoldText(void);
    void setItalicText(void);
    void setUnderlineText(void);
    void resetFont(void);
    void changeLevelTextColor(void);
    void changeInputTextColor(void);
    void resetTextColors(void);
    void changeBgColor(void);
    void changePaperColor(void);
    void resetBgPaperColors(void);
    void changeTheme(int index);
};
#endif // OPENTYPER_H
