#ifndef INVADEROCTOPUS_H
#define INVADEROCTOPUS_H

#include "graphicalobject.h"

class InvaderOctopus : public GraphicalObject
{
public:
    InvaderOctopus(Position position, Color color);
    void render() override;
};

#endif // INVADEROCTOPUS_H
