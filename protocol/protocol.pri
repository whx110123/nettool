HEADERS += \
    $$PWD/dataconfig.h \
    $$PWD/functotext.h \
    $$PWD/globaldefine.h \
    $$PWD/mybase.h \
    $$PWD/protocol101apdu.h \
    $$PWD/protocol101asdu.h \
    $$PWD/protocol103asdu.h \
    $$PWD/protocol103com.h \
    $$PWD/protocol103wiscomnet.h \
    $$PWD/protocol104apdu.h

SOURCES += \
    $$PWD/dataconfig.cpp \
    $$PWD/functotext.cpp \
    $$PWD/globaldefine.cpp \
    $$PWD/mybase.cpp \
    $$PWD/protocol101apdu.cpp \
    $$PWD/protocol101asdu.cpp \
    $$PWD/protocol103asdu.cpp \
    $$PWD/protocol103com.cpp \
    $$PWD/protocol103wiscomnet.cpp \
    $$PWD/protocol104apdu.cpp


include             ($$PWD/protocol104/protocol104.pri)
include				($$PWD/protocol103/protocol103.pri)
include             ($$PWD/protocol101/protocol101.pri)
INCLUDEPATH         += $$PWD/protocol104
INCLUDEPATH         += $$PWD/protocol103
INCLUDEPATH         += $$PWD/protocol101


