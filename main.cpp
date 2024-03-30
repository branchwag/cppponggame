#include <iostream>
#include <raylib.h>

using namespace std;

int main () {

    const int screenWidth = 1280;
    const int screenHeight = 800;
    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 15;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if(ball_x + ball_radius >= screenWidth  || ball_x - ball_radius <= 0)
        {
            ball_speed_x *= -1;
        }

        if(ball_y + ball_radius >= screenHeight  || ball_y - ball_radius <= 0)
        {
            ball_speed_y *= -1;
        }

        DrawCircle(ball_x,ball_y,ball_radius, WHITE);
        DrawRectangle(0, 0, 25, 120, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}