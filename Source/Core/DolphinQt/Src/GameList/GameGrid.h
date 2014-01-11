#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QListWidget>
#include "GameTracker.h"

namespace Ui {
class GameGrid;
}

class GameGrid : public QListWidget, AbstractGameViewer
{
	Q_OBJECT

public:
	explicit GameGrid(QWidget *p = 0);
	~GameGrid();

	/* AbstractGameViewer stuffs */
	virtual inline GameObject* selectedGame() { return objectForItem.value(selectedItems().at(0)); }
	virtual inline QWidget* myWidget() { return (QWidget*)this; }

	virtual void setViewStyle(TrackerStyle newStyle);

	virtual void addNewGame(GameObject* itm);
	virtual void removeGame(GameObject* itm);

signals:
	void GameStarter();

private slots:
	void itemActivated();

private:
	Ui::GameGrid *ui;

	QList<GameObject*> objects;
	QMap<QListWidgetItem*, GameObject*> objectForItem;
	TrackerStyle currentStyle;
};

#endif // GAMEGRID_H
