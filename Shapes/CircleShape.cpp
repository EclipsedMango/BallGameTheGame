//
// Created by eclipsedmango on 11/11/24.
//

#include "CircleShape.h"

CircleShape::CircleShape(const Vector2 randomPos) {
    this->pos = randomPos;
    this->radius = 22;
    this->type = RED_CIRCLE;
    this->lifeSpan = 255;
}

void CircleShape::draw() const {
    DrawCircle(pos.x, pos.y, radius, Color(160, 51, 60, 255));
    DrawCircle(pos.x, pos.y, radius - 5, Color(212, 65, 77, 255));
}

void CircleShape::physicsUpdate() {
    pos = Vector2Add(pos, Vector2MultiplyS(velocity, physicsDelta));

    if (destoryShape) {
        if (radius > 0) {
            radius -= physicsDelta * 128.0;
        }

        if (lifeSpan > 0) {
            lifeSpan -= physicsDelta * 10;
            isDead = false;
        } else {
            isDead = true;
        }
    }
}
