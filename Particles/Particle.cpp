/*
 * Particle.cpp
 *
 * Implementation of the Particle class. Demonstrates
 * a minimal approach to a simple physics update and rendering.
 *
 * Created by eclipsedmango on 23/11/24.
 */

#include "Particle.h"

//------------------------------------------------------------------------------
// Constructor & Destructor
//------------------------------------------------------------------------------
Particle::Particle()
    : posX(0.0f), posY(0.0f),  // Initialize position to (0,0)
      velX(0.0f), velY(0.0f)   // Initialize velocity to (0,0)
{
    // Optional: print for debugging
    // std::cout << "Particle created at (0, 0) with velocity (0, 0)\n";
}

Particle::~Particle() {
    // No dynamically allocated resources to release in this example.
    // std::cout << "Particle destroyed\n";
}

//------------------------------------------------------------------------------
// Rendering
//------------------------------------------------------------------------------
void Particle::draw() const {
    // Here you would typically call into a rendering library/engine
    // Example (pseudo-code):
    //
    //   drawCircle(posX, posY, radius, color);
    //
    // For demonstration, we'll just log to standard output (if desired):
    // std::cout << "Drawing particle at (" << posX << ", " << posY << ")\n";
}

//------------------------------------------------------------------------------
// Physics Update
//------------------------------------------------------------------------------
void Particle::physicsUpdate() {
    // A simple Euler integration approach for demonstration:
    posX += velX;
    posY += velY;

    // If you need to apply damping or gravity, you can do it here:
    //   velY += gravityValue;
    //   velX *= dampingFactor;
    //   velY *= dampingFactor;
}

//------------------------------------------------------------------------------
// Getters and Setters
//------------------------------------------------------------------------------
void Particle::setPosition(float x, float y) {
    posX = x;
    posY = y;
}

void Particle::setVelocity(float vx, float vy) {
    velX = vx;
    velY = vy;
}

void Particle::getPosition(float& x, float& y) const {
    x = posX;
    y = posY;
}

void Particle::getVelocity(float& vx, float& vy) const {
    vx = velX;
    vy = velY;
}
