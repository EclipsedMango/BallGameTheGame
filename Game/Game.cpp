//
// Created by eclipsedmango on 10/11/24.
//

#include "Game.h"

#include <cstdio>
#include <vector>

#include "raylib.h"
#include "raymath.h"
#include "../Shapes/CircleShape.h"
#include "../Util.h"
#include "../Shapes/GoldCircleShape.h"
#include "../Shapes/ScoreText.h"
#include "../Shapes/TriangleShape.h"

void runGame() {
    // Timers
    float physicsTimer = 0.0f;

    float shapeSpawnTimer = 0.0f;
    constexpr float shapesDelta = 1.0f / 2.0f;

    float scoreTimer = 0.0f;

    float inputTimeLeft = 1.0f;

    // Player Attributes
    constexpr auto playerStartingPos = Vector2(0, 540);
    constexpr float playerRadius = 15.0f;
    constexpr float gravity = 2048.0f;
    constexpr float playerSpeed = 3.0f;

    Vector2 playerPos = playerStartingPos;

    auto velocity = Vector2(0, 0);

    bool isMouseClicked = false;

    // Player Related Info
    float displayScore = 0;
    float scoreMultiplier = 1.0f;
    float scoreMultiplierMax = 8.0f;
    score = 0;

    float timeMultiplier = 1.0f;

    // Shapes
    auto shapes = std::vector<Shape*>();

    // Camera Attributes
    Camera2D camera = {0};
    camera.target = Vector2(playerPos.x, playerPos.y);
    camera.offset = Vector2(windowWidth / 2.0f, windowHeight / 2.0f);
    camera.rotation = 0.0f;
    camera.zoom = 1.25f * (windowHeight / 1080.0f);

    for (int i = 0; i < 75; ++i) {
        spawnShape(&shapes, 0);

        if (i < 15) {
            spawnShape(&shapes, 1);
        }

        if (i < 2) {
            spawnShape(&shapes, 2);
        }
    }

    // Main game loop
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();
        physicsTimer += delta * timeMultiplier;
        shapeSpawnTimer += delta * timeMultiplier;
        scoreTimer -= delta * timeMultiplier;
        inputTimeLeft = std::max(inputTimeLeft - delta / timeMultiplier / 24.0f, 0.0f);

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();

            camera.offset = Vector2(windowWidth / 2.0f, windowHeight / 2.0f);
            camera.zoom = 1.25f * (windowHeight / 1080.0f);
        }

        if (inputTimeLeft > 0.0f) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                timeMultiplier = 0.3f;
            } else {
                timeMultiplier = 1.0f;
            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isMouseClicked = true;

                inputTimeLeft = std::max(inputTimeLeft - 0.25f, 0.0f);
            }
        } else if (inputTimeLeft == 0) {
            timeMultiplier = 1.0f;
        }

        if (scoreTimer < 0.0f) {
            scoreMultiplier = 1.0f;
        }

        // Shape Process
        while (shapeSpawnTimer > shapesDelta && shapes.size() < 1500) {
            shapeSpawnTimer -= shapesDelta;

            if (GetRandomValue(0, 8) == 0) {
                spawnShape(&shapes, 0);
            }

            if (GetRandomValue(0, 24) == 0) {
                spawnShape(&shapes, 1);
            }

            if (GetRandomValue(0, 32) == 0) {
                spawnShape(&shapes, 2);
            }
        }

        // Physics Process
        while (physicsTimer > physicsDelta) {
            physicsTimer -= physicsDelta;

            // Update
            velocity.y += gravity * physicsDelta;
            playerPos = Vector2Add(playerPos, Vector2MultiplyS(velocity, physicsDelta));

            for (const auto shape: shapes) {
                shape->physicsUpdate();
            }

            std::erase_if(shapes,
                [](const Shape* o) { return o->killYourSelf; });

            // Main Player Movement
            if (isMouseClicked) {
                velocity = Vector2MultiplyS(Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), playerPos), playerSpeed);
            }

            // Floor and Ceiling Collision
            if (playerPos.y > 1000 - 15) {
                playerPos.y = 1000 - 15;
                velocity.y = -velocity.y * 0.75f;
                velocity.x = velocity.x * 0.99f;

                inputTimeLeft = 1.0f;
            } else if (playerPos.y < -1480 - 15) {
                playerPos.y = -1480 - 15;
                velocity.y = -velocity.y * 0.75f;
            }

            // Wall Collision
            if (playerPos.x > 3000 - 15) {
                playerPos.x = 3000 - 15;
                velocity.x = -velocity.x * 0.75f;
            } else if (playerPos.x < -3000 + 15) {
                playerPos.x = -3000 + 15;
                velocity.x = -velocity.x * 0.75f;
            }

            // Shape Collision
            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];

                if (shape->type != 4 && Vector2DistanceSqr(shape->pos, playerPos) < pow(shape->radius + playerRadius, 2.0)) {
                    velocity.y = -1000.0;
                    velocity.x = velocity.x * 0.5f;

                    switch (shape->type) {
                        case 0:
                            displayScore = 100.0f * scoreMultiplier;
                            score += displayScore;
                            spawnShape(&shapes, 0);
                            shapes.push_back(new ScoreText(shape->pos, displayScore));
                            break;
                        case 1:
                            inMenu = true;
                            hasDied = true;
                            return;
                        case 2:
                            displayScore = 500.0f * scoreMultiplier;
                            score += displayScore;
                            shapes.push_back(new ScoreText(shape->pos, displayScore));
                            break;
                        default: break;
                    }

                    scoreTimer = 1.5f;
                    inputTimeLeft = std::min(inputTimeLeft + 0.5f, 1.0f);

                    if (scoreMultiplier < scoreMultiplierMax) {
                        scoreMultiplier++;
                    }

                    shapes.erase(shapes.begin() + i);
                    delete shape;
                    break;
                }
            }
            camera.target = Vector2Lerp(camera.target,
                Vector2(
                    std::clamp(playerPos.x, -3030.0f + (windowWidth / camera.zoom) / 2.0f, 3030.0f - (windowWidth / camera.zoom) / 2.0f),
                    std::min(std::max(playerPos.y, -1115.0f), 1080 / 1.8f)),
                    10.0f * physicsDelta);

            isMouseClicked = false;
        }

        // Draw
        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));

        // Draw within the camera
        BeginMode2D(camera);

        // Velocity Preview
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && inputTimeLeft > 0.0f) {
            Vector2 vel = Vector2MultiplyS(Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), playerPos), playerSpeed);
            Vector2 pos = playerPos;

            constexpr int lineCount = 300;

            for (int i = 0; i < lineCount; ++i) {
                vel.y += gravity * physicsDelta;
                const Vector2 newPos = Vector2Add(pos, Vector2MultiplyS(vel, physicsDelta));
                DrawLineEx(pos, newPos, 5, Color(240, 240, 240, (1.0f - static_cast<float>(i) / static_cast<float>(lineCount)) * 255.0f));
                pos = newPos;
            }
        }

        // Draw Shapes
        for (auto shape: shapes) {
            shape->draw();
        }

        // Player
        DrawCircleV(playerPos, playerRadius, Color(52, 156, 243, 255));

        // Floor
        DrawRectangleV(Vector2(-3000, 1080 - 80.0f), Vector2(7500, 160), Color(33, 37, 43, 255));
        // Left Wall
        DrawRectangleV(Vector2(-3000 - 160, -2500), Vector2(160, 5000), Color(33, 37, 43, 255));
        // Right Wall
        DrawRectangleV(Vector2(3000, -2500), Vector2(160, 5000), Color(33, 37, 43, 255));
        // Ceiling
        DrawRectangleV(Vector2(-3000, -1670), Vector2(7500, 160), Color(33, 37, 43, 255));

        EndMode2D();

        drawTextCentered(TextFormat("%d", score), windowWidth / 2.0f, 24, 64, RAYWHITE);
        drawProgressBar(windowWidth / 2.0f, 128, 30, 600, WHITE, GRAY, inputTimeLeft);

        drawTextCentered(TextFormat("%d", shapes.size()), 24, 36, 20, LIME);
        DrawFPS(6, 6);
        EndDrawing();
    }
}

void spawnShape(std::vector<Shape*>* shapes, const int type) {
    switch (type) {
        case 0:
            shapes->push_back(new CircleShape(Vector2(GetRandomValue(-3000 + 50, 3000 - 50), GetRandomValue(-1500, 980))));
            break;
        case 1:
            shapes->push_back(new TriangleShape(Vector2(GetRandomValue(-3000 + 50, 3000 - 50), GetRandomValue(-1500, 980))));
            break;
        case 2:
            shapes->push_back(new GoldCircleShape(Vector2(GetRandomValue(-3000 + 50, 3000 - 50), GetRandomValue(-1500, 980))));
            break;
        default: printf("This shape doesn't exist\n");
    }
}
