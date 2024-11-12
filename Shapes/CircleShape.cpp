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
    DrawCircle(pos.x, pos.y, radius, RED);
    // } else if (type == 1) {
    //     DrawPoly(pos, 3, radius, PI, GREEN);
    // } else if (type == 2) {
    //     DrawCircle(pos.x, pos.y, radius, GOLD);
    // }
}