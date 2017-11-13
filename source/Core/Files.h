#ifndef FILES_H
#define FILES_H

#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QFile>
#include <QDebug>

namespace Jui
{
	// Node /////////////////////////////////////////////////////

	class Node {
	public:
		Node();
		Node(QString key, QVariant value);

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
		QString m_key, m_tabs;
		QVariant m_value;

		static QString asString(Node value);
		static Node asNode(QString txt);
	};

	// Data /////////////////////////////////////////////////////

	class Data {
	public:
		Data();

		void add(QString key, QVariant value);
		void add(QString key, Data value);

		QVariant at(QString key);
		QList<QVariant> nodes();
		QList<QString> keys();
		QMap<QString, QVariant> map();

		void print();

		operator QByteArray();

	private:
		//QMultiMap<QString, Node> library;
		QMap<QString, QVariant> library;
		int currentLevel;

		static QString level(int n);
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
