//
// Created by eclipsedmango on 22/11/24.
//

#include "MainMenu.h"

#include "raylib.h"
#include "../Util.h"

void mainMenu() {
    const float button1X = (windowWidth - 150) / 2.0f;
    const float button1Y = (windowHeight - 2.0f) / 2.0f;
    Color buttonColor;

    while (!WindowShouldClose()) {
        if (GetMouseX() > button1X && GetMouseX() < (button1X + 150)
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
            drawTextCentered("You Died!", windowWidth / 2.0f, windowHeight / 2.0 - 200, 72, Color(236, 55, 82, 255));
        }

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
        }

        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));

        drawTextCentered("Play", windowWidth / 2.0f, windowHeight / 2.0f, 64, buttonColor);

        EndDrawing();
    }
}

void checkRegion() {

}