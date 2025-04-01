#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include "vertexbuffer.h"
#include "shaderprogram.h"

class GraphicalObject
{
    ShaderProgram* m_program;
    VertexBuffer* m_buffer;
public:
    GraphicalObject(ShaderProgram* program, VertexBuffer* buffer);
    ~GraphicalObject();
    void render() const;
};

#endif // GRAPHICALOBJECT_H
