#include <QDockWidget>
#include <QList>

#include "LogManager.h"

class QCheckBox;
class QRadioButton;
namespace Ui {
class LogSettings;
}
class DLogSettings : public QDockWidget
{
	Q_OBJECT

public:
	DLogSettings(QWidget * p = NULL, Qt::WindowFlags flags = 0);
	~DLogSettings();

signals:
	void Closed();

protected:
	void closeEvent(QCloseEvent* e);

private slots:
	void on_togAllBtn_clicked();

private:
	Ui::LogSettings *ui;
	QList<QCheckBox*> logChannels;
	QList<QRadioButton*> logLevelsRadio;
	bool enableAllChannels;
};

namespace Ui {
class LogWindow;
}
class DLogWindow : public QDockWidget, LogListener
{
	Q_OBJECT

public:
	DLogWindow(QWidget * p = NULL, Qt::WindowFlags flags = 0);
	~DLogWindow();

signals:
	void Closed();

protected:
	void closeEvent(QCloseEvent* e);

private:
	Ui::LogWindow *ui;

	// LogListener
	void Log(LogTypes::LOG_LEVELS, const char *msg);
	const char *getName() const { return "LogWindow"; }
};
