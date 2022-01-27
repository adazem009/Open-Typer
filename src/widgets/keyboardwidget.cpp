/*
 * keyboardwidget.cpp
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

#include "widgets/keyboardwidget.h"

/*! Constructs keyboardWidget. */
keyboardWidget::keyboardWidget(QWidget *parent) :
	QFrame(parent),
	mainLayout(new QVBoxLayout(this)),
	currentRow(-1),
	currentColumn(0)
{
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->setSpacing(3);
	mainLayout->setContentsMargins(0,0,0,0);
	keys.clear();
	keyLabels.clear();
	keyMap.clear();
	// Numeric row
	nextRow();
	for(int i=0; i < 13; i++)
		addKey();
	addKey("⌫",Qt::Key_Backspace,125);
	// Above main row
	nextRow();
	addKey("Tab ⭾",Qt::Key_Tab,75);
	for(int i=0; i < 12; i++)
		addKey();
	// Main row
	nextRow();
	addKey("Caps lock",Qt::Key_CapsLock,100);
	for(int i=0; i < 12; i++)
		addKey();
	addKey("⏎",Qt::Key_Return,75);
	// Below main row
	nextRow();
	addKey("⇧ Shift",Qt::Key_Shift,125);
	for(int i=0; i < 10; i++)
		addKey();
	addKey("Shift ⇧",-2,156); // Qt doesn't recognize left and right shift; -2 is a special code for right shift
	// Bottom row
	nextRow();
	addKey("Ctrl",Qt::Key_Control,75);
	addKey("Alt",Qt::Key_Alt,75);
	addKey("",Qt::Key_Space,475);
	addKey("Alt",Qt::Key_AltGr,75);
	addKey("Ctrl",Qt::Key_Control,103);
}

/*! Adds a key. */
void keyboardWidget::addKey(QString keyLabelText, int keyCode, int keyMinimumWidth)
{
	if(currentRowLayout == nullptr)
		return;
	if(!keyLabelText.contains("\n"))
		keyLabelText += "\n";
	// Create key frame
	QFrame *newKey = new QFrame(this);
	newKey->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	newKey->setMinimumWidth(keyMinimumWidth);
	newKey->setFrameShape(QFrame::WinPanel);
	newKey->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
	currentRowLayout->addWidget(newKey);
	keyMap.insert(QPair<int,int>(currentRow,currentColumn),newKey);
	currentRow++;
	// Create key label
	QHBoxLayout *keyLayout = new QHBoxLayout(newKey);
	QLabel *keyLabel = new QLabel(keyLabelText,newKey);
	keyLabel->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
	keyLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	keyLabel->setMargin(0);
	keyLayout->addWidget(keyLabel);
	keyLayout->setContentsMargins(1,1,1,1);
	keyLabels.insert(newKey,keyLabel);
	// Save the key
	keys.insert(newKey,keyCode);
}

/*! Starts a new row. */
void keyboardWidget::nextRow(void)
{
	QFrame *currentRowFrame = new QFrame(this);
	currentRowFrame->setContentsMargins(0,0,0,0);
	currentRowFrame->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
	currentRowFrame->setFrameShape(QFrame::NoFrame);
	currentRowFrame->setFrameStyle(QFrame::NoFrame | QFrame::Plain);
	currentRowLayout = new QHBoxLayout(currentRowFrame);
	currentRowLayout->setSizeConstraint(QLayout::SetFixedSize);
	currentRowLayout->setSpacing(3);
	currentRowLayout->setContentsMargins(0,0,0,0);
	mainLayout->addWidget(currentRowFrame);
	currentRow++;
	currentColumn = 0;
}

/*! Adds a layout-specific key. */
void keyboardWidget::registerKey(int row, int column, QString keyLabelText, int keyCode, int shiftKeyCode)
{
	QPair<int,int> keyPos = QPair<int,int>(row,column);
	if(!keyMap.contains(keyPos))
		return;
	QFrame *targetKeyFrame = keyMap[keyPos];
	keys.insert(targetKeyFrame,keyCode);
	keys.insert(targetKeyFrame,shiftKeyCode);
	keyLabels[targetKeyFrame]->setText(keyLabelText);
}

