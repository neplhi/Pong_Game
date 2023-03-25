#include <iostream>
#include <raylib.h>

using namespace std;

int main() {

    const int screenWidth = 800;
    const int screenHeight = 450;

    int score1 = 0, score2 = 0;

    InitWindow(screenWidth, screenHeight, "Exp");

    Vector2 ballPosition = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
    Vector2 ballSpeed = {5.0f, 5.0f};
    const int ballRadius = 10;

    Rectangle box1 = {100, screenHeight/2 - 60, 15, 120};
    Rectangle box2 = {700, screenHeight/2 - 60, 15, 120};

    bool pause = false;
    int framesCounter = 0;

    float rotation = 0.0f;
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT))){
            int display = GetCurrentMonitor();

            if (IsWindowFullscreen())
                SetWindowSize(screenWidth,screenHeight);
            else
                SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));

            ToggleFullscreen();
        }

        if(IsKeyPressed(KEY_SPACE))
            pause = !pause;
        //player 2 movement
        if(IsKeyDown(KEY_UP))
            box2.y -= 10.0f;
        if(IsKeyDown(KEY_DOWN))
            box2.y += 10.0f;
        if(IsKeyDown(KEY_RIGHT))
            box2.x += 10.0f;
        if(IsKeyDown(KEY_LEFT))
            box2.x -= 10.0f;
        //player 1 movement
        if(IsKeyDown(KEY_W))
            box1.y -= 10.0f;
        if(IsKeyDown(KEY_S))
            box1.y += 10.0f;
        if(IsKeyDown(KEY_D))
            box1.x += 10.0f;
        if(IsKeyDown(KEY_A))
            box1.x -= 10.0f;

        // make sure the player does not leqave the screen box1
        if((box1.x + box1.width) >= GetScreenWidth())
            box1.x = GetScreenWidth() - box1.width;
        else if (box1.x <= 0)
            box1.x =0;
        if((box1.y + box1.height) >= GetScreenHeight())
            box1.y = GetScreenHeight() - box1.height;
        else if (box1.y <= 0)
            box1.y =0;
        // make sure the player does not leqave the screen box2
        if((box2.x + box2.width) >= GetScreenWidth())
            box2.x = GetScreenWidth() - box2.width;
        else if (box2.x <= 0)
            box2.x =0;
        if((box2.y + box2.height) >= GetScreenHeight())
            box2.y = GetScreenHeight() - box2.height;
        else if (box2.y <= 0)
            box2.y =0;

        // ball bounce
        if (CheckCollisionCircleRec(ballPosition, ballRadius, box1)){
            if(ballSpeed.x < 0)
                ballSpeed.x *= -1.0f;
                ballSpeed.x += 1.0f;
        }
        if (CheckCollisionCircleRec(ballPosition, ballRadius, box2)){
            if(ballSpeed.x > 0)
                ballSpeed.x *= -1.0f;
                ballSpeed.x -= 1.0f;
        }

        // Pause game
        if (!pause){
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;

            if ((ballPosition.x >= (GetScreenWidth() - ballRadius)) || (ballPosition.x <= ballRadius))
                ballSpeed.x *= -1.0f;

            if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius))
                ballSpeed.y *= -1.0f;

            if (ballPosition.x >= GetScreenWidth() - ballRadius){
                score1 += 1;
                ballPosition = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
                ballSpeed = {5.0f, 5.0f};
            }
            if (ballPosition.x <= 0 + ballRadius) {
                score2 += 1;
                ballPosition = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
                ballSpeed = {5.0f, 5.0f};
            }
        }
        else framesCounter++;

        rotation += 0.2f;

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText((TextFormat("Score: %02i", score1)), 20, 20, 20, GRAY);
            DrawText((TextFormat("Score: %02i", score2)), screenWidth - 120, 20, 20,
                     GRAY);

            DrawCircleV(ballPosition, (float) ballRadius, WHITE);
            DrawRectangleLinesEx(box1,2.0f,  WHITE);
            DrawRectangleLinesEx(box2, 2.0f, WHITE);

            DrawLine(GetScreenWidth()/2, GetScreenHeight(),GetScreenWidth()/2,
                     0, WHITE);

            if (pause && ((framesCounter/30)%2)) //the (framesCounter/30)%2) is used to make blinking
                DrawText("Pause", 350, 200, 30, GRAY);

            if (score1 == 10) {
                DrawText("Player 1 Won", 300, 200, 30, GRAY);
                ballSpeed = {0.0f, 0.0f};
            }
            if (score2 == 10) {
                DrawText("Player 2 Won", 300, 200, 30, GRAY);
                ballSpeed = {0.0f, 0.0f};
            }

        DrawFPS(0,0);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
