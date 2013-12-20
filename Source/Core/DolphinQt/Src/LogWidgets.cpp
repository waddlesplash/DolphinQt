#include "ui_LogWindow.h"
#include "ui_LogSettings.h"

#include "LogWidgets.h"
#include "LogManager.h"

#include <QRadioButton>

DLogSettings::DLogSettings(QWidget * p, Qt::WindowFlags flags)
	: QDockWidget(tr("Log Settings"), p, flags),
	  ui(new Ui::LogSettings),
	  enableAllChannels(true)
{
	ui->setupUi(this);
	LogManager* logManager = LogManager::GetInstance();

	QStringList logLevels;
	logLevels << tr("Notice") << tr("Error") << tr("Warning") << tr("Info") << tr("Debug");
	for (int i = 0; i < MAX_LOGLEVEL && i < logLevels.size(); ++i) {
		logLevelsRadio.append(new QRadioButton(logLevels.at(i)));
		ui->verbosityLayout->addWidget(logLevelsRadio[i]);
	}
	logLevelsRadio[0]->setChecked(true);

	for (int i = 0; i < LogTypes::NUMBER_OF_LOGS; i++)
		logChannels.append(new QCheckBox(QString(logManager->GetFullName( (LogTypes::LOG_TYPE)i ))));

	for (int i = 0; i < LogTypes::NUMBER_OF_LOGS; i++)
	{
		QListWidgetItem* item = new QListWidgetItem(ui->listVerbosity);
		item->setText(QString(logManager->GetFullName((LogTypes::LOG_TYPE)i))); // TODO: translate
		item->setCheckState(Qt::Unchecked);
	}
}

DLogSettings::~DLogSettings()
{
	delete ui;
}

void DLogSettings::on_togAllBtn_clicked()
{
	// if no channels are selected, but enableAllChannels is false, force enableAllChannels to true (and vice versa)
	for (int i = 0; i < LogTypes::NUMBER_OF_LOGS; ++i)
	{
		if(ui->listVerbosity->item(i)->checkState() != (enableAllChannels ? Qt::Checked : Qt::Unchecked)) {
			break;
		} else if (i == LogTypes::NUMBER_OF_LOGS-1) {
			enableAllChannels = !enableAllChannels;
		}
	}

	for (int i = 0; i < LogTypes::NUMBER_OF_LOGS; ++i)
		ui->listVerbosity->item(i)->setCheckState(enableAllChannels ? Qt::Checked : Qt::Unchecked);

	enableAllChannels = !enableAllChannels;
}

void DLogSettings::closeEvent(QCloseEvent* e)
{
	// TODO: Handle this differently, since we need to keep the window open if the "really stop emulation?" question was answered with "no"
	emit Closed();
	QWidget::closeEvent(e);
}

DLogWindow::DLogWindow(QWidget * p, Qt::WindowFlags flags)
	: QDockWidget(p, flags),
	  ui(new Ui::LogWindow)
{
	ui->setupUi(this);
	LogManager* logManager = LogManager::GetInstance();

	// TODO: Check if logging is actually enabled
	// TODO: Some messages get dropped in the beginning
	for (int i = 0; i < LogTypes::NUMBER_OF_LOGS; ++i)
	{
		logManager->AddListener((LogTypes::LOG_TYPE)i, this);
	}
}

DLogWindow::~DLogWindow()
{
	delete ui;
}

void DLogWindow::Log(LogTypes::LOG_LEVELS, const char *msg)
{
	// TODO: For some reason, this line makes the emulator crash after a few log messages..
	if(isVisible())
		ui->logEdit->appendPlainText(QString(msg));
}

void DLogWindow::closeEvent(QCloseEvent* e)
{
	emit Closed();
	QWidget::closeEvent(e);
}
