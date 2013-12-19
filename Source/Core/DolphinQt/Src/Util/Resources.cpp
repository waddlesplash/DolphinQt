#include "Resources.h"

#include "Volume.h"
#include "FileUtil.h"
#include "ConfigManager.h"

QVector<QPixmap> Resources::platforms;
QVector<QPixmap> Resources::regions;
QVector<QPixmap> Resources::ratings;
QVector<QPixmap> Resources::pixmaps;

void Resources::Init()
{
	regions.resize(DiscIO::IVolume::NUMBER_OF_COUNTRIES);
	regions[DiscIO::IVolume::COUNTRY_EUROPE].load(":/Flag_Europe.png");
	regions[DiscIO::IVolume::COUNTRY_FRANCE].load(":/Flag_France.png");
	regions[DiscIO::IVolume::COUNTRY_RUSSIA].load(":/Flag_Unknown.png"); // TODO
	regions[DiscIO::IVolume::COUNTRY_USA].load(":/Flag_USA.png");
	regions[DiscIO::IVolume::COUNTRY_JAPAN].load(":/Flag_Japan.png");
	regions[DiscIO::IVolume::COUNTRY_KOREA].load(":/Flag_Korea.png");
	regions[DiscIO::IVolume::COUNTRY_ITALY].load(":/Flag_Italy.png");
	regions[DiscIO::IVolume::COUNTRY_TAIWAN].load(":/Flag_Taiwan.png");
	regions[DiscIO::IVolume::COUNTRY_SDK].load(":/Flag_SDK.png");
	regions[DiscIO::IVolume::COUNTRY_UNKNOWN].load(":/Flag_Unknown.png");

	platforms.resize(3);
	platforms[0].load(":/Platform_Gamecube.png");
	platforms[1].load(":/Platform_Wii.png");
	platforms[2].load(":/Platform_Wad.png");

	ratings.resize(6);
	ratings[0].load(":/rating0.png");
	ratings[1].load(":/rating1.png");
	ratings[2].load(":/rating2.png");
	ratings[3].load(":/rating3.png");
	ratings[4].load(":/rating4.png");
	ratings[5].load(":/rating5.png");

	pixmaps.resize(NUM_ICONS);
	UpdatePixmaps();
}

void Resources::UpdatePixmaps()
{
	QString dir = QString::fromStdString(File::GetThemeDir(SConfig::GetInstance().m_LocalCoreStartupParameter.theme_name));
	pixmaps[TOOLBAR_OPEN].load(dir + "open.png");
	pixmaps[TOOLBAR_REFRESH].load(dir + "refresh.png");
	pixmaps[TOOLBAR_BROWSE].load(dir + "browse.png");
	pixmaps[TOOLBAR_PLAY].load(dir + "play.png");
	pixmaps[TOOLBAR_STOP].load(dir + "stop.png");
	pixmaps[TOOLBAR_PAUSE].load(dir + "pause.png");
	pixmaps[TOOLBAR_FULLSCREEN].load(dir + "fullscreen.png");
	pixmaps[TOOLBAR_SCREENSHOT].load(dir + "screenshot.png");
	pixmaps[TOOLBAR_CONFIGURE].load(dir + "config.png");
	pixmaps[TOOLBAR_PLUGIN_GFX].load(dir + "graphics.png");
	pixmaps[TOOLBAR_PLUGIN_DSP].load(dir + "dsp.png");
	pixmaps[TOOLBAR_PLUGIN_GCPAD].load(dir + "gcpad.png");
	pixmaps[TOOLBAR_PLUGIN_WIIMOTE].load(dir + "wiimote.png");
	pixmaps[TOOLBAR_HELP].load(":/Dolphin.png"); // TODO
	// TODO: toolbar[MEMCARD];
	// TODO: toolbar[HOTKEYS];
	pixmaps[DOLPHIN_LOGO].load(":/Dolphin.png");
	pixmaps[BANNER_MISSING].load(dir + "nobanner.png");
}

QPixmap& Resources::GetRegionPixmap(DiscIO::IVolume::ECountry region)
{
	return regions[region];
}

QPixmap& Resources::GetPlatformPixmap(int console)
{
	if (console >= platforms.size()) return platforms[0];
	return platforms[console];
}

QPixmap& Resources::GetRatingPixmap(int rating)
{
	if (rating >= ratings.size()) return ratings[0];
	return ratings[rating];
}

QPixmap& Resources::GetPixmap(int id)
{
	if (id >= pixmaps.size()) return pixmaps[0];
	return pixmaps[id];
}

QIcon Resources::GetIcon(int id)
{
	return QIcon(GetPixmap(id));
}
