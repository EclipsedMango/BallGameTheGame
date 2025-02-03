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
    const Texture2D plusTexture = LoadTexture("Plus.png");
    const Texture2D plusHoverTexture = LoadTexture("PlusHighlight.png");
    const Texture2D plusPressTexture = LoadTexture("PlusPress.png");

    const Texture2D backTexture = LoadTexture("Back.png");
    const Texture2D backHoverTexture = LoadTexture("BackHighlight.png");
    const Texture2D backPressTexture = LoadTexture("BackPress.png");

    const Font textFont = LoadFontEx("Fonts/JetBrainsMono-VariableFont_wght.ttf", 128, nullptr, 0);

    auto *plusButton = new TextureButton(Vector2(500, 150), Vector2(73, 74), plusTexture, plusHoverTexture, plusPressTexture);
    auto *backButton = new TextureButton(Vector2(-890, -450), Vector2(73, 74), backTexture, backHoverTexture, backPressTexture);

    auto *colorButton1 = new RegularButton(Vector2(-150, 400),
        Vector2(100, 100), 0, Color(67, 222, 108, 255), WHITE, "");
    auto *colorButton2 = new RegularButton(Vector2(0, 400),
        Vector2(100, 100), 0, Color(52, 156, 243, 255), WHITE, "");
    auto *colorButton3 = new RegularButton(Vector2(150, 400),
        Vector2(100, 100), 0, Color(194, 74, 237, 255), WHITE, "");

    while(!WindowShouldClose()) {
        if (!inUpgradeMenu) {
            delete plusButton;
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

        if (plusButton->checkButtonRegion() && money >= scoreMultiplierCost) {
            scoreMultiplierMax += 1;
            money -= scoreMultiplierCost;
            scoreMultiplierCost *= 2.0;
            scoreMultiplierCost = scoreMultiplierCost / 5 * 5;
        }

        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));
        DrawFPS(6, 6);

        plusButton->draw();
        backButton->draw();

        colorButton1->draw();
        colorButton2->draw();
        colorButton3->draw();

        drawTextCenteredFont(textFont, "Money", windowWidth / 2.0, windowHeight / 2.0 - 450, 84, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%d", money), windowWidth / 2.0, windowHeight / 2.0 - 375, 64, 0, WHITE);

        drawTextCenteredFont(textFont, "Combo Size", windowWidth / 2.0 + 500, windowHeight / 2.0 + 25, 40, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%.0f", scoreMultiplierMax), windowWidth / 2.0 + 500, windowHeight / 2.0 + 75, 34, 0, WHITE);
        drawTextCenteredFont(textFont, TextFormat("%d", scoreMultiplierCost), windowWidth / 2.0 + 500 , windowHeight / 2.0 + 225, 34, 0, WHITE);

        EndDrawing();
    }
}
