//
// Created by eclipsedmango on 12/11/24.
//

#ifndef TIRANGLESHAPE_H
#define TIRANGLESHAPE_H
#include "Shape.h"


class PentagonShape final : public Shape {
public:
    explicit PentagonShape(Vector2 randomPos);
    void draw() const override;
    void physicsUpdate() override;
    PentagonShape() = default;
};



#endif //TIRANGLESHAPE_H
