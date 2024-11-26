//
// Created by eclipsedmango on 26/11/24.
//

#ifndef PLAYERMOVEMENTPARTICLES_H
#define PLAYERMOVEMENTPARTICLES_H
#include "Particle.h"


class PlayerMovementParticles : public Particle {
public:
    explicit PlayerMovementParticles(Vector2 playerPos, float size, Vector2 playerVel);

    void draw() const override;
    void physicsUpdate() override;

    float colorAlpha = 0;
    float explosionAmountY = 0;
    float explosionAmountX = 0;
};



#endif //PLAYERMOVEMENTPARTICLES_H
