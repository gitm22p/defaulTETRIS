#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
    Block();
    int id;
    void Draw(int x, int y);
    void DrawSmall(int x, int y);
    void Rotate();
    void RevRotate();
    void Move(int rows, int columns);
    std::vector<Position> GetCellPosition();

protected:
    std::map<int, std::vector<Position>> cells;
    
private:
    int cellSize;
    int rotationState;
    int rowOffset;
    int columnOffset;
    std::vector<Color> colors;
};