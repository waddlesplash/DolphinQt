#include "ui_SystemInfo.h"
#include "SystemInfo.h"

#include <QtGlobal>
#include "Common.h"

DSystemInfo::DSystemInfo(QWidget *p) :
	QDialog(p),
	ui(new Ui::DSystemInfo)
{
	ui->setupUi(this);
	UpdateSystemInfo();
}

DSystemInfo::~DSystemInfo()
{
	delete ui;
}

void DSystemInfo::on_textSysInfo_selectionChanged()
{
	ui->textSysInfo->selectAll();
}

void DSystemInfo::UpdateSystemInfo()
{
	QString sysinfo = "";

	sysinfo += "System\n===========================\n";
	int s = sizeof(void*)*8;
	sysinfo += QString("OS: %1 %2-bit").arg(GetOS()).arg(s) + "\n";

	sysinfo += "\nDolphin\n===========================\n";
	sysinfo += QString("SCM: branch %1, rev %2\n").arg(scm_branch_str).arg(scm_rev_git_str);
	sysinfo += QString("Compiled: %1, %2\n").arg(__DATE__).arg(__TIME__);

	sysinfo += "\nGUI\n===========================\n";
	sysinfo += "Compiled for Qt: " + QString(QT_VERSION_STR) + "\n";
	sysinfo += "Running on Qt: " + QString(qVersion()) + "\n";

	ui->textSysInfo->setPlainText(sysinfo);
}

QString DSystemInfo::GetOS()
{
	QString ret = "";
	/* DON'T REORDER WITHOUT READING Qt DOCS! */
#if defined(Q_WS_WIN)
	ret += "Windows ";
	switch(QSysInfo::WindowsVersion) {
	case WV_XP: ret += "XP"; break;
	case WV_2003: ret += "Server 2003"; break;
	case WV_VISTA: ret += "Vista"; break;
	case WV_WINDOWS7: ret += "7"; break;
	case WV_WINDOWS8: ret += "8"; break;
	case WV_NT_based: ret += "(unknown NT-based)"; break;
	default: ret += "(unknown)"; break;
	}
#elif defined(Q_OS_MAC)
	ret += "Mac OS X ";
	switch(QSysInfo::MacVersion) {
	case MV_10_7: ret += "10.7"; break;
	case MV_10_8: ret += "10.8"; break;
	case MV_10_9: ret += "10.9"; break;
	default: ret += "(unknown)"; break;
	}
#elif defined(Q_OS_LINUX)
	ret += "Linux";
#elif defined(Q_OS_FREEBSD)
	ret += "FreeBSD";
#elif defined(Q_OS_OPENBSD)
	ret += "OpenBSD";
#elif defined(Q_OS_NETBSD)
	ret += "NetBSD";
#elif defined(Q_OS_BSD4)
	ret += "Other BSD";
#elif defined(Q_OS_UNIX)
	ret += "Unix";
#else
	ret += "Unknown";
#endif

#ifdef Q_WS_X11 || Q_OS_X11
	ret += "/X11";
#endif

	return ret;
}
