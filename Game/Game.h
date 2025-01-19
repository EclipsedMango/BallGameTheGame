//
// Created by eclipsedmango on 10/11/24.
//

#ifndef GAME_H
#define GAME_H
#include <vector>
#include "../Shapes/Shape.h"

class Particle;

void runGame();
bool trySpawnShape(std::vector<Shape*>* shapes, int type);
bool tryDeleteShape(std::vector<Shape*> shapes, const Shape* shape, int index);
void spawnShapeParticles(std::vector<Particle*>* particles, Vector2 shapePos, Vector2 playerVel, int type);
void spawnPlayerParticles(std::vector<Particle*>* particles, Vector2 playerPos, Vector2 playerVel, int type);
void createDisplayScore (std::vector<Shape*> shapes, const Shape* shape, int type, int index);

#endif //GAME_H
