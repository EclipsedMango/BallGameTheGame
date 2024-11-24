//
// Created by eclipsedmango on 23/11/24.
//

#include "PlayerDeathParticle.h"

#include "../Util.h"

PlayerDeathParticle::PlayerDeathParticle(const Vector2 playerPos, const float size) {
    this->pos = playerPos;
    this->velocity;
    this->size = size;
    this->lifespan = 255;
    this->colorAlpha = 255;
    this->explosionAmountY = GetRandomValue(-2048, 2048);
    this->explosionAmountX = GetRandomValue(-2048, 2048);
}

void PlayerDeathParticle::draw() const {
    if (lifespan > 0) {
        DrawCircle(pos.x - velocity.x, pos.y - velocity.y, size, Color(52, 156, 243, colorAlpha));
    }
}

void PlayerDeathParticle::physicsUpdate() {
    velocity.y += explosionAmountY * physicsDelta;
    velocity.x += explosionAmountX * physicsDelta;

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
