//
// Created by eclipsedmango on 23/11/24.
//

#include "PlayerDeathParticle.h"

PlayerDeathParticle::PlayerDeathParticle(const Vector2 playerPos, const float size, const Vector2 playerVel) {
    this->pos = playerPos;
    this->size = size;
    this->lifespan = 500;
    this->colorAlpha = 255;
    this->color = color;
    this->explosionAmountY = GetRandomValue(-2048, 2048);
    this->explosionAmountX = GetRandomValue(-2048, 2048);
    this->velocity = Vector2(playerVel.x + explosionAmountX, playerVel.y + explosionAmountY);
}

void PlayerDeathParticle::draw() const {
    if (lifespan > 0) {
        DrawCircleV(pos, size, Color(playerColor.r, playerColor.g, playerColor.b, colorAlpha));
    }
}

void PlayerDeathParticle::physicsUpdate() {
    size -= physicsDelta * 50;
    pos.x += velocity.x * 0.4f * physicsDelta;
    pos.y += velocity.y * 0.4f * physicsDelta;

    if (lifespan > 0) {
        lifespan -= physicsDelta * 10;
        destoryParticle = false;
    } else {
        destoryParticle = true;
    }

    if (colorAlpha > 0) {
        colorAlpha -= physicsDelta * 500;
    }
}
