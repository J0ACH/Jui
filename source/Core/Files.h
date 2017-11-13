#ifndef FILES_H
#define FILES_H

#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QFile>
#include <QColor>
#include <QDebug>

namespace Jui
{
	// Data /////////////////////////////////////////////////////

	// Node /////////////////////////////////////////////////////

	class Node {
	public:
		Node();
		Node(QString key, QVariant value, Node *parent = 0);

		void key(QString name);
		void value(QVariant val);
		void value(QMap<QString, QVariant> val);
		void tabs(int n);

		operator QByteArray();
		operator QString();
		operator int();
		operator double();
		operator QMap<QString, QVariant>();

	private:
		Node *parent;
		QString m_key, m_tabs;
		QVariant m_value;

		static QString asString(Node value);
		static Node asNode(QString txt);
	};

	// Data /////////////////////////////////////////////////////

	class Data {
	public:
		Data();

		void add(QString key, QString value);
		void add(QString key, int value);
		void add(QString key, double value);
		void add(QString key, Data value);
		void add(QString key, int red, int green, int blue, int alpha = 255);

		//void add(QString key, QVariant value);		

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
		File(QString path, QString name);

		void write(QString data);
		void write(Data data);

		void show();

	private:
		QFile file;
	};
}

#endif // FILES_H
