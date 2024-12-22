//
// Created by eclipsedmango on 22/11/24.
//

#include "MainMenu.h"

#include <cstring>

#include "raylib.h"
#include "../Util.h"

void mainMenu() {
    Color buttonColor;
    char *buttonLabel = "Play";
    const Texture2D plusTexture = LoadTexture("Plus.png");

    auto colorButton1Color = Color(252, 152, 3, 255);
    auto colorButton2Color = Color(52, 156, 243, 255);
    auto colorButton3Color = Color(127, 5, 235, 255);

    while (!WindowShouldClose()) {
        const float button1X = (windowWidth - MeasureText(buttonLabel, 64)) / 2.0f;
        const float button1Y = (windowHeight - 2.0f) / 2.0f;

        const float colorSelectButtonsX = windowWidth / 2.0;
        const float colorSelectButtonsY = windowHeight / 2.0;

        // Play Button (Button1)
        if (GetMouseX() > button1X && GetMouseX() < (button1X + MeasureText(buttonLabel, 64))
            && GetMouseY() > button1Y && GetMouseY() < button1Y + 72) {
            buttonColor = Color(168, 168, 168, 255);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                buttonColor = Color(110, 110, 110, 255);
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                inMenu = false;
            }
        } else {
            buttonColor = Color(255, 255, 255, 255);
        }

        // Color Select Buttons
        if (GetMouseX() > colorSelectButtonsX - 200 && GetMouseX() < colorSelectButtonsX - 200 + 100
            && GetMouseY() > colorSelectButtonsY + 350 && GetMouseY() < colorSelectButtonsY + 350 + 100) {
            colorButton1Color = Color(250, 174, 60, 255);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                colorButton1Color = Color(219, 133, 2, 255);
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                playerColor = Color(252, 152, 3, 255);
            }
        } else if (GetMouseX() > colorSelectButtonsX - 50 && GetMouseX() < colorSelectButtonsX - 50 + 100
            && GetMouseY() > colorSelectButtonsY + 350 && GetMouseY() < colorSelectButtonsY + 350 + 100) {
            colorButton2Color = Color(91, 175, 245, 255);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                colorButton2Color = Color(7, 125, 224, 255);
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                playerColor = Color(52, 156, 243, 255);
            }
        } else if (GetMouseX() > colorSelectButtonsX + 100 && GetMouseX() < colorSelectButtonsX + 100 + 100
            && GetMouseY() > colorSelectButtonsY + 350 && GetMouseY() < colorSelectButtonsY + 350 + 100) {
            colorButton3Color = Color(151, 42, 247, 255);

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                colorButton3Color = Color(113, 2, 212, 255);
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                playerColor = Color(127, 5, 235, 255);
            }
        } else {
            colorButton1Color = Color(252, 152, 3, 255);
            colorButton2Color = Color(52, 156, 243, 255);
            colorButton3Color = Color(127, 5, 235, 255);
        }

        if (GetMouseX() > windowWidth / 1.25 && GetMouseX() < windowWidth / 1.25 + 40
            && GetMouseY() > windowHeight / 2.0 + 150 && GetMouseY() < windowHeight / 2.0 + 188) {

            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                scoreMultiplierMax += 1;
            }
        }

        if (!inMenu) {
            return;
        }

        if (hasDied) {
            drawTextCentered("You Died!", windowWidth / 2.0f, windowHeight / 2.0f - 250.0f, 72, Color(236, 55, 82, 255));
            drawTextCentered("Your Final Score is:", windowWidth / 2.0f, windowHeight / 2.0f - 125.0f, 40, GOLD);
            drawTextCentered(TextFormat("%d", score), windowWidth / 2.0f, windowHeight / 2.0 - 75.0f, 40, GOLD);
            buttonLabel = "Play Again";
        }

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
        }

        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));

        DrawFPS(6, 6);
        drawTextCentered("Ball Game The Game", windowWidth / 2.0f, windowHeight / 2.0 - 400, 84, Color(255, 255, 255, 255));

        // Buttons
        drawTextCentered(buttonLabel, windowWidth / 2.0f, windowHeight / 2.0f, 64, buttonColor);

        // Options Buttons
        //DrawRectangle(windowWidth / 1.25, windowHeight / 2.0 + 150, 50, 50, WHITE);
        drawTextCentered("Combo Size", windowWidth / 1.235, windowHeight / 2.0 + 50, 40, WHITE);
        drawTextCentered(TextFormat("%.0f", scoreMultiplierMax), windowWidth / 1.235, windowHeight / 2.0 + 100, 34, WHITE);
        DrawTextureEx(plusTexture, Vector2(windowWidth / 1.25, windowHeight / 2.0 + 150), 0, 0.075, WHITE);

        // Color Selectors
        DrawRectangle(windowWidth / 2.0 - 200, windowHeight / 2.0 + 350, 100, 100, colorButton1Color);
        DrawRectangle(windowWidth / 2.0 - 50, windowHeight / 2.0 + 350, 100, 100, colorButton2Color);
        DrawRectangle(windowWidth / 2.0 + 100, windowHeight / 2.0 + 350, 100, 100, colorButton3Color);

        EndDrawing();
    }
}

void checkRegion() {

}