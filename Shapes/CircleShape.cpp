//
// Created by eclipsedmango on 11/11/24.
//

#include "CircleShape.h"

CircleShape::CircleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 20;
    this->type = 0;
}

void CircleShape::draw() const {
    DrawCircle(pos.x, pos.y, radius, Color(138, 36, 60, 255));
    DrawCircle(pos.x, pos.y, radius - 4, Color(236, 55, 82, 255));
}