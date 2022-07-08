TEMPLATE = app
TARGET = createDB
INCLUDEPATH += .

QT += core gui widgets sql
DEFINES += QT_DEPRECATED_WARNINGS

MOC_DIR = build
OBJECTS_DIR = build

SOURCES += create.cpp \
           ../connection/connectDB.cpp

HEADERS += ../connection/connectDB.hpp
