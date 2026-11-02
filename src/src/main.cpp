/***************************************************************************
 *   Copyright (C) 2008, 2009, 2010, 2011 by Miguel Escudero Gestal
 *   miguelescudero@users.sourceforge.net
 *
 *   This file is part of tubularix
 *
 *   tubularix is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   tubularix is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 ***************************************************************************/

#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QSettings>
#include <QStringList>
#include <QTranslator>

#ifdef __HAIKU__
#include <FindDirectory.h>
#include <StorageDefs.h>
#endif


//Directories that may contain the compiled translations (*.qm)
static QStringList translationDirectories()
{
	QStringList directories;
	const QString applicationDir = QCoreApplication::applicationDirPath();

	//running from the build tree or from an unpackaged copy next to the binary
	directories << applicationDir
		<< applicationDir + "/translations"
		<< applicationDir + "/../translations";

#ifdef __HAIKU__
	//installed through a package: /boot/system/data/tubularix
	//installed by hand: ~/config/non-packaged/data/tubularix
	char path[B_PATH_NAME_LENGTH];
	if(find_directory(B_SYSTEM_DATA_DIRECTORY, -1, false, path, sizeof(path)) == B_OK)
		directories << QString::fromLocal8Bit(path) + "/tubularix";
	if(find_directory(B_USER_NONPACKAGED_DATA_DIRECTORY, -1, false, path, sizeof(path)) == B_OK)
		directories << QString::fromLocal8Bit(path) + "/tubularix";
#endif

	return directories;
}

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QCoreApplication::setOrganizationName("tubularix");
	QCoreApplication::setOrganizationDomain("tubularix.sourceforge.net");
	QCoreApplication::setApplicationName("tubularix");

	//Read settings to establish game's language
	QSettings settings;
	settings.beginGroup("General");

	const QString language = settings.value("language", QLocale::system().name()).toString();
	const QString translationFile = QString("tubularix_") + language;

	QTranslator translator;
	const QStringList directories = translationDirectories();
	for(int i = 0; i < directories.size(); i++)
	{
		if(translator.load(translationFile, directories.at(i)))
			break;
	}
	if(translator.isEmpty())
		translator.load(translationFile); //Qt's standard translation directories
	app.installTranslator(&translator);
	settings.endGroup();

	//Qt5 always uses UTF-8 for tr() strings, so the Qt4 codec setup
	//(QTextCodec::setCodecForTr) is neither needed nor available anymore.

	MainWindow win;
	//win.setGeometry(20, 80, 1024, 900);
	win.show();

	return app.exec();
}
