TEMPLATE = lib
QT += widgets
include(../../g/g.pri)

SOURCES += 	gaugewidget.cpp \
	infocar.cpp \
	obd.cpp

HEADERS += gaugewidget.h \
	infocar.h

DESTDIR = $${PWD}/../../g/bin/plugin/obd

FORMS += \
	gaugewidget.ui
