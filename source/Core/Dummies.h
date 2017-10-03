#ifndef DUMMIES_H
#define DUMMIES_H

#include "Core.h"
#include "Button.h"

namespace Jui
{
	// Header /////////////////////////////////////////////////////

	class Header : public Button
	{
	public:
		Header(QWidget *parent);
	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		bool eventFilter(QObject *object, QEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
	private:
		QWidget* m_parent;
		void fitSize();
		int thickness;
		QPoint mousePressedGlobalCoor, mousePressedOriginCoor;
	};

	// EdgeControler /////////////////////////////////////////////////////

	class EdgeControler : public Button
	{
		Q_OBJECT

	public:
		EdgeControler(QWidget *parent, Jui::direction dir);
		Jui::direction direction();
	signals:
		void actControlerMoved(Jui::direction, QPoint deltaPt);
	protected:
		void mousePressEvent(QMouseEvent *e) override;
		void mouseReleaseEvent(QMouseEvent *e) override;
		void mouseMoveEvent(QMouseEvent *e) override;
		void paintEvent(QPaintEvent *e) override;
	private:
		Jui::direction m_direction;
		QPoint mousePressedGlobalCoor;
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