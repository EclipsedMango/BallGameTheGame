//
// Created by eclipsedmango on 23/11/24.
//

#ifndef PLAYERDEATHPARTICLE_H
#define PLAYERDEATHPARTICLE_H
#include "Particle.h"

class PlayerDeathParticle : public Particle {
public:
    explicit PlayerDeathParticle(Vector2 playerPos, float size);

    void draw() const override;
    void physicsUpdate() override;

    float colorAlpha = 0;
    float explosionAmountY = 0;
    float explosionAmountX = 0;
};



#endif //PLAYERDEATHPARTICLE_H
