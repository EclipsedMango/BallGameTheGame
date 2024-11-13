//
// Created by eclipsedmango on 10/11/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "raylib.h"

constexpr int windowWidth = 1920;
constexpr int windowHeight = 1080;
constexpr float physicsDelta = 1.0f / 240.0f;

void drawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
Vector2 Vector2MultiplyS(Vector2 a, float b);
void drawProgressBar(int posX, int posY, int height, int width, Color fillColor, Color emptyColor, float progress);

#endif //UTIL_H
