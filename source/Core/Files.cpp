
#include "Files.h"

namespace Jui
{
	// Node /////////////////////////////////////////////////////

	Node::Node() { m_tabs = ""; }
	Node::Node(QString key, QVariant value, Node *parent) : m_key(key), m_value(value) { m_tabs = ""; }

	void Node::key(QString name) { m_key = name; }
	void Node::value(QVariant val) { m_value = val; }
	void Node::value(QMap<QString, QVariant> val) {

	};
	void Node::tabs(int n) {
		m_tabs = "";
		for (int i = 0; i < n; i++) { m_tabs += "\t"; }
	}

	Node::operator QByteArray() {
		qDebug() << "m_value.typeName():" << m_value.type();
		QString txt;

		switch (m_value.type())
		{
		case QVariant::Type::Map:
			QMap<QString, QVariant> map = m_value.toMap();
			foreach(QString oneKey, map.keys())
			{
				qDebug() << " QVariant::Type::Map::" << oneKey;
			}
			break;
		}
		txt = m_tabs + "- " + m_key + ": " + m_value.toString() + "\n";
		return txt.toUtf8();
	}
	Node::operator QString() {
		switch (m_value.type())
		{
		case QVariant::Int:	return QString::number(m_value.toInt());
		case QVariant::Double: return QString::number(m_value.toDouble());
		default: return m_value.toString();
		}
	}
	Node::operator int() { return m_value.toInt(); }
	Node::operator double() { return m_value.toDouble(); }
	Node::operator QMap<QString, QVariant>() { return m_value.toMap(); }

	QString Node::asString(Node node) {
		QString txt;
		/*
		switch (m_value.type())
		{
		case QVariant::Int:	txt + QString::number(value.toInt());
		case QVariant::Double: return QString::number(value.toDouble());
		default: return value.toString();
		}
		*/

		//txt = m_tabs + "- " + m_key + ": " + m_value.toString() + "\n";
		return txt;
	}

	Node Node::asNode(QString txt) {
		Node node;
		return node;
	}


	// Data /////////////////////////////////////////////////////

	Data::Data() {
		currentLevel = 1;
	}

	void Data::add(QString key, QString value) { library.insert(key, value); }
	void Data::add(QString key, int value) { library.insert(key, value); }
	void Data::add(QString key, double value) { library.insert(key, value); }
	void Data::add(QString key, Data value) { library.insert(key, value.map()); }
	void Data::add(QString key, int red, int green, int blue, int alpha) {
		Data color;
		color.add("red", red);
		color.add("green", green);
		color.add("blue", blue);
		color.add("alpha", alpha);
		add(key, color);
	}

	QVariant Data::at(QString key) { return library.value(key); }
	QList<QString> Data::keys() { return library.keys(); }
	QList<QVariant> Data::nodes() { return library.values(); }
	QMap<QString, QVariant> Data::map() { return library; }

	void Data::print() { foreach(QString oneLine, map2string(library)) { qDebug() << oneLine; } }

	QStringList Data::map2string(QMap<QString, QVariant> data, int level) {
		QStringList txt;
		QString tabs = "";
		for (int i = 0; i < level; i++) { tabs += "\t"; }

		foreach(QString key, data.keys())
		{
			QVariant value = data.value(key);
			switch (data.value(key).type())
			{
			case QVariant::Type::Map:
				txt.append(tabs + "- " + key + ": ");
				foreach(QString oneLine, map2string(value.toMap(), level + 1)) { txt.append(oneLine); }
				//txt.append(tabs + "-");
				break;
			default:
				txt.append(tabs + "- " + key + ": " + value.toString());
				break;
			}
		}
		return txt;
	}

	Data::operator QByteArray() {
		QByteArray ba;
		foreach(QString oneLine, map2string(library)) { ba.append(oneLine + "\n"); }
		return ba;
	}

	Data::operator QString() {
		QString txt;
		foreach(QString oneLine, map2string(library)) { txt += oneLine + "\n"; }
		return txt;
	}


	// Folder /////////////////////////////////////////////////////

	Folder::Folder() {
		dir = QDir::current();
	}
	Folder::Folder(QString path) {
		dir = QDir(path);
		if (!dir.exists()) { bool done = dir.mkpath(dir.path()); }
		QDir::setCurrent(path);
	}

	void Folder::make(QString name) { dir.mkdir(name); }

	void Folder::enter(QString name) {
		bool done = dir.cd(name);
		if (done) { QDir::setCurrent(dir.path()); }
		//else { qDebug() << "Folder::enter err (" << name << ") at" << current(); }
	}
	void Folder::escape() {
		bool done = dir.cdUp();
		if (done) { QDir::setCurrent(dir.path()); }
	}

	QString Folder::current() { return QDir::currentPath(); }

	void Folder::show() {
		bool done = QDesktopServices::openUrl(QUrl(current()));
	}

	// File /////////////////////////////////////////////////////

	File::File(QString name) {
		file.setFileName(name);
	}
	File::File(QString path, QString name) {
		Folder::Folder(path);
		file.setFileName(name);
	}

	void File::write(QString data) {
		file.open(QIODevice::WriteOnly);
		file.write(data.toUtf8());
		file.close();
	}
	void File::write(Data data) {
		file.open(QIODevice::WriteOnly);
		file.write(data);
		file.close();
	}

	void File::show() {
		bool done = QDesktopServices::openUrl(QUrl(QDir::currentPath()));
	}
}