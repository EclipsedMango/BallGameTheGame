cmake_minimum_required(VERSION 3.29)
project(BallGameTheGame)

set(CMAKE_CXX_STANDARD 20)

set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

add_executable(BallGameTheGame Main.cpp
        Shapes/Shape.cpp
        Shapes/Shape.h
        Game/Game.cpp
        Game/Game.h
        Util.cpp
        Util.h
        Shapes/CircleShape.cpp
        Shapes/CircleShape.h
        Shapes/TriangleShape.cpp
        Shapes/TriangleShape.h
        Shapes/GoldCircleShape.cpp
        Shapes/GoldCircleShape.h
        Shapes/ScoreText.cpp
        Shapes/ScoreText.h
        Menus/MainMenu.cpp
        Menus/MainMenu.h
        Particles/Particle.cpp
        Particles/Particle.h
        Particles/PlayerDeathParticle.cpp
        Particles/PlayerDeathParticle.h
        Particles/ShapeParticles.cpp
        Particles/ShapeParticles.h
        Particles/PlayerMovementParticles.cpp
        Particles/PlayerMovementParticles.h
        Buttons/Button.cpp
        Buttons/Button.h
        Buttons/TextureButton.cpp
        Buttons/TextureButton.h
        Buttons/RegularButton.cpp
        Buttons/RegularButton.h
        Menus/UpgradeMenu.cpp
        Menus/UpgradeMenu.h)

target_link_libraries(BallGameTheGame raylib)
