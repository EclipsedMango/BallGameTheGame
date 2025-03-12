//
// Created by eclipsedmango on 2/01/25.
//

#ifndef REGULARBUTTON_H
#define REGULARBUTTON_H
#include "Button.h"


class RegularButton final : public Button {
public:
    explicit RegularButton(Vector2 buttonPos, Vector2 buttonSize, int fontSize, Color color,
        Color fontColor,
        const std::string& buttonLabel,
        bool toggle);

    bool checkButtonRegion() override;
    void draw() const override;

    bool toggle = false;
    bool toggled = false;
};



#endif //REGULARBUTTON_H
