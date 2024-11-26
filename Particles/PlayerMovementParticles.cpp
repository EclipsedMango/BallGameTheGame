//
// Created by eclipsedmango on 26/11/24.
//

#include "PlayerMovementParticles.h"

PlayerMovementParticles::PlayerMovementParticles(Vector2 playerPos, float size, Vector2 playerVel) {
    this->pos = playerPos;
    this->size = size;
    this->lifespan = 255;
    this->colorAlpha = 255;
    this->color = color;
    this->explosionAmountY = GetRandomValue(-2048, 2048);
    this->explosionAmountX = GetRandomValue(-2048, 2048);
    this->velocity = Vector2(playerVel.x + explosionAmountX, playerVel.y + explosionAmountY);
}

void PlayerMovementParticles::draw() const {
    if (lifespan > 0) {
        DrawCircleV(pos, size, Color(255, 255, 255, colorAlpha));
    }
}

void PlayerMovementParticles::physicsUpdate() {
    size -= physicsDelta * 50;
    pos.x += velocity.x * 0.2f * physicsDelta;
    pos.y += velocity.y * 0.2f * physicsDelta;

    if (lifespan > 0) {
        lifespan -= physicsDelta * 500;
        destoryParticle = false;
    } else {
        destoryParticle = true;
    }

    if (colorAlpha > 0) {
        colorAlpha -= physicsDelta * 500;
    }
}

