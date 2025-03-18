//
// Created by eclipsedmango on 12/11/24.
//

#include "PentagonShape.h"

#include "../Util.h"

PentagonShape::PentagonShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 32;
    this->type = GREEN_PENTAGON;
    this->lifeSpan = 20;
    this->rotation = static_cast<float>(GetRandomValue(0, 1024)) / 1024.0f * 360.0f;
}

void PentagonShape::draw() const {
    DrawPoly(pos, 5, radius, rotation, Color(41, 146, 74, 255));
    DrawPoly(pos, 5, radius - 8, rotation, Color(66, 183, 106, 255));
}

void PentagonShape::physicsUpdate() {
    pos = Vector2Add(pos, Vector2MultiplyS(velocity, physicsDelta));

    if (destoryShape) {
        if (radius > 0) {
            radius -= physicsDelta * 256.0;
        }

        if (lifeSpan > 0) {
            lifeSpan -= physicsDelta * 10;
            isDead = false;
        } else {
            isDead = true;
        }
    }

    rotation += physicsDelta * 180.0f;
}
