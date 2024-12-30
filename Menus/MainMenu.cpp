//
// Created by eclipsedmango on 22/11/24.
//

#include "MainMenu.h"

#include "raylib.h"
#include "../Util.h"
#include "../Buttons/Button.h"

void mainMenu() {
    const Texture2D plusTexture = LoadTexture("Plus.png");
    std::string playButtonLabel = "Play";
    float playButtonSizeX = 155;

    if (hasDied) {
        playButtonLabel = "Play Again";
        playButtonSizeX = 350;
    }

    std::printf("test\n");

    auto *playButton = new Button(Vector2(windowWidth / 2.0f, windowHeight / 2.0f),
        Vector2(playButtonSizeX, 72), 64, Color(40, 44, 52, 255), WHITE, playButtonLabel);

    auto *colorButton1 = new Button(Vector2(windowWidth / 2.0 - 150, windowHeight / 2.0 + 400),
        Vector2(100, 100), 0, Color(252, 152, 3, 255), WHITE, "");

    auto *colorButton2 = new Button(Vector2(windowWidth / 2.0, windowHeight / 2.0 + 400),
        Vector2(100, 100), 0, Color(52, 156, 243, 255), WHITE, "");

    auto *colorButton3 = new Button(Vector2(windowWidth / 2.0 + 150, windowHeight / 2.0 + 400),
        Vector2(100, 100), 0, Color(127, 5, 235, 255), WHITE, "");

    auto *scoreMultiplierButton = new Button(Vector2(windowWidth / 1.25 + 19.5, windowHeight / 2.0 + 169.5),
        Vector2(40, 40), 0, Color(40, 44, 52, 255), WHITE, "");

    while (!WindowShouldClose()) {
        if (!inMenu) {
            delete playButton;
            delete colorButton1;
            delete colorButton2;
            delete colorButton3;
            delete scoreMultiplierButton;
            return;
        }

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
        }

        if (playButton->checkButtonRegion()) {
            inMenu = false;
        }

        // Color Buttons
        if (colorButton1->checkButtonRegion()) {
            playerColor = Color(252, 152, 3, 255);
        }

        if (colorButton2->checkButtonRegion()) {
            playerColor = Color(52, 156, 243, 255);
        }

        if (colorButton3->checkButtonRegion()) {
            playerColor = Color(127, 5, 235, 255);
        }

        if (scoreMultiplierButton->checkButtonRegion()) {
            scoreMultiplierMax += 1;
        }

        if (hasDied) {
            drawTextCentered("You Died!", windowWidth / 2.0f, windowHeight / 2.0f - 250.0f, 72, Color(236, 55, 82, 255));
            drawTextCentered("Your Final Score is:", windowWidth / 2.0f, windowHeight / 2.0f - 125.0f, 40, GOLD);
            drawTextCentered(TextFormat("%d", score), windowWidth / 2.0f, windowHeight / 2.0 - 75.0f, 40, GOLD);
        }

        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));
        DrawFPS(6, 6);

        drawTextCentered("Ball Game The Game", windowWidth / 2.0f, windowHeight / 2.0 - 400, 84, Color(255, 255, 255, 255));

        playButton->draw();
        colorButton1->draw();
        colorButton2->draw();
        colorButton3->draw();
        scoreMultiplierButton->draw();

        drawTextCentered("Combo Size", windowWidth / 1.235, windowHeight / 2.0 + 50, 40, WHITE);
        drawTextCentered(TextFormat("%.0f", scoreMultiplierMax), windowWidth / 1.235, windowHeight / 2.0 + 100, 34, WHITE);
        DrawTextureEx(plusTexture, Vector2(windowWidth / 1.25, windowHeight / 2.0 + 150), 0, 0.075, WHITE);

        EndDrawing();
    }
}
