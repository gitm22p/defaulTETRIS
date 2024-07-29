#include "colors.h"

const Color darkGrey = {71, 74, 80, 155};
const Color red = {139, 0, 0, 255};
const Color orange = {255, 140, 0, 255};
const Color yellow = {204, 204, 0, 255};
const Color green = {0, 100, 0, 255};
const Color cyan = {0, 135, 145, 255};
const Color blue = {0, 100, 255, 255};
const Color purple = {100, 0, 180, 255};
const Color darkRed = {35, 0, 0, 200};
const Color grey = {222, 222, 222, 20};
const Color menu = {0, 0, 0, 200};

std::vector<Color> GetCellColors()
{
    return {darkGrey, red, orange, yellow, green, cyan, blue, purple, darkRed, grey, menu};
}