#include "raylib.h"
#include "Util.h"
#include "Game/Game.h"
#include "Menus/MainMenu.h"

int main() {
    // Initialization
    const int monitor = GetCurrentMonitor();

    InitWindow(windowWidth, windowHeight, "Ball Game The Game");
    SetWindowMonitor(monitor);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose() && !shouldGameClose) {
        if (inMenu) {
            mainMenu();
        } else {
            runGame();
        }
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}
