#include <iostream>
#include <raylib.h>

using namespace std;

Color Green = Color{38, 185, 154, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int computer_score = 0;


class Ball{
    public:
        float x, y;
        int speed_x, speed_y;
        int radius;
    
    void Draw(){
        DrawCircle(x, y, radius, Yellow);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        // Computer wins
        if (x + radius >= GetScreenWidth()) {
            computer_score++;
            ResetBall();
        }

        if (x - radius <= 0) {
            player_score++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;

        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
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
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
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
        ClearBackground(Dark_Green);

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

        DrawRectangle(screenWidth / 2, 0, screenWidth / 2, screenHeight, Green);
        DrawCircle(screenWidth / 2, screenHeight / 2, 150, Light_Green);
        DrawLine(screenWidth/2, 0, screenWidth/2, screenHeight, WHITE);
        ball.Draw();
        computerpaddle.Draw();
        // DrawRectangle(10, screenHeight/2 - 120/2, 25, 120, WHITE);
        player.Draw();
        DrawText(TextFormat("%i", computer_score), screenWidth / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screenWidth / 4 - 20, 20, 80, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}