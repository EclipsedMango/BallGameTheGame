//
// Created by eclipsedmango on 22/11/24.
//

#include "MainMenu.h"

#include "raylib.h"
#include "../Util.h"
#include "../Buttons/Button.h"
#include "../Buttons/RegularButton.h"
#include "../Buttons/TextureButton.h"

void mainMenu() {
    // Initialize Textures from resource file.
    const Texture2D plusTexture = LoadTexture("PlusSmaller.png");
    const Texture2D titleTexture = LoadTexture("Title.png");

    const Texture2D playTexture = LoadTexture("Play.png");
    const Texture2D playHoverTexture = LoadTexture("PlayHighlight.png");
    const Texture2D playPressTexture = LoadTexture("PlayPress.png");

    const Texture2D upgradesTexture = LoadTexture("Upgrades.png");
    const Texture2D upgradesHoverTexture = LoadTexture("UpgradesHighlight.png");
    const Texture2D upgradesPressTexture = LoadTexture("UpgradesPress.png");

    const Texture2D optionsTexture = LoadTexture("Options.png");
    const Texture2D optionsHoverTexture = LoadTexture("OptionsHighlight.png");
    const Texture2D optionsPressTexture = LoadTexture("OptionsPress.png");

    const Texture2D exitTexture = LoadTexture("Exit.png");
    const Texture2D exitHoverTexture = LoadTexture("ExitHighlight.png");
    const Texture2D exitPressTexture = LoadTexture("ExitPress.png");

    std::printf("test\n");

    auto *playButton = new TextureButton(Vector2(0, -150), Vector2(242, 92), playTexture, playHoverTexture, playPressTexture);
    auto *upgradeButton = new TextureButton(Vector2(0, -0), Vector2(353, 92), upgradesTexture, upgradesHoverTexture, upgradesPressTexture);
    auto *optionsButton = new TextureButton(Vector2(0, 150), Vector2(320, 92), optionsTexture, optionsHoverTexture, optionsPressTexture);
    auto *exitButton = new TextureButton(Vector2(0, 300), Vector2(242, 92), exitTexture, exitHoverTexture, exitPressTexture);

    auto *colorButton1 = new RegularButton(Vector2(-150, 400),
        Vector2(100, 100), 0, Color(67, 222, 108, 255), WHITE, "");
    auto *colorButton2 = new RegularButton(Vector2(0, 400),
        Vector2(100, 100), 0, Color(52, 156, 243, 255), WHITE, "");
    auto *colorButton3 = new RegularButton(Vector2(150, 400),
        Vector2(100, 100), 0, Color(194, 74, 237, 255), WHITE, "");

    auto *scoreMultiplierButton = new RegularButton(Vector2(500, 170),
        Vector2(40, 40), 0, Color(40, 44, 52, 255), WHITE, "");

    while (!WindowShouldClose()) {
        if (!inMenu) {
            delete playButton;
            delete upgradeButton;
            delete optionsButton;
            delete exitButton;

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

        if (upgradeButton->checkButtonRegion()) {
            printf("open upgrade menu\n");
        }

        if (optionsButton->checkButtonRegion()) {
            printf("open options menu\n");
        }

        if (exitButton->checkButtonRegion()) {
            shouldGameClose = true;
            return;
        }

        // Color Buttons
        if (colorButton1->checkButtonRegion()) {
            playerColor = Color(67, 222, 108, 255);
            playerColorOutline = Color(49, 120, 54, 255);
        }

        if (colorButton2->checkButtonRegion()) {
            playerColor = Color(52, 156, 243, 255);
            playerColorOutline = Color(31, 104, 150, 255);
        }

        if (colorButton3->checkButtonRegion()) {
            playerColor = Color(194, 74, 237, 255);
            playerColorOutline = Color(94, 50, 125, 255);
        }

        if (scoreMultiplierButton->checkButtonRegion()) {
            scoreMultiplierMax += 1;
        }

        if (hasDied) {
            drawTextCentered("You Died!", windowWidth / 2.0, windowHeight / 2.0 - 280, 72, Color(236, 55, 82, 255));
            drawTextCentered("Your Final Score is:", windowWidth / 2.0, windowHeight / 2.0 - 150, 40, GOLD);
            drawTextCentered(TextFormat("%d", score), windowWidth / 2.0, windowHeight / 2.0 - 100, 40, GOLD);
        }

        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));
        DrawFPS(6, 6);

        DrawTextureEx(titleTexture, Vector2(windowWidth / 2.0 - 547, windowHeight / 2.0 - 471), 0, 1.0, WHITE);

        playButton->draw();
        upgradeButton->draw();
        optionsButton->draw();
        exitButton->draw();

        colorButton1->draw();
        colorButton2->draw();
        colorButton3->draw();
        scoreMultiplierButton->draw();

        drawTextCentered("Combo Size", windowWidth / 2.0 + 500, windowHeight / 2.0 + 50, 40, WHITE);
        drawTextCentered(TextFormat("%.0f", scoreMultiplierMax), windowWidth / 2.0 + 500, windowHeight / 2.0 + 100, 34, WHITE);
        DrawTextureEx(plusTexture, Vector2(windowWidth / 2.0 + 480, windowHeight / 2.0 + 150), 0, 0.1, WHITE);

        EndDrawing();
    }
}
