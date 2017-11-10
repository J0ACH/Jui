#ifndef FILES_H
#define FILES_H

#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QDebug>

namespace Jui
{
	class Folder {
	public:
		Folder();
		Folder(QString path);

		void makeFolder(QString name);

		void enter(QString name);
		void escape();

		QString current();
		void show();

	private:
		QDir dir;
	};
}

#endif // FILES_H
