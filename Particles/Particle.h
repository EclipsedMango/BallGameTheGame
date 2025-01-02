/*
 * Particle.h
 *
 * A simple class representing a particle in a 2D (or 3D) scene.
 * Demonstrates basic concepts: position, velocity, drawing, and physics updates.
 *
 * Created by eclipsedmango on 23/11/24.
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdint>  // For fixed-width integer types if needed
#include <iostream> // For debugging logs (optional)

class Particle {
public:
    /**
     * Default constructor for Particle.
     * Initializes position and velocity to zero,
     * plus any other default initialization as needed.
     */
    Particle();

    /**
     * Destructor for Particle.
     * Perform cleanup if any resources are dynamically allocated.
     */
    ~Particle();

    /**
     * Draw the particle on-screen or to the current rendering context.
     * Implementation is minimal here, but typically you would invoke
     * some rendering API calls (e.g., OpenGL, SFML, etc.).
     */
    void draw() const;

    /**
     * Update the particle's velocity, position, or other physics-based
     * properties on each frame. This is the place to apply any forces,
     * damping, or collision detection as needed.
     */
    void physicsUpdate();

    // -- Getters and Setters (Optional) --

    /**
     * Set the position of the particle.
     * @param x The new x-coordinate.
     * @param y The new y-coordinate.
     */
    void setPosition(float x, float y);

    /**
     * Set the velocity of the particle.
     * @param vx The new x-component of velocity.
     * @param vy The new y-component of velocity.
     */
    void setVelocity(float vx, float vy);

    /**
     * Retrieve the current position of the particle.
     * @param x [out] Will be filled with the current x-coordinate.
     * @param y [out] Will be filled with the current y-coordinate.
     */
    void getPosition(float& x, float& y) const;

    /**
     * Retrieve the current velocity of the particle.
     * @param vx [out] Will be filled with the current x-component of velocity.
     * @param vy [out] Will be filled with the current y-component of velocity.
     */
    void getVelocity(float& vx, float& vy) const;

private:
    float posX, posY;   ///< Particle's current position on the X and Y axes.
    float velX, velY;   ///< Particle's velocity on the X and Y axes.

    // Optionally, you could store other properties (e.g., color, size, mass).
};

#endif // PARTICLE_H
