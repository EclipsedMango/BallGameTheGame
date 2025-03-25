//
// Created by eclipsedmango on 10/11/24.
//

#include "Game.h"

#include <cstdio>
#include <vector>

#include "raylib.h"
#include "raymath.h"
#include "../CollisionCheck.h"
#include "../Util.h"
#include "../Particles/Particle.h"

void runGame() {
    // Timers
    float physicsTimer = 0.0f;
    int physicsFrameCount = 0;

    float shapeSpawnTimer = 0.0f;
    constexpr float shapesDelta = 4.0f;

    float particleTimer = 0.0f;
    constexpr float particleDelta = 0.01f;

    float deathTimer = 0.75f;
    float screenShakeTimer = 0.1f;

    auto vecDir = Vector2(0, 0);

    bool isMouseClicked = false;
    hasDied = false;

    // Player Related Info
    displayScore = 0;
    scoreMultiplier = 1.0;
    score = 0;

    // Shapes
    auto shapes = std::vector<Shape*>();

    // Particles
    auto particles = std::vector<Particle*>();

    // reset player values.
    player->playerPos = Vector2(0, 500);
    player->velocity = Vector2(0, 0);

    // Camera Attributes
    Camera2D camera = {0};
    camera.target = Vector2(player->playerPos.x, player->playerPos.y);
    camera.offset = Vector2(windowWidth / 2.0f, windowHeight / 2.0f);
    camera.rotation = 0.0f;
    camera.zoom = 1.25f * (windowHeight / 1080.0f);

    player->shader = LoadShader(nullptr, TextFormat("resources/shaders/glsl%i/player.fsh", GLSL_VERSION));
    RenderTexture2D shaderTarget = LoadRenderTexture(windowWidth, windowHeight);
    const Shader bloomShader = LoadShader(nullptr, TextFormat("resources/shaders/glsl%i/bloom.fsh", GLSL_VERSION));

    for (int i = 0; i < 75; i++) {
        spawnShapeRandom(&shapes, RED_CIRCLE, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980), true);

        if (i < 15) {
            spawnShapeRandom(&shapes, GREEN_PENTAGON, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980), true);
        }

        if (i < 2) {
            spawnShapeRandom(&shapes, GOLD_CIRCLE, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980), true);
        }

        if (i < 12) {
            spawnShapeRandom(&shapes, BLACK_HOLE, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980), true);
        }
    }

    // This is needed to prevent the player immediately clicking when entering the game.
    BeginDrawing();
    EndDrawing();

    SetExitKey(KEY_NULL);

    // Main game loop
    while (!WindowShouldClose()) {
        if (isPaused) {
            timeMultiplier = 0.0f;
        }

        const float delta = GetFrameTime();
        physicsTimer += delta * timeMultiplier;
        shapeSpawnTimer += delta * timeMultiplier;
        particleTimer += delta * timeMultiplier;
        scoreTimer = std::max(scoreTimer - delta * timeMultiplier, 0.0f);
        inputTimeLeft = std::max(inputTimeLeft - delta / timeMultiplier / inputTimeLeftUpgrade, 0.0f);

        // Update window size as well as adjust camera to new size.
        if (IsWindowResized()) {
            windowHeight = GetScreenHeight();
            windowWidth = GetScreenWidth();

            camera.offset = Vector2(windowWidth / 2.0f, windowHeight / 2.0f);
            camera.zoom = 1.25f * (windowHeight / 1080.0f);
        }

        if (IsKeyPressed(KEY_ESCAPE)) {
            isPaused = !isPaused;
        }

        // Slows time when mouse button left is held otherwise continue as normal.
        if (inputTimeLeft > 0.0f) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                timeMultiplier = timeMultiplierUpgrade;
            } else {
                timeMultiplier = 1.0f;
            }

            if (!hasDied && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                isMouseClicked = true;

                inputTimeLeft = std::max(inputTimeLeft - inputTimeLeftStrength, 0.0f);

                for (int i = 0; i < 5; ++i) {
                    spawnPlayerParticles(&particles, player->playerPos, player->velocity, 0);
                }
            }
        } else if (inputTimeLeft == 0) {
            timeMultiplier = 1.0f;
        }

        if (scoreTimer == 0.0f) {
            scoreMultiplier = 1.0f;
        }

        // Particle Process
        while (particleTimer > particleDelta) {
            particleTimer -= particleDelta;

            for (int i = 0; i < particles.size(); ++i) {
                Particle* particle = particles[i];

                // Check if particle is alive before deleting.
                if (!particles.empty() && particle->lifespan <= 0) {
                    particles.erase(particles.begin());
                }
            }
        }

        if (IsKeyPressed(KEY_R)) {
            inMenu = true;
            return;
        }

        if (IsKeyDown(KEY_C)) {
            timeMultiplier += 1.0;
        }

        // Screen Shake
        if (shouldScreenShake) {
            screenShakeTimer -= delta;
            if (screenShakeTimer >= 0) {
                camera.target = Vector2(camera.target.x + getRandomFloatRange(-1.75, 1.75),
                                        camera.target.y + getRandomFloatRange(-1.75, 1.75));
            } else {
                screenShakeTimer = 0.1f;
                shouldScreenShake = false;
            }
        }

        // Death Process
        if (hasDied) {
            deathTimer -= delta;
            if (deathTimer > 0.5) {
                camera.target = Vector2(camera.target.x + GetRandomValue(-2, 2), camera.target.y + GetRandomValue(-2, 2));
            }

            if (deathTimer <= 0.0f) {
                money += score;
                inMenu = true;
                return;
            }
        }

        // Shape Process
        while (shapeSpawnTimer > shapesDelta && shapes.size() < 1500) {
            shapeSpawnTimer -= shapesDelta;

            // Spawn shape in varying chances.
            if (GetRandomValue(0, 12) == 0) {
                spawnShapeRandom(&shapes, RED_CIRCLE, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980));
            }

            if (GetRandomValue(0, 24) == 0) {
                spawnShapeRandom(&shapes, GREEN_PENTAGON, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980));
            }

            if (GetRandomValue(0, 128) == 0) {
                spawnShapeRandom(&shapes, GOLD_CIRCLE, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980));
            }
        }

        // Physics Process
        while (physicsTimer > physicsDelta) {
            physicsTimer -= physicsDelta;
            physicsFrameCount++;

            if (scoreSize > 64) {
                scoreSize -= physicsDelta * 5;
            }

            player->physicsUpdate();

            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];

                Vector2 screenPos = GetWorldToScreen2D(shape->pos, camera);

                if (screenPos.x > 0 && screenPos.x < windowWidth && screenPos.y > 0 && screenPos.y < windowHeight) {
                    if (shape->type == 3 && physicsFrameCount % 16 == 0) {
                        spawnShapeParticles(&particles, shape->pos, Vector2(0, 0), BLACK_HOLE);
                    }
                }

                shape->physicsUpdate();
                tryDeleteShape(&shapes, shape, i);
            }

            for (Particle* particle: particles) {
                particle->physicsUpdate();
            }

            std::erase_if(shapes,
                [](const Shape* o) { return o->killYourSelf; });

            // Set velocity based on the distance the cursor is to the player and multiply by playerSpeed.
            if (isMouseClicked) {
                player->velocity = Vector2MultiplyS(Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), player->playerPos), player->speed);
            }

            // Calculates the collision then applies rewards.
            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];
                CollisionCheck().checkCollision(shapes, particles, player, vecDir, i, shape);
            }

            // Camera movement based on playerPos and playerSpeed while keeping it clamp within game map.
            camera.target = Vector2Lerp(camera.target,
                Vector2(
                    Clamp(player->playerPos.x, -3030.0f + (windowWidth / camera.zoom) / 2.0f, 3030.0f - (windowWidth / camera.zoom) / 2.0f),
                    std::min(std::max(player->playerPos.y, -1115.0f), 1080 / 1.8f)),
                    10.0f * physicsDelta);

            isMouseClicked = false;
        }

        // Draw
        BeginTextureMode(shaderTarget);
        ClearBackground(Color(40, 44, 52, 255));

        // Draw within the camera
        BeginMode2D(camera);

        createVelocityPreview(shapes, vecDir, camera);

        // Draw Particles
        for (Particle* particle: particles) {
            particle->draw();
        }

        // Draw Shapes
        for (Shape* shape: shapes) {
            shape->draw();
        }

        player->draw();

        // Floor
        DrawRectangleV(Vector2(-3000, 1080 - 80.0f), Vector2(7500, 160), Color(33, 37, 43, 255));
        // Left Wall
        DrawRectangleV(Vector2(-3000 - 160, -2500), Vector2(160, 5000), Color(33, 37, 43, 255));
        // Right Wall
        DrawRectangleV(Vector2(3000, -2500), Vector2(160, 5000), Color(33, 37, 43, 255));
        // Ceiling
        DrawRectangleV(Vector2(-3000, -1670), Vector2(7500, 160), Color(33, 37, 43, 255));

        EndMode2D();
        EndTextureMode();

        BeginDrawing();
        runPostProcessing(shaderTarget.texture, bloomShader);

        drawTextCentered(TextFormat("%d", score), windowWidth / 2.0f, 24, scoreSize, RAYWHITE);
        drawProgressBar(windowWidth / 2.0f, 128, 30, 600, WHITE, GRAY, inputTimeLeft);

        // Various counters for testing.
        drawTextCentered(TextFormat("%d", shapes.size()), 24, 32, 20, LIME);
        drawTextCentered(TextFormat("%d", particles.size()), 24, 60, 20, LIME);
        drawTextCentered(TextFormat("%.2f", deathTimer), 24, 88, 20, LIME);
        drawTextCentered(TextFormat("%.2f", scoreTimer), 24, 116, 20, LIME);
        DrawFPS(6, 6);

        EndDrawing();
    }
}

