#include <iostream>

#include "raylib.h"
#include "raymath.h"

void drawTextCentered(const char* text, int posX, int posY, int fontSize, Color color);
Vector2 Vector2MultiplyS(Vector2 a, float b);

int main() {
    const int monitor = GetCurrentMonitor();

    InitWindow(1920, 1080, "Ball Game The Game");
    SetWindowMonitor(monitor);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Player Attributes
    constexpr auto playerStartingPos = Vector2(960, 540);
    Vector2 playerPos = playerStartingPos;
    auto velocity = Vector2(0, 0);

    bool isMouseClicked = false;

    float physicsTimer = 0.0f;
    constexpr float physicsDelta = 1.0f / 240.0f;

    // Main game loop
    // Detect window close button or ESC key
    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();
        physicsTimer += delta;

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            isMouseClicked = true;
        }

        // Physics Process
        if (physicsTimer > physicsDelta) {
            physicsTimer -= physicsDelta;

            constexpr float gravity = 2048.0f;
            constexpr float playerSpeed = 512.0f;

            // Update
            velocity.y += gravity * physicsDelta;
            playerPos = Vector2Add(playerPos, Vector2MultiplyS(velocity, physicsDelta));

            // Main Player Movement
            if (isMouseClicked) {
                velocity = Vector2((GetMousePosition().x - playerPos.x) * 2.0f, (GetMousePosition().y - playerPos.y) * 2.0f);
            }

            // Floor Collision
            if (playerPos.y > 1000 - 15) {
                playerPos.y = 1000 - 15;
                velocity.y = -velocity.y * 0.75f;
            }

            isMouseClicked = false;
        }

        // Draw
        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));

        // Circle is player, Cube is ground.
        DrawCircleV(playerPos, 15, Color(52, 156, 243, 255));
        DrawCube(Vector3(960, 1080, 0), 1920, 160, 0, Color(33, 37, 43, 255));

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
