#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "Config/ConfigMain.h"
#include "RenderWidget.h"

#include <Core.h>

class DLogWindow;
class DLogSettings;
class DGameTracker;
namespace Ui {
class MainWindow;
}

class DMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	DMainWindow();
	~DMainWindow();

	QWidget* GetRenderWindow() const { return renderWindow; }

private slots:
	void OnLoadIso();
	void OnBrowseIso();
	void OnRefreshList();

	void OnStartPause();
	void OnStop();

	void OnConfigure();
    void OnConfigureHotkeys() {}
	void OnGfxSettings();
	void OnSoundSettings();
	void OnGCPadSettings();
	void OnWiimoteSettings();

	void on_actionWebsite_triggered();
	void on_actionDocumentation_triggered();
	void on_actionDevelopment_triggered();
	void on_actionReportIssue_triggered();
	void on_actionAbout_triggered();

	void OnCoreStateChanged(Core::EState state);

private:
	void UpdateIcons();
	void CreateDockWidgets();

	void OpenConfigDialog(DConfigDialog::InitialConfigItem initialConfigItem);

	void StartGame(const std::string& filename);
	std::string RequestBootFilename();
	void DoStartPause();
	void DoStop();

	void closeEvent(QCloseEvent*);

	Ui::MainWindow *ui;
	DGameTracker* gameTracker;
	DRenderWidget* renderWindow;
	DLogWindow* logWindow;
	DLogSettings* logSettings;
	DConfigDialog* dialog;

	// Emulation stopping closes the render window; closing the render window also stops emulation
	// Thus, in order to prevent endless loops, we need this variable.
	bool is_stopping;

signals:
	void CoreStateChanged(Core::EState state);
	void StartIsoScanning();
};

#endif // MAINWINDOW_H
