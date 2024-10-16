#include "infocar.h"

InfoCar::InfoCar(QObject* parent) : GStateObj(parent) {
	qDebug() << "";
}

InfoCar::~InfoCar() {
	qDebug() << "";
	close();
	if (gw_ != nullptr) {
		delete gw_;
		gw_ = nullptr;
	}
}

bool InfoCar::doOpen() {
	if (gw_ == nullptr)
		gw_ = new GaugeWidget;
	gw_->setWindowTitle("YESICAN");
	gw_->show();

	return true;
}

bool InfoCar::doClose() {
	return true;
}

void InfoCar::analyze(GPacket* packet) {
	if (packet->buf_.data_[4] != 0x02) return; // ACL Data
	QString heystack = QString::fromLatin1(pchar(packet->buf_.data_), packet->buf_.size_);

	int index = heystack.indexOf("410C");
	if (index != -1) {
		QString value = heystack.mid(index + 4, 4);
		if (value.size() == 4) {
			int rpm = value.toInt(nullptr, 16) / 4;
			QMetaObject::invokeMethod(this, [this, rpm]() {
				qDebug() << "rpm=" << rpm;
				gw_->updateRpm(rpm);
			}, Qt::BlockingQueuedConnection);

		}
	}

	index = heystack.indexOf("410D");
	if (index != -1) {
		QString value = heystack.mid(index + 4, 4);
		if (value.size() == 4) {
			int speed = value.toInt(nullptr, 16);
			QMetaObject::invokeMethod(this, [this, speed]() {
				qDebug() << "speed=" << speed;
				gw_->updateSpeed(speed);
			}, Qt::BlockingQueuedConnection);

		}
	}
}
