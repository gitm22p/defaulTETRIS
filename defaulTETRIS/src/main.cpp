#include <raylib.h>
#include <iostream>
#include "game.h"
#include "grid.h"
#include "menu.h"

double lastTime = 0;
double speed = 0.8;

bool TimeTrigger(double interval)
{
    double currentTime = GetTime();
    if(currentTime - lastTime >= interval)
    {
        lastTime = currentTime;
        return true;
    }
    return false;
} 

int main()
{
    Color background = {35, 0, 0, 200};

    InitWindow(1920, 1080, "defaulTETRIS");
    ToggleFullscreen();
    SetExitKey(KEY_F);
    SetTargetFPS(60);
    InitAudioDevice();

    Font font = LoadFontEx("Font\fontik.ttf", 64, 0, 0);
    Game game = Game();
    Menu menu = Menu();

    while(WindowShouldClose() == false)
    {        
        BeginDrawing();
        ClearBackground(background);

        if(menu.gameMode == false)
        {
            menu.MenuKBInput();
            menu.Draw();
            game.Reset();
        }
        else if(menu.gameMode == true)
        {
            game.GameKBInput(menu.gameMode);
            game.Draw();

            if(TimeTrigger(speed))
            {
                game.MoveBlockDown();
            }

            if(game.pause && game.gameOver == 0)
            {
                game.DrawPause();
                PauseMusicStream(game.music);
            }

            if(game.gameOver == true)
            {
                if(game.gameOverCheck == false)
                {
                    PlaySound(game.gameOverSound);
                    StopMusicStream(game.music);
                    game.gameOverCheck = true;
                }
                DrawTextEx(font, "GAME", {1136, 764}, 55, 5, WHITE);
                DrawTextEx(font, "OVER", {1136, 813}, 55, 5, WHITE);
            }
        }
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
}