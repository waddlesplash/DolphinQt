#ifndef GAMETRACKER_H
#define GAMETRACKER_H

#include <QStackedWidget>
#include <QList>
#include <QMap>

#include "../GameObject.h"

class QStatusBar;
class QComboBox;

enum TrackerStyle {
	STYLE_LIST,
	STYLE_TREE,
	STYLE_GRID,
	STYLE_ICONS
};

class AbstractGameViewer
{
public:
	virtual GameObject* selectedGame() = 0;
	virtual QWidget* myWidget() = 0;

	virtual void setViewStyle(TrackerStyle newStyle) = 0;

	void addNewGames(QList<GameObject*> items);
	virtual void addNewGame(GameObject* item) = 0;
	void removeGames(QList<GameObject*> items);
	virtual void removeGame(GameObject* item) = 0;
};

class DGameTracker : public QStackedWidget
{
	Q_OBJECT
public:
	DGameTracker(QWidget *p = 0);
	void addWidgetsToStatusBar(QStatusBar* s);

	inline TrackerStyle getViewStyle() { return currentStyle; }
	void setViewStyle(TrackerStyle newStyle);

	void scanForGames();

	GameObject* selectedGame();

signals:
	void StartGame();

private slots:
	void SwitchStyle(QString styleName);
	void GameStarter();

private:
	enum WidgetType {
		TYPE_TREEWIDGET,
		TYPE_LISTWIDGET
	};

	QList<GameObject*> gameObjects;
	QMap<QString, GameObject*> gameObjectForFilename;

	QComboBox* styleSwitcher;

	TrackerStyle currentStyle;
	WidgetType currentType;
	QMap<WidgetType, AbstractGameViewer*> myViewers;
};

#endif // GAMETRACKER_H
