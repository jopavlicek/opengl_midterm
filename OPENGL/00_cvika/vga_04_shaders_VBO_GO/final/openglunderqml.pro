QT += qml quick

CONFIG += qmltypes
QML_IMPORT_NAME = OpenGLUnderQML
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    OpenGLScene.h \
    Vertex.h \
    graphicalobject.h \
    shaderprogram.h \
    vertexbuffer.h
SOURCES += main.cpp \
    OpenGLScene.cpp \
    graphicalobject.cpp \
    shaderprogram.cpp \
    vertexbuffer.cpp
RESOURCES += openglunderqml.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/quick/scenegraph/openglunderqml
INSTALLS += target

DISTFILES += \
    grayscale.frag \
    grayscale.vert \
    invert.frag \
    invert.vert
