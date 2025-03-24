//
// Created by eclipsedmango on 2/01/25.
//

#ifndef TEXTUREBUTTON_H
#define TEXTUREBUTTON_H
#include "Button.h"


class TextureButton final : public Button {
public:
    TextureButton(Vector2 buttonPos, Vector2 buttonSize, const Texture2D &textureOriginal,
                  const Texture2D &textureHover,
                  const Texture2D &texturePress,
                  bool toggle);

    void draw() const override;
    bool checkButtonRegion() override;

    Texture2D texture{};
    Texture2D textureOriginal{};
    Texture2D textureHover{};
    Texture2D texturePress{};
    bool toggle = false;
    bool toggled = false;
    bool updateValue = false;
};



#endif //TEXTUREBUTTON_H
