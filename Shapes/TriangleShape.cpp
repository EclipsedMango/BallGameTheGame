//
// Created by eclipsedmango on 12/11/24.
//

#include "TriangleShape.h"

TriangleShape::TriangleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 20 * 1.25;
    this->type = 1;
}

void TriangleShape::draw() const {
    DrawPoly(pos, 3, radius, PI, GREEN);
}