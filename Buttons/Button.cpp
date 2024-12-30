//
// Created by eclipsedmango on 29/12/24.
//

#include "Button.h"

#include "../Util.h"

Button::Button(const Vector2 buttonPos, const Vector2 buttonSize, const int fontSize, const Color color, const Color fontColor, const std::string& buttonLabel) {
    this->pos = buttonPos;
    this->size = buttonSize;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    this->color = color;
    this->label = buttonLabel;
    this->colorOriginal = color;
    this->colorHover = Color(colorClamp(color.r * 1.25), colorClamp(color.g * 1.25), colorClamp(color.b * 1.25), color.a);
    this->colorPress = Color(colorClamp(color.r * 0.75), colorClamp(color.g * 0.75), colorClamp(color.b * 0.75), color.a);
}

bool Button::checkButtonRegion() {
    if (GetMouseX() < pos.x + size.x / 2.0 && GetMouseX() > pos.x - size.x / 2.0 && GetMouseY() < pos.y + size.y / 2.0 && GetMouseY() > pos.y - size.y / 2.0) {
        color = colorHover;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            color = colorPress;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return true;
        }
    } else {
        color = colorOriginal;
        return false;
    }

    return false;
}

void Button::draw() const {
    DrawRectangle(pos.x - size.x / 2.0, pos.y - size.y / 2.0, size.x, size.y, color);
    drawTextCentered(label.c_str(), pos.x, pos.y - size.y / 2.0 + 2.0, fontSize, fontColor);
}


