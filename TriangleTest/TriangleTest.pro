QT += core gui

CONFIG += c++11

TARGET = TriangleTest
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    window.cpp \
    ray.cpp \
    triangle.cpp \
    trianglecutter.cpp \
    mesh.cpp \
    vertex.cpp

INCLUDEPATH += "C:\glm\glm"

HEADERS += \
    window.h \
    vertex.h \
    ray.h \
    triangle.h \
    mesh.h \
    trianglecutter.h

DISTFILES += \
    simple.vert \
    simple.frag
