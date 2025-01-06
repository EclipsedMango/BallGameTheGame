//
// Created by eclipsedmango on 12/11/24.
//

#include "GoldCircleShape.h"


GoldCircleShape::GoldCircleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 25 * 0.75;
    this->type = 2;
}

void GoldCircleShape::draw() const {
    DrawCircle(pos.x, pos.y, radius, Color(176, 129, 31, 255));
    DrawCircle(pos.x, pos.y, radius - 4, Color(222, 166, 51, 255));
}