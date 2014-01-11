#include "GameTracker.h"

#include "ConfigManager.h"
#include "FileSearch.h"
#include "CDUtils.h"

#include <QProgressDialog>
#include <QComboBox>
#include <QStatusBar>
#include <QLabel>

#include "GameTree.h"
#include "GameGrid.h"

DGameTracker::DGameTracker(QWidget* p)
	: QStackedWidget(p)
{
	GameTree* w = new GameTree(this);
	addWidget(w);
	myViewers.insert(TYPE_TREEWIDGET, (AbstractGameViewer*)w);
	connect(w, SIGNAL(GameStarter()), this, SLOT(GameStarter()));

	GameGrid* g = new GameGrid(this);
	addWidget(g);
	myViewers.insert(TYPE_LISTWIDGET, (AbstractGameViewer*)g);
	connect(g, SIGNAL(GameStarter()), this, SLOT(GameStarter()));

	setViewStyle(STYLE_LIST);
	setDisabled(false);

	styleSwitcher = new QComboBox(p);
	connect(styleSwitcher, SIGNAL(currentIndexChanged(QString)), this, SLOT(SwitchStyle(QString)));
	styleSwitcher->addItem(tr("Tree"));
	styleSwitcher->addItem(tr("List"));
	styleSwitcher->addItem(tr("Grid"));
	styleSwitcher->addItem(tr("Icons"));
}

void DGameTracker::addWidgetsToStatusBar(QStatusBar* s)
{
	s->addWidget(new QLabel(tr("Style: "), s));
	s->addWidget(styleSwitcher);
}

void DGameTracker::setViewStyle(TrackerStyle newStyle)
{
	currentStyle = newStyle;
	if(newStyle == STYLE_LIST || newStyle == STYLE_TREE) {
		currentType = TYPE_TREEWIDGET;
		setCurrentWidget(myViewers.value(TYPE_TREEWIDGET)->myWidget());
		myViewers.value(TYPE_TREEWIDGET)->setViewStyle(newStyle);
	} else {
		currentType = TYPE_LISTWIDGET;
		setCurrentWidget(myViewers.value(TYPE_LISTWIDGET)->myWidget());
		myViewers.value(TYPE_LISTWIDGET)->setViewStyle(newStyle);
	}
}

void DGameTracker::SwitchStyle(QString styleName)
{
	if(styleName == tr("Tree")) {
		setViewStyle(STYLE_TREE);
	} else if(styleName == tr("List")) {
		setViewStyle(STYLE_LIST);
	} else if(styleName == tr("Grid")) {
		setViewStyle(STYLE_GRID);
	} else if(styleName == tr("Icons")) {
		setViewStyle(STYLE_ICONS);
	}
}

void DGameTracker::GameStarter()
{
	emit StartGame();
}

GameObject* DGameTracker::selectedGame()
{
	return myViewers.value(currentType)->selectedGame();
}

void DGameTracker::scanForGames()
{
	setDisabled(true);
	QProgressDialog prog(tr("Scanning for games..."), tr("Cancel"), 0, 1, this->parentWidget());
	prog.setWindowModality(Qt::ApplicationModal);
	QList<GameObject*> newItems;

	CFileSearch::XStringVector Directories(SConfig::GetInstance().m_ISOFolder);
	if (SConfig::GetInstance().m_RecursiveISOFolder)
	{
		for (u32 i = 0; i < Directories.size(); i++)
		{
			File::FSTEntry FST_Temp;
			File::ScanDirectoryTree(Directories.at(i).c_str(), FST_Temp);
			for (u32 j = 0; j < FST_Temp.children.size(); j++)
			{
				if (FST_Temp.children.at(j).isDirectory)
				{
					bool duplicate = false;
					for (u32 k = 0; k < Directories.size(); k++)
					{
						if (strcmp(Directories.at(k).c_str(), FST_Temp.children.at(j).physicalName.c_str()) == 0)
						{
							duplicate = true;
							break;
						}
					}
					if (!duplicate)
						Directories.push_back(FST_Temp.children.at(j).physicalName.c_str());
				}
			}
		}
	}

	CFileSearch::XStringVector Extensions;

	if (SConfig::GetInstance().m_ListGC)
		Extensions.push_back("*.gcm");
	if (SConfig::GetInstance().m_ListWii || SConfig::GetInstance().m_ListGC)
	{
		Extensions.push_back("*.iso");
		Extensions.push_back("*.ciso");
		Extensions.push_back("*.gcz");
		Extensions.push_back("*.wbfs");
		Extensions.push_back("*.elf");
		Extensions.push_back("*.dol");
		Extensions.push_back("*.dff");
		Extensions.push_back("*.tmd");
	}
	if (SConfig::GetInstance().m_ListWad)
		Extensions.push_back("*.wad");

	CFileSearch FileSearch(Extensions, Directories);
	const CFileSearch::XStringVector& rFilenames = FileSearch.GetFileNames();

	if (rFilenames.size() > 0)
	{
		prog.setRange(0, rFilenames.size());
		prog.show();

		for (u32 i = 0; i < rFilenames.size(); i++)
		{
			std::string FileName;
			SplitPath(rFilenames[i], NULL, &FileName, NULL);
			QString NameAndPath = QString::fromStdString(rFilenames[i]);

			prog.setValue(i);
			prog.setLabelText(NameAndPath);

			if(gameObjectForFilename.keys().contains(NameAndPath)) {
				continue;
			}
			GameObject* obj = new GameObject(rFilenames[i]);
			if (obj->IsValid())
			{
				bool list = true;

				switch(obj->GetPlatform())
				{
					case GameObject::WII_DISC:
						if (!SConfig::GetInstance().m_ListWii)
							list = false;
						break;
					case GameObject::WII_WAD:
						if (!SConfig::GetInstance().m_ListWad)
							list = false;
						break;
					default:
						if (!SConfig::GetInstance().m_ListGC)
							list = false;
						break;
				}

				switch(obj->GetCountry())
				{
					case DiscIO::IVolume::COUNTRY_TAIWAN:
						if (!SConfig::GetInstance().m_ListTaiwan)
							list = false;
					case DiscIO::IVolume::COUNTRY_KOREA:
						if (!SConfig::GetInstance().m_ListKorea)
							list = false;
						break;
					case DiscIO::IVolume::COUNTRY_JAPAN:
						if (!SConfig::GetInstance().m_ListJap)
							list = false;
						break;
					case DiscIO::IVolume::COUNTRY_USA:
						if (!SConfig::GetInstance().m_ListUsa)
							list = false;
						break;
					case DiscIO::IVolume::COUNTRY_FRANCE:
						if (!SConfig::GetInstance().m_ListFrance)
							list = false;
						break;
					case DiscIO::IVolume::COUNTRY_ITALY:
						if (!SConfig::GetInstance().m_ListItaly)
							list = false;
						break;
					default:
						if (!SConfig::GetInstance().m_ListPal)
							list = false;
						break;
				}

				if (list)
					newItems.append(obj);
			}
		}
	}

	prog.hide();

	/* Process all the new stuffs */
	foreach(GameObject* o, newItems) {
		gameObjects.append(o);
		gameObjectForFilename.insert(o->GetFileName(), o);
	}

	foreach(AbstractGameViewer* a, myViewers.values()) {
		a->addNewGames(newItems);
	}

	setDisabled(false);
}

void AbstractGameViewer::addNewGames(QList<GameObject*> items)
{
	foreach(GameObject* o, items) {
		addNewGame(o);
	}
}
void AbstractGameViewer::removeGames(QList<GameObject*> items)
{
	foreach(GameObject* o, items) {
		removeGame(o);
	}
}
