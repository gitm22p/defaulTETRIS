#include "game.h"
#include "colors.h"
#include <random>
#include <raylib.h>

Game::Game()
{
    grid = Grid();

    music = LoadMusicStream("Sounds/Music.mp3");
    rotateSound = LoadSound("Sounds/Rotate.mp3");
    lockBlockSound = LoadSound("Sounds/Lock Block.mp3");
    clearSound = LoadSound("Sounds/Clear.mp3");
    gameOverSound = LoadSound("Sounds/Game Over.mp3");

    score = 0;
    globalCompleted = 0;
    activeMode = 0;
    selectButton = 1;
    blocks = GetAllBlocks();
    colors = GetCellColors();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    font = LoadFontEx("Font\fontik.ttf", 64, 0, 0);
    gameOver = false;
    gameOverCheck = false;
    PlayMusicStream(music);
}

Game::~Game()
{
    UnloadSound(rotateSound);
    UnloadSound(lockBlockSound);
    UnloadSound(clearSound);
    UnloadSound(gameOverSound);

    UnloadMusicStream(music);
}

Block Game::GetRandomBlock()
{
    if(blocks.empty())
    {
        blocks = GetAllBlocks();
    }

    int randomIndex = rand() % blocks.size();

    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);

    return block;
}

std::vector<Block> Game::GetAllBlocks()
{
    return {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};
}

void Game::Draw()
{
    grid.DrawGreyBack();
    grid.Draw();
    currentBlock.Draw(0, 0);
    DrawMenu();
    UpdateMusicStream(music);
    grid.ClearFullRows();
}

void Game::DrawPause()
{
    DrawRectangle(0, 0, 1920, 1080, darkRed);
    DrawRectangleRounded({432, 302, 1031, 198}, 0.15, 100, darkGrey);
    DrawRectangleRoundedLines({432, 302, 1031, 198}, 0.15, 100, 10, BLACK);
    DrawTextEx(font, "PAUSED", {462, 317}, 200, 50, WHITE);

    DrawAllButtons();
}

void Game::DrawRestartButton(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangleRounded({800, 663, 320, 80}, 0.4, 100, WHITE);
        DrawRectangleRoundedLines({800, 663, 320, 80},  0.4, 100, 7, BLACK);
        DrawTextEx(font, "RESTART", {855, 705}, 30, 5, BLACK);
    }
    else
    {
        DrawRectangleRounded({810, 683, 300, 40}, 0.4, 100, darkGrey);
        DrawRectangleRoundedLines({810, 683, 300, 40}, 0.4, 100, 5, BLACK);
        DrawTextEx(font, "RESTART", {855, 705}, 30, 5, WHITE);
    }
}

void Game::DrawMenuButton(bool activeMode)
{
    if(activeMode)
    {
        DrawRectangleRounded({800, 753, 320, 80}, 0.4, 100, WHITE);
        DrawRectangleRoundedLines({800, 753, 320, 80},  0.4, 100, 7, BLACK);
        DrawTextEx(font, "MENU", {855, 795}, 30, 5, BLACK);
    }
    else
    {
        DrawRectangleRounded({810, 773, 300, 40}, 0.4, 100, darkGrey);
        DrawRectangleRoundedLines({810, 773, 300, 40}, 0.4, 100, 5, BLACK);
        DrawTextEx(font, "MENU", {855, 795}, 30, 5, WHITE);
    }
}

void Game::DrawAllButtons()
{
    switch(selectButton)
    {
        case 1:
        {
            DrawRestartButton(1);
            DrawMenuButton(0);
        }
        break;

        case 2:
        {
            DrawRestartButton(0);
            DrawMenuButton(1);
        }
        break;

        default:
            break;
    }
}

void Game::DrawNextBlock()
{
    switch(nextBlock.id)
    {
    case 3:
        nextBlock.DrawSmall(1035, 471);
        break;

    case 4:
        nextBlock.DrawSmall(1035, 450);
        break;

    default:
        nextBlock.DrawSmall(1055, 450);
        break;
    }
}

void Game::MoveBlockLeft()
{
    if(!gameOver && pause == false)
    {
        currentBlock.Move(-1, 0);
        if(IsBlockOutside() || BlockFits() == false)
        {
        currentBlock.Move(1, 0);    
        }
    }
}

void Game::MoveBlockRight()
{
    if(!gameOver && pause == false)
    {
        currentBlock.Move(1, 0);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);    
        }
    }
}

void Game::MoveBlockDown()
{
    if(!gameOver && pause == false)
    {
        currentBlock.Move(0, 1);
        if(IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
            LockBlock();   
            grid.Print();
        }
    }
}

