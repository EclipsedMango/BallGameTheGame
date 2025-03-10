//
// Created by eclipsedmango on 22/11/24.
//

#include "MainMenu.h"

#include "raylib.h"
#include "../Util.h"
#include "../Buttons/Button.h"
#include "../Buttons/TextureButton.h"

void mainMenu() {
    // Initialize Textures from resources file.
    const Texture2D titleTexture = LoadTexture("resources/Title.png");

    const Texture2D playTexture = LoadTexture("resources/Play.png");
    const Texture2D playHoverTexture = LoadTexture("resources/PlayHighlight.png");
    const Texture2D playPressTexture = LoadTexture("resources/PlayPress.png");

    const Texture2D upgradesTexture = LoadTexture("resources/Upgrades.png");
    const Texture2D upgradesHoverTexture = LoadTexture("resources/UpgradesHighlight.png");
    const Texture2D upgradesPressTexture = LoadTexture("resources/UpgradesPress.png");

    const Texture2D optionsTexture = LoadTexture("resources/Options.png");
    const Texture2D optionsHoverTexture = LoadTexture("resources/OptionsHighlight.png");
    const Texture2D optionsPressTexture = LoadTexture("resources/OptionsPress.png");

    const Texture2D exitTexture = LoadTexture("resources/Exit.png");
    const Texture2D exitHoverTexture = LoadTexture("resources/ExitHighlight.png");
    const Texture2D exitPressTexture = LoadTexture("resources/ExitPress.png");

    std::printf("MainMenuTest\n");

    auto *playButton = new TextureButton(Vector2(0, -150), Vector2(242, 92), playTexture, playHoverTexture, playPressTexture, false);
    auto *upgradeButton = new TextureButton(Vector2(0, -0), Vector2(353, 92), upgradesTexture, upgradesHoverTexture, upgradesPressTexture, false);
    auto *optionsButton = new TextureButton(Vector2(0, 150), Vector2(320, 92), optionsTexture, optionsHoverTexture, optionsPressTexture, true);
    auto *exitButton = new TextureButton(Vector2(0, 300), Vector2(242, 92), exitTexture, exitHoverTexture, exitPressTexture, false);

    RenderTexture2D shaderTarget = LoadRenderTexture(windowWidth, windowHeight);
    const Shader bloomShader = LoadShader(nullptr, TextFormat("resources/shaders/glsl%i/bloom.fsh", GLSL_VERSION));

    // Shapes
    auto shapes = std::vector<Shape*>();

    float shapeSpawnTimer = 0.0f;
    float shapeJumpTimer = 0.0f;

    float physicsTimer = 0.0f;

    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();
        physicsTimer += delta;
        shapeSpawnTimer = std::max(shapeSpawnTimer - delta / 2.0, 0.0);
        shapeJumpTimer = std::max(shapeJumpTimer - delta / 2.0, 0.0);

        if (!inMenu) {
            delete playButton;
            delete upgradeButton;
            delete optionsButton;
            delete exitButton;

            return;
        }

        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();
        }

        if (shapeSpawnTimer == 0 && shapes.size() < 30) {
            spawnShapeRandom(&shapes, 0, Vector2(50, -50), Vector2(windowWidth - 50, -40));
            if (shapes.size() % 4 == 2) {
                spawnShapeRandom(&shapes, 1, Vector2(50, -50), Vector2(windowWidth - 50, -40));
            } else if (shapes.size() % 8 == 4) {
                spawnShapeRandom(&shapes, 2, Vector2(50, -50), Vector2(windowWidth - 50, -40));
            }

            shapeSpawnTimer = 0.5;
        }

        if (shapeJumpTimer == 0) {
            for (int i = 0; i < shapes.size(); i++) {
                Shape* shape = shapes[i];
                if (shape->pos.y > windowHeight / 2.0 + 250) {
                    shape->velocity.y -= GetRandomValue(2000, 3000);
                    shape->velocity.x += GetRandomValue(-1000, 1000);
                }
            }
            shapeJumpTimer = 1.0;
        }

        while (physicsTimer > physicsDelta) {
            physicsTimer -= physicsDelta;

            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];
                shape->physicsUpdate();
            }

            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];

                shape->velocity.y += 2048.0 * physicsDelta;

                for (int j = i + 1; j < shapes.size(); j++) {
                    Shape* shape2 = shapes[j];
                    if (shape == shape2) continue;

                    float disX = shape2->pos.x - shape->pos.x;
                    float disY = shape2->pos.y - shape->pos.y;

                    float distance = sqrtf(disX * disX + disY * disY);

                    if (distance > shape->radius + shape2->radius) continue;

                    shape->pos = Vector2Subtract(shape->pos, Vector2(disX / 16.0, disY / 16.0));
                    shape2->pos = Vector2Subtract(shape2->pos, Vector2(-disX / 16.0, -disY / 16.0));

                    shape->velocity = Vector2MultiplyS(Vector2Reflect(shape->velocity, Vector2Normalize(Vector2(disX, disY))), 0.75);
                    shape2->velocity = Vector2MultiplyS(Vector2Reflect(shape2->velocity, Vector2Normalize(Vector2(disX, disY))), 0.75);
                }

                if (shape->velocity.x == 0) {
                    shape->velocity.x = GetRandomValue(-50, 50);
                }

                if (shape->pos.y > windowHeight - shape->radius) {
                    shape->pos.y = windowHeight - shape->radius;
                    shape->velocity.y = -shape->velocity.y * 0.8f;
                }
                else if (shape->pos.x > windowWidth - shape->radius) {
                    shape->pos.x = windowWidth - shape->radius;
                    shape->velocity.x = -shape->velocity.x * 0.8f;
                }
                else if (shape->pos.x < 0 + shape->radius) {
                    shape->pos.x = 0 + shape->radius;
                    shape->velocity.x = -shape->velocity.x * 0.8f;
                }
            }
        }

        std::erase_if(shapes,
            [](const Shape* o) { return o->killYourSelf; });

        if (playButton->checkButtonRegion()) {
            inMenu = false;
            inUpgradeMenu = false;
        }

        if (upgradeButton->checkButtonRegion()) {
            inMenu = false;
            inUpgradeMenu = true;
        }

        if (optionsButton->checkButtonRegion()) {
            printf("open options menu\n");
        }

        if (exitButton->checkButtonRegion()) {
            shouldGameClose = true;
            return;
        }

        if (hasDied) {
            drawTextCentered("You Died!", windowWidth / 2.0 - 500, windowHeight / 2.0 - 280, 72, Color(236, 55, 82, 255));
            drawTextCentered("Your Final Score is:", windowWidth / 2.0 - 500, windowHeight / 2.0 - 150, 40, GOLD);
            drawTextCentered(TextFormat("%d", score), windowWidth / 2.0 - 500, windowHeight / 2.0 - 100, 40, GOLD);
        }

        BeginTextureMode(shaderTarget);
        runPostProcessing(shaderTarget.texture, bloomShader);
        ClearBackground(Color(40, 44, 52, 255));
        DrawFPS(6, 6);

        // Draw Shapes
        for (Shape* shape : shapes) {
            shape->draw();
        }

        DrawTextureEx(titleTexture, Vector2(windowWidth / 2.0 - 547, windowHeight / 2.0 - 471), 0, 1.0, WHITE);

        playButton->draw();
        upgradeButton->draw();
        optionsButton->draw();
        exitButton->draw();

        EndTextureMode();

        BeginDrawing();
        runPostProcessing(shaderTarget.texture, bloomShader);
        EndDrawing();
    }
}
