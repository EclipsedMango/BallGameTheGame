//
// Created by eclipsedmango on 10/11/24.
//

#ifndef UTIL_H
#define UTIL_H
#include <vector>

#include "raylib.h"
#include "Player.h"
#include "Particles/Particle.h"
#include "Shapes/Shape.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#endif

inline int windowWidth = 1920;
inline int windowHeight = 1080;
constexpr float physicsDelta = 1.0f / 240.0f;

inline bool shouldGameClose = false;
inline bool shouldScreenShake = false;

inline Player* player = new Player();

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

inline int money = 1000000000;

inline float timeMultiplier = 1.0f;
inline float timeMultiplierUpgrade = 0.6f;
inline int timeMultiplierCost = 20000;

inline float scoreTimer = 0.0f;
inline float scoreTimerUpgrade = 0.75f;

inline float inputTimeLeft = 1.0f;
inline int inputTimeLeftCost = 20000;
inline float inputTimeLeftUpgrade = 4.0;
inline float inputTimeLeftStrength = 0.75;

inline bool canDestroyPentagon = false;
inline int destroyPentagonCost = 500000;

void drawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
void drawTextCenteredFont(const Font &font, const char* text, float posX, float posY, int fontSize, float fontSpacing, Color color);
Vector2 Vector2MultiplyS(Vector2 a, float b);
Vector2 Vector2DivideS(Vector2 a, float b);
float getRandomFloat();
float getRandomFloatRange(float min, float max);
void drawProgressBar(int posX, int posY, int height, int width, Color fillColor, Color emptyColor, float progress);
float colorClamp(float colorValue);
bool checkOverlapShape(std::vector<Shape*> shapes, Shape* shape);
bool trySpawnShape(std::vector<Shape*>* shapes, Shapes type, Vector2 pos, bool ignoreWindowBounds = false);
bool compareColors(Color color1, Color color2);
void spawnShapeRandom(std::vector<Shape*>* shapes, Shapes type, Vector2 minPos, Vector2 maxPos, bool ignoreWindowBounds = false);
bool tryDeleteShape(std::vector<Shape*>* shapes, const Shape* shape, int index);
void spawnShapeParticles(std::vector<Particle*>* particles, Vector2 shapePos, Vector2 playerVel, Shapes type);
void spawnPlayerParticles(std::vector<Particle*>* particles, Vector2 playerPos, Vector2 playerVel, int type);
void createDisplayScore (Shapes type);
void runPostProcessing(const Texture2D &texture, Shader shader);

#endif //UTIL_H
