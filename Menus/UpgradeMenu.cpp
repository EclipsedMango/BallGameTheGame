//
// Created by eclipsedmango on 3/01/25.
//

#include "UpgradeMenu.h"

#include "raylib.h"
#include "../Util.h"
#include "../Buttons/Button.h"
#include "../Buttons/RegularButton.h"
#include "../Buttons/TextureButton.h"

void upgradeMenu() {
    const Texture2D plusTexture = LoadTexture("resources/Plus.png");
    const Texture2D plusHoverTexture = LoadTexture("resources/PlusHighlight.png");
    const Texture2D plusPressTexture = LoadTexture("resources/PlusPress.png");

    const Texture2D backTexture = LoadTexture("resources/Back.png");
    const Texture2D backHoverTexture = LoadTexture("resources/BackHighlight.png");
    const Texture2D backPressTexture = LoadTexture("resources/BackPress.png");

    const Font textFont = LoadFontEx("resources/Fonts/JetBrainsMono-VariableFont_wght.ttf", 128, nullptr, 0);

    auto *scoreMultiplierButton = new TextureButton(Vector2(0, 150), Vector2(73, 74), plusTexture, plusHoverTexture, plusPressTexture, false);
    auto *timeMultiplierButton = new TextureButton(Vector2(-200, 150), Vector2(73, 74), plusTexture, plusHoverTexture, plusPressTexture, false);
    auto *inputTimeLeftButton = new TextureButton(Vector2(200, 150), Vector2(73, 74), plusTexture, plusHoverTexture, plusPressTexture, false);
    auto *destroyPentagonButton = new TextureButton(Vector2(-200, -120), Vector2(73, 74), plusTexture, plusHoverTexture, plusPressTexture, true);
    auto *backButton = new TextureButton(Vector2(-890, -450), Vector2(73, 74), backTexture, backHoverTexture, backPressTexture, false);

    auto *colorButton1 = new RegularButton(Vector2(-150, 400),
        Vector2(100, 100), 0, Color(67, 222, 108, 255), WHITE, "", true);
    auto *colorButton2 = new RegularButton(Vector2(0, 400),
        Vector2(100, 100), 0, Color(52, 156, 243, 255), WHITE, "", true);
    auto *colorButton3 = new RegularButton(Vector2(150, 400),
        Vector2(100, 100), 0, Color(194, 74, 237, 255), WHITE, "", true);

    RenderTexture2D shaderTarget = LoadRenderTexture(windowWidth, windowHeight);
    const Shader bloomShader = LoadShader(nullptr, TextFormat("resources/shaders/glsl%i/bloom.fsh", GLSL_VERSION));

    if (compareColors(playerColor, Color(67, 222, 108, 255))) {
        colorButton1->toggled = true;

        colorButton1->color = colorButton1->colorPress;
        colorButton1->scale = 0.98;
    } else if (compareColors(playerColor, Color(52, 156, 243, 255))) {
        colorButton2->toggled = true;

        colorButton2->color = colorButton2->colorPress;
        colorButton2->scale = 0.98;
    } else if (compareColors(playerColor, Color(194, 74, 237, 255))) {
        colorButton3->toggled = true;

        colorButton3->color = colorButton3->colorPress;
        colorButton3->scale = 0.98;
    }

    while(!WindowShouldClose()) {
        if (!inUpgradeMenu) {
            delete scoreMultiplierButton;
            delete timeMultiplierButton;
            delete inputTimeLeftButton;
            delete destroyPentagonButton;
            delete backButton;

            delete colorButton1;
            delete colorButton2;
            delete colorButton3;

            return;
        }

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
        }

        if (IsKeyPressed(KEY_R)) {
            inMenu = true;
            return;
        }

        if (backButton->checkButtonRegion()) {
            inMenu = true;
            return;
        }

        // Color Buttons
        if (colorButton1->checkButtonRegion()) {
            colorButton2->toggled = false;
            colorButton3->toggled = false;

            playerColor = Color(67, 222, 108, 255);
            playerColorOutline = Color(49, 120, 54, 255);
        }

        if (colorButton2->checkButtonRegion()) {
            colorButton1->toggled = false;
            colorButton3->toggled = false;

            playerColor = Color(52, 156, 243, 255);
            playerColorOutline = Color(31, 104, 150, 255);
        }

        if (colorButton3->checkButtonRegion()) {
            colorButton1->toggled = false;
            colorButton2->toggled = false;

            playerColor = Color(194, 74, 237, 255);
            playerColorOutline = Color(94, 50, 125, 255);
        }

        if (scoreMultiplierButton->checkButtonRegion() && money >= scoreMultiplierCost) {
            scoreMultiplierMax += 1;
            money -= scoreMultiplierCost;
            scoreMultiplierCost *= 2.0;
            scoreMultiplierCost = scoreMultiplierCost / 5 * 5;
        }

        if (timeMultiplierButton->checkButtonRegion() && money >= timeMultiplierCost && timeMultiplierUpgrade > 0.3) {
            timeMultiplierUpgrade -= 0.05;
            money -= timeMultiplierCost;
            timeMultiplierCost *= 2.0;
            timeMultiplierCost = timeMultiplierCost / 5 * 5;
        }

        if (inputTimeLeftButton->checkButtonRegion() && money >= inputTimeLeftCost && inputTimeLeftUpgrade < 24.0) {
            inputTimeLeftStrength -= 0.05;
            inputTimeLeftUpgrade += 1.0;
            money -= inputTimeLeftCost;
            inputTimeLeftCost *= 2.0;
            inputTimeLeftCost = inputTimeLeftCost / 5 * 5;
        }

        if (destroyPentagonButton->checkButtonRegion() && money >= destroyPentagonCost) {
            canDestroyPentagon = !canDestroyPentagon;
            money -= destroyPentagonCost;
        }

        BeginTextureMode(shaderTarget);
        ClearBackground(Color(40, 44, 52, 255));
        DrawFPS(6, 6);

        scoreMultiplierButton->draw();
        timeMultiplierButton->draw();
        inputTimeLeftButton->draw();
        destroyPentagonButton->draw();

        backButton->draw();

        colorButton1->draw();
        colorButton2->draw();
        colorButton3->draw();

        drawTextCenteredFont(textFont, "Money", windowWidth / 2.0, windowHeight / 2.0 - 450, 84, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%d", money), windowWidth / 2.0, windowHeight / 2.0 - 375, 64, 0, WHITE);

        drawTextCenteredFont(textFont, "Combo Size", windowWidth / 2.0, windowHeight / 2.0 + 25, 40, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%.0f", scoreMultiplierMax), windowWidth / 2.0, windowHeight / 2.0 + 75, 34, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%d", scoreMultiplierCost), windowWidth / 2.0, windowHeight / 2.0 + 225, 34, 0, WHITE);

        drawTextCenteredFont(textFont, "Time Slow", windowWidth / 2.0 - 200, windowHeight / 2.0 + 25, 40, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%.2f", timeMultiplierUpgrade), windowWidth / 2.0 - 200, windowHeight / 2.0 + 75, 34, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%d", timeMultiplierCost), windowWidth / 2.0 - 200, windowHeight / 2.0 + 225, 34, 0, WHITE);

        drawTextCenteredFont(textFont, "Time Left", windowWidth / 2.0 + 200, windowHeight / 2.0 + 25, 40, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%.1f", inputTimeLeftUpgrade), windowWidth / 2.0 + 200, windowHeight / 2.0 + 75, 34, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%.2f", inputTimeLeftStrength), windowWidth / 2.0 + 200, windowHeight / 2.0 + 50, 34, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%d", inputTimeLeftCost), windowWidth / 2.0 + 200, windowHeight / 2.0 + 225, 34, 0, WHITE);

        drawTextCenteredFont(textFont, "Extra Damage", windowWidth / 2.0 - 200, windowHeight / 2.0 - 245, 40, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%i", destroyPentagonCost), windowWidth / 2.0 - 200, windowHeight / 2.0 - 45, 34, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%i", canDestroyPentagon), windowWidth / 2.0 - 200, windowHeight / 2.0 - 195, 34, 0, WHITE);

        EndTextureMode();

        BeginDrawing();
        runPostProcessing(shaderTarget.texture, bloomShader);
        EndDrawing();
    }
}