void Game::GameKBInput(bool& gameMode)
{
    int keyPressed = GetKeyPressed();

    if(pause == false)
    {
        if(IsKeyPressedRepeat(KEY_LEFT))
        {
            MoveBlockLeft();
        }
        if(IsKeyPressedRepeat(KEY_RIGHT))
        {
            MoveBlockRight();
        }
        if(IsKeyPressedRepeat(KEY_DOWN))
        {
            score += 1;
            MoveBlockDown();
        }

        switch (keyPressed)
        {
        case KEY_SPACE:
            if(!pause)
                RotateCurrentBlock();
            break;
    
        case KEY_LEFT:
            MoveBlockLeft();
            break;

        case KEY_RIGHT:
            MoveBlockRight();
            break;

        case KEY_DOWN:
            MoveBlockDown();
            break;

        case KEY_ESCAPE:
            if(gameOver == 0)
            {
                pause = !pause;
                ResumeMusicStream(music);
            }
            break;

        default:
            break;
        }

        if(gameOver == 1 && keyPressed != 0)
        {
            gameOver = false;
            gameOverCheck = false;
            globalCompleted = 0;
            score = 0;
            Reset();
        }
    }
    else
    {
        switch (keyPressed)
        {
        case KEY_DOWN:
        {
            if(selectButton == 2)
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
            if(selectButton == 1)
            {
                selectButton = 2;
            }
            else
            {
                selectButton--;
            }
        }
        break;
        
        case KEY_ENTER:
        {
            switch(selectButton)
            {
                case 1:
                {
                    pause = !pause;
                    Reset();
                }
                break;

                case 2:
                {
                    pause = !pause;
                    gameMode = 0;
                }
                break;
            }
        }
        break;

        case KEY_ESCAPE:
        {
            selectButton = 1;
            pause = !pause;
            ResumeMusicStream(music);
        }
        break;

        default:
            break;
        }
    }
}

void Game::DrawMenu()
{
    char scoreText[10];
    char completedText[10];

    sprintf(scoreText, "%d", score);
    sprintf(completedText, "%i", globalCompleted);

    Vector2 scoreTextSize = MeasureTextEx(font, scoreText, 23, 5);
    Vector2 completedTextSize = MeasureTextEx(font, completedText, 23, 5);

    DrawTextEx(font, "Score:", {1155, 70}, 33, 5, WHITE);
    DrawTextEx(font, "Next Block:", {1110, 346}, 33, 5, WHITE);

    DrawRectangleRounded({1120, 131, 180, 180}, 0.15, 100, darkRed);
    DrawRectangleRounded({1120, 401, 180, 180}, 0.15, 100, darkRed);

    DrawNextBlock();

    DrawTextEx(font, completedText, {1120 + (180 - completedTextSize.x) / 2, 189}, 23, 5, WHITE);
    DrawTextEx(font, scoreText, {1120 + (180 - scoreTextSize.x) / 2, 237}, 23, 5, WHITE);
}

void Game::RotateCurrentBlock()
{
    PlaySound(rotateSound);
    if(!gameOver)
    {
        currentBlock.Rotate();

        if(IsBlockOutside())
        {
            currentBlock.RevRotate();    
        }
    }
}

void Game::LockBlock()
{
    PlaySound(lockBlockSound);
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item:tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if(BlockFits() == false)
    {
        gameOver = true;
    }
    nextBlock = GetRandomBlock();

    int completedCount = grid.ClearFullRows(); 

    if(completedCount != 0)
    {
        PlaySound(clearSound);
    } 

    globalCompleted += completedCount;
    UpdateScore(completedCount);
}

void Game::Reset()
{
    grid.Initialize();
    activeMode = 0;
    pause = 0;
    score =0;
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    StopMusicStream(music);
    PlayMusicStream(music);
}

void Game::UpdateScore(int linesCleared)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    
    case 2:
        score += 250;
        break;

    case 3:
        score += 400;
        break;
        
    case 4:
        score += 500;
        break;

    default:
        break;
    }
}

bool Game::IsBlockOutside()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item:tiles)
    {
        if(grid.IsCellOutside(item.column, item.row))
        {
            return true;
        }
    }
    return false;
}

bool Game::BlockFits()
{
    std::vector<Position> tiles = currentBlock.GetCellPosition();
    for(Position item:tiles)
    {
        if(grid.IsCellEmpty(item.column, item.row) == false)
        {
            return false;
        }
    }
    return true;
}