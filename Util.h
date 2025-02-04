//
// Created by eclipsedmango on 10/11/24.
//

#ifndef UTIL_H
#define UTIL_H
#include <vector>

#include "raylib.h"
#include "Shapes/Shape.h"

inline int windowWidth = 1920;
inline int windowHeight = 1080;
constexpr float physicsDelta = 1.0f / 240.0f;

inline bool shouldGameClose = false;

inline bool inMenu = true;
inline bool inUpgradeMenu = false;
inline bool isPaused = false;
inline bool hasDied = false;
inline bool destoryParticle = false;

inline float displayScore = 0;
inline float scoreMultiplier = 1.0f;
inline int score = 0;
inline int scoreSize = 64;
inline float scoreMultiplierMax = 8.0f;
inline int scoreMultiplierCost = 15000;

inline int money = 1000000;

inline float timeMultiplier = 1.0f;
inline float timeMultiplierUpgrade = 0.6f;
inline int timeMultiplierCost = 20000;

inline float scoreTimer = 0.0f;
inline float scoreTimerUpgrade = 0.75f;

inline float inputTimeLeft = 1.0f;
inline int inputTimeLeftCost = 20000;
inline float inputTimeLeftUpgrade = 4.0;

inline auto playerColor = Color(52, 156, 243, 255);
inline auto playerColorOutline = Color(31, 104, 150, 255);

void drawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
void drawTextCenteredFont(const Font &font, const char* text, float posX, float posY, int fontSize, float fontSpacing, Color color);
Vector2 Vector2MultiplyS(Vector2 a, float b);
Vector2 Vector2DivideS(Vector2 a, float b);
void drawProgressBar(int posX, int posY, int height, int width, Color fillColor, Color emptyColor, float progress);
float colorClamp(float colorValue);
bool checkOverlapShape(std::vector<Shape*> shapes, Shape* shape);

#endif //UTIL_H
