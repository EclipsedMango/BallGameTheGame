//
// Created by eclipsedmango on 29/12/24.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "raylib.h"


class Button {
public:
    ~Button() = default;

    Button(Vector2 buttonPos, Vector2 buttonSize, int fontSize, Color color, Color fontColor, const std::string& buttonLabel);

    Vector2 pos = {};
    Vector2 size = {};
    std::string label;
    int fontSize = 16;
    Color fontColor = Color(0, 0, 0, 255);
    Color color;
    Color colorOriginal;
    Color colorHover;
    Color colorPress;

    bool checkButtonRegion();
    void draw() const;
    Vector2 getScreenPos() const;
};



#endif //BUTTON_H
