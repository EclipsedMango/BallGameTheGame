//
// Created by eclipsedmango on 2/01/25.
//

#include "TextureButton.h"
#include "../Util.h"

TextureButton::TextureButton(const Vector2 buttonPos, const Vector2 buttonSize, const Texture2D &textureOriginal,
        const Texture2D &textureHover,
        const Texture2D &texturePress) {

    this->pos = buttonPos;
    this->size = buttonSize;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
    this->texture = textureOriginal;
    this->textureOriginal = textureOriginal;
    this->textureHover = textureHover;
    this->texturePress = texturePress;
}

bool TextureButton::checkButtonRegion() {
    Vector2 centeredPos = getScreenPos();

    if (GetMouseX() < centeredPos.x + size.x / 2.0 && GetMouseX() > centeredPos.x - size.x / 2.0 && GetMouseY() < centeredPos.y + size.y / 2.0 && GetMouseY() > centeredPos.y - size.y / 2.0) {
        texture = textureHover;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            texture = texturePress;
        } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            return true;
        }
    } else {
        texture = textureOriginal;
        return false;
    }

    return false;
}

void TextureButton::draw() const {
    Vector2 centeredPos = getScreenPos();
    DrawTextureEx(texture, Vector2(centeredPos.x - size.x / 2.0, centeredPos.y - size.y / 2.0), 0, 1, WHITE);
}



