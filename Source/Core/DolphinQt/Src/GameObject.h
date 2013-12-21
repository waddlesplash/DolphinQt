// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

#include "Volume.h"
#include "VolumeCreator.h"

#include <QImage>
#include <QString>

class PointerWrap;
class GameObject
{
public:
	GameObject(std::string rFileName);
	~GameObject();

	bool IsValid() const {return m_Valid;}
	QString GetFileName() {return QString::fromStdString(m_FileName);}
	QString GetFolderName();
	QString GetBannerName(int index) const;
	QString GetVolumeName(int index) const;
	QString GetName(int index) const;
	QString GetCompany() const;
	QString GetDescription(int index = 0) const;
	int GetRevision() const { return m_Revision; }
	const QString GetUniqueID() const {return QString::fromStdString(m_UniqueID);}
	const QString GetWiiFSPath() const;
	DiscIO::IVolume::ECountry GetCountry() const {return m_Country;}
	int GetPlatform() const {return m_Platform;}
	const std::string& GetIssues() const {return m_issues;}
	int GetEmuState() const { return m_emu_state; }
	bool IsCompressed() const {return m_BlobCompressed;}
	u64 GetFileSize() const {return m_FileSize;}
	u64 GetVolumeSize() const {return m_VolumeSize;}
	bool IsDiscTwo() const {return m_IsDiscTwo;}
	const QImage GetBitmap() const {return m_Banner;}

	void DoState(PointerWrap &p);

	enum
	{
		GAMECUBE_DISC = 0,
		WII_DISC,
		WII_WAD,
		NUMBER_OF_PLATFORMS
	};

private:
	std::string m_FileName;

	// TODO: eliminate this and overwrite with names from banner when available?
	std::vector<std::string> m_volume_names;

	// Stuff from banner
	std::string m_company;
	std::vector<std::string> m_names;
	std::vector<std::string> m_descriptions;

	std::string m_UniqueID;

	std::string m_issues;
	int m_emu_state;

	u64 m_FileSize;
	u64 m_VolumeSize;

	DiscIO::IVolume::ECountry m_Country;
	int m_Platform;
	int m_Revision;

	QImage m_Banner;
	bool m_Valid;
	bool m_BlobCompressed;
	int m_ImageWidth, m_ImageHeight;
	bool m_IsDiscTwo;

	bool LoadFromCache();
	void SaveToCache();

	std::string CreateCacheFilename();
};

#endif // GAMEOBJECT_H
