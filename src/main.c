/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <math.h>
#include "raylib.h"
#include "raymath.h"
#include "sr_resolve.h"

sr_vec2 to_sr_vec(Vector2 vec) {
	return (sr_vec2){ vec.x, vec.y };
}

Vector2 to_vec(sr_vec2 vec) {
	return (Vector2){ vec.x, vec.y };
}

sr_rec to_sr_rec(Rectangle rec) {
	return (sr_rec){rec.x, rec.y, rec.width, rec.height};
}


int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    Vector2 mousePos;
    sr_vec2 pos = { 0.0f , 0.0f };
    sr_vec2 hitbox = { 30.0f, 30.0f };
    sr_vec2 vel = { 0.0f, 0.0f };
    sr_ray2 testRay = { { 50.0f, 50.0f}, { 0.0f, 0.0f } };

    int k = 15;

    sr_rec objects[k];
    objects[0] = (sr_rec){ 10.0f, 200.0f, 20.0f, 20.0f };
    objects[1] = (sr_rec){ 30.0f, 200.0f, 20.0f, 20.0f };
    objects[2] = (sr_rec){ 50.0f, 200.0f, 20.0f, 20.0f };
    objects[3] = (sr_rec){ 70.0f, 200.0f, 20.0f, 20.0f };
    objects[4] = (sr_rec){ 90.0f, 200.0f, 20.0f, 20.0f };
    objects[5] = (sr_rec){ 110.0f, 200.0f, 20.0f, 20.0f  };
    objects[6] = (sr_rec){ 130.0f, 200.0f, 20.0f, 20.0f };
    objects[7] = (sr_rec){ 150.0f, 200.0f, 20.0f, 20.0f };
    objects[8] = (sr_rec){ 170.0f, 200.0f, 20.0f, 20.0f };
    objects[9] = (sr_rec){ 190.0f, 200.0f, 20.0f, 20.0f };

    objects[10] = (sr_rec){ 5.0f, 150.0f, 5.0f, 70.0f };
    objects[11] = (sr_rec){ 210.0f, 150.0f, 5.0f, 70.0f };

    objects[12] = (sr_rec){ 100.0f, 20.0f, 30.0f, 100.0f };
    objects[13] = (sr_rec){ 50.0f, 60.0f, 100.0f, 30.0f };

    objects[14] = (sr_rec){ 150.0f, 30.0f, 5.0f, 5.0f };

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        testRay.direction = to_sr_vec(Vector2Subtract(GetMousePosition(), to_vec(pos)));
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_UP)) {
            vel.y = -50.0f;
        }

        if (IsKeyDown(KEY_DOWN)) {
            vel.y = 50.0f;
        }

        if (IsKeyDown(KEY_RIGHT)) {
            vel.x = 50.0f;
        }

        if (IsKeyDown(KEY_LEFT)) {
            vel.x = -50.0f;
        }
        
        mousePos = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            vel = to_sr_vec(Vector2Add((Vector2){vel.x, vel.y}, Vector2Scale(Vector2Normalize(to_vec(testRay.direction)), 100.0f * GetFrameTime())));
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            testRay.position = to_sr_vec(GetMousePosition());
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw hitbox
            DrawRectangleLinesEx((Rectangle){pos.x - hitbox.x/2, pos.y -hitbox.y/2, hitbox.x, hitbox.y}, 2, BLUE);
            
            // Draw Player pos
            DrawCircleV((Vector2){pos.x, pos.y}, 10, BLACK);

            // Draw objects
            for (int i = 0; i < k; i++) {
                DrawRectangle(objects[i].x, objects[i].y, objects[i].width, objects[i].height, RED);
            }

            // Move and slide player
            sr_move_and_slide(objects, k, hitbox, &vel, &pos, GetFrameTime());
            
            pos.x += vel.x * GetFrameTime();
            pos.y += vel.y * GetFrameTime();
            

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}