//
// Created by eclipsedmango on 12/11/24.
//

#ifndef TIRANGLESHAPE_H
#define TIRANGLESHAPE_H
#include "Shape.h"


class TriangleShape final : public Shape {
public:
    explicit TriangleShape(Vector2 randomPos);
    void draw() const override;
    TriangleShape() = default;
};



#endif //TIRANGLESHAPE_H
