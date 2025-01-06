//
// Created by eclipsedmango on 29/12/24.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "raylib.h"


class Button {
public:
    virtual ~Button() = default;

    Vector2 pos = {};
    Vector2 size = {};
    std::string label;
    int fontSize = 16;
    float scale = 1.0;
    Color fontColor = Color(0, 0, 0, 255);
    Color color = Color(0, 0, 0, 255);
    Color colorOriginal = Color(0, 0, 0, 255);
    Color colorHover = Color(0, 0, 0, 255);
    Color colorPress = Color(0, 0, 0, 255);

    virtual bool checkButtonRegion();
    virtual void draw() const;
    virtual Vector2 getScreenPos() const;
    Button();
};



#endif //BUTTON_H
