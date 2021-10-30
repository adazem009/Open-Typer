/*
 * packselector.cpp
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

#include "packEditor/packselector.h"
#include "ui_packselector.h"

packSelector::packSelector(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::packSelector)
{
	ui->setupUi(this);
	// Load built-in packs
	QDirIterator it(":/res/configs/",QDirIterator::NoIteratorFlags);
	int i;
	QString item, current;
	QStringList items;
	while(it.hasNext())
	{
		item = it.next();
		current = "";
		for(i=14; i < QStringLen(item); i++)
			current += item[i];
		items += current;
	}
	ui->selBox->addItems(items);
	// Connect buttons
	connect(ui->loadButton,SIGNAL(clicked()),this,SLOT(accept()));
	connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

packSelector::~packSelector()
{
	delete ui;
}

QString packSelector::selectedConfig(void)
{
	return ui->selBox->currentText();
}
