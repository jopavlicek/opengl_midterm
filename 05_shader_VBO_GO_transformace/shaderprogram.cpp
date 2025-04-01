#include "shaderprogram.h"

ShaderProgram::ShaderProgram(const QString vertexShaderPath, const QString fragmentShaderPath,
                             const QString positionAttrName, const QString colorAttrName, const QString matrixName){

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderPath);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderPath);
    m_program->link();

    m_posAttr = m_program->attributeLocation(positionAttrName);
    m_colAttr = m_program->attributeLocation(colorAttrName);
    m_matrix = m_program->uniformLocation(matrixName);
}

GLuint ShaderProgram::getPositionAttr() const{
    return m_posAttr;
}

GLuint ShaderProgram::getColorAttr() const{
    return m_colAttr;
}

GLuint ShaderProgram::getMatrix() const {
    return m_matrix;
}

QOpenGLShaderProgram* ShaderProgram::getProgram() const{
    return m_program;
}

ShaderProgram::~ShaderProgram(){
    delete m_program;
}
