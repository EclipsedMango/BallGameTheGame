//
// Created by eclipsedmango on 10/11/24.
//

#ifndef UTIL_H
#define UTIL_H
#include "raylib.h"

inline int windowWidth = 1920;
inline int windowHeight = 1080;
constexpr float physicsDelta = 1.0f / 240.0f;

inline bool inMenu = true;
inline bool isPaused = false;
inline bool hasDied = false;
inline bool destoryParticle = false;

inline int score = 0;
inline int scoreSize = 64;
inline float scoreMultiplierMax = 8.0f;

inline auto playerColor = Color(52, 156, 243, 255);

void drawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
Vector2 Vector2MultiplyS(Vector2 a, float b);
void drawProgressBar(int posX, int posY, int height, int width, Color fillColor, Color emptyColor, float progress);

#endif //UTIL_H
