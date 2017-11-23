
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

	Path Path::root() { return Path().add("root"); }
	Path Path::disk(QString latter) { return Path(latter.toUpper() + ":"); }
	Path Path::current() { return Path(QDir::currentPath()); }
	Path Path::home() { return Path(QDir::homePath()); }
	Path Path::temp() { return Path(QDir::tempPath()); }

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
	int Path::level() { return dir.size() - 1; }

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
		QString fileName;
		if (!name.isEmpty()) { fileName = QString("%1/%2.%3").arg(path.toString(), name, extension); }
		else { fileName = QString("%2.%3").arg(name, extension); }
		file.setFileName(fileName);
	}

	void File::show(Path folder) {
		QString path = folder.toString();
		if (QDir(path).exists() || QFile(path).exists()) { QDesktopServices::openUrl(QUrl(path)); }
		else { qDebug() << "Directory at" << path << "not found"; }
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

	bool File::exist() { return file.exists(); }
	int File::size() { return file.size(); }
	QString File::name() { return file.fileName(); }

	QStringList File::readLines() {
		QStringList list;
		if (file.open(QIODevice::ReadOnly)) {
			while (!file.atEnd()) { list.append(QString(file.readLine())); }
			file.close();
		}
		return list;
	}
	QStringList File::read(QString separator) {
		QString txt;
		if (file.open(QIODevice::ReadOnly)) {
			while (!file.atEnd()) { txt += QString(file.readLine()); }
			file.close();
		}
		return txt.split(separator);
	}

	File &File::show() {
		QString path = file.fileName();
		if (exist()) { QDesktopServices::openUrl(QUrl(path)); }
		else { qDebug() << "File" << path << "doesn't exist"; }
		return *this;
	}
	File &File::write(QString txt, bool newLine) {
		if (file.open(QIODevice::WriteOnly)) {
			file.write(txt.toUtf8());
			if (newLine) { file.write("\n"); }
			file.close();
		}
		return *this;
	}
	File &File::append(QString txt, bool newLine) {
		if (file.open(QIODevice::WriteOnly | QIODevice::Append))
		{
			file.write(txt.toUtf8());
			if (newLine) { file.write("\n"); }
			file.close();
		}
		return *this;
	}

	QDebug operator<<(QDebug dbg, File &file)
	{
		dbg.nospace() << "File(" << file.name() << ")";
		return dbg.space();
	}
	QDebug operator<<(QDebug dbg, File *file)
	{
		dbg.nospace() << *file;
		return dbg.space();
	}

	/*
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

	Leaf::Leaf() { Leaf::Leaf(Path::root(), "Untitled", "Nan"); }
	Leaf::Leaf(QString name, QVariant val) { Leaf::Leaf(Path::root(), name, val); }
	Leaf::Leaf(Path path, QString name, QVariant val) {
		key_(name);
		value_(val);
		path_(path);
	}
	Leaf::Leaf(QByteArray ba) {
		QList<QByteArray> lines = ba.split('\n');
		foreach(const QByteArray oneLine, lines)
		{
			qDebug() << oneLine;
		}
	}

	Leaf &Leaf::path_(Path folder) {
		map.insert("path", folder.toString());
		return *this;
	}
	Leaf &Leaf::key_(QString name) {
		map.insert("key", name);
		return *this;
	}
	Leaf &Leaf::value_(QVariant val) {
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
		return *this;
	}

	QString Leaf::key() { return map.value("key").toString(); }
	QVariant Leaf::value() { return map.value("value"); }
	QVariant::Type Leaf::type() { return QVariant::nameToType(map.value("type").typeName()); }
	Path Leaf::path() { return Path(map.value("path").toString().split("/")); }
	int Leaf::level() { return path().level(); }

	QString Leaf::toString() {
		QString txt;
		QMap<QString, QVariant> data(map);
		QString strPath = data.take("path").toString();
		QString strKey = data.take("key").toString();
		QString strType = data.take("type").typeName();

		txt += tabs(level()) + "[\n";
		txt += tabs(level() + 1) + "path: " + strPath + ",\n";
		txt += tabs(level() + 1) + "key: " + strKey + ",\n";
		txt += tabs(level() + 1) + "type: " + strType + ",\n";

		foreach(QString oneKey, data.keys())
		{
			txt += tabs(level() + 1);
			txt += oneKey + ": ";
			txt += data.value(oneKey).toString();
			if (oneKey != data.keys().last()) { txt += ","; };
			txt += "\n";
		}
		txt += tabs(level()) + "]\n";
		return txt;
	}

	QString Leaf::tabs(int level) {
		QString tabs = "";
		for (int i = 0; i < level; i++) { tabs += "\t"; };
		return tabs;
	}

	QDebug operator<<(QDebug dbg, Leaf &leaf)
	{
		dbg.nospace() << "Leaf(" << leaf.key() << ")";
		return dbg.space();
	}
	QDebug operator<<(QDebug dbg, Leaf *leaf)
	{
		dbg.nospace() << *leaf;
		return dbg.space();
	}


	// Data /////////////////////////////////////////////////////

	Data::Data() { }

	Data::Data(QByteArray ba) {
		//qDebug() << "Data(QByteArray ba) /////////////////////";

		QList<QByteArray> lines = ba.split('\n');
		foreach(const QByteArray oneLine, lines)
		{
			//qDebug() << oneLine;
		}
	}

	Data &Data::add(Leaf leaf)
	{
		library.insert(mapPath(leaf), leaf);
		qDebug() << "add:" << mapPath(leaf);
		return *this;
	}
	Data &Data::add(Path path, QString key, QVariant value)
	{
		add(Leaf(path, key, value));
		return *this;
	}

	Leaf Data::at(Path path, QString key) { return library.value(mapPath(path, key)); }
	QStringList Data::keys() { return library.keys(); }
	QList<Leaf> Data::filter(Path path) {
		QList<Leaf> list;
		QStringList paths = keys().filter(path.toString());
	//	qDebug() << path.toString();
		foreach(QString onePath, paths) {
			//list.append(at(onePath));
			qDebug() << onePath;
		}
		return list;
	}

	QString Data::toString() {
		QString txt;
		foreach(Leaf oneLeaf, library) {
			txt += oneLeaf.toString();// +"\n";
			//if (oneLeaf != library2.values().last()) { txt += ","; };

		}
		return txt;
	}

	QString Data::mapPath(Path path, QString key) {
		return path.toString() + "/" + key;
	}
	QString Data::mapPath(Leaf leaf) {
		return leaf.path().toString() + "/" + leaf.key();
	}

	/*
	void Data::add(QString key, QVariant value) {
		Leaf leaf;
		leaf.key_(key);
		leaf.value_(value);
	*/

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
	//	}

		//void Data::add(QString key, Data value) { library.insert(key, value.map()); }
	/*
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
	*/



}