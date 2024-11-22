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
        drawTextCentered(buttonLabel, windowWidth / 2.0f, windowHeight / 2.0f, 64, buttonColor);

        EndDrawing();
    }
}

void checkRegion() {

}