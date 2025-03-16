#ifndef GRAVITYSHAPEPARTICLES_H
#define GRAVITYSHAPEPARTICLES_H
#include "Particle.h"

class GravityShapeParticles : public Particle {
public:
    explicit GravityShapeParticles(Vector2 shapePos, float size, Color color);

    void draw() const override;
    void physicsUpdate() override;

    float colorAlpha = 100;
    int radius = 250;
};

#endif //GRAVITYSHAPEPARTICLES_H
