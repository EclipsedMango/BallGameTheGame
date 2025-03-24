#ifndef COLLISIONCHECK_H
#define COLLISIONCHECK_H

#include "Shapes/Shape.h"
#include "Shapes/ScoreText.h"
#include "Player.h"
#include "Util.h"
#include <vector>

class CollisionCheck {
public:
    void checkCollision(std::vector<Shape*> &shapes, std::vector<Particle*> &particles, Player* player, Vector2 vecDir, int i, Shape* shape);
    void collisionRewards(std::vector<Shape*> &shapes, std::vector<Particle*> &particles, Shape* shape, int index);
};

#endif //COLLISIONCHECK_H
