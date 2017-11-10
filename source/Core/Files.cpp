
#include "Files.h"

namespace Jui
{
	Folder::Folder() {
		dir = QDir::current();
	}
	Folder::Folder(QString path) {
		dir = QDir(path);
		if (!dir.exists()) { bool done = dir.mkpath(dir.path()); }
	}

	void Folder::makeFolder(QString name) { dir.mkdir(name); }

	void Folder::enter(QString name) {
		bool done = dir.cd(name);
		if (!done) { qDebug() << "Folder::enter err (" << name << ") at" << current(); }
	}
	void Folder::escape() { dir.cdUp(); }

	QString Folder::current() {
		QString currentPath = dir.path();
		qDebug() << "Folder::current:" << currentPath;
		return currentPath;
	}

	void Folder::show() {
		bool done = QDesktopServices::openUrl(QUrl(current()));
	}
}