//
// Created by eclipsedmango on 23/11/24.
//

#ifndef PARTICLE_H
#define PARTICLE_H
#include "raylib.h"
#include "../Util.h"

class Particle {
public:
    virtual ~Particle();

    Vector2 pos = {};
    Vector2 velocity = {};
    Color color = Color(255, 255, 255, 255);
    int shape = 0;
    int amount = 0;
    float size = 1;
    float lifespan = 0;

    virtual void draw() const;
    virtual void physicsUpdate();
    Particle();
};

#endif //PARTICLE_H
