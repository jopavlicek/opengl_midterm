#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <QOpenGLBuffer>
#include "Vertex.h"

class VertexBuffer
{
    QOpenGLBuffer* m_buffer;
    GLuint m_numberOfVertices;

public:
    VertexBuffer(const Vertex array[], const GLuint verticesCount);
    void bind() const;
    GLuint getNumberOfVertices() const;
    ~VertexBuffer();
};

#endif // VERTEXBUFFER_H
