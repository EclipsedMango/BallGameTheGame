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
}

void PlayerDeathParticle::draw() const {
    if (lifespan > 0) {
        DrawCircle(pos.x, pos.y - velocity.y, size, Color(52, 156, 243, colorAlpha));
    }
}

void PlayerDeathParticle::physicsUpdate() {
    velocity.y -= 512 * physicsDelta;

    if (colorAlpha > 0) {
        colorAlpha -= physicsDelta * 500;
    }

    if (lifespan > 0) {
        lifespan -= physicsDelta * 500;
        destoryParticle = false;
    } else {
        destoryParticle = true;
    }
}
