#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>

class DRenderWidget : public QWidget
{
	Q_OBJECT

public:
	DRenderWidget(QWidget* p = NULL);

	// Some window managers start window dragging if an "empty" window area was clicked.
	// Prevent this by intercepting the mouse press event.
	void mousePressEvent (QMouseEvent* ev) {}

private slots:
	virtual void closeEvent(QCloseEvent*);

signals:
	void Closed();
};

#endif // RENDERWIDGET_H
