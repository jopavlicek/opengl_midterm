#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QString>
#include <QOpenGLShaderProgram>

class ShaderProgram
{
    QOpenGLShaderProgram* m_program;
    GLuint m_positionAttr;
    GLuint m_colorAttr;
public:
    ShaderProgram(QString vertexShaderPath,
                  QString fragmentShaderPath,
                  QString positionAttrName,
                  QString colorAttrName);
    GLuint getPositionAttr();
    GLuint getColorAttr();
    QOpenGLShaderProgram* getProgram();
    ~ShaderProgram();
};

#endif // SHADERPROGRAM_H
