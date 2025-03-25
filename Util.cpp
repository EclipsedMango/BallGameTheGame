//
// Created by eclipsedmango on 10/11/24.
//

#include "Util.h"

#include <cstdio>
#include <vector>

#include "raymath.h"
#include "Particles/GravityShapeParticles.h"
#include "Particles/PlayerDeathParticle.h"
#include "Particles/PlayerMovementParticles.h"
#include "Particles/ShapeParticles.h"
#include "Shapes/CircleShape.h"
#include "Shapes/GoldCircleShape.h"
#include "Shapes/GravityShape.h"
#include "Shapes/PentagonShape.h"
#include "Shapes/ScoreText.h"
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

float getRandomFloat() {
    return static_cast<float>(GetRandomValue(0, 2147483647)) / 2147483648.0f;
}

float getRandomFloatRange(const float min, const float max) {
    return getRandomFloat() * (max - min) + min;
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

bool isShapeInWindow(Shape shape, const Vector2 windowPos) {
    Vector2 shapeWindowPos = Vector2Subtract(shape.pos, windowPos);
    return shapeWindowPos.x > 0 && shapeWindowPos.x < windowWidth &&
           shapeWindowPos.y > 0 && shapeWindowPos.y < windowHeight;
}

// Tries to spawn shape if the new shapes pos isn't overlapping with existing shape pos.
bool trySpawnShape(std::vector<Shape*>* shapes, const Shapes type, Vector2 pos, bool ignoreWindowBounds) {
    Shape* shape;

    switch (type) {
    case RED_CIRCLE:
        shape = new CircleShape(pos);
        break;
    case GREEN_PENTAGON:
        shape = new PentagonShape(pos);
        break;
    case GOLD_CIRCLE:
        shape = new GoldCircleShape(pos);
        break;
    case BLACK_HOLE:
        shape = new GravityShape(pos);
        break;
    default: return false;
    }

    bool passWindowCheck = ignoreWindowBounds || !isShapeInWindow(*shape, Vector2Subtract(player->playerPos, Vector2(windowWidth / 2.0, windowHeight / 2.0)));

    if (!checkOverlapShape(*shapes, shape) && passWindowCheck) {
        shapes->push_back(shape);
        return true;
    }

    delete shape;
    return false;
}

bool compareColors(const Color color1, const Color color2) {
    return color1.r == color2.r && color1.g == color2.g && color1.b == color2.b && color1.a == color2.a;
}

void spawnShapeRandom(std::vector<Shape*>* shapes, const Shapes type, const Vector2 minPos, const Vector2 maxPos, bool ignoreWindowBounds) {
    for (int i = 0; i < 128; i++) {
        if (trySpawnShape(shapes, type, Vector2(GetRandomValue(minPos.x, maxPos.x), GetRandomValue(minPos.y, maxPos.y)), ignoreWindowBounds)) {
            return;
        }
    }

    printf("\nFailed to spawn to spawn shape.\n");
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

void spawnShapeParticles(std::vector<Particle*>* particles, const Vector2 shapePos, const Vector2 playerVel, const Shapes type) {
    switch (type) {
        case RED_CIRCLE:
            particles->push_back(new ShapeParticles(shapePos, playerVel, 15, Color(236, 55, 82)));
            break;
        case GOLD_CIRCLE:
            particles->push_back(new ShapeParticles(shapePos, playerVel, 10, Color(232, 184, 54)));
            break;
        case BLACK_HOLE:
            particles->push_back(new GravityShapeParticles(shapePos, 3, Color(126, 0, 176)));
            break;
        case GREEN_PENTAGON:
            particles->push_back(new ShapeParticles(shapePos, playerVel, 18, Color(41, 146, 74)));
        default: printf("This particle doesn't exist\n");
    }
}

void spawnPlayerParticles(std::vector<Particle*>* particles, const Vector2 playerPos, const Vector2 playerVel, const int type) {
    switch (type) {
        case 0:
            particles->push_back(new PlayerMovementParticles(playerPos, 8, playerVel));
            break;
        case 1:
            particles->push_back(new PlayerDeathParticle(Vector2(GetRandomValue(playerPos.x, playerPos.x + GetRandomValue(-30, 30)),
                GetRandomValue(playerPos.y, playerPos.y - 45)), 16, playerVel));
            break;
        default: printf("This PlayerParticle doesn't exist\n");
    }
}

void createDisplayScore (const Shapes type) {
    switch (type) {
        case RED_CIRCLE:
            displayScore = 100.0f * scoreMultiplier;
            score += displayScore;
            scoreSize += 25;
            break;
        case GOLD_CIRCLE:
            displayScore = 500.0f * scoreMultiplier;
            score += displayScore;
            scoreSize += 35;
            break;
        case GREEN_PENTAGON:
            displayScore = 350.0f * scoreMultiplier;
            score += displayScore;
            scoreSize += 30;
        default: break;
    }
}

void runPostProcessing(const Texture2D &texture, const Shader shader) {
    BeginShaderMode(shader);
    DrawTextureRec(texture, (Rectangle){0, 0, static_cast<float>(texture.width), static_cast<float>(-texture.height)}, Vector2(0, 0), WHITE);
    EndShaderMode();
}

