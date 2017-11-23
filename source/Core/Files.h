#ifndef FILES_H
#define FILES_H

#include <QQueue>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QFile>
#include <QStorageInfo>
#include <QColor>
#include <QFont>
#include <QDebug>

namespace Jui
{

	// Path /////////////////////////////////////////////////////

	class Path {
	public:
		Path();
		Path(QStringList folder);
		Path(QString folder);
		Path(QString f1, QString f2, QString f3 = "", QString f4 = "", QString f5 = "", QString f6 = "");

		static Path root();
		static Path disk(QString latter = "C");
		static Path current();
		static Path home();
		static Path temp();

		Path &add(QStringList folder);
		Path &add(QString folder);
		Path &add(QString f1, QString f2, QString f3 = "", QString f4 = "", QString f5 = "", QString f6 = "");
		Path &del();

		QString toString();
		QStringList toList();
		int level();

		Path operator + (Path otherPath);

	private:
		QStringList dir;
	};
	QDebug operator<<(QDebug dbg, Path *path);
	QDebug operator<<(QDebug dbg, Path &path);

	// File /////////////////////////////////////////////////////

	class File {
	public:
		File(Path path, QString name = "", QString extension = "txt");

		static void show(Path folder);
		static bool exist(Path folder);
		static bool make(Path folder);

		bool exist();
		int size();
		QString name();
		QStringList readLines();
		QStringList read(QString separator = "\n");

		File &show();
		File &write(QString txt, bool newLine = true);
		File &append(QString txt, bool newLine = true);

		/*
		void write(Data data);
		QByteArray read();
		*/

	private:
		QFile file;
	};
	QDebug operator<<(QDebug dbg, File *file);
	QDebug operator<<(QDebug dbg, File &file);

	// Leaf /////////////////////////////////////////////////////

	class Leaf {
	public:
		Leaf();
		Leaf(QString name, QVariant val);
		Leaf(Path path, QString name, QVariant val);
		Leaf(QByteArray ba);

		Leaf &path_(Path folder);
		Leaf &key_(QString name);
		Leaf &value_(QVariant val);

		QString key();
		QVariant value();
		QVariant::Type type();
		int level();
		Path path();

		QString toString();

	private:
		QMap<QString, QVariant> map;
		QString tabs(int level);
	};

	// Data /////////////////////////////////////////////////////

	class Data {
	public:
		Data();
		Data(QByteArray ba);

		void add(QString key, QVariant value);
		void add(QString key, Data value);

		QVariant at(QString key);
		QList<QVariant> nodes();
		QList<QString> keys();
		QMap<QString, QVariant> map();

		void print();
		operator QByteArray();
		operator QString();

	private:
		QMap<QString, QVariant> library;

		QStringList map2string(QMap<QString, QVariant> data, int level = 0);
		int currentLevel;

	};

}


#endif // FILES_H
