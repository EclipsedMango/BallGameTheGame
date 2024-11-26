//
// Created by eclipsedmango on 10/11/24.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "../Shapes/Shape.h"

class Particle;

void runGame();
void spawnShape(std::vector<Shape*>*, int type);
void spawnShapeParticles(std::vector<Particle*>* particles, Vector2 shapePos, Vector2 playerVel, int type);
void spawnPlayerParticles(std::vector<Particle*>* particles, Vector2 playerPos, Vector2 playerVel, int type);

#endif //GAME_H
