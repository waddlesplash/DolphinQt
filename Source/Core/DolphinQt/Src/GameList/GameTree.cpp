#include "GameTree.h"
#include "ui_GameTree.h"

#include "../Util/Util.h"
#include "../Util/Resources.h"

#define DVD_BANNER_WIDTH 96
#define DVD_BANNER_HEIGHT 32

GameTree::GameTree(QWidget *p) :
	QTreeWidget(p),
	ui(new Ui::GameTree)
{
	ui->setupUi(this);
	setViewStyle(STYLE_LIST);
	setIconSize(QSize(DVD_BANNER_WIDTH, DVD_BANNER_HEIGHT));
	sortByColumn(COL_TITLE);

	connect(this, SIGNAL(itemActivated(QTreeWidgetItem*,int)), this, SLOT(itemActivated(QTreeWidgetItem*)));
}

GameTree::~GameTree()
{
	delete ui;
}

void GameTree::resizeAllCols()
{
	for(int i = 0; i < columnCount(); i++) {
		resizeColumnToContents(i);
	}
}

void GameTree::itemActivated(QTreeWidgetItem *item)
{
	if(!rootNodesForPath.values().contains(item)) {
		emit GameStarter();
	}
}

void GameTree::setViewStyle(TrackerStyle newStyle)
{
	if(newStyle == currentStyle) { return; }
	if(newStyle == STYLE_LIST) {
		currentStyle = STYLE_LIST;
		setIndentation(0);
		rebuildTree();
	} else {
		currentStyle = STYLE_TREE;
		setIndentation(20);
		rebuildTree();
	}
}

void GameTree::addNewGame(GameObject* item)
{
	if(objects.contains(item)) { return; }
	objects.append(item);
	QString folderName = item->GetFolderName();
	if(!rootNodesForPath.contains(folderName)) {
		QTreeWidgetItem* i = new QTreeWidgetItem;
		i->setText(0, folderName);
		rootNodesForPath.insert(folderName, i);
		if(currentStyle == STYLE_TREE) {
			addTopLevelItem(i);
		}
	}

	QTreeWidgetItem* i = new QTreeWidgetItem;
	i->setIcon(COL_TYPE, QIcon(Resources::GetPlatformPixmap(item->GetPlatform())));
	i->setIcon(COL_BANNER, QIcon(QPixmap::fromImage(item->GetBitmap())));
	i->setText(COL_TITLE, item->GetName(0));
	i->setText(COL_NOTES, item->GetDescription());
	i->setIcon(COL_REGION, QIcon(Resources::GetRegionPixmap(item->GetCountry())));
	i->setText(COL_SIZE, NiceSizeFormat(item->GetFileSize()));
	objectForItem.insert(i, item);

	rebuildTree(); // TODO: only call this once!
}
void GameTree::removeGame(GameObject* item)
{
	if(!objects.contains(item)) { return; }
	QTreeWidgetItem* i = objectForItem.key(item);
	objectForItem.remove(i);
	objects.removeOne(item);
	delete i;
}

void GameTree::rebuildTree()
{
	// TODO: benchmark this function!
	for(int a = 0; a < topLevelItemCount(); a++) {
		takeTopLevelItem(a);
	}
	foreach(QTreeWidgetItem* i, rootNodesForPath.values()) {
		for(int a = 0; a < i->childCount(); a++) {
			i->takeChild(a);
		}
	}

	if(currentStyle == STYLE_TREE) {
		foreach(QTreeWidgetItem *i, rootNodesForPath.values()) {
			addTopLevelItem(i);
		}
		foreach(QTreeWidgetItem* i, objectForItem.keys()) {
			rootNodesForPath.value(objectForItem.value(i)->GetFolderName())->addChild(i);
		}
	} else {
		foreach(QTreeWidgetItem *i, objectForItem.keys()) {
			addTopLevelItem(i);
		}
	}

	expandAll();
	resizeAllCols();
}
