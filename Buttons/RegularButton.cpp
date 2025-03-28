//
// Created by eclipsedmango on 2/01/25.
//

#include "RegularButton.h"

#include "../Util.h"

RegularButton::RegularButton(const Vector2 buttonPos, const Vector2 buttonSize, const int fontSize, const Color color,
        const Color fontColor,
        const std::string& buttonLabel,
        const bool toggle) {

    this->pos = buttonPos;
    this->size = buttonSize;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    this->color = color;
    this->label = buttonLabel;
    this->colorOriginal = color;
    this->colorHover = Color(colorClamp(color.r * 1.25), colorClamp(color.g * 1.25), colorClamp(color.b * 1.25), color.a);
    this->colorPress = Color(colorClamp(color.r * 0.75), colorClamp(color.g * 0.75), colorClamp(color.b * 0.75), color.a);
    this->toggle = toggle;
}

bool RegularButton::checkButtonRegion() {
    Vector2 centeredPos = getScreenPos();

    if (toggle) {
        if (GetMouseX() < centeredPos.x + size.x / 2.0 && GetMouseX() > centeredPos.x - size.x / 2.0 && GetMouseY() < centeredPos.y + size.y / 2.0 && GetMouseY() > centeredPos.y - size.y / 2.0) {
            if (!toggled) {
                color = colorHover;
                scale = 1.05;
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                toggled = !toggled;

                if (toggled) {
                    color = colorPress;
                    scale = 0.98;
                }
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                return true;
            }
        } else {
            if (!toggled) {
                color = colorOriginal;
                scale = 1.0;
            }
            return false;
        }
        return false;
    }

    if (GetMouseX() < centeredPos.x + size.x / 2.0 && GetMouseX() > centeredPos.x - size.x / 2.0 && GetMouseY() < centeredPos.y + size.y / 2.0 && GetMouseY() > centeredPos.y - size.y / 2.0) {
        color = colorHover;
        scale = 1.06;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            color = colorPress;
            scale = 0.98;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return true;
        }
    } else {
        scale = 1.0;
        color = colorOriginal;
        return false;
    }

    return false;
}

void RegularButton::draw() const {
    Vector2 centeredPos = getScreenPos();
    DrawRectangle(centeredPos.x - size.x / 2.0 - scale, centeredPos.y - size.y / 2.0 - scale, size.x * scale, size.y * scale, color);
    drawTextCentered(label.c_str(), centeredPos.x, centeredPos.y - size.y / 2.0 + 2.0, fontSize * scale, fontColor);
}

