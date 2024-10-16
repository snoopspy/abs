TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS= -lpcap
DESTDIR = $$PWD/../bin
SOURCES += \
	abs.cpp
