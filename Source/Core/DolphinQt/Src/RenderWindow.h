#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QWidget>

class DRenderWindow : public QWidget
{
	Q_OBJECT

public:
	DRenderWindow(QWidget* p = NULL);

	// Some window managers start window dragging if an "empty" window area was clicked.
	// Prevent this by intercepting the mouse press event.
	void mousePressEvent (QMouseEvent* ev) {}

private slots:
	virtual void closeEvent(QCloseEvent*);

signals:
	void Closed();
};

#endif // RENDERWINDOW_H
