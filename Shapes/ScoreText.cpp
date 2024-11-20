//
// Created by eclipsedmango on 19/11/24.
//

#include "ScoreText.h"

ScoreText::ScoreText(const Vector2 pos, float displayScore) {
    this->pos = pos;
    this->radius = -1000;
    this->type = 4;
    this->displayScore = displayScore;
    this->colorAlpha = 255;
}

void ScoreText::draw() const {
    drawTextCentered(TextFormat("%.0f", displayScore), pos.x, pos.y, 32, Color(255, 255, 255, colorAlpha));
}

void ScoreText::physicsUpdate() {
    if (colorAlpha > 0) {
        colorAlpha -= physicsDelta * 255;
    }
}