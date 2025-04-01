#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QOpenGLBuffer>
#include "Vertex.h"

class VertexBuffer
{
    QOpenGLBuffer* m_buffer;
public:
    VertexBuffer(Vertex array[], GLuint verticiesCount);
    void bind();
    ~VertexBuffer();
};

#endif // VERTEXBUFFER_H
