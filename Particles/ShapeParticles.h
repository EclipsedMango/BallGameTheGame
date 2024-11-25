//
// Created by eclipsedmango on 25/11/24.
//

#ifndef SHAPEPARTICLES_H
#define SHAPEPARTICLES_H
#include "Particle.h"
#include "raylib.h"

class ShapeParticles : public Particle {
public:
    explicit ShapeParticles(Vector2 shapePos, Vector2 playerVel, float size, Color color);

    void draw() const override;
    void physicsUpdate() override;

    float colorAlpha = 0;
    float gravity = 0;
    float explosionAmountY = 0;
    float explosionAmountX = 0;
};



#endif //SHAPEPARTICLES_H
