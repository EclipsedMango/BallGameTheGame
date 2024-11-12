//
// Created by eclipsedmango on 11/11/24.
//

#ifndef CIRCLESHAPE_H
#define CIRCLESHAPE_H
#include "Shape.h"

class CircleShape : public Shape {
public:
    explicit CircleShape(Vector2 randomPos);
    void draw() const override;
    CircleShape() = default;
};



#endif //CIRCLESHAPE_H
