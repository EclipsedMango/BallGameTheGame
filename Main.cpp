#include "raylib.h"
#include "rlgl.h"
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

    Texture2D texture = { rlGetTextureIdDefault(), 1, 1, 1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 };
    SetShapesTexture(texture, (Rectangle){ 0.0f, 0.0f, 1.0f, 1.0f });

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
