#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {
public:
    Player() = default;

    Vector2 playerPos = Vector2(0, 500);
    Vector2 velocity = Vector2(0, 0);

    Color playerColor = Color(52, 156, 243, 255);
    Color playerColorOutline = Color(31, 104, 150, 255);

    float speed = 3;
    float gravity = 2048;
    float hitBox = 20;
    float radius = 16;
    float displayRadius = 160;
    float outLineRadius = 20;

    Shader shader{};

    void draw() const;
    void physicsUpdate();
};



#endif //PLAYER_H
