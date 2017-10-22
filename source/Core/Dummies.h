#ifndef DUMMIES_H
#define DUMMIES_H

#include "Core.h"
#include "Text.h"
#include "Button.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	class Header : public QWidget
	{
		Q_OBJECT

	public:
		Header(QWidget *parent = 0);
		void font_(QString family);

	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		PureText* m_text;
		int thickness;
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
		FadeColor colorBackground;

		private slots:
		void onParentResize(QSize size);
	};

	// EdgeControler /////////////////////////////////////////////////////

	class EdgeControler : public QWidget
	{
		Q_OBJECT

	public:
		EdgeControler(QWidget *parent, Jui::direction dir);
		Jui::direction direction();

	signals:
		void pressed();
		void controlerMoved(Jui::direction, QPoint deltaPt);

	protected:
		void enterEvent(QEvent *e) override;
		void leaveEvent(QEvent *e) override;
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;

	private:
		Jui::direction m_direction;
		QPoint mousePressedGlobalCoor;
		FadeColor colorFrame;
	};

	// Edges ///////////////////////////////////////////////////// 

	class Edges : public QObject
	{
		Q_OBJECT

	public:
		Edges(QWidget *parent);

		public slots:
		void onControlerPressed();
		void onControlerMoved(Jui::direction, QPoint);
	protected:
		bool eventFilter(QObject *object, QEvent *e) override;
	private:
		QWidget* m_parent;
		QMap<Jui::direction, EdgeControler*> mEdges;
		void fitSize();
		int thickness, offset, corner, gap;
		QSize mousePressedParentSize;
		QPoint mousePressedOriginCoor;
	};

}

#endif // DUMMIES_H