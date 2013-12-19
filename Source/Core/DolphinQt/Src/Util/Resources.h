#include <QPixmap>
#include <QIcon>

#include "Volume.h"

class Resources
{
public:
	static void Init();
	static void UpdatePixmaps();

	static QPixmap& GetPlatformPixmap(int console);
	static QPixmap& GetRegionPixmap(DiscIO::IVolume::ECountry region);
	static QPixmap& GetRatingPixmap(int rating);
	static QPixmap& GetPixmap(int id);
	static QIcon GetIcon(int id);

	enum
	{
		TOOLBAR_OPEN = 0,
		TOOLBAR_REFRESH,
		TOOLBAR_BROWSE,
		TOOLBAR_PLAY,
		TOOLBAR_STOP,
		TOOLBAR_PAUSE,
		TOOLBAR_FULLSCREEN,
		TOOLBAR_SCREENSHOT,
		TOOLBAR_CONFIGURE,
		TOOLBAR_PLUGIN_GFX,
		TOOLBAR_PLUGIN_DSP,
		TOOLBAR_PLUGIN_GCPAD,
		TOOLBAR_PLUGIN_WIIMOTE,
		TOOLBAR_HELP,
		MEMCARD,
		HOTKEYS,
		DOLPHIN_LOGO,
		BANNER_MISSING,
		NUM_ICONS
	};

private:
	static QVector<QPixmap> platforms;
	static QVector<QPixmap> regions;
	static QVector<QPixmap> ratings;
	static QVector<QPixmap> pixmaps;
};
