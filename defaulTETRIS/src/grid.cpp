#include "grid.h"
#include "colors.h"

#include <iostream>

Grid::Grid()
{
    rowsCount = 20;
    columnsCount = 10;
    cellSize = 50;
    Initialize();
    colors = GetCellColors();
}

void Grid::Initialize()
{
    for(int row{}; row < rowsCount; row++)
    {
        for(int column{}; column < columnsCount; column++)
        {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print()
{
    for(int row{}; row < rowsCount; row++)
    {
        for(int column{}; column < columnsCount; column++)
        {
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;
    }
}

void Grid::Draw()
{
    for(int row{}; row < rowsCount; row++)
    {
        for(int column{}; column < columnsCount; column++)
        {
            int cellValue = grid[row][column];

            Rectangle cord;

            cord.x = (column * cellSize) + 585;
            cord.y = (row * cellSize) + 40;
            cord.height = cellSize;
            cord.width = cellSize;

            DrawRectangleRounded(cord, 0.3, 100, colors[cellValue]);
            DrawRectangleRoundedLines(cord, 0.3, 100, 0.1, colors[8]);
        }
    }
}

void Grid::AnimationDel(int row)
{
    for(int column{0}; column < columnsCount; column++)
    {
        grid[row][column] = 1;
    }
}

int Grid::ClearFullRows()
{
    int completed = 0;
    for(int row{rowsCount - 1}; row >= 0; row--)
    {
        if(IsRowFull(row))
        {
            completed ++;
            AnimationDel(row);
            ClearRow(row);
        }
        else if(completed > 0)
        {
            MoveRow(row, completed);
        }
    }
    return completed;
}

bool Grid::IsCellOutside(int column, int row)
{
    if(column >= 0 && column < columnsCount && row >= 0 && row < rowsCount)
    {
        return false;
    }
    return true;
}

bool Grid::IsCellEmpty(int column, int row)
{
    if(grid[row][column] == 0)
    {
        return true;
    }
    return false;
}

void Grid::DrawGreyBack()
{
    Rectangle cord;
    cord.x = 580;
    cord.y = 35;
    cord.width = 760;
    cord.height = 1010;
    DrawRectangleRounded(cord, 0.03, 100, colors[9]);
}

void Grid::MoveRow(int row, int numRows)
{
    for(int column{0}; column < columnsCount; column++)
    {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}

void Grid::ClearRow(int row)
{
    for(int column{0}; column < columnsCount; column++)
    {
        grid[row][column] = 0;
    }
}

bool Grid::IsRowFull(int row)
{
    for(int column{0}; column < columnsCount; column++)
    {
        if(grid[row][column] == 0)
        {
            return false;
        }
    }
    return true;
}
