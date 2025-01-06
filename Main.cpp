#include "raylib.h"
#include "Util.h"
#include "Game/Game.h"
#include "Menus/MainMenu.h"
#include "Menus/UpgradeMenu.h"

int main() {
    // Initialization
    const int monitor = GetCurrentMonitor();
    SetConfigFlags(FLAG_MSAA_4X_HINT);

    InitWindow(windowWidth, windowHeight, "Ball Game The Game");
    SetWindowMonitor(monitor);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose() && !shouldGameClose) {
        if (inMenu) {
            mainMenu();
        } else if (inUpgradeMenu) {
            upgradeMenu();
        } else {
            runGame();
        }
    }

    CloseWindow();        // Close window and OpenGL context
    return 0;
}
