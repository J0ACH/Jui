
#include "Files.h"

namespace Jui
{
	// Folder /////////////////////////////////////////////////////

	Folder::Folder() {
		dir = QDir::current();
	}
	Folder::Folder(QString path) {
		dir = QDir(path);
		if (!dir.exists()) { bool done = dir.mkpath(dir.path()); }
	}

	void Folder::make(QString name) { dir.mkdir(name); }

	void Folder::enter(QString name) {
		bool done = dir.cd(name);
		if (!done) { qDebug() << "Folder::enter err (" << name << ") at" << current(); }
	}
	void Folder::escape() { dir.cdUp(); }

	QString Folder::current() {
		QString currentPath = dir.path();
		qDebug() << "Folder::current:" << currentPath;
		//QDir::setCurrent(currentPath);
		return currentPath;
	}

	void Folder::show() {
		bool done = QDesktopServices::openUrl(QUrl(current()));
	}

	// File /////////////////////////////////////////////////////

	File::File(QString name) {
		file.setFileName(name);
		file.open(QIODevice::WriteOnly);
		file.write("ahoj");        // write to stderr
		file.close();
	}

	File::File(Folder path, QString name) {
		QDir::setCurrent(path.current());
		file.setFileName(name);
		file.open(QIODevice::WriteOnly);
		file.write("ahoj");        // write to stderr
		file.close();
	}
}