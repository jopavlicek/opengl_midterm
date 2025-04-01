#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <QOpenGLFunctions>
#include <vector>

#include "vertexbuffer.h"
#include "shaderprogram.h"
#include "drawmethod.h"

class GraphicalObject
{
    ShaderProgram* m_shaderProgram;
    VertexBuffer* m_vertexBuffer;
    std::vector<DrawMethod*> m_drawMethods;

public:
    GraphicalObject(ShaderProgram* program, VertexBuffer* buffer);
    ~GraphicalObject();
    void addDrawMethod(DrawMethod* drawMethod);
    void render();
};

#endif // GRAPHICALOBJECT_H
