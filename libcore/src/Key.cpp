/*
 * Key.cpp
 * This file is part of Open-Typer
 *
 * Copyright (C) 2023 - adazem009
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

#include <QMetaEnum>
#include "Key.h"

/*! Constructs Key. */
Key::Key() { }

/*! Constructs Key (with properties). */
Key::Key(QString text, QString shiftText)
{
	setText(text);
	setShiftText(shiftText);
}

/*! The text for this key. */
QString Key::text(void)
{
	return m_text;
}

void Key::setText(QString text)
{
	m_text = text;
}

/*! The text for this key when pressed with shift. */
QString Key::shiftText(void)
{
	return m_shiftText;
}

void Key::setShiftText(QString text)
{
	m_shiftText = text;
}

/*! The type of the key (string representation of a Type enum member). */
QString Key::type(void)
{
	QMetaEnum metaEnum = QMetaEnum::fromType<Qt::Key>();
	return metaEnum.valueToKey(m_type);
}

/*! Sets the key type using a Type value. */
void Key::setTypeFromEnum(Type type)
{
	m_type = type;
}
