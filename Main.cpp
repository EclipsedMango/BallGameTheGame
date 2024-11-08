#include <array>
#include <iostream>
#include <vector>

#include "raylib.h"
#include "raymath.h"
#include "Shape.h"

void drawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
Vector2 Vector2MultiplyS(Vector2 a, float b);

int main() {
    // Initialization
    const int monitor = GetCurrentMonitor();
    constexpr int windowWidth = 1920;
    constexpr int windowHeight = 1080;

    InitWindow(windowWidth, windowHeight, "Ball Game The Game");
    SetWindowMonitor(monitor);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Timers
    float physicsTimer = 0.0f;
    constexpr float physicsDelta = 1.0f / 240.0f;

    float shapeSpawnTimer = 0.0f;
    constexpr float shapesDelta = 1.0f / 2.0f;

    float scoreTimer = 0.0f;

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

    // Camera Attributes
    Camera2D camera = {0};
    camera.target = Vector2(playerPos.x, playerPos.y);
    camera.offset = Vector2(windowWidth / 2.0f, windowHeight / 2.0f);
    camera.rotation = 0.0f;
    camera.zoom = 1.25f;

    // Shapes
    auto shapes = std::vector<Shape>();

    for (int i = 0; i < 100; ++i) {
        shapes.emplace_back(Vector2(GetRandomValue(-3000 + 960, 3000 + 960), GetRandomValue(-1500, 980)), 20, RED);
    }

    // Main game loop
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();
        physicsTimer += delta * timeMultiplier;
        shapeSpawnTimer += delta * timeMultiplier;
        scoreTimer -= delta * timeMultiplier;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            timeMultiplier = 0.3f;
        } else {
            timeMultiplier = 1.0f;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            isMouseClicked = true;
        }

        if (scoreTimer < 0.0f) {
            scoreMultiplier = 1.0f;
        }

        // Shape Process
        while (shapeSpawnTimer > shapesDelta && shapes.size() < 1500) {
            shapeSpawnTimer -= shapesDelta;
            shapes.emplace_back(Vector2(GetRandomValue(-3000 + 960, 3000 + 960), GetRandomValue(-1500, 980)), 20, RED);
        }

        // Physics Process
        while (physicsTimer > physicsDelta) {
            physicsTimer -= physicsDelta;

            // Update
            velocity.y += gravity * physicsDelta;
            playerPos = Vector2Add(playerPos, Vector2MultiplyS(velocity, physicsDelta));

            // Main Player Movement
            if (isMouseClicked) {
                velocity = Vector2MultiplyS(Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), playerPos), playerSpeed);
            }

            // Floor Collision
            if (playerPos.y > 1000 - 15) {
                playerPos.y = 1000 - 15;
                velocity.y = -velocity.y * 0.75f;
            }

            // Shape Collision
            for (int i = 0; i < shapes.size(); ++i) {
                Shape shape = shapes[i];
                if (Vector2DistanceSqr(shape.pos, playerPos) < pow(shape.radius + playerRadius, 2.0)) {
                    shapes.erase(shapes.begin() + i);

                    velocity.y = -1000.0;
                    velocity.x = velocity.x * 0.5f;

                    score += 100.0f * scoreMultiplier;
                    scoreTimer = 1.0f;

                    if (scoreMultiplier < scoreMultiplierMax) {
                        scoreMultiplier++;
                    }

                    break;
                }
            }

            camera.target = Vector2(playerPos.x, std::min(playerPos.y, windowHeight / 1.8f));
            isMouseClicked = false;
        }

        // Draw
        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));

        // Draw within the camera
        BeginMode2D(camera);

        // Velocity Preview
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
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
            shape.draw();
        }

        // Circle is player, Rectangle is ground.
        DrawCircleV(playerPos, playerRadius, Color(52, 156, 243, 255));
        DrawRectangleV(Vector2(-5000, windowHeight - 80.0f), Vector2(10000, 160), Color(33, 37, 43, 255));

        EndMode2D();

        drawTextCentered(TextFormat("%d", score), 960, 6, 64, RAYWHITE);
        DrawFPS(6, 6);
        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}

// This function centers text based on its size and input pos.
void drawTextCentered(const char* text, const int posX, const int posY, const int fontSize, const Color color) {
    const int textSize = MeasureText(text, fontSize);
    DrawText(text, posX - (textSize / 2), posY, fontSize, color);
}

// Simple Vector2 Multiply because it wasn't built in.
Vector2 Vector2MultiplyS(const Vector2 a, float b) {
    return Vector2(a.x * b, a.y * b);
}
