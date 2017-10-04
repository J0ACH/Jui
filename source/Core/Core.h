#ifndef CORE_H
#define CORE_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

/*
#include <QObject>
#include <QWidget>
#include <QCoreApplication>
#include <QTranslator>
#include <QFontDatabase>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPushButton>
#include <QPainter>
#include <QString>
#include <QDebug>
#include <QMetaObject>
#include <QVariantAnimation>
#include <QColor>
*/

namespace Jui
{
	enum fade { out, in };
	enum direction { right, bottom, left, top };
	void loadFonts();
}

#endif // CORE_H