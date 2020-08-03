SOURCES	+= \
		$$PWD/main.cpp
HEADERS	+= \
		$$PWD/head.h

include ($$PWD/api/api.pri)
include ($$PWD/form/form.pri)
include ($$PWD/protocol/protocol.pri)
include ($$PWD/qextserialport/qextserialport.pri)

INCLUDEPATH	+= \
			$$PWD/api \
			$$PWD/form \
			$$PWD/protocol \
			$$PWD/qextserialport


