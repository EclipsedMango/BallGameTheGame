//
// Created by eclipsedmango on 10/11/24.
//

#include "Util.h"

#include <vector>

#include "raymath.h"
#include "Shapes/Shape.h"

void drawTextCentered(const char* text, const int posX, const int posY, const int fontSize, const Color color) {
    const int textSize = MeasureText(text, fontSize);
    DrawText(text, posX - (textSize / 2), posY, fontSize, color);
}

void drawProgressBar(const int posX, const int posY, const int height, const int width, const Color fillColor, const Color emptyColor, const float progress) {
    const int barWidth = posX - width / 2.0;
    const int barHeight = posY - height / 2.0;

    DrawRectangle(barWidth, barHeight, width, height, emptyColor);
    DrawRectangle(barWidth, barHeight, width * progress, height, fillColor);
}

Vector2 Vector2MultiplyS(const Vector2 a, float b) {
    return Vector2(a.x * b, a.y * b);
}

float colorClamp(const float colorValue) {
    if (colorValue > 255) {
        return 255;
    }
    if (colorValue < 0) {
        return 0;
    }
    return colorValue;
}

bool checkOverlapShape(std::vector<Shape*> shapes, Shape* shape) {
    for (Shape* shapeOld: shapes) {

        if (Vector2Distance(shapeOld->pos, shape->pos) < shapeOld->radius + shape->radius) {
            return true;
        }
    }
    return false;
}

