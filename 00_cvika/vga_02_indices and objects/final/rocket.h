#ifndef ROCKET_H
#define ROCKET_H

#include "graphicalobject.h"

class Rocket : public GraphicalObject
{
public:
    Rocket(Position position);

    void render() override;
};

#endif // ROCKET_H
