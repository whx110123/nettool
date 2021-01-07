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


include             ($$PWD/iec104/iec104.pri)
include				($$PWD/iec103/iec103.pri)
include             ($$PWD/iec101/iec101.pri)
include             ($$PWD/modbus/modbus.pri)
include             ($$PWD/measured_terminal/measured_terminal.pri)
INCLUDEPATH         += $$PWD/iec104
INCLUDEPATH         += $$PWD/iec103
INCLUDEPATH         += $$PWD/iec101
INCLUDEPATH         += $$PWD/modbus
INCLUDEPATH         += $$PWD/measured_terminal



