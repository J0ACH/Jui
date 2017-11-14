
#include "Files.h"

namespace Jui
{
	// Leaf /////////////////////////////////////////////////////

	Leaf::Leaf(QString key, QVariant value) {
		map.insert("path", "");
		map.insert("key", key);
		map.insert("value", value);
		map.insert("type", QVariant::nameToType(value.typeName()));
	}
	Leaf::Leaf(QString folder, QString key, QVariant value) {
		map.insert("path", folder);
		map.insert("key", key);
		map.insert("value", value);
		map.insert("type", value.typeName());
	}

	QString Leaf::key() { return map.value("key").toString(); }
	QVariant Leaf::value() { return map.value("value"); }
	QVariant::Type Leaf::type() { return QVariant::nameToType(map.value("type").typeName()); }

	Leaf::operator QString() {
		QString txt;
		txt += map.value("key").toString() + " [\n";
		foreach(QString key, map.keys())
		{
			if (key != "key") {
				txt += map.value(key).toString() + ",\n";
			}
		}
		txt += "]\n";
		return txt;
	}

	// Data /////////////////////////////////////////////////////

	Data::Data() {
		currentLevel = 1;
	}

	Data::Data(QByteArray ba) {
		//qDebug() << "Data(QByteArray ba) /////////////////////";

		QList<QByteArray> lines = ba.split('\n');
		foreach(const QByteArray oneLine, lines)
		{
			//qDebug() << oneLine;
		}
	}

	void Data::add(QString key, QVariant value) {
		Data data;
		QColor color;
		QFont font;

		switch (value.type())
		{
		case QVariant::Type::Color:
			color = value.value<QColor>();
			data.add("red", color.red());
			data.add("green", color.green());
			data.add("blue", color.blue());
			data.add("alpha", color.alpha());
			add(key, data);
			break;
		case QVariant::Type::Font:
			font = value.value<QFont>();
			data.add("family", font.family());
			data.add("pointSize", font.pointSize());
			add(key, data);
			break;
		case QVariant::Type::Map:
			library.insert(key, value.toMap());
			break;
		default:
			library.insert(key, value);
			/*
			//qDebug() << library.value(key).typeName();
			data.add("type", value.typeName());
			data.add("value", value.toString());
			//add(key, data);
			qDebug() << value.typeName();
			library.insert(key, data.map());
			*/
			break;
		};
	}
	void Data::add(QString key, Data value) { library.insert(key, value.map()); }

	QVariant Data::at(QString key) { return library.value(key); }
	QList<QString> Data::keys() { return library.keys(); }
	QList<QVariant> Data::nodes() { return library.values(); }
	QMap<QString, QVariant> Data::map() { return library; }

	void Data::print() { foreach(QString oneLine, map2string(library)) { qDebug() << oneLine; } }

	QStringList Data::map2string(QMap<QString, QVariant> data, int level) {
		QMap<QString, QVariant> temp;
		QStringList txt;
		QString tabs = "";
		for (int i = 0; i < level; i++) { tabs += "    "; }
		//for (int i = 0; i < level; i++) { tabs += "\t"; }

		foreach(QString key, data.keys())
		{
			QVariant value = data.value(key);
			switch (data.value(key).type())
			{
			case QVariant::Type::Map:
				txt.append(tabs + "- " + key + "[" + value.typeName() + "]: ");
				foreach(QString oneLine, map2string(value.toMap(), level + 1)) {
					txt.append(oneLine);
				}
				//txt.append(tabs + "-");
				break;
			default:

				txt.append(tabs + "- " + key + "[" + value.typeName() + "]: " + value.toString());
				//txt.append(tabs + "- " + key + ": " + value.toString());
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
	QByteArray File::read() {
		//if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
		QByteArray ba;
		file.open(QIODevice::ReadOnly);
		while (!file.atEnd()) {
			ba.append(file.readLine());
			//process_line(line);
		}
		file.close();
		return ba;
	}

	void File::show() {
		bool done = QDesktopServices::openUrl(QUrl(QDir::currentPath()));
	}
}