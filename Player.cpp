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
    const Vector3 shaderPlayerColor = Vector3(
        static_cast<float>(playerColor.r) / 255.0f,
        static_cast<float>(playerColor.g) / 255.0f,
        static_cast<float>(playerColor.b) / 255.0f
    );

    const Vector3 shaderPlayerOutlineColor = Vector3(
        static_cast<float>(playerColorOutline.r) / 255.0f,
        static_cast<float>(playerColorOutline.g) / 255.0f,
        static_cast<float>(playerColorOutline.b) / 255.0f
    );

    SetShaderValue(shader, 1, &velocity, SHADER_UNIFORM_VEC2);
    SetShaderValue(shader, 2, &shaderPlayerColor, SHADER_UNIFORM_VEC3);
    SetShaderValue(shader, 3, &shaderPlayerOutlineColor, SHADER_UNIFORM_VEC3);

    if (!hasDied) {
        // DrawCircle(playerPos.x, playerPos.y, 20, playerColorOutline);
        // DrawCircle(playerPos.x, playerPos.y, 16, playerColor);

        BeginShaderMode(shader);
        DrawRectangleV(Vector2SubtractValue(playerPos, displayRadius / 2), Vector2(displayRadius, displayRadius), playerColor);
        //DrawRectangle(playerPos.x - 960, playerPos.y - 540, 1920, 1080, WHITE);
        EndShaderMode();
    }
}