/*! Sets style sheet of all keys. */
void keyboardWidget::setKeyStyleSheet(QString styleSheet)
{
	QList<QFrame*> keyList = keys.keys();
	for(int i=0; i < keyList.count(); i++)
		keyList[i]->setStyleSheet(styleSheet);
}

/*! Loads a keyboard layout. */
void keyboardWidget::loadLayout(QLocale::Language language, QLocale::Country country, QString variant)
{
	if(variant == "")
		variant = "QWERTY";
	QLocale inputLocale(language,country);
	QString layoutPath = ":res/keyboard-layouts/" + inputLocale.name() + "-" + variant + ".json";
	QFile layoutFile(layoutPath);
	if(layoutFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QJsonDocument layoutDocument = QJsonDocument::fromJson(layoutFile.readAll());
		QJsonObject layoutObject = layoutDocument.object();
		QJsonArray layoutKeys = layoutObject["keys"].toArray();
		for(int i=0; i < layoutKeys.count(); i++)
		{
			QJsonObject layoutKey = layoutKeys[i].toObject();
			registerKey(layoutKey["x"].toInt(),layoutKey["y"].toInt(),layoutKey["label"].toString(),layoutKey["code"].toInt(),layoutKey["shiftCode"].toInt());
		}
	}
}

/*! Highlights a key. */
void keyboardWidget::highlightKey(int keyCode)
{
	QList<int> keyCodes = keys.values();
	if(keyCodes.contains(keyCode))
	{
		QFrame *targetKey = keys.key(keyCode);
		targetKey->setGraphicsEffect(new QGraphicsColorizeEffect);
	}
}

/*! Dehighlights a key. */
void keyboardWidget::dehighlightKey(int keyCode)
{
	QList<int> keyCodes = keys.values();
	if(keyCodes.contains(keyCode))
	{
		QFrame *targetKey = keys.key(keyCode);
		targetKey->setGraphicsEffect(nullptr);
	}
}

/*! Returns the finger that should be used to press the key. */
keyboardWidget::Finger keyboardWidget::keyFinger(int keyX, int keyY)
{
	if(!keyMap.contains(QPair<int,int>(keyX,keyY)))
		return Finger_Invalid;
	QPoint keyPos(keyX,keyY);
	switch(keyPos.y()) {
		case 0:
			switch(keyPos.x()) {
				case 0:
					return Finger_LeftPinky;
					break;
				case 1:
					return Finger_LeftPinky;
					break;
				case 2:
					return Finger_LeftPinky;
					break;
				case 3:
					return Finger_LeftRing;
					break;
				case 4:
					return Finger_LeftMiddle;
					break;
				case 5:
					return Finger_LeftIndex;
					break;
				case 6:
					return Finger_LeftIndex;
					break;
				case 7:
					return Finger_RightIndex;
					break;
				case 8:
					return Finger_RightIndex;
					break;
				case 9:
					return Finger_RightMiddle;
					break;
				case 10:
					return Finger_RightRing;
					break;
				case 11:
					return Finger_RightPinky;
					break;
				case 12:
					return Finger_RightPinky;
					break;
				case 13:
					return Finger_RightPinky;
					break;
				default:
					return Finger_Invalid;
					break;
			}
			break;
		default:
			return Finger_Invalid;
			break;
	}
}

/*! Finds a key that contains label and returns its position. */
QPoint keyboardWidget::findKey(QString label)
{
	QList<QLabel*> labels = keyLabels.values();
	for(int i=0; i < labels.count(); i++)
	{
		if(labels[i]->text().contains(label,Qt::CaseInsensitive))
		{
			QFrame *targetKey = keyLabels.key(labels[i]);
			QPair<int,int> keyPos = keyMap.key(targetKey);
			return QPoint(keyPos.first,keyPos.second);
		}
	}
	return QPoint();
}

/*!
 * Returns the hand of a finger.\n
 * -1 - Invalid\n
 * 0 - Left\n
 * 1 - Right
 */
int keyboardWidget::fingerHand(keyboardWidget::Finger finger)
{
	if(finger == Finger_Invalid)
		return -1;
	else if((finger == Finger_LeftThumb) ||
		(finger == Finger_LeftIndex) ||
		(finger == Finger_LeftMiddle) ||
		(finger == Finger_LeftRing) || 
		(finger == Finger_LeftPinky))
		return 0;
	return 1;
}
