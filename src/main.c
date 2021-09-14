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

Rectangle from_sr_rec(sr_rec rec) {
    return (Rectangle){
        .x = rec.x,
        .y = rec.y,
        .width = rec.width,
        .height = rec.height
    };
}

int main() {
    srand(time(0));
    InitWindow(800, 500, "sr_resolve_example");

    sr_rec static_recs[10] = { 0 };

    sr_rec static_recs2[10] = { 0 };

    sr_rec static_recs_final[20] = { 0 };

    sr_rec player = {
        .x = 800/2,
        .y = 500/2,
        .width = WIDTH,
        .height = HEIGHT
    };

    int speed = 500;
    Vector2 dir = { 0.0f, 0.0f };

    for (int i = 0; i < 10; i++) {
        static_recs[i] = (sr_rec){
            .x = (i + 5) * WIDTH,
            .y = 300,
            .width = WIDTH,
            .height = HEIGHT
        };
    }

    for (int i = 0; i < 10; i++) {
        static_recs2[i] = (sr_rec){
            .x = 300,
            .y =  (i + 5) * HEIGHT,
            .width = WIDTH,
            .height = HEIGHT
        };
    }

    for (int i = 0; i < 10; i++) {
        static_recs_final[i] = static_recs[i];
    }

    for (int i = 10; i < 20; i++) {
        static_recs_final[i] = static_recs2[i-10];
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

        // Move the player and collide
        player = sr_move_and_collide(static_recs_final, 20, player, (sr_vec2){
			.x = dir.x * speed * GetFrameTime(),
        	.y = dir.y * speed * GetFrameTime(),
		});

        
        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (int i = 0; i < 20; i++) {
                DrawRectangleRec(from_sr_rec(static_recs_final[i]), RED);
                DrawRectangleLinesEx(from_sr_rec(static_recs_final[i]), 1, BLACK);
            }

            DrawRectangleRec(from_sr_rec(player), GREEN);

        EndDrawing();
    }

    CloseWindow();
}
