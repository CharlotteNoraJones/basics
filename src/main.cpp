#include <stdio.h>

#include "raylib.h"
#include "raymath.h"
#include "flecs.h"

struct Position {
    float x;
    float  y;
};

struct CircleBody {
    int radius;
    Color color;
};

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Basics");

    flecs::world world;

    auto player = world.entity();

    player.set<Position>({ .x{200}, .y{100} });
    player.set<CircleBody>({ .radius{50}, .color{BLUE} });

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        world.each([](Position& p) {
            if (IsKeyDown(KEY_LEFT)) { p.x -= 5; }
            if (IsKeyDown(KEY_RIGHT)) { p.x += 5; }
            });

        world.each([](Position& p) {
            p.y = Lerp(p.y, p.y + 50, 5);
            });

        world.each([](const Position& p, const CircleBody& b) {
            DrawCircle(p.x, p.y, b.radius, b.color);
            });

        EndDrawing();

    }
}
