#include "gaugewidget.h"
#include "ui_gaugewidget.h"

GaugeWidget::GaugeWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::GaugeWidget)
{
	ui->setupUi(this);
}

GaugeWidget::~GaugeWidget()
{
	delete ui;
}

void GaugeWidget::updateRpm(int rpm) {
	ui->dialRpm->setValue(rpm);
	ui->lblRpm->setText(QString::number(rpm));
}

void GaugeWidget::updateSpeed(int speed) {
	ui->dialSpeed->setValue(speed);
	ui->lblSpeed->setText(QString::number(speed));
}
