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
#include "../Shapes/TriangleShape.h"

void runGame() {
    // Timers
    float physicsTimer = 0.0f;

    float shapeSpawnTimer = 0.0f;
    constexpr float shapesDelta = 1.0f / 2.0f;

    float scoreTimer = 0.0f;

    float inputTimeLeft = 1.0f;

    // Player Attributes
    constexpr auto playerStartingPos = Vector2(960, 540);
    constexpr float playerRadius = 15.0f;
    constexpr float gravity = 2048.0f;
    constexpr float playerSpeed = 3.0f;

    Vector2 playerPos = playerStartingPos;

    auto velocity = Vector2(0, 0);

    bool isMouseClicked = false;

    // Player Related Info
    int score = 0;
    float scoreMultiplier = 1.0f;
    float scoreMultiplierMax = 8.0f;

    float timeMultiplier = 1.0f;

    // Shapes
    auto shapes = std::vector<Shape*>();

    // Camera Attributes
    Camera2D camera = {0};
    camera.target = Vector2(playerPos.x, playerPos.y);
    camera.offset = Vector2(windowWidth / 2.0f, windowHeight / 2.0f);
    camera.rotation = 0.0f;
    camera.zoom = 1.25f;

    for (int i = 0; i < 50; ++i) {
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

            if (GetRandomValue(0, 2) == 0) {
                spawnShape(&shapes, 0);
            }

            if (GetRandomValue(0, 12) == 0) {
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

            // Main Player Movement
            if (isMouseClicked) {
                velocity = Vector2MultiplyS(Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), playerPos), playerSpeed);
            }

            // Floor and Ceiling Collision
            if (playerPos.y > 1000 - 15) {
                playerPos.y = 1000 - 15;
                velocity.y = -velocity.y * 0.75f;

                inputTimeLeft = 1.0f;
            } else if (playerPos.y < -1480 - 15) {
                playerPos.y = -1480 - 15;
                velocity.y = -velocity.y * 0.75f;
            }

            // Wall Collision
            if (playerPos.x > 3960 - 15) {
                playerPos.x = 3960 - 15;
                velocity.x = -velocity.x * 0.75f;
            } else if (playerPos.x < -2050 + 15) {
                playerPos.x = -2050 + 15;
                velocity.x = -velocity.x * 0.75f;
            }

            // Shape Collision
            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];

                if (Vector2DistanceSqr(shape->pos, playerPos) < pow(shape->radius + playerRadius, 2.0)) {
                    velocity.y = -1000.0;
                    velocity.x = velocity.x * 0.5f;

                    switch (shape->type) {
                        case 0:
                            score += 100.0f * scoreMultiplier;
                            break;
                        case 1:
                            runGame();
                            return;
                        case 2:
                            score += 200.0f * scoreMultiplier;
                            break;
                        default: break;
                    }

                    scoreTimer = 1.0f;
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
                    std::min(std::max(playerPos.x, -1320.0f), 3225.0f),
                    std::min(std::max(playerPos.y, -1115.0f), windowHeight / 1.8f)),
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

        // Map Walls
        // Floor
        DrawRectangleV(Vector2(-3000, windowHeight - 80.0f), Vector2(7500, 160), Color(33, 37, 43, 255));
        // Right Wall
        DrawRectangleV(Vector2(-3000 + 790, -2500), Vector2(160, 5000), Color(33, 37, 43, 255));
        // Left Wall
        DrawRectangleV(Vector2(3000 + 960, -2500), Vector2(160, 5000), Color(33, 37, 43, 255));
        // Ceiling
        DrawRectangleV(Vector2(-3000, -1670), Vector2(7500, 160), Color(33, 37, 43, 255));

        EndMode2D();

        drawTextCentered(TextFormat("%d", score), 960, 6, 64, RAYWHITE);
        drawProgressBar(960, 128, 50, 600, WHITE, GRAY, inputTimeLeft);

        drawTextCentered(TextFormat("%d", shapes.size()), 24, 36, 24, DARKGREEN);
        DrawFPS(6, 6);
        EndDrawing();
    }
}

void spawnShape(std::vector<Shape*>* shapes, const int type) {
    switch (type) {
        case 0:
            shapes->push_back(new CircleShape(Vector2(GetRandomValue(-3000 + 960, 3000 + 960), GetRandomValue(-1500, 980))));
            break;
        case 1:
            shapes->push_back(new TriangleShape(Vector2(GetRandomValue(-3000 + 960, 3000 + 960), GetRandomValue(-1500, 980))));
            break;
        case 2:
            shapes->push_back(new GoldCircleShape(Vector2(GetRandomValue(-3000 + 960, 3000 + 960), GetRandomValue(-1500, 980))));
            break;
        default: printf("This shape doesn't exist\n");
    }
}
