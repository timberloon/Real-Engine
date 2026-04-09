#pragma once
#include "component.h"

// Movement system = logic
inline void MovementSystem(Position &pos, Velocity &vel) {
    pos.x += vel.dx;
    pos.y += vel.dy;
}