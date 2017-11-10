#ifndef FILES_H
#define FILES_H

#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QFile>
#include <QDebug>

namespace Jui
{
	// Folder /////////////////////////////////////////////////////

	class Folder {
	public:
		Folder();
		Folder(QString path);

		void make(QString name);

		void enter(QString name);
		void escape();

		QString current();
		void show();

	private:
		QDir dir;
	};

	// File /////////////////////////////////////////////////////

	class File {
	public:
		File(QString name);
		File(Folder path, QString name);
	private:
		QFile file;
	};
}

#endif // FILES_H
