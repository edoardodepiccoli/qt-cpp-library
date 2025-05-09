QT += core gui widgets
CONFIG += c++17

INCLUDEPATH += app

# Automatically include all .cpp and .h files recursively from /app
SOURCES += $$files(app/*.cpp, true)
HEADERS += $$files(app/*.h, true)

# Build output organization
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
DESTDIR = bin

TARGET = qt-library
