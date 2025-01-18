//
// Created by eclipsedmango on 12/11/24.
//

#ifndef GOLDCIRCLESHAPE_H
#define GOLDCIRCLESHAPE_H
#include "Shape.h"
#include "../Util.h"


class GoldCircleShape final : public Shape {
public:
    explicit GoldCircleShape(Vector2 randomPos);
    void draw() const override;
    void physicsUpdate() override;
    GoldCircleShape() = default;
};



#endif //GOLDCIRCLESHAPE_H
