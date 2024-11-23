//
// Created by eclipsedmango on 23/11/24.
//

#include "PlayerDeathParticle.h"

#include "../Util.h"

PlayerDeathParticle::PlayerDeathParticle(const Vector2 playerPos, const Color color, const float size) {
    this->pos = playerPos;
    this->velocity;
    this->color = color;
    this->size = size;
    this->lifespan = 300;
}

void PlayerDeathParticle::draw() const {
    if (lifespan > 0) {
        DrawCircle(pos.x, pos.y - velocity.y, size, color);
    }
}

void PlayerDeathParticle::physicsUpdate() {
    velocity.y -= 512 * physicsDelta;

    if (lifespan > 0) {
        lifespan -= physicsDelta * 500;
    }
}
