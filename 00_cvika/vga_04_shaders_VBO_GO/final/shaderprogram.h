#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <QString>
#include <QOpenGLShaderProgram>

class ShaderProgram
{
    QOpenGLShaderProgram* m_program;
    GLuint m_posAttr;
    GLuint m_colAttr;

public:
    ShaderProgram(const QString vertexShaderPath, const QString frangmentShaderPath,
                  const QString positionAttrName, const QString colorAttrName);
    GLuint getPositionAttr() const;
    GLuint getColorAttr() const;
    QOpenGLShaderProgram* getProgram() const;
    ~ShaderProgram();
};

#endif // SHADERPROGRAM_H
