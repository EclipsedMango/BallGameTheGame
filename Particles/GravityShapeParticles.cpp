
#include "GravityShapeParticles.h"
#include "raymath.h"
#include "../Util.h"

GravityShapeParticles::GravityShapeParticles(const Vector2 shapePos, const float size, const Color color) {
    Vector2 randomPoint;
    while (true) {
        float x = GetRandomValue(-rad, rad);
        float y = GetRandomValue(-rad, rad);

        if (x * x + y * y < rad * rad) {
            randomPoint = Vector2(x, y);
            break;
        }
    }

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
    size -= physicsDelta * 8.0;
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
