//
// Created by eclipsedmango on 29/12/24.
//

#include "Button.h"

#include "raymath.h"
#include "../Util.h"

Button::Button() = default;
bool Button::checkButtonRegion() { return false; }
void Button::draw() const {}
Vector2 Button::getScreenPos() const {
    return Vector2Add(pos, Vector2(windowWidth / 2.0, windowHeight / 2.0));
}



