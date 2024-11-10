//
// Created by eclipsedmango on 8/11/24.
//

#ifndef SHAPES_H
#define SHAPES_H
#include "raylib.h"

class Shape {
public:
    Vector2 pos = {};
    float radius = 0;
    int type = 0;

    Shape(Vector2 randomPos, float radius, int type);
    void draw() const;
    Shape();
};

#endif //SHAPES_H