void createVelocityPreview(const std::vector<Shape*> &shapes, Vector2 vecDir, const Camera2D &camera) {
    // Velocity Preview
    if (!hasDied && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && inputTimeLeft > 0.0f) {
        Vector2 vel = Vector2MultiplyS(Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), camera), player->playerPos), player->speed);
        Vector2 pos = player->playerPos;

        constexpr int lineCount = 100;

        for (int i = 0; i < lineCount; ++i) {
            for (int i = 0; i < shapes.size(); ++i) {
                Shape* shape = shapes[i];
                float distance = Vector2Distance(pos, shape->pos);
                const float maxDist = 450;

                if (distance > maxDist) {
                    continue;
                }

                if (shape->type == 3) {
                    float strength = pow((maxDist - distance) / maxDist, 10.0);

                    vecDir = Vector2MultiplyS(Vector2Normalize(Vector2Subtract(pos, shape->pos)), strength * -850);
                    vel = Vector2Add(vel, vecDir);
                }
            }
            vel.y += player->gravity * physicsDelta;
            Vector2 newPos = Vector2Add(pos, Vector2MultiplyS(vel, physicsDelta));
            DrawLineEx(pos, newPos, 12, Color(240, 240, 240, (1.0f - static_cast<float>(i) / static_cast<float>(lineCount)) * 255.0f));
            pos = newPos;
        }
    }
}