//
// Created by eclipsedmango on 8/11/24.
//

#include "Shape.h"

#include <random>

#include "raylib.h"


Shape::Shape(Vector2 randomPos, float radius, Color color) {
    this->pos = randomPos;
    this->radius = radius;
    this->color = color;
}

void Shape::draw() const {
    DrawCircle(pos.x, pos.y, radius, color);
}

Shape::Shape() = default;
