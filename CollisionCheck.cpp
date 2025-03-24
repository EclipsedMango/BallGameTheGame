
#include "CollisionCheck.h"

void CollisionCheck::checkCollision(std::vector<Shape*> &shapes, std::vector<Particle*> &particles, Player* player, Vector2 vecDir, int i, Shape* shape) {
    float distance = Vector2Distance(player->playerPos, shape->pos);
    const float maxDist = 450;

    if (distance > maxDist) {
        return;
    }

    if (shape->type == DISPLAY_SCORE || shape->destoryShape == true || hasDied) {
        return;
    }

    if (shape->type == 3) {
        float strength = pow((maxDist - distance) / maxDist, 10.0);

        vecDir = Vector2MultiplyS(Vector2Normalize(Vector2Subtract(player->playerPos, shape->pos)), strength * -850);
        player->velocity = Vector2Add(player->velocity, vecDir);
    }

    if (Vector2DistanceSqr(shape->pos, player->playerPos) < pow(shape->radius + player->hitBox, 2.0)) {
        collisionRewards(shapes, particles, shape, i);
    }
}

void CollisionCheck::collisionRewards(std::vector<Shape*> &shapes, std::vector<Particle*> &particles, Shape* shape, const int index) {
    if (hasDied) {
        return;
    }

    Shapes type;
    int particleAmount = 0;

    switch (shape->type) {
        case RED_CIRCLE:
            spawnShapeRandom(&shapes, RED_CIRCLE, Vector2(-3000 + 50, -1500), Vector2(3000 - 50, 980));

            type = RED_CIRCLE;
            particleAmount = 12;

            shape->destoryShape = true;
            break;
        case GREEN_PENTAGON:
            if (!canDestroyPentagon) {
                for (int i = 0; i < 16; ++i) {
                    spawnPlayerParticles(&particles, player->playerPos, player->velocity, 1);
                }
                hasDied = true;
                return;
            }

            type = GREEN_PENTAGON;
            particleAmount = 12;

            shape->destoryShape = true;
            break;
        case GOLD_CIRCLE:
            type = GOLD_CIRCLE;
            particleAmount = 8;

            shape->destoryShape = true;
            break;
        case BLACK_HOLE:
             for (int j = 0; j < 16; ++j) {
                 spawnPlayerParticles(&particles, player->playerPos, player->velocity, 1);
             }
            hasDied = true;
            return;
        default: break;
    }

    for (int j = 0; j < particleAmount; ++j) {
        spawnShapeParticles(&particles, shape->pos, player->velocity, type);
    }

    createDisplayScore(type);
    shapes.push_back(new ScoreText(shape->pos, displayScore));

    // Rewards for destroying a safe shape.
    player->velocity.y = -1000.0;
    player->velocity.x = player->velocity.x * 0.5f;

    shouldScreenShake = true;

    scoreTimer = scoreTimerUpgrade;
    inputTimeLeft = std::min(inputTimeLeft + 0.5f, 1.0f);

    if (scoreMultiplier < scoreMultiplierMax) {
        scoreMultiplier++;
    }
}
