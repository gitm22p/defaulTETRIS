#pragma once
#include <vector>
#include <raylib.h>

class Grid
{
    
public:
    Grid();
    int grid[20][10];
    void Initialize();
    void Print();
    void Draw();
    int ClearFullRows();
    void DrawGreyBack();
    bool IsCellOutside(int column, int row);
    bool IsCellEmpty(int column, int row);

private:
    void MoveRow(int row, int numRows);
    void ClearRow(int row);
    void AnimationDel(int row);
    bool IsRowFull(int row);
    int rowsCount;
    int columnsCount;
    int cellSize;
    std::vector<Color> colors;
};