#ifndef GRAPHICALOBJECT_H
#define GRAPHICALOBJECT_H

#include <QOpenGLFunctions>

struct Position{
    GLfloat x;
    GLfloat y;
};

struct Color{
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

struct Vertex{
    Position position;
    Color color;
};

class GraphicalObject
{
protected:
    Position m_position;
    Color m_color;
public:
    GraphicalObject(Position position, Color color);

    virtual void render() = 0;
    virtual ~GraphicalObject(){};
};

#endif // GRAPHICALOBJECT_H
