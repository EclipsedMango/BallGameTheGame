//
// Created by eclipsedmango on 8/11/24.
//

#include "Shape.h"

#include <cmath>
#include <random>

#include "raylib.h"


Shape::Shape(const Vector2 randomPos, const float radius, const int type) {
    this->pos = randomPos;
    this->radius = radius;
    this->type = type;
}

void Shape::draw() const {
    if (type == 0) {
        DrawCircle(pos.x, pos.y, radius, RED);
    } else if (type == 1) {
        DrawPoly(pos, 3, radius, PI, GREEN);
    } else if (type == 2) {
        DrawCircle(pos.x, pos.y, radius, GOLD);
    }

}

Shape::Shape() = default;
