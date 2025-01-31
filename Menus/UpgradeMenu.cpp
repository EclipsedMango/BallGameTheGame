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

    const Texture2D plusTexture = LoadTexture("PlusSmaller.png");

    const Texture2D backTexture = LoadTexture("Back.png");
    const Texture2D backHoverTexture = LoadTexture("BackHighlight.png");
    const Texture2D backPressTexture = LoadTexture("BackPress.png");

    const Font textFont = LoadFontEx("Fonts/JetBrainsMono-VariableFont_wght.ttf", 128, nullptr, 0);

    auto *backButton = new TextureButton(Vector2(-890, -450), Vector2(73, 74), backTexture, backHoverTexture, backPressTexture);

    auto *colorButton1 = new RegularButton(Vector2(-150, 400),
        Vector2(100, 100), 0, Color(67, 222, 108, 255), WHITE, "");
    auto *colorButton2 = new RegularButton(Vector2(0, 400),
        Vector2(100, 100), 0, Color(52, 156, 243, 255), WHITE, "");
    auto *colorButton3 = new RegularButton(Vector2(150, 400),
        Vector2(100, 100), 0, Color(194, 74, 237, 255), WHITE, "");

    auto *scoreMultiplierButton = new RegularButton(Vector2(500, 170),
        Vector2(40, 40), 0, Color(40, 44, 52, 255), WHITE, "");

    while(!WindowShouldClose()) {
        if (!inUpgradeMenu) {
            delete backButton;

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

        if (scoreMultiplierButton->checkButtonRegion() && money >= scoreMultiplierCost) {
            scoreMultiplierMax += 1;
            money -= scoreMultiplierCost;
            scoreMultiplierCost *= 2.0;
            scoreMultiplierCost = scoreMultiplierCost / 5 * 5;
        }

        BeginDrawing();
        ClearBackground(Color(40, 44, 52, 255));
        DrawFPS(6, 6);

        backButton->draw();

        colorButton1->draw();
        colorButton2->draw();
        colorButton3->draw();

        scoreMultiplierButton->draw();

        DrawTextEx(textFont, "Hallo, this a test to see changed fonts", Vector2(windowWidth / 2.0 - 500, windowHeight / 2.0 - 250), 64, 0, WHITE);

        drawTextCentered("Money:", windowWidth / 2.0, windowHeight / 2.0 - 500, 65, WHITE);
        drawTextCentered(TextFormat("%d", money), windowWidth / 2.0, windowHeight / 2.0 - 400, 55, WHITE);

        drawTextCentered("Combo Size", windowWidth / 2.0 + 500, windowHeight / 2.0 + 50, 40, WHITE);
        drawTextCentered(TextFormat("%d", scoreMultiplierCost), windowWidth / 2.0 + 500, windowHeight / 2.0 + 200, 34, WHITE);
        drawTextCentered(TextFormat("%.0f", scoreMultiplierMax), windowWidth / 2.0 + 500, windowHeight / 2.0 + 100, 34, WHITE);
        DrawTextureEx(plusTexture, Vector2(windowWidth / 2.0 + 480, windowHeight / 2.0 + 150), 0, 0.1, WHITE);

        EndDrawing();
    }
}
