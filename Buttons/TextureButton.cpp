//
// Created by eclipsedmango on 2/01/25.
//

#include "TextureButton.h"
#include "../Util.h"

TextureButton::TextureButton(const Vector2 buttonPos, const Vector2 buttonSize, const Texture2D &textureOriginal,
        const Texture2D &textureHover,
        const Texture2D &texturePress,
        const bool toggle) {

    this->pos = buttonPos;
    this->size = buttonSize;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    this->texture = textureOriginal;
    this->textureOriginal = textureOriginal;
    this->textureHover = textureHover;
    this->texturePress = texturePress;
    this->scale = scale;
    this->toggle = toggle;
}

bool TextureButton::checkButtonRegion() {
    Vector2 centeredPos = getScreenPos();

    if (toggle) {
        if (GetMouseX() < centeredPos.x + size.x / 2.0 && GetMouseX() > centeredPos.x - size.x / 2.0 && GetMouseY() < centeredPos.y + size.y / 2.0 && GetMouseY() > centeredPos.y - size.y / 2.0) {
            if (!toggled) {
                texture = textureHover;
                scale = 1.05;
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                toggled = !toggled;

                if (toggled) {
                    texture = texturePress;
                    scale = 0.98;
                }
            } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                return true;
            }
        } else {
            if (!toggled) {
                texture = textureOriginal;
                scale = 1.0;
            }
            return false;
        }
        return false;
    }

    if (GetMouseX() < centeredPos.x + size.x / 2.0 && GetMouseX() > centeredPos.x - size.x / 2.0 && GetMouseY() < centeredPos.y + size.y / 2.0 && GetMouseY() > centeredPos.y - size.y / 2.0) {
        texture = textureHover;
        scale = 1.05;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            texture = texturePress;
            scale = 0.98;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return true;
        }
    } else {
        texture = textureOriginal;
        scale = 1.0;
        return false;
    }

    return false;
}

void TextureButton::draw() const {
    Vector2 centeredPos = getScreenPos();
    DrawTextureEx(texture, Vector2(centeredPos.x - size.x / 2.0 * scale, centeredPos.y - size.y / 2.0 * scale), 0, scale, WHITE);
}



