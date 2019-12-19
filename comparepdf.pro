SOURCES     += main.cpp
HEADERS	    += option_parser.hpp
SOURCES     += option_parser.cpp
LIBS	    += -lpoppler-qt5
exists($(HOME)/opt/poppler018/) {
    message(Using locally built Poppler library)
    INCLUDEPATH += $(HOME)/opt/poppler018/include/poppler/cpp
    INCLUDEPATH += $(HOME)/opt/poppler018/include/poppler/qt4
    LIBS += -Wl,-rpath -Wl,$(HOME)/opt/poppler018/lib -Wl,-L$(HOME)/opt/poppler018/lib
} else {
    exists(/usr/include/poppler/qt5) {
	INCLUDEPATH += /usr/include/poppler/cpp
	INCLUDEPATH += /usr/include/poppler/qt5
    } else {
	INCLUDEPATH += /usr/local/include/poppler/cpp
	INCLUDEPATH += /usr/local/include/poppler/qt5
    }
}
