#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
    Game();
    ~Game();
    Music music;
    Sound gameOverSound;
    bool pause;
    bool gameOver;
    bool gameOverCheck;
    bool activeMode;
    void Reset();
    void Draw();
    void DrawPause();
    void GameKBInput(bool& gameMode);
    void DrawNextBlock();
    void MoveBlockDown();

private:
    Grid grid;
    Font font;
    std::vector<Block> GetAllBlocks();
    std::vector<Block> blocks;
    std::vector<Color> colors;
    Block GetRandomBlock();
    Block currentBlock;
    Block nextBlock;
    void DrawMenu();
    void DrawMenuButton(bool activeMode);
    void DrawAllButtons();
    void DrawRestartButton(bool activeMode);
    void RotateCurrentBlock();
    void LockBlock();
    void MoveBlockLeft();
    void MoveBlockRight();
    void UpdateScore(int linesCleared);
    bool IsBlockOutside();
    bool BlockFits();
    int selectButton;
    int score;
    int globalCompleted;
    Sound rotateSound;
    Sound clearSound;
    Sound lockBlockSound;
};