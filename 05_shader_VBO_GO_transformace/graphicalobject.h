#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include "vertexbuffer.h"
#include "shaderprogram.h"
#include "position.h"
#include "rotation.h"
#include "drawmethod.h"
#include "scale.h"

class GraphicalObject
{
    ShaderProgram* m_program;
    VertexBuffer* m_buffer;
    std::vector<DrawMethod*> m_drawMethods;
    Position m_position;
    Rotation m_rotation;
    Scale m_scale;

public:
    GraphicalObject(ShaderProgram* program, VertexBuffer* buffer, Position position, Rotation rotation, Scale scale);
    ~GraphicalObject();
    void addDrawMethod(DrawMethod* drawMethod);
    Position getPosition();
    Rotation getRotation();
    Scale getScale();
    void render(QMatrix4x4 matrix);
};

#endif // GRAPHICALOBJECT_H
