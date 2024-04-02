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

class Paddle{

    protected: 

    void LimitMovement(){
        
            if(y <= 0) {
            y = 0;
        }
            if(y + height >= GetScreenHeight()){
            y = GetScreenHeight() - height;
        }
        
    }

    public: 
        float x,y;
        float width, height;
        int speed;

    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update() {
        if(IsKeyDown(KEY_UP)){
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y = y + speed;
        }

        LimitMovement();

    }
};

class ComputerPaddle: public Paddle{

    public:

        void Update(int ball_y) {
            if (y + height/2 > ball_y){
                y = y - speed;
            }
            if(y + height/2 <= ball_y){
                y = y + speed;
            }
            LimitMovement();
        }
};

Ball ball;
Paddle player;
ComputerPaddle computerpaddle;

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

    player.width = 25;
    player.height = 120;
    player.x = screenWidth - player.width - 10;
    player.y = screenHeight / 2 - player.height/2;
    player.speed = 6;

    computerpaddle.height = 120;
    computerpaddle.width = 25;
    computerpaddle.x = 10;
    computerpaddle.y = screenHeight/2 - computerpaddle.height/2;
    computerpaddle.speed = 6; 

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);

        ball.Update();
        player.Update();
        computerpaddle.Update(ball.y);

        //checking for collisions
        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec({ball.x, ball.y}, ball.radius, {computerpaddle.x, computerpaddle.y, computerpaddle.width, computerpaddle.height})) {
            ball.speed_x *= -1;
        }

        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        computerpaddle.Draw();
        // DrawRectangle(10, screenHeight/2 - 120/2, 25, 120, WHITE);
        player.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}