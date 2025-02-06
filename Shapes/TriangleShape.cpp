//
// Created by eclipsedmango on 12/11/24.
//

#include "TriangleShape.h"

#include "../Util.h"

TriangleShape::TriangleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 25 * 1.25;
    this->type = 1;
    this->rotation = static_cast<float>(GetRandomValue(0, 1024)) / 1024.0f * 360.0f;
}

void TriangleShape::draw() const {
    DrawPoly(pos, 5, radius, rotation, Color(41, 146, 74, 255));
    DrawPoly(pos, 5, radius - 8, rotation, Color(66, 183, 106, 255));
}

void TriangleShape::physicsUpdate() {
    pos = Vector2Add(pos, Vector2MultiplyS(velocity, physicsDelta));

    rotation += physicsDelta * 180.0f;
}
