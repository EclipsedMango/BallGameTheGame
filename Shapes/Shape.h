//
// Created by eclipsedmango on 8/11/24.
//

#ifndef SHAPES_H
#define SHAPES_H
#include "raylib.h"
#include "raymath.h"

class Shape {
public:
    virtual ~Shape();

    Vector2 pos = {};
    Vector2 velocity = {};
    float rotation = 0;
    float radius = 0;
    int type = 0;
    int lifeSpan = 255;
    bool isDead = false;
    bool destoryShape = false;
    bool killYourSelf = false;

    virtual void draw() const;
    virtual void physicsUpdate();
    Shape();
};

#endif //SHAPES_H
