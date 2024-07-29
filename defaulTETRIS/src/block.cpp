#include "block.h"

Block::Block()
{
    cellSize = 50;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int x, int y)
{
    std::vector<Position> tiles = GetCellPosition();
    for(Position item: tiles)
    {
        Rectangle cord;

        cord.x = (item.column * cellSize + x) + 585;
        cord.y = (item.row * cellSize + y) + 40;
        cord.height = cellSize;
        cord.width = cellSize;

        DrawRectangleRounded(cord, 0.3, 100, colors[id]);
        DrawRectangleRoundedLines(cord, 0.3, 100, 0.1, colors[8]);
    }
}

void Block::DrawSmall(int x, int y)
{
    std::vector<Position> tiles = GetCellPosition();
    for(Position item: tiles)
    {
        Rectangle cord;

        cord.x = (item.column * 35 + x);
        cord.y = (item.row * 35 + y);
        cord.height = 35;
        cord.width = 35;

        DrawRectangleRounded(cord, 0.3, 100, colors[id]);
        DrawRectangleRoundedLines(cord, 0.3, 100, 0.1, colors[8]);
    }
}

void Block::Rotate()
{
    rotationState ++;

    if(rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::RevRotate()
{
    rotationState --;
    if(rotationState < 0)
    {
        rotationState = cells.size() - 1;
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPosition()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for(Position item: tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}