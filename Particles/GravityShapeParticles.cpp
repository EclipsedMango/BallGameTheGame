
#include "GravityShapeParticles.h"

GravityShapeParticles::GravityShapeParticles(const Vector2 shapePos, const float size, const Color color) {
    Vector2 randomPoint;
    while (true) {
        float x = GetRandomValue(-radius, radius);
        float y = GetRandomValue(-radius, radius);

        if (x * x + y * y < radius * radius) {
            randomPoint = Vector2(x, y);
            break;
        }
    }

    // this->pos = Vector2(GetRandomValue(shapePos.x - radius - 50, shapePos.x + radius + 50),
    //                     GetRandomValue(shapePos.y - radius - 50, shapePos.y + radius + 50));
    this->pos = Vector2Add(randomPoint, shapePos);
    this->size = size;
    this->lifespan = 20;
    this->colorAlpha = 255;
    this->color = color;
    this->velocity = Vector2Subtract(pos, shapePos);
}

void GravityShapeParticles::draw() const {
    if (lifespan > 0) {
        DrawCircleV(pos, size, Color(color.r, color.g, color.b, colorAlpha));
    }
}

void GravityShapeParticles::physicsUpdate() {
    size -= physicsDelta * 10.0;
    pos.x += -velocity.x * 0.4f * physicsDelta * GetRandomValue(1, 10);
    pos.y += -velocity.y * 0.4f * physicsDelta * GetRandomValue(1, 10);

    if (lifespan > 0) {
        lifespan -= physicsDelta * 10;
        destoryParticle = false;
    } else {
        destoryParticle = true;
    }

    if (colorAlpha > 0) {
        colorAlpha -= physicsDelta * 800;
    }
}
