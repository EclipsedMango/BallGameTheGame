//
// Created by eclipsedmango on 12/11/24.
//

#include "TriangleShape.h"

#include <cstdio>

#include "../Util.h"

TriangleShape::TriangleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 20 * 1.25;
    this->type = 1;
    this->rotation = static_cast<float>(GetRandomValue(0, 1024)) / 1024.0f * 360.0f;
}

void TriangleShape::draw() const {
    DrawPoly(pos, 3, radius, rotation, Color(65, 117, 50, 255));
    DrawPoly(pos, 3, radius - 8, rotation, Color(107, 207, 90, 255));
}

void TriangleShape::physicsUpdate() {
    rotation += physicsDelta * 180.0f;
}
