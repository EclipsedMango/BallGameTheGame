//
// Created by eclipsedmango on 15/03/25.
//

#include "GravityShape.h"

GravityShape::GravityShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 5;
    this->type = BLACK_HOLE;
    this->rotation = static_cast<float>(GetRandomValue(0, 1024)) / 1024.0f * 360.0f;
}

void GravityShape::draw() const {
    DrawPoly(pos, 3, textureRadius, rotation, Color(60, 2, 115, 255));
    DrawPoly(pos, 3, textureRadius - 8, rotation, Color(103, 6, 156, 255));
}

void GravityShape::physicsUpdate() {
    pos = Vector2Add(pos, Vector2MultiplyS(velocity, physicsDelta));

    if (destoryShape) {
        if (textureRadius > 0) {
            textureRadius -= physicsDelta * 128.0;
        }

        if (lifeSpan > 0) {
            lifeSpan -= physicsDelta * 10;
            isDead = false;
        } else {
            isDead = true;
        }
    }

    rotation += physicsDelta * 960.0f;
}
