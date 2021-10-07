TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        avltree.cpp \
        main.cpp \
        node.cpp

HEADERS += \
    avltree.h \
    benchmark.h \
    node.h \
    test.h
