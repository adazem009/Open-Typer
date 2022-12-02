/*
 * BuiltInPacks.cpp
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

#include "BuiltInPacks.h"

/*! Returns human-readable name of the built-in pack. */
QString BuiltInPacks::packName(QString rawName)
{
	QString autoGeneratedTr = QObject::tr("auto-generated");
	// Human-readable built-in pack names
	if(rawName == "sk_SK-QWERTZ-B1")
		return "SK QWERTZ (ADK)";
	else if(rawName == "sk_SK-QWERTZ-A")
		return "SK QWERTZ (" + autoGeneratedTr + ")";
	else if(rawName == "sk_SK-QWERTY-A")
		return "SK QWERTY (" + autoGeneratedTr + ")";
	else if(rawName == "cs_CZ-QWERTZ-A")
		return "CZ QWERTZ (" + autoGeneratedTr + ")";
	else if(rawName == "cs_CZ-QWERTY-A")
		return "CZ QWERTY (" + autoGeneratedTr + ")";
	else if(rawName == "en_US-default-A")
		return "EN (USA) (" + autoGeneratedTr + ")";
	else if(rawName == "de_DE-QWERTZ-A")
		return "DE QWERTZ (DE) (" + autoGeneratedTr + ")";
	else if(rawName == "de_DE-QWERTY-A")
		return "DE QWERTY (DE) (" + autoGeneratedTr + ")";
	else
		return QObject::tr("Unknown pack");
}
