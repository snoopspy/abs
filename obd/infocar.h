#pragma once

#include <GStateObj>
#include <GPacket>
#include "gaugewidget.h"

struct G_EXPORT InfoCar : GStateObj {
	Q_OBJECT
	Q_PROPERTY(QString prop MEMBER prop_)

public:
	QString prop_;

public:
	Q_INVOKABLE InfoCar(QObject* parent = nullptr);
	~InfoCar() override;

protected:
	GaugeWidget *gw_{nullptr};

protected:
	bool doOpen() override;
	bool doClose() override;

signals:
	void signalMyObj();

public slots:
	void analyze(GPacket* packet);
};
