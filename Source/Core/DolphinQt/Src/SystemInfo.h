#ifndef DSYSTEMINFO_H
#define DSYSTEMINFO_H

#include <QDialog>

namespace Ui {
class DSystemInfo;
}

class DSystemInfo : public QDialog
{
	Q_OBJECT

public:
	explicit DSystemInfo(QWidget *p = 0);
	~DSystemInfo();

private slots:
	void on_textSysInfo_selectionChanged();

private:
	Ui::DSystemInfo *ui;

	void UpdateSystemInfo();
	QString GetOS();
};

#endif // DSYSTEMINFO_H
