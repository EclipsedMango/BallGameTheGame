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
    Color color = {};

    Shape(Vector2 randomPos, float radius, Color color);
    void draw() const;
    Shape();
};

#endif //SHAPES_H
