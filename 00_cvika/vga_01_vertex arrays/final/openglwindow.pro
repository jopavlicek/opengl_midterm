include(openglwindow.pri)

SOURCES += \
    main.cpp

target.path = $$[PWD]/openglwindow
INSTALLS += target

CONFIG += c++11

QT += opengl
