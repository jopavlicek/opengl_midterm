#ifndef INVADER_H
#define INVADER_H

#include "graphicalobject.h"

class Invader : public GraphicalObject
{
public:
    Invader(Position position, Color color);
    void render() override;
};

#endif // INVADER_H
