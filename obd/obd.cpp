#include "infocar.h"

#ifdef Q_OS_WIN
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" {

EXPORT int count() {
	qRegisterMetaType<InfoCar*>();
	return 1;
}

EXPORT const char* name(int index) {
	switch (index) {
		case 0: return InfoCar::staticMetaObject.className();
		default: return nullptr;
	}
}

EXPORT void* create(int index) {
	switch (index) {
		case 0: return new InfoCar;
		default: return nullptr;
	}
}

}
