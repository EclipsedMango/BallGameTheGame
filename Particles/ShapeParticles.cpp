//
// Created by eclipsedmango on 25/11/24.
//

#include "ShapeParticles.h"
#include "../Util.h"

ShapeParticles::ShapeParticles(const Vector2 shapePos, const Vector2 playerVel, const float size, const Color color) {
    this->pos = shapePos;
    this->size = size;
    this->lifespan = 155;
    this->colorAlpha = 255;
    this->color = color;
    this->explosionAmountY = GetRandomValue(-2048, 2048);
    this->explosionAmountX = GetRandomValue(-2048, 2048);
    this->velocity = Vector2(playerVel.x + explosionAmountX, playerVel.y + explosionAmountY);
}

void ShapeParticles::draw() const {
    if (lifespan > 0) {
        DrawCircleV(pos, size, Color(color.r, color.g, color.b, colorAlpha));
    }
}

void ShapeParticles::physicsUpdate() {
    size -= physicsDelta * 50;
    pos.x += velocity.x * 0.5f * physicsDelta;
    pos.y += velocity.y * 0.5f * physicsDelta;

    if (lifespan > 0) {
        lifespan -= physicsDelta * 255;
        destoryParticle = false;
    } else {
        destoryParticle = true;
    }

    if (colorAlpha > 0) {
        colorAlpha -= physicsDelta * 500;
    }
}
