//
// Created by eclipsedmango on 8/11/24.
//

#ifndef SHAPES_H
#define SHAPES_H
#include "raylib.h"

class Shape {
public:
    virtual ~Shape();

    Vector2 pos = {};
    float radius = 0;
    int type = 0;

    virtual void draw() const;
    Shape();
};

#endif //SHAPES_H
