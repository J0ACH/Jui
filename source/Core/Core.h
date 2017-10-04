#ifndef CORE_H
#define CORE_H

#include <QtCore>
#include <QtGui>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QMetaObject>
#include <QVariantAnimation>
#include <QColor>

namespace Jui
{
	enum fade { out, in };
	enum direction { right, bottom, left, top };

	void fadeVariant(QVariantAnimation &variable, Jui::fade fade, int duration);

	
}

#endif // CORE_H