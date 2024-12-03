//
// Created by eclipsedmango on 22/11/24.
//

#include "MainMenu.h"

#include "raylib.h"
#include "../Util.h"

void mainMenu() {
    Color buttonColor;
    char *buttonLabel = "Play";

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

        if (GetMouseX() > colorSelectButtonsX - 200 && GetMouseX() < colorSelectButtonsX - 200 + 100
            && GetMouseY() > colorSelectButtonsY + 350 && GetMouseY() < colorSelectButtonsY + 350 + 100) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                playerColor = Color(252, 152, 3, 255);
            }
        } else if (GetMouseX() > colorSelectButtonsX - 50 && GetMouseX() < colorSelectButtonsX - 50 + 100
            && GetMouseY() > colorSelectButtonsY + 350 && GetMouseY() < colorSelectButtonsY + 350 + 100) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                playerColor = Color(52, 156, 243, 255);
            }
        } else if (GetMouseX() > colorSelectButtonsX + 100 && GetMouseX() < colorSelectButtonsX + 100 + 100
            && GetMouseY() > colorSelectButtonsY + 350 && GetMouseY() < colorSelectButtonsY + 350 + 100) {

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                playerColor = Color(127, 5, 235, 255);
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

        // Color Selectors
        DrawRectangle(windowWidth / 2.0 - 200, windowHeight / 2.0 + 350, 100, 100, Color(252, 152, 3, 255));
        DrawRectangle(windowWidth / 2.0 - 50, windowHeight / 2.0 + 350, 100, 100, Color(52, 156, 243, 255));
        DrawRectangle(windowWidth / 2.0 + 100, windowHeight / 2.0 + 350, 100, 100, Color(127, 5, 235, 255));

        EndDrawing();
    }
}

void checkRegion() {

}