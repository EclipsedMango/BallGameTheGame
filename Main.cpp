#include "raylib.h"
#include "Util.h"

void runGame();

int main() {
    // Initialization
    const int monitor = GetCurrentMonitor();

    InitWindow(windowWidth, windowHeight, "Ball Game The Game");
    SetWindowMonitor(monitor);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    runGame();

    CloseWindow();        // Close window and OpenGL context
    return 0;
}
