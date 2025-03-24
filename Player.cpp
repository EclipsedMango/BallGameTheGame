//
// Created by eclipsedmango on 20/03/25.
//

#include "Player.h"
#include "Util.h"

void Player::physicsUpdate() {
    // Update players position every physics frame.
    if (!hasDied) {
        velocity.y += gravity * physicsDelta;
        playerPos = Vector2Add(playerPos, Vector2MultiplyS(velocity, physicsDelta));
    }

    // Floor and Ceiling Collision
    if (playerPos.y > 1000 - hitBox) {
        playerPos.y = 1000 - hitBox;

        // Prevents the value from effecting player while stationary.
        if (velocity.y > 0.1) {
            velocity.y = -velocity.y * 0.75f;
        }

        velocity.x = velocity.x * 0.99f;

        inputTimeLeft = 1.0f;
    } else if (playerPos.y < -1480 - hitBox) {
        playerPos.y = -1480 - hitBox;
        velocity.y = -velocity.y * 0.75f;
    }

    // Wall Collision
    if (playerPos.x > 3000 - hitBox) {
        playerPos.x = 3000 - hitBox;
        velocity.x = -velocity.x * 0.75f;
    } else if (playerPos.x < -3000 + hitBox) {
        playerPos.x = -3000 + hitBox;
        velocity.x = -velocity.x * 0.75f;
    }
}

void Player::draw() const {
    if (!hasDied) {
        DrawCircle(playerPos.x, playerPos.y, 20, playerColorOutline);
        DrawCircle(playerPos.x, playerPos.y, 16, playerColor);
    }
}
