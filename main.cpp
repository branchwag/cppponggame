#include <iostream>
#include <raylib.h>

using namespace std;


class Ball{
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;
    
    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Update(){
        x += speed_x;
        y += speed_y;

        if(x + radius >= GetScreenWidth() || x - radius <= 0)
        {
            speed_x *= -1;
        }

        if(y + radius >= GetScreenHeight()  || y - radius <= 0)
        {
            speed_y *= -1;
        }
    }

};

Ball ball;

int main () {

    const int screenWidth = 1280;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);
    
    ball.radius = 20;
    ball.x = screenWidth/2;
    ball.y = screenHeight/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);

        ball.Update();

        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        DrawRectangle(10, screenHeight/2 - 120/2, 25, 120, WHITE);
        DrawRectangle(screenWidth - 35, screenHeight /2 - 60, 25, 120, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}