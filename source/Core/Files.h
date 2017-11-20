#ifndef FILES_H
#define FILES_H

#include <QQueue>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QFile>
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
		static Path current();
		static Path home();
		static Path temp();
		static Path disk(QString latter = "C");

		Path &add(QStringList folder);
		Path &add(QString folder);
		Path &add(QString f1, QString f2, QString f3 = "", QString f4 = "", QString f5 = "", QString f6 = "");
		Path &del();

		QString toString();
		QStringList toList();
	
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

		static bool show(Path folder);
		static bool exist(Path folder);
		static bool make(Path folder);
		
		/*
		void write(QString data);
		void write(Data data);
		QByteArray read();
		*/		

	private:
		QFile file;
	};


	// Leaf /////////////////////////////////////////////////////

	class Leaf {
	public:
		Leaf();
		Leaf(QString name, QVariant val);
		Leaf(QByteArray ba);

		void key_(QString name);
		void value_(QVariant val);
		void level_(int n);

		QString key();
		QVariant value();
		QVariant::Type type();
		int level();

		operator QString();

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

	// Folder /////////////////////////////////////////////////////
/*
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
*/
}


#endif // FILES_H
