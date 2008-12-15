
CONFIQ += qt app console debug

MOC_DIR = tmp
OBJECTS_DIR = tmp
RCC_DIR = tmp

DESTDIR = bin

INCLUDEPATH += ./src/lua/ 

HEADERS += 	\
		src/lua/*.h \
		src/Unicalc.h \
		src/UnicalcAccess.h \
		src/UnicalcMath.h \
		src/UnicalcLua.h \
		src/Unilua.h \
		\

SOURCES += 	\
		src/lua/*.c \
		src/main.cpp \
		src/Unicalc.cpp \
		src/UnicalcMath.cpp \
		src/UnicalcLua.cpp \
		src/Unilua.cpp \
		\


RESOURCES += 	res/images.qrc \


