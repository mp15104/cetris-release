#include "defs.h"
#include "Game.h"

double updateTime = ZERO;

bool eventTrigger(double interval){
    double currentTime = GetTime();
    if(currentTime-updateTime >= interval){
        updateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(640, 900, "Cetris+");
    SetTargetFPS(FPS);

    Font font = LoadFontEx("Font/AtariGames.ttf", 64, 0 , 0);

    Game cetris = Game();

    while(WindowShouldClose() == false){
        UpdateMusicStream(cetris.music);
        cetris.inputHandler();
        if(eventTrigger(0.4)){
            cetris.MoveBlockDown();
        }
        BeginDrawing();
        ClearBackground(BACKGROUND_COLOR);
        DrawTextEx(font, "SCORE", {445, 15}, 38, 2, WHITE);
        DrawTextEx(font, "NEXT", {455, 150}, 38, 2, WHITE);
        DrawTextEx(font, "SAVED", {455, 485}, 38, 2, WHITE);
        if(cetris.gameOver){
            DrawTextEx(font, "GAME OVER!", {120, 840}, 30, 2, YELLOW);
        }
        DrawRectangle(435,50,150,50,BLACK);
        DrawTextEx(font, TextFormat("%i", cetris.score), {445, 50}, 38, 2, WHITE);
        DrawRectangleRounded({420,215,200,200},0.3,6,BLACK);
        DrawRectangleRounded({420,550,200,200},0.3,6,BLACK);
        cetris.draw();
        EndDrawing();
    }

    CloseWindow();
}