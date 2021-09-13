#include "raylib.h"
#include "math.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "sr_resolve.h"

#define rand_range(a, b) (rand() % (b + 1 - a) + a)

#define WIDTH 30
#define HEIGHT 30

int main() {
    srand(time(0));
    InitWindow(800, 500, "sr_resolve_example");

    Rectangle static_recs[20] = { 0 };

    Rectangle player = {
        .x = 800/2,
        .y = 500/2,
        .width = WIDTH,
        .height = HEIGHT
    };

    int speed = 500;
    Vector2 dir = { 0.0f, 0.0f };

    for (int i = 0; i < 20; i++) {
        static_recs[i] = (Rectangle){
            .x = rand_range(0, 800),
            .y = rand_range(0, 500),
            .width = WIDTH,
            .height = HEIGHT
        };
    }

    while (!WindowShouldClose()) {
        dir.x = 0; dir.y = 0;
        // Get the keyboard input
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
            dir.y = -1;
        }
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
            dir.y = 1;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            dir.x = 1;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            dir.x = -1;
        }

        // Move the player
        player.x += dir.x * speed * GetFrameTime();
        player.y += dir.y * speed * GetFrameTime();

        // Check for collision
        for (int i = 0; i < 20; i++) {
            sr_rec static_rec = (sr_rec){
                .x = static_recs[i].x,
                .y = static_recs[i].y,
                .width = static_recs[i].width,
                .height = static_recs[i].height
            };

            sr_rec player_rec = (sr_rec){
                .x = player.x,
                .y = player.y,
                .width = player.width,
                .height = player.height
            };

            player_rec = sr_resolver_rects_collision(static_rec, player_rec);

            player = (Rectangle){
                .x = player_rec.x,
                .y = player_rec.y,
                .width = player_rec.width,
                .height = player_rec.height
            };
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 20; i++) {
                DrawRectangleRec(static_recs[i], RED);
            }

            DrawRectangleRec(player, GREEN);

        EndDrawing();
    }

    CloseWindow();
}
