//
// Created by eclipsedmango on 2/01/25.
//

#include "RegularButton.h"

#include "raymath.h"
#include "../Util.h"

RegularButton::RegularButton(const Vector2 buttonPos, const Vector2 buttonSize, const int fontSize, const Color color, const Color fontColor, const std::string& buttonLabel) {
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

bool RegularButton::checkButtonRegion() {
    Vector2 centeredPos = getScreenPos();

    if (GetMouseX() < centeredPos.x + size.x / 2.0 && GetMouseX() > centeredPos.x - size.x / 2.0 && GetMouseY() < centeredPos.y + size.y / 2.0 && GetMouseY() > centeredPos.y - size.y / 2.0) {
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

void RegularButton::draw() const {
    Vector2 centeredPos = getScreenPos();
    DrawRectangle(centeredPos.x - size.x / 2.0, centeredPos.y - size.y / 2.0, size.x, size.y, color);
    drawTextCentered(label.c_str(), centeredPos.x, centeredPos.y - size.y / 2.0 + 2.0, fontSize, fontColor);
}

