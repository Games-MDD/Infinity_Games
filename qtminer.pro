TEMPLATE = app
TARGET = qtminer
INCLUDEPATH += .

DEFINES += QT_DEPRECATED_WARNINGS

QT += core gui widgets sql

MOC_DIR = build
OBJECTS_DIR = build

# Input
HEADERS += src/Minefield/Button.hpp \
           src/Minefield/Change.hpp \
           src/Minefield/genField.hpp \
           src/Results/connection/connectDB.hpp \
           src/Results/select/selectFromDB.hpp \
					 src/Results/insert/insertIntoDB.hpp \
           src/Results/Results.hpp \
           src/MainWindow.hpp

SOURCES += src/Minefield/Button.cpp \
           src/Minefield/Change.cpp \
           src/Minefield/genField.cpp \
           src/Results/connection/connectDB.cpp \
           src/Results/select/selectFromDB.cpp \
					 src/Results/insert/insertIntoDB.cpp \
           src/Results/Results.cpp \
           src/MainWindow.cpp \
           src/main.cpp