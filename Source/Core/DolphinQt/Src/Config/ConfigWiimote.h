#include <QWidget>

class DConfigWiimote : public QWidget
{
	Q_OBJECT

public:
	DConfigWiimote(QWidget* p = NULL);

public slots:
	void Reset();
	void Apply();
};
