//
// Created by eclipsedmango on 23/11/24.
//

#ifndef PLAYERDEATHPARTICLE_H
#define PLAYERDEATHPARTICLE_H
#include "Particle.h"

class PlayerDeathParticle : public Particle {
public:
    explicit PlayerDeathParticle(Vector2 playerPos, Color color, float size);

    void draw() const override;
    void physicsUpdate() override;
};



#endif //PLAYERDEATHPARTICLE_H
