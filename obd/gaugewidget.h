#ifndef GAUGEWIDGET_H
#define GAUGEWIDGET_H

#include <QWidget>

namespace Ui {
	class GaugeWidget;
}

class GaugeWidget : public QWidget
{
	Q_OBJECT

public:
	explicit GaugeWidget(QWidget *parent = nullptr);
	~GaugeWidget();

	void updateRpm(int rpm);
	void updateSpeed(int speed);

private:
	Ui::GaugeWidget *ui;
};

#endif // GAUGEWIDGET_H
