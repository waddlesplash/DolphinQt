#ifndef GAMETREE_H
#define GAMETREE_H

#include <QTreeWidget>
#include "GameTracker.h"

namespace Ui {
class GameTree;
}

class GameTree : public QTreeWidget, AbstractGameViewer
{
	Q_OBJECT
public:
	explicit GameTree(QWidget *p = 0);
	~GameTree();

	/* AbstractGameViewer stuffs */
	virtual inline GameObject* selectedGame() { return objectForItem.value(selectedItems().at(0)); }
	virtual inline QWidget* myWidget() { return (QWidget*)this; }

	virtual void setViewStyle(TrackerStyle newStyle);

	virtual void addNewGame(GameObject* item);
	virtual void removeGame(GameObject* item);

signals:
	void GameStarter();

private slots:
	void itemActivated(QTreeWidgetItem *item);

private:
	enum Columns {
		COL_TYPE = 0,
		COL_BANNER = 1,
		COL_TITLE = 2,
		COL_NOTES = 3,
		COL_REGION = 4,
		COL_SIZE = 5,
		COL_STATE = 6
	};

	Ui::GameTree *ui;
	TrackerStyle currentStyle;

	QList<GameObject*> objects;
	QMap<QTreeWidgetItem*, GameObject*> objectForItem;
	QMap<QString, QTreeWidgetItem*> rootNodesForPath;

	void rebuildTree();
	void resizeAllCols();
};

#endif // GAMETREE_H
