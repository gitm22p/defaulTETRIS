#include "menu.h"
#include "colors.h"
#include <raylib.h>
#include "game.h"

Menu::Menu()
{
    gameMode = false;
    selectButton = 0;
    buttonMode = false;

    menuMusic = LoadMusicStream("Sounds\1Menu Music.mp3");
    PlayMusicStream(menuMusic);

    font = LoadFontEx("Font\fontik.ttf", 64, 0, 0);
}

Menu::~Menu()
{
    UnloadMusicStream(menuMusic);
}

void Menu::Draw()
{
    UpdateMusicStream(menuMusic);
    DrawLogo();
    DrawAllButtons();
}

void Menu::DrawAllButtons()
{
    switch (selectButton)
    {
    case 0:
        DrawStartButton(0);
        DrawCreditsButton(0);
        DrawExitButton(0);
        break;
    
    case 1:
        DrawStartButton(1);
        DrawCreditsButton(0);
        DrawExitButton(0);
        break;
    
    case 2:
        DrawStartButton(0);
        DrawCreditsButton(1);
        DrawExitButton(0);
        DrawCreditsMenu(buttonMode);
        break;

    case 3:
        DrawStartButton(0);
        DrawCreditsButton(0);
        DrawExitButton(1);
        DrawExitMenu(buttonMode);
        break;

    default:
        break;
    }
}

void Menu::MenuKBInput()
{
    int keyPressed = GetKeyPressed();

    switch (keyPressed)
    {
    case KEY_DOWN:
    {
        buttonMode = 0;
        if(selectButton == 3)
        {
            selectButton = 1;
        }
        else
        {
            selectButton++;
        }
    }
    break;
    
    case KEY_UP:
    {
        buttonMode = 0;
        if(selectButton == 0)
        {
            selectButton = 3;
        }
        else
        {
            if(selectButton == 1)
            {
                selectButton = 3;
            }
            else
            {
                selectButton--;
            }
        }
    }
    break;

    case KEY_ENTER:
    {
        switch(selectButton)
        {
        case 1:
            gameMode = true;
            break;

        case 2:
            buttonMode = 1;
            break;

        case 3:
        {
            if(buttonMode)
            {
                CloseWindow();
                CloseAudioDevice();
            }
            buttonMode = true;
        }
        break;

        default:
            break;
        }
    }
    break;

    case KEY_ESCAPE:
    {
        buttonMode = false;           
    }

    default:
        break;
    }
}

void Menu::DrawLogo()
{
    DrawRectangleRounded({277, 113, 1365, 204}, 0.15, 100, darkGrey);
    DrawRectangleRoundedLines({277, 113, 1365, 204}, 0.15, 100, 10, BLACK);
    DrawTextEx(font, "defaulTETRIS", {307, 143}, 160, 30, WHITE);
}

void Menu::DrawExitButton(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangleRounded({800, 753, buttonWidthActive, buttonHeightActive}, 0.4, 100, WHITE);
        DrawRectangleRoundedLines({800, 753, buttonWidthActive, buttonHeightActive}, 0.4, 100, 7, BLACK);
        DrawTextEx(font, "EXIT", {855, 795}, 30, 5, BLACK);
    }
    else
    {
        DrawRectangleRounded({810, 773, buttonWidthInactive, buttonHeightInactive}, 0.4, 100, darkGrey);
        DrawRectangleRoundedLines({810, 773, buttonWidthInactive, buttonHeightInactive}, 0.4, 100, 5, BLACK);
        DrawTextEx(font, "EXIT", {855, 795}, 30, 5, WHITE);
    }

}

void Menu::DrawCreditsButton(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangleRounded({800, 623, buttonWidthActive, buttonHeightActive}, 0.4, 100, WHITE);
        DrawRectangleRoundedLines({800, 623, buttonWidthActive, buttonHeightActive},  0.4, 100, 7, BLACK);
        DrawTextEx(font, "CREDITS", {855, 665}, 30, 5, BLACK);
    }
    else
    {
        DrawRectangleRounded({810, 643, buttonWidthInactive, buttonHeightInactive}, 0.4, 100, darkGrey);
        DrawRectangleRoundedLines({810, 643, buttonWidthInactive, buttonHeightInactive},  0.4, 100, 5, BLACK);
        DrawTextEx(font, "CREDITS", {855, 665}, 30, 5, WHITE);
    }
}

void Menu::DrawStartButton(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangleRounded({800, 493, buttonWidthActive, buttonHeightActive}, 0.4, 100, WHITE);
        DrawRectangleRoundedLines({800, 493, buttonWidthActive, buttonHeightActive},  0.4, 100, 7, BLACK);
        DrawTextEx(font, "START", {855, 535}, 30, 5, BLACK);
    }
    else
    {
        DrawRectangleRounded({810, 513, buttonWidthInactive, buttonHeightInactive}, 0.4, 100, darkGrey);
        DrawRectangleRoundedLines({810, 513, buttonWidthInactive, buttonHeightInactive}, 0.4, 100, 5, BLACK);
        DrawTextEx(font, "START", {855, 535}, 30, 5, WHITE);
    }
}

void Menu::DrawExitMenu(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangle(0, 0, 1920, 1080, menu);
        DrawTextEx(font, "ARE YOU SURE?",{120, 485}, 150, 50, WHITE);
    }
}


void Menu::DrawCreditsMenu(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangle(0, 0, 1920, 1080, menu);
        DrawTextEx(font, "Author: rem22p",{767, 267}, 50, 5, WHITE);
        DrawTextEx(font, "Based on YouTube channel: Programming With Nick",{317, 517}, 50, 5, WHITE);
        DrawTextEx(font, "Library used: raylib",{710, 784}, 50, 5, WHITE);
    }
}
