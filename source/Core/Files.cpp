
#include "Files.h"

namespace Jui
{

	// Path /////////////////////////////////////////////////////

	Path::Path() {}
	Path::Path(QStringList folder) { dir = folder; }
	Path::Path(QString folder) { dir = folder.split("/"); }
	Path::Path(QString f1, QString f2, QString f3, QString f4, QString f5, QString f6) {
		add(f1, f2, f3, f4, f5, f6);
	}

	Path Path::root() { return Path(QDir::rootPath()); }
	Path Path::current() { return Path(QDir::currentPath()); }
	Path Path::home() { return Path(QDir::homePath()); }
	Path Path::temp() { return Path(QDir::tempPath()); }
	Path Path::disk(QString latter) { return Path(latter.toUpper() + ":"); }

	Path &Path::add(QStringList folder) {
		dir.append(folder);
		return *this;
	}
	Path &Path::add(QString folder) { return add(folder.split("/")); }
	Path &Path::add(QString f1, QString f2, QString f3, QString f4, QString f5, QString f6) {
		dir.append(f1);
		dir.append(f2);
		if (!f3.isEmpty()) { dir.append(f3); }
		if (!f4.isEmpty()) { dir.append(f4); }
		if (!f5.isEmpty()) { dir.append(f5); }
		if (!f6.isEmpty()) { dir.append(f6); }
		return *this;
	}
	Path &Path::del() {
		if (dir.size() > 0) { dir.removeLast(); }
		return *this;
	}

	QString Path::toString() { return QStringList(dir).join("/"); }
	QStringList Path::toList() { return QStringList(dir); }

	Path Path::operator + (Path otherPath) {
		QStringList newPath(toList());
		newPath.append(otherPath.toList());
		return Path(newPath);
	}

	QDebug operator<<(QDebug dbg, Path &path)
	{
		dbg.nospace() << "Path(" << path.toString() << ")";
		return dbg.space();
	}
	QDebug operator<<(QDebug dbg, Path *path)
	{
		dbg.nospace() << *path;
		return dbg.space();
	}

	// File /////////////////////////////////////////////////////

	File::File(Path path, QString name, QString extension) {

		QString fileName = QString("%1.%2").arg(name, extension);
		qDebug() << "path:" << fileName;
		qDebug() << "fileName:" << fileName;
		file.setFileName(fileName);
	}

	bool File::show(Path folder) {
		bool done = false;
		QString path = folder.toString();
		if (QDir(path).exists()) { done = QDesktopServices::openUrl(QUrl(path)); }
		else { qDebug() << "Directory at" << path << "not found"; }
		return done;
	}
	bool File::exist(Path folder) { return QDir(folder.toString()).exists(); }
	bool File::make(Path folder) {
		bool done = false;
		QString path = folder.toString();
		if (!File::exist(folder))
		{
			QDir::setCurrent(path);
			QDir dir = QDir::current();
			done = dir.mkpath(path);
		}
		return done;
	}

	/*
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
	*/


	// Leaf /////////////////////////////////////////////////////

	Leaf::Leaf() {
		map = QMap<QString, QVariant>();
		tabs(1);
	}
	Leaf::Leaf(QString name, QVariant val) {
		map = QMap<QString, QVariant>();
		tabs(1);
		key_(name);
		value_(val);
	}
	Leaf::Leaf(QByteArray ba) {
		QList<QByteArray> lines = ba.split('\n');
		foreach(const QByteArray oneLine, lines)
		{
			qDebug() << oneLine;
		}
	}
	/*
	Leaf::Leaf(QString folder, QString key, QVariant value) {
		map.insert("path", folder);
		map.insert("key", key);
		map.insert("value", value);
		map.insert("type", value.typeName());
	}
	*/

	void Leaf::key_(QString name) { map.insert("key", name); }
	void Leaf::value_(QVariant val) {
		map.insert("type", QVariant::nameToType(val.typeName()));
		switch (val.type())
		{
		case QVariant::Type::Color:
			map.insert("red", val.value<QColor>().red());
			map.insert("green", val.value<QColor>().green());
			map.insert("blue", val.value<QColor>().blue());
			map.insert("alpha", val.value<QColor>().alpha());
			break;
		default:
			map.insert("value", val);
			break;
		}
	}
	void Leaf::level_(int n) {
		if (n < 1) { n = 1; }
		map.insert("level", n);
	}

	QString Leaf::key() { return map.value("key").toString(); }
	QVariant Leaf::value() { return map.value("value"); }
	QVariant::Type Leaf::type() { return QVariant::nameToType(map.value("type").typeName()); }

	Leaf::operator QString() {
		QMap<QString, QVariant> data(map);
		QString txt;
		QString key = data.take("key").toString();
		QString type = data.take("type").typeName();
		int level = data.take("level").toInt();

		txt += tabs(level - 1) + "[\n";
		txt += tabs(level) + "key: " + key + ",\n";
		txt += tabs(level) + "type: " + type + ",\n";

		foreach(QString key, data.keys())
		{
			txt += tabs(level);
			txt += key + ": ";
			txt += data.value(key).toString();
			if (key != data.keys().last()) { txt += ","; };
			txt += "\n";
		}
		txt += tabs(level - 1) + "]\n";
		return txt;
	}

	QString Leaf::tabs(int level) {
		QString tabs = "";
		for (int i = 0; i <= level; i++) { tabs += "\t"; };
		return tabs;
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
		Leaf leaf;
		leaf.key_(key);
		leaf.value_(value);

		/*
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
			break;
		};
		*/
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
	/*
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
	*/


}