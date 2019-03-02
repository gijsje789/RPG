TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    capp.cpp

HEADERS += \
    log.h \
    capp.h

# Command
# -L[Directory path of "lib" folder] -lSDL2
LIBS += -LD:\SDL2-2.0.9\x86_64-w64-mingw32\lib -lSDL2
# D:\SDL2-2.0.4\x86_64-w64-mingw32\lib -lSDL2

# [Directory of "include"]
INCLUDEPATH += D:\SDL2-2.0.9\x86_64-w64-mingw32\include\SDL2
# D:\SDL2-2.0.4\x86_64-w64-mingw32\include\SDL2
