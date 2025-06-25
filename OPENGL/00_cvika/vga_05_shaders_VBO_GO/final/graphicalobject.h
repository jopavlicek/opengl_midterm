#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include "vertexbuffer.h"
#include "shaderprogram.h"
#include "position.h"
#include "rotation.h"

class GraphicalObject
{
    ShaderProgram* m_program;
    VertexBuffer* m_buffer;
    Position m_position;
    Rotation m_rotation;
public:
    GraphicalObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation);
    ~GraphicalObject();
    Position getPosition() const;
    Rotation getRotation() const;
    void render(QMatrix4x4 matrix) const;
};

#endif // GRAPHICALOBJECT_H
