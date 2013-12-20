#include <QTabWidget>

class DConfigPadWidget : public QTabWidget
{
	Q_OBJECT

public:
	DConfigPadWidget(QWidget* p = NULL);

public slots:
	void Reset();
	void Apply();
};
