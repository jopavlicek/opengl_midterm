QT += qml quick

CONFIG += qmltypes
QML_IMPORT_NAME = OpenGLUnderQML
QML_IMPORT_MAJOR_VERSION = 1

HEADERS += \
    OpenGLScene.h \
    Vertex.h \
    drawmethod.h \
    graphicalobject.h \
    position.h \
    rotation.h \
    scale.h \
    shaderprogram.h \
    vertexbuffer.h
SOURCES += main.cpp \
    OpenGLScene.cpp \
    drawmethod.cpp \
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
