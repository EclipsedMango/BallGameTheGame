//
// Created by eclipsedmango on 12/11/24.
//

#include "GoldCircleShape.h"


GoldCircleShape::GoldCircleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 20 * 0.75;
    this->type = 2;
}

void GoldCircleShape::draw() const {
    DrawCircle(pos.x, pos.y, radius, Color(145, 108, 32, 255));
    DrawCircle(pos.x, pos.y, radius - 4, Color(232, 184, 54, 255));
}