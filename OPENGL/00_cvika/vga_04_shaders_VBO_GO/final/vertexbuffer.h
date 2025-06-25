#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QOpenGLBuffer>
#include "Vertex.h"

class VertexBuffer
{
    QOpenGLBuffer* m_buffer;

public:
    VertexBuffer(const Vertex array[], const GLuint verticesCount);
    void bind() const;
    ~VertexBuffer();
};

#endif // VERTEXBUFFER_H
