TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        connections.cpp \
        main.cpp \
        mapparser.cpp \
        node.cpp

HEADERS += \
    connections.h \
    mapparser.h \
    node.h

LIBS += \
    -lGL \
    -lGLU \
    -lglut
