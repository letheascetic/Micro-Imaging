TEMPLATE = lib
DEFINES += MIATS_LIBRARY
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    miats.cpp \
    worker.cpp \
    ats.cpp

HEADERS += \
    MIAts_global.h \
    inc/AlazarApi.h \
    inc/AlazarCmd.h \
    inc/AlazarError.h \
    miats.h \
    worker.h \
    ats.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(debug, debug|release) {
DESTDIR = ../../bin/Debug
} else {
DESTDIR = ../../bin/Release
}

INCLUDEPATH += ../../lib/MIDef/
INCLUDEPATH += ../../lib/MICfg/
INCLUDEPATH += $$PWD/inc/

DEPENDPATH += ../../lib/MIDef/
DEPENDPATH += ../../lib/MICfg/
DEPENDPATH += $$PWD/lib/x64/

LIBS += -L$$PWD/lib/x64/ -lAtsApi


