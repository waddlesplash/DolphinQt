#include "GameGrid.h"
#include "ui_GameGrid.h"

GameGrid::GameGrid(QWidget *p) :
	QListWidget(p),
	ui(new Ui::GameGrid)
{
	ui->setupUi(this);
	setViewStyle(STYLE_GRID);
	setDragEnabled(false);

	connect(this, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(itemActivated()));
}

GameGrid::~GameGrid()
{
	delete ui;
}

void GameGrid::itemActivated()
{
	emit GameStarter();
}

void GameGrid::setViewStyle(TrackerStyle newStyle)
{
	if(newStyle == currentStyle) { return; }
	if(newStyle == STYLE_GRID) {
		currentStyle = STYLE_GRID;
	} else {
		currentStyle = STYLE_ICONS;
	}
}

void GameGrid::addNewGame(GameObject* itm)
{
	if(objects.contains(itm)) { return; }
	objects.append(itm);

	QListWidgetItem* i = new QListWidgetItem;
	i->setIcon(QIcon(QPixmap::fromImage(itm->GetBitmap())
					 .scaled(144, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
	i->setText(itm->GetName(0));
	addItem(i);
	objectForItem.insert(i, itm);
}
void GameGrid::removeGame(GameObject* itm)
{
	if(!objects.contains(itm)) { return; }
	QListWidgetItem* i = objectForItem.key(itm);
	objectForItem.remove(i);
	objects.removeOne(itm);
	delete i;
}
