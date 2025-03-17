#ifndef GRAVITYSHAPE_H
#define GRAVITYSHAPE_H
#include "Shape.h"
#include "../Util.h"

class GravityShape final : public Shape {
public:
    explicit GravityShape(Vector2 randomPos);
    void draw() const override;
    void physicsUpdate() override;
    GravityShape() = default;

    float textureRadius = 34;
};

#endif //GRAVITYSHAPE_H
