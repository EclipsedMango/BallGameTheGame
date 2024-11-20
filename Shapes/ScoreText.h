//
// Created by eclipsedmango on 19/11/24.
//

#ifndef SCORETEXT_H
#define SCORETEXT_H
#include "Shape.h"
#include "../Util.h"

class ScoreText final : public Shape {
public:
    ScoreText(Vector2 pos, float displayScore);
    void draw() const override;
    void physicsUpdate() override;

    float displayScore;
    float colorAlpha = 0;
};

#endif //SCORETEXT_H
