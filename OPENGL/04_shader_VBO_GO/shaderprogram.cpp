#include "shaderprogram.h"

ShaderProgram::ShaderProgram(QString vertexShaderPath, QString fragmentShaderPath, QString positionAttrName, QString colorAttrName) {
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPath);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderPath);
    m_program->link();

    m_positionAttr = m_program->attributeLocation(positionAttrName);
    m_colorAttr = m_program->attributeLocation(colorAttrName);
}

GLuint ShaderProgram::getPositionAttr() {
    return m_positionAttr;
}

GLuint ShaderProgram::getColorAttr() {
    return m_colorAttr;
}

QOpenGLShaderProgram* ShaderProgram::getProgram() {
    return m_program;
}

ShaderProgram::~ShaderProgram() {
    delete m_program;
}
