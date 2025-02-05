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

void drawTextCenteredFont(const Font &font, const char* text, const float posX, const float posY, const int fontSize, const float fontSpacing, const Color color) {
    const Vector2 textSize = MeasureTextEx(font, text, fontSize, fontSpacing);
    DrawTextEx(font, text, Vector2(posX - textSize.x / 2.0, posY - textSize.y / 2.0), fontSize, fontSpacing, color);
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

Vector2 Vector2DivideS(const Vector2 a, float b) {
    return Vector2(a.x / b, a.y / 2);
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

// Tries to spawn shape if the new shapes pos isn't overlapping with existing shape pos.
bool trySpawnShape(std::vector<Shape*>* shapes, const int type, Vector2 pos) {
    Shape* shape;

    switch (type) {
    case 0:
        shape = new CircleShape(pos);
        break;
    case 1:
        shape = new TriangleShape(pos);
        break;
    case 2:
        shape = new GoldCircleShape(pos);
        break;
    default: return false;
    }

    if (!checkOverlapShape(*shapes, shape)) {
        shapes->push_back(shape);
        return true;
    }

    return false;
}

// If tryDeleteShape succeeds then return true otherwise false.
bool tryDeleteShape(std::vector<Shape*>* shapes, const Shape* shape, const int index) {
    if (shape->isDead) {
        shapes->erase(shapes->begin() + index);
        delete shape;
        return true;
    }

    return false;
}

